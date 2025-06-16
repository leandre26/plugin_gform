#include <pugg/Kernel.h>
#include <nlohmann/json.hpp>
#include "source.hpp"
#include "common.hpp"

#include <cstdlib>
#include <iostream>
#include <thread>
#include <chrono>
#include <memory>
#include <string>
#include <array>
#include <cstring>
#include <queue>
#include <atomic>


// Classe dérivée du template Source<std::string>

class GSheetSource : public Source<nlohmann::json> {
public:
    GSheetSource() = default;
    virtual ~GSheetSource() = default;

    static std::string server_name() {
        std::cout << "[DEBUG STATIC] GSheetSource::server_name() appelé" << std::endl;
        return "SourceServer";
    }
    static std::string kind_static() { return "source_gsheet"; }
    
    
    static const int version = PLUGIN_PROTOCOL_VERSION;

    std::string kind() override { return kind_static(); }
    
    void set_params(void const *params) override {
        try {
            auto json_params = static_cast<const nlohmann::json *>(params);
            if (json_params) {
                _params = *json_params;
                _agent_id = _params.value("agent_id", "");
                script_path_ = _params.value("script_path", "fetch_gsheet.py");
                if (_params.contains("poll_interval_minutes")) {
                    int interval = _params.value("poll_interval_minutes", 5);
                    if (interval > 0) {
                        _poll_interval = std::chrono::minutes(interval);
                        std::cout << "[DEBUG] Récupération des données toutes les " << interval << " minutes" << std::endl;
                    }
                }
            } else {
                std::cerr << "[ERROR] set_params: cast vers json* invalide" << std::endl;
            }  
        } catch (const std::exception &e) {
            std::cerr << "[ERROR] Exception dans set_params: " << e.what() << std::endl;
        }
    }

    return_type get_output(nlohmann::json &out, std::vector<unsigned char> *blob = nullptr) override {
        std::cout << "[DEBUG] get_output() appelée" << std::endl;
        
        _ready = false;
        std::thread([this]() {
            std::this_thread::sleep_for(_poll_interval);
            _ready = true;
        }).detach();

        if (_data_queue.empty()) {
            std::cout << "[DEBUG] Initialisation des données depuis execScript()" << std::endl;
            std::string raw = execScript();

            try {
                auto parsed = nlohmann::json::parse(raw);
                for (const auto& entry : parsed) {
                    _data_queue.push(entry);
                }
                std::cout << "[DEBUG] Données chargées : " << _data_queue.size() << " éléments" << std::endl;
            } catch (const std::exception& e) {
                std::cerr << "[ERROR] Parsing JSON échoué : " << e.what() << std::endl;
                return return_type::error;
            }
  
            if (_data_queue.empty()) {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                std::cout << "[DEBUG] Aucune donnée à envoyer" << std::endl;
                return return_type::error;
            }
        }

            out = _data_queue.front();
        _data_queue.pop();

        if (!_agent_id.empty()) {
            out["agent_id"] = _agent_id;
        }

        std::cout << "[DEBUG] Envoi de : " << out.dump() << std::endl;

        if (_data_queue.empty()) {
            std::cout << "[DEBUG] Dernière ligne envoyée" << std::endl;
            std::this_thread::sleep_for(_poll_interval);
        }
        
        std::cout << "[DEBUG] Message publié sur le topic : source_gsheet" << std::endl;
        return return_type::success;
    }


    std::string blob_format() {
        return "";
    }

    std::map<std::string, std::string> info() override {
        return {
            {"name", "Google Sheets Source"},
            {"description", "Reads data from a Google Sheet via Python script"},
            {"blob_format", "none"}
        };
   
    }

private:
    std::string script_path_;
    std::chrono::minutes _poll_interval = std::chrono::minutes(5);
    std::atomic<bool> _ready = true;
    std::queue<nlohmann::json> _data_queue;
    
    std::string execScript() {
        std::array<char, 256> buffer;
        std::string result;
        std::string command = "python3 " + script_path_;
        std::cout << "[DEBUG] Command exécutée : " << command << std::endl;

        FILE* pipe = popen(command.c_str(), "r");
        if (!pipe) {
           std::cerr << "[ERROR] popen a échoué" << std::endl;
           return "{}";
        }

        while (fgets(buffer.data(), buffer.size(), pipe)) {
            result.append(buffer.data());
        }

        int rc = pclose(pipe);
        std::cout << "[DEBUG] Script terminé avec code: " << rc << std::endl;
        
        if (result.empty()) return "{}";
        
        if (result.size() > 10 * 1024 * 1024) {
            std::cerr << "[WARN] Output trop volumineux, tronqué" << std::endl;
            result.resize(10 * 1024 * 1024);
        }
        
        
        std::cout << "[DEBUG] Résultat : " << result.substr(0, 200) << std::endl;
        std::cout << "[DEBUG] Taille du résultat : " << result.size() << std::endl;
        return result;
    }
};

#define PLUGIN_NAME "gsheet"
INSTALL_SOURCE_DRIVER(GSheetSource, nlohmann::json)


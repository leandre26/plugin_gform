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

class GSheetSource : public Source<std::string> {
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
            } else {
                std::cerr << "[ERROR] set_params: cast vers json* invalide" << std::endl;
            }
        } catch (const std::exception &e) {
            std::cerr << "[ERROR] Exception dans set_params: " << e.what() << std::endl;
        }
    }

    return_type get_output(std::string &out, std::vector<unsigned char> *blob = nullptr) override {
        std::cout << "[DEBUG] get_output() appelée" << std::endl;

        const std::string local_line = R"({"factice":true,"val":123})";
        out = local_line;

        if (blob != nullptr) {
            blob->clear();
            blob->insert(blob->end(), local_line.begin(), local_line.end());
            std::cout << "[DEBUG] Remplissage du blob avec " << blob->size() << " octets" << std::endl;
        }

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
    
        std::vector<std::string> _buffered_lines;
        size_t _current_index = 0;

        void fill_buffer() {
            std::string raw = execScript();
            try {
                auto json_array = nlohmann::json::parse(raw);
                _buffered_lines.clear();
                for (const auto& entry : json_array) {
                    _buffered_lines.push_back(entry.dump());  // convertit chaque ligne JSON en string
                }
                _current_index = 0;
                std::cout << "[DEBUG] Nombre de lignes chargées : " << _buffered_lines.size() << std::endl;
            } catch (const std::exception& e) {
                std::cerr << "[ERROR] parsing JSON dans fill_buffer : " << e.what() << std::endl;
                
                _buffered_lines.clear();
            }
        }
};

#define PLUGIN_NAME "gsheet"
INSTALL_SOURCE_DRIVER(GSheetSource, std::string)

//class GSheetSourceDriver : public SourceDriver<std::string> {
//public:
//    GSheetSourceDriver() : SourceDriver("source", "gsheet", 1) {
//        std::cout << "[DEBUG] Driver enregistré : gsheet" << std::endl;
//    }
//
//    Source<std::string>* create() override {
//        return new GSheetSource();
//    }
//};
//
//extern "C" void register_pugg_plugin(pugg::Kernel* kernel) {
//    auto* driver = new GSheetSourceDriver();
//   std::cout << "[DEBUG PLUGIN] driver->server_name(): " << driver->server_name() << std::endl;
//
//    bool ok = kernel->add_driver(driver);
//    std::cout << "[DEBUG PLUGIN] add_driver success: " << std::boolalpha << ok << std::endl;
//}

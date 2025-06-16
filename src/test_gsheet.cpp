#pragma message("✅ [COMMON] Version locale de common.hpp utilisée dans le TEST")
#include <iostream>
#include <memory>
#include <string>
#include <pugg/Kernel.h>
#include <source.hpp>
#include <common.hpp>
#include <dlfcn.h>
#include <nlohmann/json.hpp>

typedef void (*RegisterPluginFunc)(pugg::Kernel*);

int main() {
    using namespace std;

    pugg::Kernel kernel;
    
    kernel.add_server("source", 1);
    
    std::string plugin_path = "./source_gsheet.plugin";

    if (!kernel.load_plugin(plugin_path)) {
        cerr << "Erreur : impossible de charger le plugin depuis " << plugin_path << endl;
        return 1;
    }
    cout << "[INFO] Plugin chargé depuis : " << plugin_path << endl;


    auto* driver = kernel.get_driver<SourceDriver<std::string>>("source", "gsheet");
    if (!driver) {
        cerr << "Erreur : plugin 'gsheet' non trouvé dans le kernel" << endl;
        return 2;
    }

    cout << "[INFO] Driver 'gsheet' trouvé, création de la source..." << endl;


    std::unique_ptr<Source<std::string>> source(driver->create());

    nlohmann::json params = {
        {"script_path", "/home/mads/Devel/questionnaire_gform/Plugin/src/fetch_gsheet.py"}
    };
    source->set_params(&params);

    std::string result;
    auto ret = source->get_output(result);
    
    if (ret == return_type::success) {
        cout << "✅ Output : " << result << endl;
    } else {
        cerr << "❌ Erreur lors de la lecture depuis la source. Code: " << static_cast<int>(ret) << endl;
    }

    return 0;
}

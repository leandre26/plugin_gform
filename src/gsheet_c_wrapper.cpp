#include "source_gsheet.cpp"

static std::string output;

extern "C" {

void* gsheet_create() {
    return new GSheetSource();
}

void gsheet_destroy(void* ptr) {
    delete static_cast<GSheetSource*>(ptr);
}

const char* gsheet_get_next_line(void* ptr) {
    GSheetSource* plugin = static_cast<GSheetSource*>(ptr);
    std::string out;
    auto result = plugin->get_output(out);

    if (result == Source<std::string>::return_type::success) {
        output = out;
        return output.c_str();
    } else {
        return nullptr;
    }
}

}

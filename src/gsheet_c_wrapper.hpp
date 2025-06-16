#pragma once

extern "C" {
    void* gsheet_create();
    void gsheet_destroy(void* ptr);
    const char* gsheet_get_next_line(void* ptr);
}

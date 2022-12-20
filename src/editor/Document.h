#pragma once

#include <string>
#include <gfx/lib_gfx.h>
#include <utilities/error.h>
#include <editor/settings.h>

class Document {
private:
    std::string buffer;
public:
    Document(char * file_name) {
        FILE *file;

        ASSERT((file = fopen(file_name, "r")) != nullptr, "File couldn't be opened");

        fseek(file, 0, SEEK_END);
        size_t len = ftell(file);
        ASSERT(len > 0, "File not successfully read");

        buffer = std::string(len+1, 0);

        fseek(file, 0, SEEK_SET);
        fread(&buffer[0], 1, len, file);

        ASSERT(buffer.length() == len + 1, "file wasn't fully read");
        ASSERT(fclose(file) == 0, "Couldn't close file");
    }

    void Render() {
        
        float line = 0;
        float x = START_X, y;

        for(const auto & ch : buffer) {
            if(ch == '\n') {
                line++;
                x = START_X;
                continue;
            }

            y = LINE_HEIGHT * FONT_SIZE * line + START_Y;

            gfx::render_char(ch, x, y, gfx::sFont("consola", FONT_SIZE));
        }

    }
    ~Document() {}
};

#ifndef _SHADER_H
#define _SHADER_H

#include "gfx.h"

#include <iostream>
#include <vector>
#include <string>
#include <string.h>

class Shader {
private:
    enum SHADER_TYPE {
        SHADER,
        PROGRAM
    };

    uint32_t pg;
    uint32_t _compile(std::string path, GLenum type);
    void _report_if_error(uint32_t handle, SHADER_TYPE type);

public:
    Shader(std::string path);
    ~Shader();
    uint32_t getUniform(const char * name) const;
    void bind() const {glUseProgram(pg);}

    template<typename T>
    const Shader & setUniform(const char *name, const T & value) const;
};


#endif // _SHADER_H
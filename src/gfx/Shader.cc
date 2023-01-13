#include "Shader.h"

Shader::Shader(std::string path) {
    uint32_t vs = this->_compile(path+".vs", GL_VERTEX_SHADER);
    uint32_t fs = this->_compile(path+".fs", GL_FRAGMENT_SHADER);

    pg = glCreateProgram();

    GLCall(glAttachShader(pg, vs));
    GLCall(glAttachShader(pg, fs));
    
    GLCall(glLinkProgram(pg));
    _report_if_error(pg, SHADER_TYPE::PROGRAM);
    GLCall(glDeleteShader(vs));
    GLCall(glDeleteShader(fs));
}

Shader::~Shader() {
    GLCall(glDeleteProgram(pg));
}

uint32_t Shader::_compile(std::string path, GLenum type) {
    FILE * file;
    char * text;
    uint32_t len;

    ASSERT(file = fopen(path.c_str(), "rb"), 
                "File not successfully read");
    fseek(file, 0, SEEK_END);

    len = ftell(file);
    ASSERT(len > 0, "File not successfully read");

    fseek(file, 0, SEEK_SET);

    text = new char[len+1];
    ASSERT(text, "Couldn't allocate memory for shader text");

    fread(text, 1, len, file);
    text[len] = '\0';

    ASSERT((strlen(text) == len), "file wasn't fully read");
    ASSERT(fclose(file) == 0, "Couldn't close file");

    uint32_t handle = glCreateShader(type);
    GLCall(glShaderSource(handle, 1, &text, nullptr));
    GLCall(glCompileShader(handle));

    _report_if_error(handle, SHADER_TYPE::SHADER);

    delete [] text;
    return handle;
}

void Shader::_report_if_error(uint32_t handle, SHADER_TYPE type) {
    int success;
    char infoLog[1024];

    if (type == SHADER_TYPE::SHADER) {
        GLCall(glGetShaderiv(handle, GL_COMPILE_STATUS, &success));
        if (!success) {
            GLCall(glGetShaderInfoLog(handle, 1024, NULL, infoLog));
            EXIT_FAILUR("SHADER::Compiling::Failed" << infoLog);
        }
    } else {
        GLCall(glGetProgramiv(handle, GL_LINK_STATUS, &success));
        if (!success) {
            GLCall(glGetProgramInfoLog(handle, 1024, NULL, infoLog));
            EXIT_FAILUR("SHADER::Linking::Failed" << infoLog);
        }
    }

}

uint32_t Shader::getUniform(const char * name) const {
    GLCall(int32_t location = glGetUniformLocation(this->pg, name));
    ASSERT(location != -1, "No active uniform variable with name " << name << " found");
    return location;
}

template<> const Shader& Shader::setUniform<glm::mat4>(const char *name, const glm::mat4 & value) const {
    GLCall(glUniformMatrix4fv(getUniform(name), 1, GL_FALSE, glm::value_ptr(value)));
    return *this;
}

template<> const Shader& Shader::setUniform<glm::vec2>(const char *name, const glm::vec2 & value) const {
    GLCall(glUniform2f(getUniform(name), value.x, value.y));
    return *this;
}

template<> const Shader& Shader::setUniform<glm::vec3>(const char *name, const glm::vec3 & value) const {
    GLCall(glUniform3f(getUniform(name), value.x, value.y, value.z));
    return *this;
}

template<> const Shader& Shader::setUniform<glm::vec4>(const char *name, const glm::vec4 & value) const {
    GLCall(glUniform4f(getUniform(name), value.x, value.y, value.z, value.w));
    return *this;
}

template<> const Shader& Shader::setUniform<float>(const char *name, const float & value) const {
    GLCall(glUniform1f(getUniform(name), value));
    return *this;
}

template<> const Shader& Shader::setUniform<int32_t>(const char *name, const int32_t & value) const {
    GLCall(glUniform1i(getUniform(name), value));
    return *this;
}
template<> const Shader& Shader::setUniform<uint32_t>(const char *name, const uint32_t & value) const {
    GLCall(glUniform1ui(getUniform(name), value));
    return *this;
}

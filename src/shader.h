#ifndef SHADER_H
#define SHADER_H
#include <string>

struct ShaderSource {
    std::string VertexSource;
    std::string FragmentSource;


    ShaderSource(std::string path);
    unsigned int createShader();
};

#endif
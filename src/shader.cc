#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "shader.h"
using namespace std;

static unsigned int compileShader(unsigned int type, const string& source) {
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    // Error handling
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if(!result) {
        int len;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &len);

        char *message = (char*)alloca(len * sizeof(char));
        glGetShaderInfoLog(id, len, &len, message);

        glDeleteShader(id);
        
        throw runtime_error(message);
    }

    return id;
}

unsigned int ShaderSource::createShader() {

    unsigned int program = glCreateProgram();
    unsigned int vShader = compileShader(GL_VERTEX_SHADER, this->VertexSource);
    unsigned int fShader = compileShader(GL_FRAGMENT_SHADER, this->FragmentSource);

    glAttachShader(program, vShader);
    glAttachShader(program, fShader);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vShader);
    glDeleteShader(fShader);

    return program;
}

ShaderSource::ShaderSource(const string path) {
    ifstream inputfile(path);

    enum ShaderType {
        NONE = -1,
        VERTEX = 0,
        FRAGMENT = 1
    };

    stringstream ss[2];
    ShaderType type = ShaderType::NONE;

    string line;
    while(getline(inputfile, line)) {
        if(line.find("#shader") != string::npos) {
            if(line.find("vertex") != string::npos) type = ShaderType::VERTEX;
            else if(line.find("fragment") != string::npos) type = ShaderType::FRAGMENT;
        }

        else ss[type] << line << "\n";
    }

    this->VertexSource = ss[ShaderType::VERTEX].str();
    this->FragmentSource = ss[ShaderType::FRAGMENT].str();
}
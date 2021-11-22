#include "Shader.h"

Shader::Shader() {
    shaderID = 0;
    uniformProjection = 0;
    uniformModel = 0;
}

Shader::~Shader() {
    if (shaderID != 0) {
        glDeleteProgram(shaderID);
    }
    uniformModel = 0;
    uniformProjection = 0;
}

void Shader::CreateFromString(const char* vertexCode, const char* fragmentCode) {
    Compile(vertexCode, fragmentCode);
}

void Shader::CreateFromFile(const char* vertexLocation, const char* fragmentLocation) {
    std::string vertexCode = ReadFile(vertexLocation);
    std::string fragmentCode = ReadFile(fragmentLocation);

    CreateFromString(vertexCode.c_str(), fragmentCode.c_str());
}

void Shader::Compile(const char* vertexCode, const char* fragmentCode) {
    shaderID = glCreateProgram(); //Cria um programa
    if (!shaderID) {
        printf("Erro ao criar o programa");
        return;
    }

    AddShader(GL_VERTEX_SHADER, vertexCode);
    AddShader(GL_FRAGMENT_SHADER, fragmentCode);

    glLinkProgram(shaderID);
    GLint result;
    glGetProgramiv(shaderID, GL_LINK_STATUS, &result);
    if (!result) {
        GLchar log[1024] = { 0 };
        glGetProgramInfoLog(shaderID, sizeof(log), NULL, log);
        printf("Erro linkar o programa (%d): %s", result, log);
    }

    uniformModel = glGetUniformLocation(shaderID, "model");
    uniformProjection = glGetUniformLocation(shaderID, "projection");
    uniformView = glGetUniformLocation(shaderID, "view");
}

void Shader::AddShader(GLenum shaderType, const char* shaderCode) {
    //Vertex
    GLuint shader = glCreateShader(shaderType); //Cria um shader

    //Gambiarra para transformar em array
    const GLchar* code[1];
    code[0] = shaderCode;

    glShaderSource(shader, 1, code, NULL); //Adiciona o código na memória
    glCompileShader(shader); //Compila o código
    GLint result;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
    if (!result) {
        GLchar log[1024] = { 0 };
        glGetShaderInfoLog(shader, sizeof(log), NULL, log);
        printf("Erro ao compilar o shader %c (%d): %s", shaderType, result, log);
    }

    glAttachShader(shaderID, shader); //Liga o shader ao programa
}

std::string Shader::ReadFile(const char* fileLocation) {
    std::string content = "";
    std::ifstream fileStream(fileLocation, std::ios::in);

    if (!fileStream.is_open()) {
        printf("Arquivo não foi encontrado (%s)", fileLocation);
        return "";
    }

    std::string line;
    while (!fileStream.eof()) {
        std::getline(fileStream, line);
        content.append(line + '\n');
    }
    fileStream.close();
    return content;
}

void Shader::UseProgram() {
    glUseProgram(shaderID);
}
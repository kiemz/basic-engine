#pragma once
#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>
class Shader
{
public:
    // ����ID
	unsigned int ID;

    // ��������ȡ��������ɫ��
    Shader(const char* vertexPath, const char* fragmentPath) {
        auto v_source = load_shader(vertexPath);
        auto f_source = load_shader(fragmentPath);
        auto vertexShaderSource = v_source.c_str();
        const char* fragmentShaderSource = f_source.c_str();
        unsigned int vertexShader, fragmentShader;

        vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
        glCompileShader(vertexShader);
        check_error(vertexShader, "VERTEX");

        fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
        glCompileShader(fragmentShader);
        check_error(fragmentShader, "FRAGMENT");

        ID = glCreateProgram();
        glAttachShader(ID, vertexShader);
        glAttachShader(ID, fragmentShader);
        glLinkProgram(ID);
        check_error(ID, "PROGRAM");

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }
    // ʹ��/�������
    void use() {
        glUseProgram(ID);
    }
    // uniform���ߺ���
    void setBool(const std::string& name, bool value) const
    {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
    }
    void setInt(const std::string& name, int value) const
    {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
    }
    void setFloat(const std::string& name, float value) const
    {
        glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
    }
    void setMat4(const std::string& name, glm::mat4 value) const
    {
        glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
    }
    void setVec3(const std::string& name, const glm::vec3& value) const
    {
        glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
    }
    void setVec3(const std::string& name, float x, float y, float z) const
    {
        glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
    }
private:
    auto load_shader(std::string filename) -> std::string {
        std::string str = std::filesystem::current_path().generic_string();
        auto count = str.find("out/build");
        auto path = str.substr(0, count);
        std::ifstream loader(path + "source/shaders/" + filename);
        std::stringstream buffer;
        buffer << loader.rdbuf();
        return buffer.str();
    }
    auto check_error(GLuint shader, std::string type) -> void {
        GLint success;
        GLchar infoLog[512];
        auto error_str = "ERROR::SHADER_COMPILATION_ERROR::";

        if (type == "PROGRAM") {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            error_str = "ERROR::SHADER_LINK_ERROR::";
        }
        else glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

        if (!success)
        {
            glGetShaderInfoLog(shader, 512, NULL, infoLog);
            std::cout << error_str << type << "\n" << infoLog << std::endl;
        }
    }
};
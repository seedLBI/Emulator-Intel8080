#pragma once
#ifndef SHADER_H
#define SHADER_H


#include "Config_Compilier.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

#define GLEW_STATIC
#include <glew.h>
#include <glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class Shader
{
public:
    unsigned int ID;
    // ����������� ���������� ������ "�� ����"

    Shader(const char* vertexCode, const char* fragmentCode) {
        const char* vShaderCode = vertexCode;
        const char* fShaderCode = fragmentCode;

        // 2. ����������� �������
        unsigned int vertex, fragment;

        // ��������� ������ 
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);
        checkCompileErrors(vertex, "VERTEX");

        // ����������� ������
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);
        checkCompileErrors(fragment, "FRAGMENT");

        // ��������� ���������
        ID = glCreateProgram();
        glAttachShader(ID, vertex);
        glAttachShader(ID, fragment);
        glLinkProgram(ID);
        checkCompileErrors(ID, "PROGRAM");

        // ����� ����, ��� �� ������� ������� � ����� ����������, ������� ��, �.�. ��� ������ �� �����
        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }

    Shader(std::string vertexPath, std::string fragmentPath)
    {
        // 1. ��������� ��������� ���� ����������/������������ ������� �� ���������� filePath
        std::string vertexCode;
        std::string fragmentCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;

        // ����������, ��� ������� ifstream ����� ��������� ����������:
        vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try
        {
            // ��������� �����
            vShaderFile.open(vertexPath);
            fShaderFile.open(fragmentPath);
            std::stringstream vShaderStream, fShaderStream;

            // ������ ���������� �������� �������
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();

            // ��������� �����
            vShaderFile.close();
            fShaderFile.close();

            // ������������ � ��������� ���������� ������ �� ������
            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();
        }
        catch (std::ifstream::failure& e)
        {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
        }
        const char* vShaderCode = vertexCode.c_str();
        const char* fShaderCode = fragmentCode.c_str();

        // 2. ����������� �������
        unsigned int vertex, fragment;

        // ��������� ������ 
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);
        checkCompileErrors(vertex, "VERTEX");

        // ����������� ������
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);
        checkCompileErrors(fragment, "FRAGMENT");

        // ��������� ���������
        ID = glCreateProgram();
        glAttachShader(ID, vertex);
        glAttachShader(ID, fragment);
        glLinkProgram(ID);
        checkCompileErrors(ID, "PROGRAM");

        // ����� ����, ��� �� ������� ������� � ����� ����������, ������� ��, �.�. ��� ������ �� �����
        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }

    ~Shader() {
        glDeleteProgram(ID);
    }

    // ��������� �������
    void use()
    {
        glUseProgram(ID);
    }


    // �������� uniform-�������
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
        if (glGetUniformLocation(ID, name.c_str()) <= -1)
        {
            //std::cout << name << " not founded((((" << std::endl;
        }
        glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
    }
    void setFloat(GLuint ID, float value) const
    {
        glUniform1f(ID, value);
    }
    void set2Float(const std::string& name, float value1, float value2) const
    {
        glUniform2f(glGetUniformLocation(ID, name.c_str()),value1, value2);
    }
    void set3Float(const std::string& name, float value1, float value2, float value3) const
    {
        glUniform3f(glGetUniformLocation(ID, name.c_str()), value1, value2,value3);
    }
    void set3Float(const std::string& name, glm::vec3 value) const
    {
        glUniform3f(glGetUniformLocation(ID, name.c_str()), value.x, value.y, value.z);
    }
    void set3Float(GLuint ID, glm::vec3 value) const
    {
        glUniform3f(ID, value.x, value.y, value.z);
    }
    void set4Float(const std::string& name, float v1, float v2, float v3, float v4) {
        glUniform4f(glGetUniformLocation(ID, name.c_str()), v1, v2, v3, v4);
    }
    void set4Float(const std::string& name, glm::vec4 values) {
        //if (glGetUniformLocation(ID, name.c_str()) <= -1)
        //{
        //    std::cout << "not founded " << name << std::endl;
        //}
        {
            //std::cout << "founded " << name << " as " << glGetUniformLocation(ID, name.c_str()) << std::endl;
        }
        glUniform4f(glGetUniformLocation(ID, name.c_str()), values.x, values.y, values.z, values.w);
    }
    void set4FloatWithInfo(const std::string& name, glm::vec4 values) {
#ifdef WITH_DEBUG_OUTPUT
        if (glGetUniformLocation(ID, name.c_str()) <= -1)
        {
            std::cout << "not founded " << name << std::endl;
        }
        {
            std::cout << "founded " << name << " as " << glGetUniformLocation(ID, name.c_str()) << std::endl;
        }
#endif
        glUniform4f(glGetUniformLocation(ID, name.c_str()), values.x, values.y, values.z, values.w);
    }
    void setMat4(const std::string& name, const glm::mat4& mat) const
    {
#ifdef WITH_DEBUG_OUTPUT
        if (glGetUniformLocation(ID, name.c_str()) <= -1)
        {
            std::cout << name << "   not founded\n";
        }
#endif
        glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
    void setMat4(GLuint ID, const glm::mat4& mat) const
    {
        glUniformMatrix4fv(ID, 1, GL_FALSE, &mat[0][0]);
    }


    void BindUniformBlock(const std::string& name, int number_UBO) {
        unsigned int name_index = glGetUniformBlockIndex(ID, name.c_str());
#ifdef WITH_DEBUG_OUTPUT
        std::cout << name << " |in shader have id| " << name_index << std::endl;
#endif
        glUniformBlockBinding(ID, name_index, number_UBO);
    }

private:
    // �������� ������� ��� �������� ������ ����������/���������� ��������
    void checkCompileErrors(unsigned int shader, std::string type)
    {
        int success;
        char infoLog[1024];
        if (type != "PROGRAM")
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
                exit(0);
            }
            else {
#ifdef WITH_DEBUG_OUTPUT
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "SUCCESS::SHADER_COMPILED of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
#endif
            }
        }
        else
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
                exit(0);
            }
            else {
#ifdef WITH_DEBUG_OUTPUT
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "SUCCESS::PROGRAM_LINKED of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
#endif
            }
        }
    }
};




#endif
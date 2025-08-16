#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
#include <sstream>

#ifdef _DEBUG
#include <iostream>
#endif

#include <vector>

#define GLEW_STATIC
#include <GL/glew.h>

#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class Shader
{
public:
    unsigned int ID;
    // Конструктор генерирует шейдер "на лету"

    Shader(const char* vertexCode, const char* fragmentCode) {
        const char* vShaderCode = vertexCode;
        const char* fShaderCode = fragmentCode;

        // 2. Компилируем шейдеры
        unsigned int vertex, fragment;

        // Вершинный шейдер 
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);
        checkCompileErrors(vertex, "VERTEX");

        // Фрагментный шейдер
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);
        checkCompileErrors(fragment, "FRAGMENT");

        // Шейдерная программа
        ID = glCreateProgram();
        glAttachShader(ID, vertex);
        glAttachShader(ID, fragment);
        glLinkProgram(ID);
        checkCompileErrors(ID, "PROGRAM");

        // После того, как мы связали шейдеры с нашей программой, удаляем их, т.к. они больше не нужны
        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }

    Shader(std::string vertexPath, std::string fragmentPath)
    {

#ifdef _DEBUG
        std::cout << "Trying compile shader programm\n\t[" << vertexPath << "]\n\t[" << fragmentPath << "]\n";
#endif // _DEBUG

        
        // 1. Получение исходного кода вершинного/фрагментного шейдера из переменной filePath
        std::string vertexCode;
        std::string fragmentCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;

        // Убеждаемся, что объекты ifstream могут выбросить исключение:
        vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try
        {
            // Открываем файлы
            vShaderFile.open(vertexPath);
            fShaderFile.open(fragmentPath);
            std::stringstream vShaderStream, fShaderStream;

            // Читаем содержимое файловых буферов
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();

            // Закрываем файлы
            vShaderFile.close();
            fShaderFile.close();

            // Конвертируем в строковую переменную данные из потока
            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();
        }
        catch (std::ifstream::failure& e)
        {
#ifdef _DEBUG
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
#endif
        }
        const char* vShaderCode = vertexCode.c_str();
        const char* fShaderCode = fragmentCode.c_str();

        // 2. Компилируем шейдеры
        unsigned int vertex, fragment;

        // Вершинный шейдер 
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);
        checkCompileErrors(vertex, "VERTEX");

        // Фрагментный шейдер
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);
        checkCompileErrors(fragment, "FRAGMENT");

        // Шейдерная программа
        ID = glCreateProgram();
        glAttachShader(ID, vertex);
        glAttachShader(ID, fragment);
        glLinkProgram(ID);
        checkCompileErrors(ID, "PROGRAM");

        // После того, как мы связали шейдеры с нашей программой, удаляем их, т.к. они больше не нужны
        glDeleteShader(vertex);
        glDeleteShader(fragment);

#ifdef _DEBUG
        std::cout << "CORRECT shader\n";
#endif
    }

    // Конструктор, принимающий исходный код для вершинного, геометрического и фрагментного шейдеров
    Shader(const char* vertexCode, const char* geometryCode, const char* fragmentCode)
    {
        const char* vShaderCode = vertexCode;
        const char* gShaderCode = geometryCode;
        const char* fShaderCode = fragmentCode;

        unsigned int vertex, geometry, fragment;

        // Компиляция вершинного шейдера
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);
        checkCompileErrors(vertex, "VERTEX");

        // Компиляция геометрического шейдера
        geometry = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(geometry, 1, &gShaderCode, NULL);
        glCompileShader(geometry);
        checkCompileErrors(geometry, "GEOMETRY");

        // Компиляция фрагментного шейдера
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);
        checkCompileErrors(fragment, "FRAGMENT");

        // Создание шейдерной программы и связывание всех трёх шейдеров
        ID = glCreateProgram();
        glAttachShader(ID, vertex);
        glAttachShader(ID, geometry);
        glAttachShader(ID, fragment);
        glLinkProgram(ID);
        checkCompileErrors(ID, "PROGRAM");

        // После связывания удаляем отдельные шейдеры
        glDeleteShader(vertex);
        glDeleteShader(geometry);
        glDeleteShader(fragment);
    }

    // Конструктор, принимающий пути к файлам для вершинного, геометрического и фрагментного шейдеров
    Shader(std::string vertexPath, std::string geometryPath, std::string fragmentPath)
    {
        std::string vertexCode;
        std::string geometryCode;
        std::string fragmentCode;
        std::ifstream vShaderFile;
        std::ifstream gShaderFile;
        std::ifstream fShaderFile;

        // Настройка исключений для ifstream
        vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        gShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try
        {
            // Открываем файлы
            vShaderFile.open(vertexPath);
            gShaderFile.open(geometryPath);
            fShaderFile.open(fragmentPath);
            std::stringstream vShaderStream, gShaderStream, fShaderStream;

            // Чтение содержимого файлов
            vShaderStream << vShaderFile.rdbuf();
            gShaderStream << gShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();

            // Закрываем файлы
            vShaderFile.close();
            gShaderFile.close();
            fShaderFile.close();

            // Конвертируем содержимое в строки
            vertexCode = vShaderStream.str();
            geometryCode = gShaderStream.str();
            fragmentCode = fShaderStream.str();
        }
        catch (std::ifstream::failure& e)
        {
#ifdef _DEBUG
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
#endif
        }
        const char* vShaderCode = vertexCode.c_str();
        const char* gShaderCode = geometryCode.c_str();
        const char* fShaderCode = fragmentCode.c_str();

        unsigned int vertex, geometry, fragment;

        // Компиляция вершинного шейдера
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);
        checkCompileErrors(vertex, "VERTEX");

        // Компиляция геометрического шейдера
        geometry = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(geometry, 1, &gShaderCode, NULL);
        glCompileShader(geometry);
        checkCompileErrors(geometry, "GEOMETRY");

        // Компиляция фрагментного шейдера
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);
        checkCompileErrors(fragment, "FRAGMENT");

        // Создание шейдерной программы и связывание шейдеров
        ID = glCreateProgram();
        glAttachShader(ID, vertex);
        glAttachShader(ID, geometry);
        glAttachShader(ID, fragment);
        glLinkProgram(ID);
        checkCompileErrors(ID, "PROGRAM");

        glDeleteShader(vertex);
        glDeleteShader(geometry);
        glDeleteShader(fragment);
    }


    ~Shader() {
        glDeleteProgram(ID);
    }

    // Активация шейдера
    void use()
    {
        glUseProgram(ID);
    }


    // Полезные uniform-функции
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
    void set2Int(const std::string& name, int value1, int value2) const
    {
        glUniform2i(glGetUniformLocation(ID, name.c_str()), value1, value2);
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
    // Полезные функции для проверки ошибок компиляции/связывания шейдеров
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
#ifdef _DEBUG
                std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
#endif
                exit(0);
            }
            else {
#ifdef WITH_DEBUG_OUTPUT
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);

#ifdef _DEBUG
                std::cout << "SUCCESS::SHADER_COMPILED of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
#endif

#endif
            }
        }
        else
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
#ifdef _DEBUG
                std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
#endif
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
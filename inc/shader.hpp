#pragma once

#include <glad/gl.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>

class Shader
{
public:
    Shader(
        const std::filesystem::path& vertex,
        const std::filesystem::path& fragment)
    {
        const std::string vertex_source   = read_file(vertex);
        const std::string fragment_source = read_file(fragment);

        m_id = compile_shader_program(vertex_source, fragment_source);
    }

    void Bind() const
    {
        glUseProgram(m_id);
    }

    void Unbind() const
    {
        glUseProgram(0);
    }

    unsigned int
    get_id() const
    {
        return m_id;
    }

private:
    unsigned int m_id;

    std::string
    read_file(const std::filesystem::path& path)
    {
        std::ifstream file(path, std::ios::in);

        if (!file.is_open())
            return "";

        std::stringstream buffer;

        buffer << file.rdbuf();

        return buffer.str();
    }

    unsigned int
    compile_shader_program(const std::string_view vertex_source, const std::string_view fragment_source)
    {
        unsigned int vertex_shader =
            compile_shader<GL_VERTEX_SHADER>(vertex_source);
        unsigned int fragment_shader =
            compile_shader<GL_FRAGMENT_SHADER>(fragment_source);

        unsigned int shader_program =
            glCreateProgram();

        glAttachShader(shader_program, vertex_shader);
        glAttachShader(shader_program, fragment_shader);

        glLinkProgram(shader_program);

        int success;
        glGetProgramiv(shader_program, GL_LINK_STATUS, &success);

        if (!success)
        {
            char info_log[512];
            glGetProgramInfoLog(shader_program, sizeof(info_log), nullptr, info_log);

            std::cerr << "Failed to link shader program: " << info_log << std::endl;

            return 0;
        }

        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);

        return shader_program;
    }

    template <GLenum type>
    unsigned int
    compile_shader(const std::string_view source)
    {
        unsigned int shader = glCreateShader(type);

        const char* src = source.data();

        glShaderSource(shader, 1, &src, nullptr);
        glCompileShader(shader);

        int success;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

        if (!success)
        {
            char info_log[512];
            glGetShaderInfoLog(shader, sizeof(info_log), nullptr, info_log);

            std::cerr << "Failed to compile shader: " << info_log << std::endl;

            return 0;
        }

        return shader;
    }
}; // class Shader

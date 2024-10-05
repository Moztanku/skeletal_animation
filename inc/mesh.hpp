#pragma once

#include <glad/gl.h>

#include <assimp/scene.h>

#include <glm/glm.hpp>

#include <iostream>
#include <vector>

#if __cplusplus >= 202600L
#   define attr_indeterminate [[indeterminate]]
#else
#   define attr_indeterminate
#endif

struct Vertex
{
    glm::vec3 pos;
    glm::vec3 normal;
    glm::vec2 tex_coords;

    // glm::vec3 tangent;
    // glm::vec3 bitangent;
};

struct Face
{
    glm::uvec3 indices;
};

class Mesh
{
public:
    Mesh(const aiMesh* mesh, const aiScene* scene)
    {
        std::vector<Vertex> vertices = parse_vertices(mesh);
        std::vector<Face>   faces    = parse_faces   (mesh);

        m_vbo = create_vbo(vertices);
        m_ibo = create_ibo(faces);

        m_vao = create_vao(m_vbo, m_ibo);

        m_num_faces = faces.size();
    }

    ~Mesh()
    {
        glDeleteBuffers(1, &m_vbo);
        glDeleteBuffers(1, &m_ibo);
        glDeleteVertexArrays(1, &m_vao);
    }

    void
    draw() const
    {
        // Bind the vertex array object
        glBindVertexArray(m_vao);

        // Draw the mesh
        glDrawElements(
            GL_TRIANGLES,
            m_num_faces * 3,
            GL_UNSIGNED_INT,
            nullptr
        );

        // Unbind the vertex array object
        glBindVertexArray(0);
    }

private:
    unsigned int m_vao;
    unsigned int m_vbo;
    unsigned int m_ibo;

    size_t m_num_faces;

    std::vector<Vertex>
    parse_vertices(const aiMesh* mesh)
    {
        std::vector<Vertex> vertices;

        vertices.reserve(mesh->mNumVertices);

        for (size_t i = 0; i < mesh->mNumVertices; i++)
        {
            Vertex vertex;

            const auto& pos = mesh->mVertices[i];
            vertex.pos = {
                pos.x, pos.y, pos.z
            };

            const auto& normal = mesh->mNormals[i];
            vertex.normal = {
                normal.x, normal.y, normal.z
            };

            if (mesh->HasTextureCoords(0))
            {
                const auto& tex_coords = mesh->mTextureCoords[0][i];

                vertex.tex_coords = {
                    tex_coords.x, tex_coords.y
                };
            }
            else
            {
                vertex.tex_coords = {
                    0.0f, 0.0f
                };
            }

            vertices.push_back(
                std::move(vertex)
            );
        }

        return vertices;
    }

    std::vector<Face>
    parse_faces(const aiMesh* mesh)
    {
        std::vector<Face> faces;

        faces.reserve(mesh->mNumFaces);

        for (size_t i = 0; i < mesh->mNumFaces; i++)
        {
            const auto& face = mesh->mFaces[i];

            Face f;

            if (face.mNumIndices != 3)
            {
                std::cerr << "Err: mesh is not triangulated, use aiProcess_Triangulate" << std::endl;
                std::exit(EXIT_FAILURE);
            }

            f.indices = {
                face.mIndices[0],
                face.mIndices[1],
                face.mIndices[2]
            };

            faces.push_back(
                std::move(f)
            );
        }

        return faces;
    }

    unsigned int
    create_vbo(const std::vector<Vertex>& vertices)
    {
        attr_indeterminate
        unsigned int vbo;

        // Generate a buffer object
        glGenBuffers(1, &vbo);

        // Bind the array buffer to the buffer object
        glBindBuffer(GL_ARRAY_BUFFER, vbo);

        // Fill the buffer with vertex data
        glBufferData(
            GL_ARRAY_BUFFER,
            vertices.size() * sizeof(Vertex),
            vertices.data(),
            GL_STATIC_DRAW
        );

        // Unbind the buffer object
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        return vbo;
    }

    unsigned int
    create_ibo(const std::vector<Face>& faces)
    {
        attr_indeterminate
        unsigned int ibo;

        // Generate a buffer object
        glGenBuffers(1, &ibo);

        // Bind the element array buffer to the buffer object
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

        // Fill the buffer with indices data
        glBufferData(
            GL_ELEMENT_ARRAY_BUFFER,
            faces.size() * sizeof(Face),
            faces.data(),
            GL_STATIC_DRAW
        );

        // Unbind the buffer object
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        return ibo;
    }

    unsigned int
    create_vao(unsigned int vbo, unsigned int ibo)
    {
        attr_indeterminate
        unsigned int vao;

        // Generate a vertex array object
        glGenVertexArrays(1, &vao);

        // Bind the vertex array object
        glBindVertexArray(vao);

        // Bind the buffer objects to the vertex array object
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

        // Enable the vertex attributes
        // Position
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(
            0,
            3,
            GL_FLOAT,
            GL_FALSE,
            sizeof(Vertex),
            (void*)offsetof(Vertex, pos));

        // Normal
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(
            1,
            3,
            GL_FLOAT,
            GL_FALSE,
            sizeof(Vertex),
            (void*)offsetof(Vertex, normal));

        // Texture coordinates
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(
            2,
            2,
            GL_FLOAT,
            GL_FALSE,
            sizeof(Vertex),
            (void*)offsetof(Vertex, tex_coords));

        // Unbind the vertex array object
        glBindVertexArray(0);

        return vao;
    }

}; // class Mesh

#pragma once

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include <glm/glm.hpp>

#include <filesystem>
#include <iostream>
#include <format>
#include <vector>
#include <array>

#include "mesh.hpp"
#include "material.hpp"

class Model
{
public:
    Model(const std::filesystem::path& path)
    {
        Assimp::Importer importer;
        
        const aiScene* scene = importer.ReadFile(
            path.string(),
                aiProcess_Triangulate |
                aiProcess_GenSmoothNormals //|
                // aiProcess_CalcTangentSpace
        );

        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        {
            std::cerr << "Failed to load model: " << path << std::endl;
            std::exit(EXIT_FAILURE);
        }

        m_meshes.reserve(scene->mNumMeshes);

        process_node(scene->mRootNode, scene);

        m_materials.reserve(scene->mNumMaterials);

        for (size_t i = 0; i < scene->mNumMaterials; i++)
        {
            m_materials.push_back(
                Material{scene->mMaterials[i]}
            );
        }
    }

private:
    std::vector<Mesh>       m_meshes;
    std::vector<Material>   m_materials;

    void
    process_node(const aiNode* node, const aiScene* scene)
    {
        for (size_t i = 0; i < node->mNumMeshes; i++)
        {
            const aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            
            m_meshes.push_back(
                Mesh{mesh, scene}
            );
        }

        for (size_t i = 0; i < node->mNumChildren; i++)
        {
            process_node(node->mChildren[i], scene);
        }
    }

}; // class Model

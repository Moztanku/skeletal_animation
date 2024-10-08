#pragma once

#include <assimp/scene.h>

#include <iostream>
#include <vector>

#include "texture.hpp"

class Material
{
public:
    Material(const aiMaterial* material, const std::filesystem::path& path)
    {
        for(const auto& type : texture_types)
        {
            const size_t count = material->GetTextureCount(type);

            for(size_t i = 0; i < count; i++)
            {
                aiString rel_path;

                const auto result = material->GetTexture(
                    type,
                    i,
                    &rel_path
                );

                if (result != aiReturn_SUCCESS)
                {
                    std::cerr << "Failed to get texture" << std::endl;
                }

                const auto tex_path = path / rel_path.C_Str();

                m_textures.push_back(
                    Texture(tex_path)
                );
            }
        }
    }

    void
    bind() const
    {
        for (size_t i = 0; i < m_textures.size(); i++)
        {
            m_textures[i].bind(i);
        }
    }

    void
    unbind() const
    {
        for (size_t i = 0; i < m_textures.size(); i++)
        {
            m_textures[i].unbind(i);
        }
    }
    
private:
    std::vector<Texture> m_textures;
}; // class Material

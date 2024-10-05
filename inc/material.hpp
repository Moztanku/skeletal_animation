#pragma once

#include <assimp/scene.h>


#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include <iostream>
#include <vector>

#include "texture.hpp"

class Material
{
public:
    Material(const aiMaterial* material)
    {
        std::cout << material->GetName().C_Str() << std::endl;

        for(const auto& type : texture_types)
        {
            const size_t count = material->GetTextureCount(type);

            for(size_t i = 0; i < count; i++)
            {
                aiString path;

                const auto result = material->GetTexture(
                    type,
                    i,
                    &path
                );

                if (result != aiReturn_SUCCESS)
                {
                    std::cerr << "Failed to get texture" << std::endl;
                }
                
            }
        }
    }
private:
    std::vector<Texture> m_textures;
}; // class Material

#pragma once

#include <assimp/material.h>
#include <assimp/texture.h>

#include <glad/gl.h>

#include <iostream>
#include <string>
#include <array>

constexpr
std::array<aiTextureType, 22>
texture_types
{
    aiTextureType_NONE          , aiTextureType_DIFFUSE             , aiTextureType_SPECULAR            ,
    aiTextureType_AMBIENT       , aiTextureType_EMISSIVE            , aiTextureType_HEIGHT              ,
    aiTextureType_NORMALS       , aiTextureType_SHININESS           , aiTextureType_OPACITY             ,
    aiTextureType_DISPLACEMENT  , aiTextureType_LIGHTMAP            , aiTextureType_REFLECTION          ,
    aiTextureType_BASE_COLOR    , aiTextureType_NORMAL_CAMERA       , aiTextureType_EMISSION_COLOR      ,
    aiTextureType_METALNESS     , aiTextureType_DIFFUSE_ROUGHNESS   , aiTextureType_AMBIENT_OCCLUSION   ,
    aiTextureType_SHEEN         , aiTextureType_CLEARCOAT           , aiTextureType_TRANSMISSION        ,
    aiTextureType_UNKNOWN
};

constexpr
std::string_view
to_string(const aiTextureType type)
{
    return
        type == aiTextureType_NONE              ? "none"                :
        type == aiTextureType_DIFFUSE           ? "diffuse"             :
        type == aiTextureType_SPECULAR          ? "specular"            :
        type == aiTextureType_AMBIENT           ? "ambient"             :
        type == aiTextureType_EMISSIVE          ? "emissive"            :
        type == aiTextureType_HEIGHT            ? "height"              :
        type == aiTextureType_NORMALS           ? "normals"             :
        type == aiTextureType_SHININESS         ? "shininess"           :
        type == aiTextureType_OPACITY           ? "opacity"             :
        type == aiTextureType_DISPLACEMENT      ? "displacement"        :
        type == aiTextureType_LIGHTMAP          ? "lightmap"            :
        type == aiTextureType_REFLECTION        ? "reflection"          :
        type == aiTextureType_BASE_COLOR        ? "base_color"          :
        type == aiTextureType_NORMAL_CAMERA     ? "normal_camera"       :
        type == aiTextureType_EMISSION_COLOR    ? "emission_color"      :
        type == aiTextureType_METALNESS         ? "metalness"           :
        type == aiTextureType_DIFFUSE_ROUGHNESS ? "diffuse_roughness"   :
        type == aiTextureType_AMBIENT_OCCLUSION ? "ambient_occlusion"   :
        type == aiTextureType_SHEEN             ? "sheen"               :
        type == aiTextureType_CLEARCOAT         ? "clearcoat"           :
        type == aiTextureType_TRANSMISSION      ? "transmission"        :
        type == aiTextureType_UNKNOWN           ? "unknown"             :
                                                  "invalid"             ;
}

struct Texture
{
    Texture(const aiTexture* texture)
    {
        
    }

    unsigned int id;

}; // class Texture

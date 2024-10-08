#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

uniform mat4 uModel;
uniform mat4 uMVP;

out vec3 normal;
out vec2 texCoords;

void main()
{
    normal = mat3(transpose(inverse(uModel))) * aNormal;
    texCoords = aTexCoords;

    gl_Position = uMVP * vec4(aPos, 1.0);
}

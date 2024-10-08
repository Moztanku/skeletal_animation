#version 460 core

in vec3 normal;
in vec2 texCoords;

uniform sampler2D tex_diffuse;
// uniform sampler2D tex_specular;
// uniform sampler2D tex_normal;
// uniform sampler2D tex_emission;

uniform vec3 uLightColor = vec3(1.0, 1.0, 1.0);
uniform vec3 uLightDir = vec3(0.0, 0.0, 1.0);

out vec4 fragColor;

void main()
{
    vec3 norm = normalize(normal);

    float diff = max(dot(norm, uLightDir), 0.0);
    vec3 diffuse = diff * uLightColor;
    vec4 texColor = texture(tex_diffuse, texCoords);

    fragColor = vec4(diffuse, 1.0) * texColor;    
}

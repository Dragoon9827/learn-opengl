#version 330 core
out vec4 FragColor;

in vec2 outTexCoord;
in vec4 outColor;

uniform sampler2D Texture;

void main()
{
    FragColor = texture(Texture, outTexCoord) * outColor;
}
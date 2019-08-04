#version 330 core
out vec4 FragColor;

in vec4 outColor;
in vec2 outTexCoord;

uniform sampler2D Texture;

void main()
{
    FragColor = texture(Texture, outTexCoord) * vec4(outColor);
}
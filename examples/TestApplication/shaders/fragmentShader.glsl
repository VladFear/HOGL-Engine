#version 400 core

in vec2 textureCoords;
out vec4 colorOut;

uniform sampler2D textureSampler;

void main()
{
	colorOut = texture(textureSampler, textureCoords);
}

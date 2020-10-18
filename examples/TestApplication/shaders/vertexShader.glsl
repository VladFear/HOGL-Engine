#version 400 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 aTextureCoords;

out vec2 textureCoords;

uniform mat4 modelMatrix;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

void main()
{
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(position, 1.0f);
	textureCoords = aTextureCoords;
}

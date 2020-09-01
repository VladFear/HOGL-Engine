#pragma once

#include <forward_list>

#include <glm/glm.hpp>

#include <graphics/Shader.h>

class ShaderProgram
{
	private:
		void createShaderProgram();
		void validate() const;

	public:
		ShaderProgram();
		~ShaderProgram();
		void attachShader(const Shader & shader);
		void compile();
		unsigned int value() const;

	private:
		std::forward_list<unsigned int> m_shaders;
		unsigned int m_shader;
};

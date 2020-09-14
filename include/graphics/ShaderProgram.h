#pragma once

#include <forward_list>
#include <memory>

#include <glm/glm.hpp>

#include <graphics/Shader.h>

class ShaderProgram
{
	public:
		ShaderProgram();
		virtual ~ShaderProgram();
		void attachShader(const Shader & shader);
		void setValidationStrategy(std::shared_ptr<IValidationStrategy> validation_strategy);
		void compile();
		unsigned int value() const;

	private:
		void createShaderProgram();
		void validate() const;

	private:
		std::forward_list<unsigned int> m_shaders;
		std::shared_ptr<IValidationStrategy> m_validation_strategy;
		unsigned int m_shader;
};

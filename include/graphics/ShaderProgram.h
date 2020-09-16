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
		ShaderProgram(const ShaderProgram & other);
		ShaderProgram(ShaderProgram && other) noexcept;
		ShaderProgram & operator=(const ShaderProgram & other);
		ShaderProgram & operator=(ShaderProgram && other) noexcept;
		void attachShader(const Shader & shader);
		void attachShader(std::shared_ptr<Shader> shader);
		void attachShader(Shader * shader) = delete;
		void setValidationStrategy(std::shared_ptr<IValidationStrategy> validation_strategy);
		void compile();
		unsigned int value() const;
		int getUniformLocation(const std::string & uniform_name) const;

	private:
		void validate() const;

	private:
		std::forward_list<unsigned int> m_shaders;
		std::shared_ptr<IValidationStrategy> m_validation_strategy;
		unsigned int m_shader;
};

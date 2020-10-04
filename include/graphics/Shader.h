#pragma once

#include <assert.h>
#include <string>
#include <sstream>
#include <fstream>
#include <exception>
#include <memory>
#include <filesystem>

#include <GL/glew.h>

#include <graphics/ValidationDefaultStrategy.h>

class Shader
{
	public:
		Shader() = default;
		virtual ~Shader() = default;
		unsigned int value() const;

	public:
		class ShaderBuilder
		{
			public:
				ShaderBuilder();
				~ShaderBuilder() = default;
				ShaderBuilder & setSource(const std::filesystem::path & shaderPath);
				ShaderBuilder & setValidationStrategy(std::shared_ptr<IValidationStrategy> validation_strategy);
				std::shared_ptr<Shader> create(GLenum shader_type);

			private:
				void validate() const;
				void createSourceStringFromFile(std::ifstream & file);

			private:
				std::shared_ptr<Shader> m_shader_ptr;
				std::shared_ptr<IValidationStrategy> m_validation_strategy;
		};

	protected:
		std::string m_source;
		unsigned int m_shader;
};

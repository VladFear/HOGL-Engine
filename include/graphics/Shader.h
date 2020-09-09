#pragma once

#include <GL/glew.h>
#include <assert.h>
#include <string>
#include <sstream>
#include <fstream>
#include <exception>
#include <memory>

class Shader
{
	public:
		Shader();
		virtual ~Shader();
		unsigned int value() const;

	public:
		class ShaderBuilder
		{
			public:
				ShaderBuilder();
				~ShaderBuilder() = default;
				ShaderBuilder & setSource(std::string && src);
				ShaderBuilder & setSource(std::fstream && file);
				std::shared_ptr<Shader> create(GLenum shader_type);

			private:
				void validate() const;
				void createSourceStringFromFile(std::fstream file);

			private:
				std::shared_ptr<Shader> m_shader_ptr;
		};

	protected:
		std::string m_source;
		unsigned int m_shader;
};

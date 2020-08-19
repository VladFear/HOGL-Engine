#pragma once

#include <GL/glew.h>
#include <assert.h>
#include <string>
#include <sstream>
#include <fstream>
#include <exception>

class Shader
{
	private:
		void virtual validate() const = 0;

	public:
		virtual ~Shader() = 0;
		void virtual compile() = 0;
		unsigned int virtual value() const = 0;

	protected:
		std::string m_source;
		unsigned int m_shader;
};

Shader::~Shader() = default;

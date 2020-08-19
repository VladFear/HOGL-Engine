#pragma once

#include "shader.h"

class VertexShader : public Shader
{
	public:
		VertexShader() = delete;
		VertexShader(const std::string & src);
		VertexShader(std::fstream & file);
		~VertexShader();
		void compile() override;
		unsigned int value() const override;

	private:
		void parseFile(std::fstream & file);
		void createShader();
		void validate() const override;
};

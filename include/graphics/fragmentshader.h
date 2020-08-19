#pragma once

#include "shader.h"

class FragmentShader : public Shader
{
	public:
		FragmentShader() = delete;
		FragmentShader(const std::string & src);
		FragmentShader(std::fstream & file);
		~FragmentShader();
		void compile() override;
		unsigned int value() const override;

	private:
		void parseFile(std::fstream & file);
		void createShader();
		void validate() const override;
};

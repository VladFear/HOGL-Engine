#pragma once

#include "ishader.h"

class FragmentShader : public IShader
{
	private:
		std::string source;
		unsigned int shader;

	private:
		void parseFile(std::fstream & file);
		void createShader();
		void validate() const override;

	public:
		FragmentShader() = delete;
		FragmentShader(const std::string & src);
		FragmentShader(std::fstream & file);
		~FragmentShader();
		void compile() override;
		unsigned int value() const override;
};

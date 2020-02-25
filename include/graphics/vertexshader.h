#pragma once

#include "ishader.h"

class VertexShader : public IShader
{
	private:
		std::string source;
		unsigned int shader;

	private:
		void parseFile(std::fstream & file);
		void createShader();
		void validate() const override;

	public:
		VertexShader() = delete;
		VertexShader(const std::string & src);
		VertexShader(std::fstream & file);
		~VertexShader();
		void compile() override;
		unsigned int value() const override;
};

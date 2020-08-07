#pragma once

#include <forward_list>

#include <graphics/ishader.h>

class ShaderProgram : IShader
{
	private:
		unsigned int shader_program;
		std::forward_list<unsigned int> shaders;

	private:
		void createShaderProgram();
		void validate() const override;

	public:
		ShaderProgram();
		virtual ~ShaderProgram();
		void attachShader(const IShader & shader);
		void compile() override;
		unsigned int value() const override;
};

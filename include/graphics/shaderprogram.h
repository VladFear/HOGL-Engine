#pragma once

#include <forward_list>

#include <graphics/shader.h>

class ShaderProgram : public Shader
{
	private:
		void createShaderProgram();
		void validate() const override;

	public:
		ShaderProgram();
		~ShaderProgram();
		void attachShader(const Shader & shader);
		void compile() override;
		unsigned int value() const override;

	private:
		std::forward_list<unsigned int> m_shaders;
};

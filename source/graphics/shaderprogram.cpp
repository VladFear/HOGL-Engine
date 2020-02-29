#include <graphics/shaderprogram.h>

ShaderProgram::ShaderProgram()
{
	createShaderProgram();
	shaders.resize(3);
}

ShaderProgram::~ShaderProgram()
{
	for (unsigned int shader : shaders)
		glDetachShader(shader_program, shader);

	glDeleteProgram(shader_program);
}

void ShaderProgram::compile()
{
	/* Link shaders in shader program */
	glLinkProgram(shader_program);
	validate();
}

void ShaderProgram::validate() const
{
	int success = 0;

	glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
	if (!success)
	{
		/* Pull the error message */
		char info_log[1024];
		glGetProgramInfoLog(shader_program, sizeof(info_log), nullptr, info_log);

		throw std::runtime_error(std::string(info_log));
	}
}

unsigned int ShaderProgram::value() const
{
	return shader_program;
}

void ShaderProgram::createShaderProgram()
{
	shader_program = glCreateProgram();
}

void ShaderProgram::attachShader(const IShader & shader)
{
	unsigned int shader_value = shader.value();
	glAttachShader(shader_program, shader_value);
	shaders.emplace_back(shader_value);
}

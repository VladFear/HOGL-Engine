#include <graphics/ShaderProgram.h>

ShaderProgram::ShaderProgram()
{
	createShaderProgram();
}

ShaderProgram::~ShaderProgram()
{
	for (unsigned int shader : m_shaders)
		glDetachShader(m_shader, shader);

	glDeleteProgram(m_shader);
}

void ShaderProgram::compile()
{
	/* Link shaders in shader program */
	glLinkProgram(m_shader);
	validate();
}

void ShaderProgram::validate() const
{
	int success = 0;

	glGetProgramiv(m_shader, GL_LINK_STATUS, &success);
	if (!success)
	{
		/* Pull the error message */
		char info_log[1024];
		glGetProgramInfoLog(m_shader, sizeof(info_log), nullptr, info_log);

		throw std::runtime_error(std::string(info_log));
	}
}

unsigned int ShaderProgram::value() const
{
	return m_shader;
}

void ShaderProgram::createShaderProgram()
{
	m_shader = glCreateProgram();
}

void ShaderProgram::attachShader(const Shader & shader)
{
	unsigned int shader_value = shader.value();
	glAttachShader(m_shader, shader_value);
	m_shaders.push_front(shader_value);
}

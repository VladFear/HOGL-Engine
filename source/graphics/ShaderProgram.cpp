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
	m_validation_strategy->validate(m_shader, ValidationPoint::LINKING);
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

void ShaderProgram::setValidationStrategy(std::shared_ptr<IValidationStrategy> validation_strategy)
{
	m_validation_strategy = validation_strategy;
}

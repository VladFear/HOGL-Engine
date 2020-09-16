#include <graphics/ShaderProgram.h>

ShaderProgram::ShaderProgram()
{
	m_shader = glCreateProgram();
}

ShaderProgram::ShaderProgram(const ShaderProgram & other)
{
	m_shader = other.m_shader;
	m_shaders = other.m_shaders;
	m_validation_strategy = other.m_validation_strategy;
}

ShaderProgram::ShaderProgram(ShaderProgram && other) noexcept
{
	m_shader = std::exchange(other.m_shader, 0);
	m_shaders = std::move(other.m_shaders);
	m_validation_strategy = std::move(other.m_validation_strategy);
}

ShaderProgram & ShaderProgram::operator=(const ShaderProgram & other)
{
	if (&other != this)
	{
		m_shader = other.m_shader;
		m_shaders = other.m_shaders;
		m_validation_strategy = other.m_validation_strategy;
	}

	return *this;
}

ShaderProgram & ShaderProgram::operator=(ShaderProgram && other) noexcept
{
	if (&other != this)
	{
		m_shader = std::exchange(other.m_shader, 0);
		m_shaders = std::move(other.m_shaders);
		m_validation_strategy = std::move(other.m_validation_strategy);
	}

	return *this;
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

void ShaderProgram::attachShader(const Shader & shader)
{
	unsigned int shader_value = shader.value();
	glAttachShader(m_shader, shader_value);
	m_shaders.push_front(shader_value);
}

void ShaderProgram::attachShader(std::shared_ptr<Shader> shader)
{
	unsigned int shader_value = shader->value();
	glAttachShader(m_shader, shader_value);
	m_shaders.push_front(shader_value);
}

void ShaderProgram::setValidationStrategy(std::shared_ptr<IValidationStrategy> validation_strategy)
{
	m_validation_strategy = validation_strategy;
}

int ShaderProgram::getUniformLocation(const std::string & uniform_name) const
{
	int location = glGetUniformLocation(m_shader, uniform_name.c_str());

	if (location == GL_INVALID_VALUE or
	    location == GL_INVALID_OPERATION or
	    location == -1)
		throw std::invalid_argument("Unable to get uniform variable with name \"" + uniform_name + "\"\n");

	return location;
}

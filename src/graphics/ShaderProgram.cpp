#include <graphics/ShaderProgram.h>

ShaderProgram::ShaderProgram()
{
	m_shader = glCreateProgram();
}

ShaderProgram::~ShaderProgram()
{
	unapply();

	for (unsigned int shader : m_shaders)
		glDetachShader(m_shader, shader);

	glDeleteProgram(m_shader);
}

void ShaderProgram::compile()
{
	/* Link shaders in shader program */
	glLinkProgram(m_shader);
	validate();

	getAllUniformLocations();
}

void ShaderProgram::validate() const
{
	m_validation_strategy->validate(m_shader, ValidationPoint::LINKING);
}

unsigned int ShaderProgram::value() const
{
	return m_shader;
}

void ShaderProgram::apply() const
{
	glUseProgram(m_shader);
}

void ShaderProgram::unapply() const
{
	glUseProgram(0);
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

void ShaderProgram::setFloatToUniform(const int location, const float value)
{
	glUniform1f(location, value);
}

void ShaderProgram::setBoolToUniform(const int location, const bool value)
{
	glUniform1f(location, value ? 1.0 : 0.0);
}

void ShaderProgram::setVector3fToUniform(const int location, const glm::vec3 & vector)
{
	glUniform3f(location, vector.x, vector.y, vector.z);
}

void ShaderProgram::setMatrixToUniform(const int location, const glm::mat4 & matrix)
{
	glUniformMatrix4fv(location, 1, false, glm::value_ptr(matrix));
}

void ShaderProgram::setTransformMatrix(const glm::mat4 & transform_matrix)
{
	glUniformMatrix4fv(m_transform_matrix_location, 1, false, glm::value_ptr(transform_matrix));
}

void ShaderProgram::setProjectionMatrix(const glm::mat4 & projection_matrix)
{
	glUniformMatrix4fv(m_projection_matrix_location, 1, false, glm::value_ptr(projection_matrix));
}

void ShaderProgram::getAllUniformLocations()
{
	m_transform_matrix_location = getUniformLocation("transform_matrix");
	m_projection_matrix_location = getUniformLocation("projection_matrix");
}

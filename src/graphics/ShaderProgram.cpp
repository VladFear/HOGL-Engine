#include "graphics/ShaderProgram.h"

namespace GE
{

	ShaderProgram::ShaderProgram()
	{
		m_id = glCreateProgram();
	}

	ShaderProgram::~ShaderProgram()
	{
		unapply();

		for (unsigned int shaderId : m_shadersIds)
			glDetachShader(m_id, shaderId);

		glDeleteProgram(m_id);
	}

	void ShaderProgram::compile()
	{
		/* Link shaders in shader program */
		glLinkProgram(m_id);
		validate();

		getAllUniformLocations();
	}

	void ShaderProgram::validate() const
	{
		m_validationStrategy->validate(m_id, ValidationPoint::Linking);
	}

	void ShaderProgram::apply() const
	{
		glUseProgram(m_id);
	}

	void ShaderProgram::unapply() const
	{
		glUseProgram(0);
	}

	void ShaderProgram::attachShader(const Shader & shader)
	{
		uint shaderId = shader.getId();
		glAttachShader(m_id, shaderId);
		m_shadersIds.push_front(shaderId);
	}

	void ShaderProgram::attachShader(sPtr<Shader> shader)
	{
		uint shaderId = shader->getId();
		glAttachShader(m_id, shaderId);
		m_shadersIds.push_front(shaderId);
	}

	void ShaderProgram::setValidationStrategy(sPtr<IValidationStrategy> validationStrategy)
	{
		m_validationStrategy = validationStrategy;
	}

	int ShaderProgram::getUniformLocation(const std::string & uniformName) const
	{
		int location = glGetUniformLocation(m_id, uniformName.c_str());

		if (location == GL_INVALID_VALUE or
				location == GL_INVALID_OPERATION or
				location == -1)
			throw std::invalid_argument("Unable to get uniform variable with name \"" + uniformName + "\"\n");

		return location;
	}

	uint ShaderProgram::getId() const
	{
		return m_id;
	}

	void ShaderProgram::setFloatToUniform(const int location, const float value)
	{
		glUniform1f(location, value);
	}

	void ShaderProgram::setBoolToUniform(const int location, const bool value)
	{
		glUniform1f(location, value ? 1.0 : 0.0);
	}

	void ShaderProgram::setVector3fToUniform(const int location, const vec3 & vector)
	{
		glUniform3f(location, vector.x, vector.y, vector.z);
	}

	void ShaderProgram::setMatrixToUniform(const int location, const mat4 & matrix)
	{
		glUniformMatrix4fv(location, 1, false, glm::value_ptr(matrix));
	}

	void ShaderProgram::setModelMatrix(const mat4 & modelMatrix)
	{
		glUniformMatrix4fv(m_modelMatrixLocation, 1, false, glm::value_ptr(modelMatrix));
	}

	void ShaderProgram::setProjectionMatrix(const mat4 & projectionMatrix)
	{
		glUniformMatrix4fv(m_projectionMatrixLocation, 1, false, glm::value_ptr(projectionMatrix));
	}

	void ShaderProgram::setViewMatrix(const mat4 & viewMatrix)
	{
		glUniformMatrix4fv(m_viewMatrixLocation, 1, false, glm::value_ptr(viewMatrix));
	}

	void ShaderProgram::getAllUniformLocations()
	{
		m_modelMatrixLocation      = getUniformLocation("modelMatrix");
		m_projectionMatrixLocation = getUniformLocation("projectionMatrix");
		m_viewMatrixLocation       = getUniformLocation("viewMatrix");
	}

} // GE

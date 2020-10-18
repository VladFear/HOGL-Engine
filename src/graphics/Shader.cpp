#include "graphics/Shader.h"

namespace GE
{

	using Builder = Shader::ShaderBuilder;

	// Shader class

	Shader::Shader(const path & shaderPath,
	               sPtr<IValidationStrategy> validationStrategy,
	               const ShaderType & shaderType)
	{
		assert(shaderType != ShaderType::Undefined);
		assert(validationStrategy != nullptr);

		if (!fs::exists(shaderPath))
			throw std::runtime_error("Shader path " + shaderPath.native() + " does not exist.\n");

		// Save data
		m_shaderType = shaderType;
		m_validationStrategy.reset();
		m_validationStrategy = std::move(validationStrategy);

		m_id = glCreateShader(static_cast<GLenum>(shaderType));

		std::ifstream file(shaderPath.native());
		createSourceStringFromFile(file);

		compile();
		validate();
	}

	uint Shader::getId() const
	{
		return m_id;
	}

	ShaderType Shader::getShaderType() const
	{
		return m_shaderType;
	}

	void Shader::validate() const
	{
		m_validationStrategy->validate(m_id, ValidationPoint::Compilation);
	}

	void Shader::compile() const
	{
		const char* csource = m_source.c_str();

		/* Shader compilation */
		glShaderSource(m_id, 1, &csource, nullptr);
		glCompileShader(m_id);
	}

	void Shader::createSourceStringFromFile(std::ifstream & file)
	{
		/* Ensures ifstream objects can throw exceptions */
		file.exceptions(std::ifstream::badbit | std::ifstream::failbit);
		assert(file.is_open());

		/* Read shader source from file */
		std::stringstream stream;
		stream << file.rdbuf();

		m_source = stream.str();
	}

	// ShaderBuilder class

	Builder & Builder::setSource(const path & shaderPath)
	{
		m_shaderPath = shaderPath;

		return *this;
	}

	Builder & Builder::setValidationStrategy(sPtr<IValidationStrategy> validationStrategy)
	{
		m_validationStrategy = std::move(validationStrategy);

		return *this;
	}

	Builder & Builder::setShaderType(const ShaderType & shaderType)
	{
		m_shaderType = shaderType;

		return *this;
	}

	sPtr<Shader> Builder::build()
	{
		return std::make_shared<Shader>(
			std::move(m_shaderPath),
			std::move(m_validationStrategy),
			m_shaderType);
	}

} // GE

#include <graphics/Shader.h>

namespace GE
{

	using Builder = Shader::ShaderBuilder;

	Builder::ShaderBuilder()
	{
		m_shaderPtr = std::make_shared<Shader>();
		m_validationStrategy = std::make_shared<ValidationDefaultStrategy>();
	}

	Builder & Builder::setSource(const path & shaderPath)
	{
		if (!fs::exists(shaderPath))
			throw std::runtime_error("Shader path " + shaderPath.native() + " does not exist.\n");

		std::ifstream file(shaderPath.native());
		createSourceStringFromFile(file);

		return *this;
	}

	sPtr<Shader> Builder::create(GLenum shaderType)
	{
		m_shaderPtr->m_id = glCreateShader(shaderType);

		const char* csource = m_shaderPtr->m_source.c_str();

		/* Shader compilation */
		glShaderSource(m_shaderPtr->m_id, 1, &csource, nullptr);
		glCompileShader(m_shaderPtr->m_id);

		return m_shaderPtr;
	}

	void Builder::validate() const
	{
		m_validationStrategy->validate(m_shaderPtr->m_id, ValidationPoint::Compilation);
	}

	void Builder::createSourceStringFromFile(std::ifstream & file)
	{
		/* Ensures ifstream objects can throw exceptions */
		file.exceptions(std::ifstream::badbit | std::ifstream::failbit);
		assert(file.is_open());

		/* Read shader source from file */
		std::stringstream stream;
		stream << file.rdbuf();

		m_shaderPtr->m_source = stream.str();
	}

	Builder & Builder::setValidationStrategy(sPtr<IValidationStrategy> validationStrategy)
	{
		m_validationStrategy = validationStrategy;

		return *this;
	}

	uint Shader::getId() const
	{
		return m_id;
	}

} // GE

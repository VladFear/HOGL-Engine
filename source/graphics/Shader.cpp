#include <graphics/Shader.h>

using Builder = Shader::ShaderBuilder;

unsigned int Shader::value() const
{
	return m_shader;
}

Builder::ShaderBuilder()
{
	m_shader_ptr = std::make_shared<Shader>();
	m_validation_strategy = std::make_shared<ValidationDefaultStrategy>();
}

Builder & Builder::setSource(std::string && src)
{
	createSourceStringFromFile(std::fstream(std::forward<std::string>(src)));

	return *this;
}

Builder & Builder::setSource(std::fstream && file)
{
	createSourceStringFromFile(std::forward<std::fstream>(file));

	return *this;
}

std::shared_ptr<Shader> Builder::create(GLenum shader_type)
{
	m_shader_ptr->m_shader = glCreateShader(shader_type);

	const char* csource = m_shader_ptr->m_source.c_str();

	/* Shader compilation */
	glShaderSource(m_shader_ptr->m_shader, 1, &csource, nullptr);
	glCompileShader(m_shader_ptr->m_shader);

	return m_shader_ptr;
}

void Builder::validate() const
{
	m_validation_strategy->validate(m_shader_ptr->m_shader, ValidationPoint::COMPILATION);
}

void Builder::createSourceStringFromFile(std::fstream file)
{
	/* Ensures ifstream objects can throw exceptions */
	file.exceptions(std::ifstream::badbit | std::ifstream::failbit);
	assert(file.is_open());

	/* Read shader source from file */
	std::stringstream stream;
	stream << file.rdbuf();

	m_shader_ptr->m_source = stream.str();
	file.close();
}

Builder & Builder::setValidationStrategy(std::shared_ptr<IValidationStrategy> validation_strategy)
{
	m_validation_strategy = validation_strategy;

	return *this;
}

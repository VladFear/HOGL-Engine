#include <graphics/shader.h>

Shader::Shader()
{

}

Shader::~Shader()
{

}

unsigned int Shader::value() const
{
	return m_shader;
}

Shader::ShaderBuilder::ShaderBuilder()
{
	m_shader_ptr.reset(new Shader());
}

Shader::ShaderBuilder & Shader::ShaderBuilder::setSource(const std::string & src)
{
	m_shader_ptr->m_source = src;
	return *this;
}

Shader::ShaderBuilder & Shader::ShaderBuilder::setSource(std::fstream & file)
{
	/* Ensures ifstream objects can throw exceptions */
	file.exceptions(std::ifstream::badbit | std::ifstream::failbit);
	assert(file.is_open());

	/* Read shader source from file */
	std::stringstream stream;
	stream << file.rdbuf();

	m_shader_ptr->m_source = stream.str();
	file.close();

	return *this;
}

std::shared_ptr<Shader> Shader::ShaderBuilder::create(GLenum shader_type)
{
	m_shader_ptr->m_shader = glCreateShader(shader_type);

	const char* csource = m_shader_ptr->m_source.c_str();

	/* Shader compilation */
	glShaderSource(m_shader_ptr->m_shader, 1, &csource, nullptr);
	glCompileShader(m_shader_ptr->m_shader);

	return m_shader_ptr;
}

void Shader::ShaderBuilder::validate() const
{
	int success = 0;

	glGetShaderiv(m_shader_ptr->m_shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		/* Pull the error message */
		char info_log[1024];
		glGetShaderInfoLog(m_shader_ptr->m_shader, sizeof(info_log), nullptr, info_log);

		throw std::runtime_error(std::string(info_log));
	}
}

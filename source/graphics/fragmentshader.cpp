#include <graphics/fragmentshader.h>

FragmentShader::FragmentShader(const std::string & src)
{
	m_source = src;
}

FragmentShader::FragmentShader(std::fstream & file)
{
	parseFile(file);
}

FragmentShader::~FragmentShader()
{
	glDeleteShader(m_shader);
}

void FragmentShader::parseFile(std::fstream & file)
{
	/* Ensures ifstream objects can throw exceptions */
	file.exceptions(std::ifstream::badbit | std::ifstream::failbit);
	assert(file.is_open());

	/* Read shader source from file */
	std::stringstream stream;
	stream << file.rdbuf();

	m_source = stream.str();
	file.close();
}

void FragmentShader::createShader()
{
	m_shader = glCreateShader(GL_FRAGMENT_SHADER);
}

void FragmentShader::validate() const
{
	int success = 0;

	glGetShaderiv(m_shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		/* Pull the error message */
		char info_log[1024];
		glGetShaderInfoLog(m_shader, sizeof(info_log), nullptr, info_log);

		throw std::runtime_error(std::string(info_log));
	}
}

void FragmentShader::compile()
{
	createShader();
	const char* csource = m_source.c_str();

	/* Shader compilation */
	glShaderSource(m_shader, 1, &csource, nullptr);
	glCompileShader(m_shader);
}

unsigned int FragmentShader::value() const
{
	return m_shader;
}

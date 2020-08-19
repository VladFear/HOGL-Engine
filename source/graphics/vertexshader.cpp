#include <graphics/vertexshader.h>

VertexShader::VertexShader(const std::string & src)
{
	m_source = src;
}

VertexShader::VertexShader(std::fstream & file)
{
	parseFile(file);
}

VertexShader::~VertexShader()
{
	glDeleteShader(m_shader);
}

void VertexShader::parseFile(std::fstream & file)
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

void VertexShader::createShader()
{
	m_shader = glCreateShader(GL_VERTEX_SHADER);
}

void VertexShader::validate() const
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

void VertexShader::compile()
{
	createShader();
	const char* csource = m_source.c_str();

	/* Shader compilation */
	glShaderSource(m_shader, 1, &csource, nullptr);
	glCompileShader(m_shader);
}

unsigned int VertexShader::value() const
{
	return m_shader;
}

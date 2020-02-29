#include <graphics/vertexshader.h>

VertexShader::VertexShader(const std::string & src) : source(src)
{

}

VertexShader::VertexShader(std::fstream & file)
{
	parseFile(file);
}

VertexShader::~VertexShader()
{
	glDeleteShader(shader);
}

void VertexShader::parseFile(std::fstream & file)
{
	/* Ensures ifstream objects can throw exceptions */
	file.exceptions(std::ifstream::badbit | std::ifstream::failbit);
	assert(file.is_open());

	/* Read shader source from file */
	std::stringstream stream;
	stream << file.rdbuf();

	source = stream.str();
	file.close();
}

void VertexShader::createShader()
{
	shader = glCreateShader(GL_VERTEX_SHADER);
}

void VertexShader::validate() const
{
	int success = 0;

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		/* Pull the error message */
		char info_log[1024];
		glGetShaderInfoLog(shader, sizeof(info_log), nullptr, info_log);

		throw std::runtime_error(std::string(info_log));
	}
}

void VertexShader::compile()
{
	createShader();
	const char* csource = source.c_str();

	/* Shader compilation */
	glShaderSource(shader, 1, &csource, nullptr);
	glCompileShader(shader);
}

unsigned int VertexShader::value() const
{
	return shader;
}

#include <graphics/globalengine.h>

GlobalEngine::GlobalEngine()
{

}

GlobalEngine::~GlobalEngine()
{
	glfwTerminate();
}

void GlobalEngine::initialize()
{
	if (!glfwInit())
		throw std::runtime_error(std::string("Failed to initialize GLFW library.\n"));

	_window = glfwCreateWindow(_width, _height, "HOGL", nullptr, nullptr);

	if (!_window)
	{
		glfwTerminate();
		throw std::runtime_error(std::string("Failed to create window context.\n"));
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(_window);

	if (glewInit() != GLEW_OK)
	{
		throw std::runtime_error(std::string("Failed to initialize GLEW library. glewInit() != GLEW_OK\n"));
	}
}

void GlobalEngine::pollEvents() const
{
	glfwPollEvents();
}

void GlobalEngine::swapBuffers() const
{
	glfwSwapBuffers(_window);
}

void GlobalEngine::render(const Model& model) const
{
	glBindVertexArray(model.vao());
	glEnableVertexAttribArray(0);
	glDrawElements(GL_TRIANGLES, model.indexesCount(), GL_UNSIGNED_INT, 0);
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
}

void GlobalEngine::clear() const
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

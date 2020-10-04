#include <GlobalEngine.h>

GlobalEngine::GlobalEngine(EngineAPI api)
{
	m_render_engine = std::make_unique<RenderEngine>(api);
	m_game_scene = std::make_unique<GameScene>();
}

void GlobalEngine::startGameLoop() const
{
	while (!m_render_engine->windowShouldClose())
	{
		/* Poll for and process events */
		m_render_engine->pollEvents();
		m_render_engine->clear();

		/* Render here */
		m_render_engine->render();
		render();
		/* Swap front and back buffers */
		m_render_engine->swapBuffers();
	}
}

void GlobalEngine::render() const
{
	m_game_scene->renderScene();
}

void GlobalEngine::addGameObject(std::unique_ptr<GameObject> game_object)
{
	m_game_scene->addGameObject(std::move(game_object));
}

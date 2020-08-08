#include <graphics/gamescene.h>

GameScene::GameScene()
{

}

GameScene::~GameScene()
{

}

void GameScene::addGameObject(Model * object)
{
	m_game_objects.push_front(std::shared_ptr<Model>(object));
}

void GameScene::renderScene() const
{
	for (const auto game_object : m_game_objects)
		game_object->draw();
}

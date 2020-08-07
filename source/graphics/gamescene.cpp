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

const std::forward_list<std::shared_ptr<Model>> & GameScene::getGameScene() const
{
	return m_game_objects;
}

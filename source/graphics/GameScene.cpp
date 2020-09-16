#include <graphics/GameScene.h>

void GameScene::addGameObject(std::unique_ptr<GameObject> object)
{
	m_objects_list.push_front(std::move(object));
}

void GameScene::renderScene() const
{
	for (const auto& object : m_objects_list)
		renderObject(object);
}

void GameScene::renderObject(const std::unique_ptr<GameObject> & object) const
{
	object->draw();
}

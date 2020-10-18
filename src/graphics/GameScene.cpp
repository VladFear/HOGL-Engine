#include "graphics/GameScene.h"
#include <memory>

namespace GE
{

	void GameScene::addGameObject(std::shared_ptr<IDrawable> object)
	{
		m_objectsList.push_front(std::move(object));
	}

	void GameScene::renderScene() const
	{
		for (const auto & object : m_objectsList)
			renderObject(object);
	}

	void GameScene::renderObject(std::shared_ptr<IDrawable> object) const
	{
		object->draw();
	}

	std::forward_list<std::shared_ptr<IDrawable>> & GameScene::getGameObjectsList()
	{
		return m_objectsList;
	}

} // GE

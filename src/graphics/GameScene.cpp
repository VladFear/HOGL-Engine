#include "graphics/GameScene.h"

namespace GE
{

	void GameScene::addGameObject(Shared<IDrawable> object)
	{
		m_objectsList.push_front(std::move(object));
	}

	void GameScene::renderScene() const
	{
		for (const auto & object : m_objectsList)
			renderObject(object);
	}

	void GameScene::renderObject(Shared<IDrawable> object) const
	{
		object->draw();
	}

	std::forward_list<Shared<IDrawable>> & GameScene::getGameObjectsList()
	{
		return m_objectsList;
	}

} // GE

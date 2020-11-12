#include "graphics/GameScene.h"

namespace GE
{

	void GameScene::addGameObject(Shared<IDrawable> object)
	{
		m_objectsList.push_front(std::move(object));
	}

	std::forward_list<Shared<IDrawable>> & GameScene::getGameObjectsList()
	{
		return m_objectsList;
	}

} // GE

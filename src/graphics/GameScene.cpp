#include "graphics/GameScene.h"

namespace GE
{

	void GameScene::addGameObject(Shared<IDrawable> object)
	{
		m_objectsList.push_front(std::move(object));
	}

	const std::forward_list<Shared<IDrawable>> & GameScene::getGameObjectsList() const
	{
		return m_objectsList;
	}

} // GE

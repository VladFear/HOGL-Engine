#include "graphics/GameScene.h"

namespace GE
{

	void GameScene::addGameObject(uPtr<GameObject> object)
	{
		m_objectsList.push_front(std::move(object));
	}

	void GameScene::renderScene() const
	{
		for (const auto & object : m_objectsList)
			renderObject(object);
	}

	void GameScene::renderObject(const uPtr<GameObject> & object) const
	{
		object->draw();
	}

	void GameScene::setCamera(uPtr<Camera> camera)
	{
		m_camera = std::move(camera);
	}

} // GE

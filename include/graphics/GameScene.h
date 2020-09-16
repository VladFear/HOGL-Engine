#pragma once

#include <forward_list>
#include <memory>

#include <graphics/GameObject.h>

class GameScene
{
	public:
		GameScene() = default;
		virtual ~GameScene() = default;
		void addGameObject(std::unique_ptr<GameObject> object);
		void renderScene() const;

	private:
		void renderObject(const std::unique_ptr<GameObject> & object) const;

	private:
		std::forward_list<std::unique_ptr<GameObject>> m_objects_list;
};

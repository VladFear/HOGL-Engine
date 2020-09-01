#pragma once

#include <forward_list>
#include <memory>

#include <graphics/Model.h>

class GameScene
{
	private:
		std::forward_list<std::shared_ptr<Model>> m_game_objects;

	public:
		GameScene();
		~GameScene();
		void addGameObject(Model * object);
		void renderScene() const;
};

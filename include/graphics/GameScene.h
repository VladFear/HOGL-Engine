#pragma once

#include <forward_list>
#include <memory>

#include <graphics/Model.h>

class GameScene
{
	public:
		GameScene();
		virtual ~GameScene();
		void addModel(Model * object);
		void renderScene() const;

	private:
		void renderObject(const std::unique_ptr<Model> & model) const;

	private:
		std::forward_list<std::unique_ptr<Model>> m_models_list;
};

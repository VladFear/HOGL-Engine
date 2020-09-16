#pragma once

#include <forward_list>
#include <memory>

#include <graphics/Model.h>

class GameScene
{
	public:
		GameScene() = default;
		virtual ~GameScene() = default;
		void addModel(std::unique_ptr<Model> object);
		void renderScene() const;

	private:
		void renderObject(const std::unique_ptr<Model> & model) const;

	private:
		std::forward_list<std::unique_ptr<Model>> m_models_list;
};

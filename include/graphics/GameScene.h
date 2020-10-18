#pragma once

#include <forward_list>
#include <memory>

#include "graphics/IDrawable.h"

namespace GE
{

	class GameScene
	{
		public:
			GameScene() = default;
			virtual ~GameScene() = default;

			// Actions
			void addGameObject(std::shared_ptr<IDrawable> object);
			void renderScene() const;

			// Getters
			[[nodiscard]] std::forward_list<std::shared_ptr<IDrawable>> & getGameObjectsList();

		private:
			void renderObject(std::shared_ptr<IDrawable> object) const;

		private:
			std::forward_list<std::shared_ptr<IDrawable>> m_objectsList;
	};

} // GE

#pragma once

#include <forward_list>

#include "core/Memory.h"
#include "graphics/IDrawable.h"

namespace GE
{

	class GameScene
	{
		public:
			GameScene() = default;
			virtual ~GameScene() = default;

			// Actions
			void addGameObject(Shared<IDrawable> object);
			void renderScene() const;

			// Getters
			[[nodiscard]] std::forward_list<Shared<IDrawable>> & getGameObjectsList();

		private:
			void renderObject(Shared<IDrawable> object) const;

		private:
			std::forward_list<Shared<IDrawable>> m_objectsList;
	};

} // GE

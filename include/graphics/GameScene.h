#pragma once

#include <forward_list>
#include <memory>

#include "graphics/GameObject.h"
#include "graphics/Camera.h"

namespace GE
{

	template <typename U>
	using uPtr = std::unique_ptr<U>;

	class GameScene
	{
		public:
			GameScene() = default;
			virtual ~GameScene() = default;

			// Actions
			void addGameObject(uPtr<GameObject> object);
			void renderScene() const;

			// Setters
			void setCamera(uPtr<Camera> camera);

		private:
			void renderObject(const uPtr<GameObject> & object) const;

		private:
			std::forward_list<uPtr<GameObject>> m_objectsList;
			uPtr<Camera> m_camera = nullptr;
	};

} // GE

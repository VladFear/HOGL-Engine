#pragma once

#include <iostream>

#include <graphics/GameScene.h>
#include <graphics/OpenGL/GLRenderSystem.h>

namespace GE
{

	template <typename U>
	using uPtr = std::unique_ptr<U>;

	template <typename S>
	using sPtr = std::shared_ptr<S>;

	using vec3 = glm::vec3;
	using mat4 = glm::mat4;

	enum class EngineAPI: int8_t
	{
		Undefined = -1,
		OpenGL = 0,
	};

	class GlobalEngine final
	{
		public:
			GlobalEngine(const EngineAPI api);
			~GlobalEngine() = default;
			void startGameLoop() const;
			void addGameObject(uPtr<GameObject> gameObject);

		private:
			void pollEvents() const;
			void render() const;

		private:
			uPtr<RenderSystem> m_renderSystem = nullptr;
			uPtr<GameScene>    m_gameScene = nullptr;
			EngineAPI m_api { EngineAPI::Undefined };
	};

} // GE

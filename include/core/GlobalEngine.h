#pragma once

#include <iostream>

#include "core/EngineArgs.h"

#include "graphics/GameScene.h"
#include "graphics/OpenGL/GLRenderSystem.h"
#include "graphics/OpenGL/GLWindow.h"

namespace GE
{

	template <typename U>
	using uPtr = std::unique_ptr<U>;

	template <typename S>
	using sPtr = std::shared_ptr<S>;

	using vec3 = glm::vec3;
	using mat4 = glm::mat4;

	class GlobalEngine final
	{
		public:
			GlobalEngine() = delete;
			explicit GlobalEngine(const EngineArgs & engineArgs);

			// Actions
			void startGameLoop() const;

			// Setters
			void setGameScene(uPtr<GameScene> gameScene);

		private:
			void pollEvents() const;
			void render() const;

		private:
			const EngineArgs    m_engineArgs;
			uPtr<IRenderSystem> m_renderSystem = nullptr;
			uPtr<GameScene>     m_gameScene    = nullptr;
	};

} // GE

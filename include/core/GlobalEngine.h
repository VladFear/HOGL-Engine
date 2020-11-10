#pragma once

#include "core/EngineArgs.h"
#include "graphics/IRenderSystem.h"

namespace GE
{

	class Camera;
	class GameScene;
	class IWindow;
	class GLRenderSystem;
	class GLWindow;

	class GlobalEngine final
	{
		public:
			GlobalEngine() = delete;
			explicit GlobalEngine(const EngineArgs & engineArgs);

			// Forbid copy semantics
			GlobalEngine(const GlobalEngine &)             = delete;
			GlobalEngine & operator=(const GlobalEngine &) = delete;

			// Actions
			void startGameLoop() const;

			// Setters
			void setGameScene(Shared<GameScene> gameScene);
			void setCamera(Shared<Camera> camera);

		private:
			class GlobalEngineImpl;
			Unique<GlobalEngineImpl> m_impl = nullptr;
	};

	class GlobalEngine::GlobalEngineImpl
	{
		public:
			GlobalEngineImpl(const EngineArgs & EngineArgs);

			// Forbid copy semantics
			GlobalEngineImpl(const GlobalEngineImpl &)             = delete;
			GlobalEngineImpl & operator=(const GlobalEngineImpl &) = delete;

			// Actions
			void startGameLoop() const;

			// Setters
			void setGameScene(Shared<GameScene> gameScene);
			void setCamera(Shared<Camera> camera);

		private:
			void initGLRenderSystem();
			void initGLFW();
			void initGLEW();
			void createGLFWwindow(const std::string & windowTitle,
			                      const uint windowWidth,
			                      const uint windowHeight);

		private:
			const EngineArgs m_engineArgs;

			Shared<IWindow>       m_window       = nullptr;
			Shared<Camera>        m_camera       = nullptr;
			Shared<GameScene>     m_gameScene    = nullptr;
			Unique<IRenderSystem> m_renderSystem = nullptr;
	};

} // GE

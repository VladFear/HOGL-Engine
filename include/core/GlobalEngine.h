#pragma once

#include <memory>

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
			void setGameScene(std::shared_ptr<GameScene> gameScene);
			void setCamera(std::shared_ptr<Camera> camera);

		private:
			class GlobalEngineImpl;
			std::unique_ptr<GlobalEngineImpl> m_impl = nullptr;
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
			void setGameScene(std::shared_ptr<GameScene> gameScene);
			void setCamera(std::shared_ptr<Camera> camera);

		private:
			void initGLRenderSystem();
			void initGLFW();
			void initGLEW();
			void createGLFWwindow(const std::string & windowTitle,
			                      const uint windowWidth,
			                      const uint windowHeight);

		private:
			const EngineArgs m_engineArgs;

			std::shared_ptr<IWindow>       m_window       = nullptr;
			std::shared_ptr<Camera>        m_camera       = nullptr;
			std::shared_ptr<GameScene>     m_gameScene    = nullptr;
			std::unique_ptr<IRenderSystem> m_renderSystem = nullptr;
	};

} // GE

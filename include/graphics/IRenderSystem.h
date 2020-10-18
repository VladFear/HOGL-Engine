#pragma once

#include <memory>

#include <glm/glm.hpp>

namespace GE
{

	class GameScene;
	class Camera;

	class IRenderSystem
	{
		public:
			virtual ~IRenderSystem() = default;

			virtual void render(std::shared_ptr<GameScene> gameScene,
			                    std::shared_ptr<Camera>    camera) = 0;
			virtual glm::mat4 createModelMatrix(const glm::vec3 & translation,
			                                    const glm::vec3 & rotation,
			                                    const glm::vec3 & scaling) = 0;
			virtual glm::mat4 createProjectionMatrix() = 0;
			virtual glm::mat4 createViewMatrix(const std::shared_ptr<Camera> & camera) = 0;
			virtual void prepareGameScene(std::shared_ptr<GameScene> gameScene) = 0;
	};

} // GE

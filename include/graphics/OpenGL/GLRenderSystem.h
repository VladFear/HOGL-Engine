#pragma once

#include <exception>

#include "core/Memory.h"
#include "graphics/IRenderSystem.h"
#include "graphics/Entity.h"
#include "graphics/GameScene.h"

namespace GE
{

	struct GLRenderProperties
	{
		float FIELD_OF_VIEW = 70.0f;
		float NEAR_PLANE    = 0.1f;
		float FAR_PLANE     = 1000.f;
	};

	class GLRenderSystem final : public IRenderSystem
	{
		public:
			void render(const GameScene & gameScene,
			            const Camera    & camera) override;
			glm::mat4 createModelMatrix(const glm::vec3 & translation,
			                            const glm::vec3 & rotation,
			                            const glm::vec3 & scaling) override;
			glm::mat4 createProjectionMatrix() override;
			glm::mat4 createViewMatrix(const Camera & camera)  override;
			void prepareGameScene(const GameScene & gameScene) override;

		private:
			GLRenderProperties m_glRenderProperties;
	};

} // GE

#include "graphics/OpenGL/GLRenderSystem.h"

namespace GE
{

	void GLRenderSystem::render(Shared<GameScene> gameScene,
	                            Shared<Camera>    camera)
	{
		glm::mat4 viewMatrix = createViewMatrix(camera);

		auto & gameObjectsList = gameScene->getGameObjectsList();
		for (const auto & gameObject : gameObjectsList)
		{
			auto entity = dynamic_cast<Entity*>(gameObject.get());
			entity->getShaderProgram()->apply();

			entity->getShaderProgram()->setViewMatrix(viewMatrix);

			auto translation = entity->getPosition();
			auto rotation    = entity->getRotation();
			auto scaling     = entity->getScalingFactor();

			auto modelMatrix = createModelMatrix(translation,
			                                     rotation,
			                                     scaling);

			entity->getShaderProgram()->setModelMatrix(modelMatrix);

			entity->draw();

			entity->getShaderProgram()->unapply();
		}
	}

	glm::mat4 GLRenderSystem::createModelMatrix(const glm::vec3 & translation,
	                                            const glm::vec3 & rotation,
	                                            const glm::vec3 & scaling)
	{
		glm::mat4 modelMatrix = glm::mat4(1.0f);

		modelMatrix = glm::translate(modelMatrix, translation);

		modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.x), vec3(1, 0, 0));
		modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.y), vec3(0, 1, 0));
		modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.z), vec3(0, 0, 1));

		modelMatrix = glm::scale(modelMatrix, scaling);

		return modelMatrix;
	}

	glm::mat4 GLRenderSystem::createProjectionMatrix()
	{
		// TODO: Remove hardcode of following variables.
		int width = 1366;
		int height = 768;

		mat4 projectionMatrix = glm::perspective(
			glm::radians(m_glRenderProperties.FIELD_OF_VIEW),
			static_cast<float>(width) / static_cast<float>(height),
			m_glRenderProperties.NEAR_PLANE,
			m_glRenderProperties.FAR_PLANE);

		return projectionMatrix;
	}

	glm::mat4 GLRenderSystem::createViewMatrix(const Shared<Camera> & camera)
	{
		return glm::lookAt(camera->getPosition(), glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	}

	void GLRenderSystem::prepareGameScene(Shared<GameScene> gameScene)
	{
		auto & gameObjectsList = gameScene->getGameObjectsList();

		glm::mat4 projectionMatrix = createProjectionMatrix();

		for (const auto & gameObject : gameObjectsList)
		{
			auto entity = dynamic_cast<Entity*>(gameObject.get());
			entity->getShaderProgram()->apply();
			entity->getShaderProgram()->setProjectionMatrix(projectionMatrix);
			entity->getShaderProgram()->unapply();
		}
	}

} // GE

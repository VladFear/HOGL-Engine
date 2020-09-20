#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <gtest/gtest.h>

#include <graphics/GlobalEngine.h>
#include <Entity.h>

namespace GEngine
{
	class GlobalEngineTestClass : public ::testing::Test
	{
		protected:
			static void SetUpTestCase()
			{
				try
				{
					// TODO: Make window invisible(not working yet)
					glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

					engine = std::make_unique<GlobalEngine>(EngineAPI::OpenGL_API,
					                                        "GlobalEngine",
					                                        720,
					                                        480);
					ASSERT_NE(engine, nullptr);
				}
				catch (const std::exception & e)
				{
					std::cerr << e.what() << '\n';
				}
			}

		protected:
			static std::unique_ptr<GlobalEngine> engine;
	};

	std::unique_ptr<GlobalEngine> GlobalEngineTestClass::engine = nullptr;

	TEST_F(GlobalEngineTestClass, EntityDefaultConstructorTest)
	{
		Entity entity;

		ASSERT_EQ(entity.getModel(), nullptr);
		ASSERT_EQ(entity.getShaderProgram(), nullptr);
		ASSERT_EQ(entity.getShaderProgramId(), 0);

		glm::vec3 position = entity.getPosition();
		EXPECT_FLOAT_EQ(position.x, 0.f);
		EXPECT_FLOAT_EQ(position.y, 0.f);
		EXPECT_FLOAT_EQ(position.z, 0.f);

		glm::vec3 rotation = entity.getRotation();
		EXPECT_FLOAT_EQ(rotation.x, 0.f);
		EXPECT_FLOAT_EQ(rotation.y, 0.f);
		EXPECT_FLOAT_EQ(rotation.z, 0.f);

		glm::vec3 scaling = entity.getScalingFactor();
		EXPECT_FLOAT_EQ(scaling.x, 1.f);
		EXPECT_FLOAT_EQ(scaling.y, 1.f);
		EXPECT_FLOAT_EQ(scaling.z, 1.f);
	}

	TEST_F(GlobalEngineTestClass, EntityMoveConstructorTest)
	{
		Entity entity;

		// Set transforms params
		auto position = glm::vec3(3.f, 4.f, 5.f);
		entity.setPosition(position);

		auto rotation = glm::vec3(10.f, 20.f, 50.f);
		entity.setRotation(rotation);

		auto scaling_factor = glm::vec3(2.f, 4.f, 5.f);
		entity.setScalingFactor(scaling_factor);

		entity.setShaderProgram(std::make_shared<ShaderProgram>());
		ASSERT_NE(entity.getShaderProgram(), nullptr);

		unsigned int shader_program_id = entity.getShaderProgramId();
		ASSERT_NE(shader_program_id, 0);

		// Get model should be nullptr, as no model set
		EXPECT_EQ(entity.getModel(), nullptr);

		Entity another_entity(std::move(entity));

		ASSERT_EQ(another_entity.getPosition(), position);
		ASSERT_EQ(another_entity.getRotation(), rotation);
		ASSERT_EQ(another_entity.getScalingFactor(), scaling_factor);

		ASSERT_NE(another_entity.getShaderProgram(), nullptr);
		ASSERT_NE(another_entity.getShaderProgramId(), 0);
		// Still should be nullptr
		ASSERT_EQ(another_entity.getModel(), nullptr);

		// Shader in entity must be nullptr after move
		ASSERT_EQ(entity.getShaderProgram(), nullptr);
		ASSERT_EQ(entity.getShaderProgramId(), 0);
		ASSERT_EQ(entity.getModel(), nullptr);
	}

	TEST_F(GlobalEngineTestClass, EntityMoveAssignmentOperatorTest)
	{
		Entity entity;

		// Set transforms params
		auto position = glm::vec3(3.f, 4.f, 5.f);
		entity.setPosition(position);

		auto rotation = glm::vec3(10.f, 20.f, 50.f);
		entity.setRotation(rotation);

		auto scaling_factor = glm::vec3(2.f, 4.f, 5.f);
		entity.setScalingFactor(scaling_factor);

		entity.setShaderProgram(std::make_shared<ShaderProgram>());
		ASSERT_NE(entity.getShaderProgram(), nullptr);

		unsigned int shader_program_id = entity.getShaderProgramId();
		ASSERT_NE(shader_program_id, 0);

		// Get model should be nullptr, as no model set
		EXPECT_EQ(entity.getModel(), nullptr);

		Entity another_entity = std::move(entity);

		ASSERT_EQ(another_entity.getPosition(), position);
		ASSERT_EQ(another_entity.getRotation(), rotation);
		ASSERT_EQ(another_entity.getScalingFactor(), scaling_factor);

		ASSERT_NE(another_entity.getShaderProgram(), nullptr);
		ASSERT_NE(another_entity.getShaderProgramId(), 0);
		// Still should be nullptr
		ASSERT_EQ(another_entity.getModel(), nullptr);

		// Shader in entity must be nullptr after move
		ASSERT_EQ(entity.getShaderProgram(), nullptr);
		ASSERT_EQ(entity.getShaderProgramId(), 0);
		ASSERT_EQ(entity.getModel(), nullptr);
	}

	TEST_F(GlobalEngineTestClass, EntityCopyConstructorTest)
	{
		Entity entity;

		// Set transforms params
		auto position = glm::vec3(3.f, 4.f, 5.f);
		entity.setPosition(position);

		auto rotation = glm::vec3(10.f, 20.f, 50.f);
		entity.setRotation(rotation);

		auto scaling_factor = glm::vec3(2.f, 4.f, 5.f);
		entity.setScalingFactor(scaling_factor);

		entity.setShaderProgram(std::make_shared<ShaderProgram>());
		ASSERT_NE(entity.getShaderProgram(), nullptr);

		unsigned int shader_program_id = entity.getShaderProgramId();
		ASSERT_NE(shader_program_id, 0);

		// Get model should be nullptr, as no model set
		EXPECT_EQ(entity.getModel(), nullptr);

		Entity another_entity(entity);

		ASSERT_EQ(another_entity.getPosition(), entity.getPosition());
		ASSERT_EQ(another_entity.getRotation(), entity.getRotation());
		ASSERT_EQ(another_entity.getScalingFactor(), entity.getScalingFactor());

		ASSERT_EQ(another_entity.getShaderProgram(), entity.getShaderProgram());
		ASSERT_EQ(another_entity.getShaderProgramId(), entity.getShaderProgramId());
		// Still should be nullptr
		EXPECT_EQ(another_entity.getModel(), nullptr);
		EXPECT_EQ(entity.getModel(), nullptr);
	}

	TEST_F(GlobalEngineTestClass, EntityCopyAssignmentOperatorTest)
	{
		Entity entity;

		// Set transforms params
		auto position = glm::vec3(3.f, 4.f, 5.f);
		entity.setPosition(position);

		auto rotation = glm::vec3(10.f, 20.f, 50.f);
		entity.setRotation(rotation);

		auto scaling_factor = glm::vec3(2.f, 4.f, 5.f);
		entity.setScalingFactor(scaling_factor);

		entity.setShaderProgram(std::make_shared<ShaderProgram>());
		ASSERT_NE(entity.getShaderProgram(), nullptr);

		unsigned int shader_program_id = entity.getShaderProgramId();
		ASSERT_NE(shader_program_id, 0);

		// Get model should be nullptr, as no model set
		EXPECT_EQ(entity.getModel(), nullptr);

		Entity another_entity = entity;

		ASSERT_EQ(another_entity.getPosition(), entity.getPosition());
		ASSERT_EQ(another_entity.getRotation(), entity.getRotation());
		ASSERT_EQ(another_entity.getScalingFactor(), entity.getScalingFactor());

		ASSERT_EQ(another_entity.getShaderProgram(), entity.getShaderProgram());
		ASSERT_EQ(another_entity.getShaderProgramId(), entity.getShaderProgramId());
		// Still should be nullptr
		EXPECT_EQ(another_entity.getModel(), nullptr);
		EXPECT_EQ(entity.getModel(), nullptr);
	}

	TEST_F(GlobalEngineTestClass, EntitySetShaderProgramTest)
	{
		Entity entity;

		ASSERT_EQ(entity.getShaderProgram(), nullptr);

		entity.setShaderProgram(std::make_shared<ShaderProgram>());
		ASSERT_NE(entity.getShaderProgram(), nullptr);
	}

	TEST_F(GlobalEngineTestClass, EntitySetPositionTest)
	{
		Entity entity;

		glm::vec3 position = entity.getPosition();
		EXPECT_FLOAT_EQ(position.x, 0.f);
		EXPECT_FLOAT_EQ(position.y, 0.f);
		EXPECT_FLOAT_EQ(position.z, 0.f);

		entity.setPosition(glm::vec3(4.f, 5.f, 6.f));
		position = entity.getPosition();
		ASSERT_FLOAT_EQ(position.x, 4.f);
		ASSERT_FLOAT_EQ(position.y, 5.f);
		ASSERT_FLOAT_EQ(position.z, 6.f);

		// Reassigning values
		entity.setPosition(glm::vec3(6.f, 7.f, 8.f));
		position = entity.getPosition();
		ASSERT_FLOAT_EQ(position.x, 6.f);
		ASSERT_FLOAT_EQ(position.y, 7.f);
		ASSERT_FLOAT_EQ(position.z, 8.f);
	}

	TEST_F(GlobalEngineTestClass, EntitySetRotationTest)
	{
		Entity entity;

		glm::vec3 rotation = entity.getRotation();
		EXPECT_FLOAT_EQ(rotation.x, 0.f);
		EXPECT_FLOAT_EQ(rotation.y, 0.f);
		EXPECT_FLOAT_EQ(rotation.z, 0.f);

		entity.setRotation(glm::vec3(4.f, 5.f, 6.f));
		rotation = entity.getRotation();
		ASSERT_FLOAT_EQ(rotation.x, 4.f);
		ASSERT_FLOAT_EQ(rotation.y, 5.f);
		ASSERT_FLOAT_EQ(rotation.z, 6.f);

		// Reassigning values
		entity.setRotation(glm::vec3(6.f, 7.f, 8.f));
		rotation = entity.getRotation();
		ASSERT_FLOAT_EQ(rotation.x, 6.f);
		ASSERT_FLOAT_EQ(rotation.y, 7.f);
		ASSERT_FLOAT_EQ(rotation.z, 8.f);
	}

	TEST_F(GlobalEngineTestClass, EntitySetScalingFactorTest)
	{
		Entity entity;

		glm::vec3 scaling = entity.getScalingFactor();
		EXPECT_FLOAT_EQ(scaling.x, 1.f);
		EXPECT_FLOAT_EQ(scaling.y, 1.f);
		EXPECT_FLOAT_EQ(scaling.z, 1.f);

		entity.setScalingFactor(glm::vec3(4.f, 5.f, 6.f));
		scaling = entity.getScalingFactor();
		ASSERT_FLOAT_EQ(scaling.x, 4.f);
		ASSERT_FLOAT_EQ(scaling.y, 5.f);
		ASSERT_FLOAT_EQ(scaling.z, 6.f);

		// Reassigning values
		entity.setScalingFactor(glm::vec3(6.f, 7.f, 8.f));
		scaling = entity.getScalingFactor();
		ASSERT_FLOAT_EQ(scaling.x, 6.f);
		ASSERT_FLOAT_EQ(scaling.y, 7.f);
		ASSERT_FLOAT_EQ(scaling.z, 8.f);
	}

	TEST_F(GlobalEngineTestClass, EntityRotateTest)
	{
		Entity entity;

		glm::vec3 rotation = entity.getRotation();
		EXPECT_FLOAT_EQ(rotation.x, 0.f);
		EXPECT_FLOAT_EQ(rotation.y, 0.f);
		EXPECT_FLOAT_EQ(rotation.z, 0.f);

		entity.rotate(glm::vec3(4.f, 5.f, 6.f));
		rotation = entity.getRotation();
		ASSERT_FLOAT_EQ(rotation.x, 4.f);
		ASSERT_FLOAT_EQ(rotation.y, 5.f);
		ASSERT_FLOAT_EQ(rotation.z, 6.f);

		entity.rotate(glm::vec3(6.f, 7.f, 8.f));
		rotation = entity.getRotation();
		ASSERT_FLOAT_EQ(rotation.x, 10.f);
		ASSERT_FLOAT_EQ(rotation.y, 12.f);
		ASSERT_FLOAT_EQ(rotation.z, 14.f);
	}

	TEST_F(GlobalEngineTestClass, EntityScaleTest)
	{
		Entity entity;

		glm::vec3 scaling = entity.getScalingFactor();
		EXPECT_FLOAT_EQ(scaling.x, 1.f);
		EXPECT_FLOAT_EQ(scaling.y, 1.f);
		EXPECT_FLOAT_EQ(scaling.z, 1.f);

		entity.scale(glm::vec3(4.f, 5.f, 6.f));
		scaling = entity.getScalingFactor();
		ASSERT_FLOAT_EQ(scaling.x, 4.f);
		ASSERT_FLOAT_EQ(scaling.y, 5.f);
		ASSERT_FLOAT_EQ(scaling.z, 6.f);

		entity.scale(glm::vec3(6.f, 7.f, 8.f));
		scaling = entity.getScalingFactor();
		ASSERT_FLOAT_EQ(scaling.x, 24.f);
		ASSERT_FLOAT_EQ(scaling.y, 35.f);
		ASSERT_FLOAT_EQ(scaling.z, 48.f);
	}

	TEST_F(GlobalEngineTestClass, EntityMoveTest)
	{
		Entity entity;

		glm::vec3 position = entity.getPosition();
		EXPECT_FLOAT_EQ(position.x, 0.f);
		EXPECT_FLOAT_EQ(position.y, 0.f);
		EXPECT_FLOAT_EQ(position.z, 0.f);

		entity.move(glm::vec3(4.f, 5.f, 6.f));
		position = entity.getPosition();
		ASSERT_FLOAT_EQ(position.x, 4.f);
		ASSERT_FLOAT_EQ(position.y, 5.f);
		ASSERT_FLOAT_EQ(position.z, 6.f);

		entity.move(glm::vec3(6.f, 7.f, 8.f));
		position = entity.getPosition();
		ASSERT_FLOAT_EQ(position.x, 10.f);
		ASSERT_FLOAT_EQ(position.y, 12.f);
		ASSERT_FLOAT_EQ(position.z, 14.f);
	}
}; // GEngine

int main(int argc, char ** argv)
{
	testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <gtest/gtest.h>

#include "core/GlobalEngine.h"
#include "core/EngineArgs.h"

#include "graphics/Entity.h"

using namespace GE;
using vec3 = glm::vec3;

class GlobalEngineTestClass : public ::testing::Test
{
	protected:
		static void SetUpTestCase()
		{
			try
			{
				// TODO: Make window invisible(not working yet)
				glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

				EngineArgs engineArgs =
					EngineArgsBuilder()
					.setEngineAPI(EngineAPI::OpenGL)
					.setWindowTitle("EntityClassTest")
					.build();

				m_engine = createUnique<GlobalEngine>(engineArgs);
				ASSERT_NE(m_engine, nullptr);
			}
			catch (const std::exception & e)
			{
				std::cerr << e.what() << '\n';
			}
		}

	protected:
		static Unique<GlobalEngine> m_engine;
};

Unique<GlobalEngine> GlobalEngineTestClass::m_engine = nullptr;

TEST_F(GlobalEngineTestClass, EntityDefaultConstructorTest)
{
	Entity entity;

	ASSERT_EQ(entity.getTexturedModel(), nullptr);
	ASSERT_EQ(entity.getShaderProgram(), nullptr);
	ASSERT_EQ(entity.getShaderProgramId(), 0);

	vec3 position = entity.getPosition();
	EXPECT_FLOAT_EQ(position.x, 0.f);
	EXPECT_FLOAT_EQ(position.y, 0.f);
	EXPECT_FLOAT_EQ(position.z, 0.f);

	vec3 rotation = entity.getRotation();
	EXPECT_FLOAT_EQ(rotation.x, 0.f);
	EXPECT_FLOAT_EQ(rotation.y, 0.f);
	EXPECT_FLOAT_EQ(rotation.z, 0.f);

	vec3 scaling = entity.getScalingFactor();
	EXPECT_FLOAT_EQ(scaling.x, 1.f);
	EXPECT_FLOAT_EQ(scaling.y, 1.f);
	EXPECT_FLOAT_EQ(scaling.z, 1.f);
}

TEST_F(GlobalEngineTestClass, EntityMoveConstructorTest)
{
	Entity entity;

	// Set transforms params
	auto position = vec3(3.f, 4.f, 5.f);
	entity.setPosition(position);

	auto rotation = vec3(10.f, 20.f, 50.f);
	entity.setRotation(rotation);

	auto scalingFactor = vec3(2.f, 4.f, 5.f);
	entity.setScalingFactor(scalingFactor);

	entity.setShaderProgram(createShared<ShaderProgram>());
	ASSERT_NE(entity.getShaderProgram(), nullptr);

	unsigned int shaderProgramId = entity.getShaderProgramId();
	ASSERT_NE(shaderProgramId, 0);

	// Get model should be nullptr, as no model set
	EXPECT_EQ(entity.getTexturedModel(), nullptr);

	Entity anotherEntity(std::move(entity));

	ASSERT_EQ(anotherEntity.getPosition(), position);
	ASSERT_EQ(anotherEntity.getRotation(), rotation);
	ASSERT_EQ(anotherEntity.getScalingFactor(), scalingFactor);

	ASSERT_NE(anotherEntity.getShaderProgram(), nullptr);
	ASSERT_NE(anotherEntity.getShaderProgramId(), 0);
	// Still should be nullptr
	ASSERT_EQ(anotherEntity.getTexturedModel(), nullptr);

	// Shader in entity must be nullptr after move
	ASSERT_EQ(entity.getShaderProgram(), nullptr);
	ASSERT_EQ(entity.getShaderProgramId(), 0);
	ASSERT_EQ(entity.getTexturedModel(), nullptr);
}

TEST_F(GlobalEngineTestClass, EntityMoveAssignmentOperatorTest)
{
	Entity entity;

	// Set transforms params
	auto position = vec3(3.f, 4.f, 5.f);
	entity.setPosition(position);

	auto rotation = vec3(10.f, 20.f, 50.f);
	entity.setRotation(rotation);

	auto scalingFactor = vec3(2.f, 4.f, 5.f);
	entity.setScalingFactor(scalingFactor);

	entity.setShaderProgram(createShared<ShaderProgram>());
	ASSERT_NE(entity.getShaderProgram(), nullptr);

	unsigned int shaderProgramId = entity.getShaderProgramId();
	ASSERT_NE(shaderProgramId, 0);

	// Get model should be nullptr, as no model set
	EXPECT_EQ(entity.getTexturedModel(), nullptr);

	Entity anotherEntity = std::move(entity);

	ASSERT_EQ(anotherEntity.getPosition(), position);
	ASSERT_EQ(anotherEntity.getRotation(), rotation);
	ASSERT_EQ(anotherEntity.getScalingFactor(), scalingFactor);

	ASSERT_NE(anotherEntity.getShaderProgram(), nullptr);
	ASSERT_NE(anotherEntity.getShaderProgramId(), 0);
	// Still should be nullptr
	ASSERT_EQ(anotherEntity.getTexturedModel(), nullptr);

	// Shader in entity must be nullptr after move
	ASSERT_EQ(entity.getShaderProgram(), nullptr);
	ASSERT_EQ(entity.getShaderProgramId(), 0);
	ASSERT_EQ(entity.getTexturedModel(), nullptr);
}

TEST_F(GlobalEngineTestClass, EntitySetShaderProgramTest)
{
	Entity entity;

	ASSERT_EQ(entity.getShaderProgram(), nullptr);

	entity.setShaderProgram(createShared<ShaderProgram>());
	ASSERT_NE(entity.getShaderProgram(), nullptr);
}

TEST_F(GlobalEngineTestClass, EntitySetPositionTest)
{
	Entity entity;

	vec3 position = entity.getPosition();
	EXPECT_FLOAT_EQ(position.x, 0.f);
	EXPECT_FLOAT_EQ(position.y, 0.f);
	EXPECT_FLOAT_EQ(position.z, 0.f);

	entity.setPosition(vec3(4.f, 5.f, 6.f));
	position = entity.getPosition();
	ASSERT_FLOAT_EQ(position.x, 4.f);
	ASSERT_FLOAT_EQ(position.y, 5.f);
	ASSERT_FLOAT_EQ(position.z, 6.f);

	// Reassigning values
	entity.setPosition(vec3(6.f, 7.f, 8.f));
	position = entity.getPosition();
	ASSERT_FLOAT_EQ(position.x, 6.f);
	ASSERT_FLOAT_EQ(position.y, 7.f);
	ASSERT_FLOAT_EQ(position.z, 8.f);
}

TEST_F(GlobalEngineTestClass, EntitySetRotationTest)
{
	Entity entity;

	vec3 rotation = entity.getRotation();
	EXPECT_FLOAT_EQ(rotation.x, 0.f);
	EXPECT_FLOAT_EQ(rotation.y, 0.f);
	EXPECT_FLOAT_EQ(rotation.z, 0.f);

	entity.setRotation(vec3(4.f, 5.f, 6.f));
	rotation = entity.getRotation();
	ASSERT_FLOAT_EQ(rotation.x, 4.f);
	ASSERT_FLOAT_EQ(rotation.y, 5.f);
	ASSERT_FLOAT_EQ(rotation.z, 6.f);

	// Reassigning values
	entity.setRotation(vec3(6.f, 7.f, 8.f));
	rotation = entity.getRotation();
	ASSERT_FLOAT_EQ(rotation.x, 6.f);
	ASSERT_FLOAT_EQ(rotation.y, 7.f);
	ASSERT_FLOAT_EQ(rotation.z, 8.f);
}

TEST_F(GlobalEngineTestClass, EntitySetScalingFactorTest)
{
	Entity entity;

	vec3 scaling = entity.getScalingFactor();
	EXPECT_FLOAT_EQ(scaling.x, 1.f);
	EXPECT_FLOAT_EQ(scaling.y, 1.f);
	EXPECT_FLOAT_EQ(scaling.z, 1.f);

	entity.setScalingFactor(vec3(4.f, 5.f, 6.f));
	scaling = entity.getScalingFactor();
	ASSERT_FLOAT_EQ(scaling.x, 4.f);
	ASSERT_FLOAT_EQ(scaling.y, 5.f);
	ASSERT_FLOAT_EQ(scaling.z, 6.f);

	// Reassigning values
	entity.setScalingFactor(vec3(6.f, 7.f, 8.f));
	scaling = entity.getScalingFactor();
	ASSERT_FLOAT_EQ(scaling.x, 6.f);
	ASSERT_FLOAT_EQ(scaling.y, 7.f);
	ASSERT_FLOAT_EQ(scaling.z, 8.f);
}

TEST_F(GlobalEngineTestClass, EntityRotateTest)
{
	Entity entity;

	vec3 rotation = entity.getRotation();
	EXPECT_FLOAT_EQ(rotation.x, 0.f);
	EXPECT_FLOAT_EQ(rotation.y, 0.f);
	EXPECT_FLOAT_EQ(rotation.z, 0.f);

	entity.rotate(vec3(4.f, 5.f, 6.f));
	rotation = entity.getRotation();
	ASSERT_FLOAT_EQ(rotation.x, 4.f);
	ASSERT_FLOAT_EQ(rotation.y, 5.f);
	ASSERT_FLOAT_EQ(rotation.z, 6.f);

	entity.rotate(vec3(6.f, 7.f, 8.f));
	rotation = entity.getRotation();
	ASSERT_FLOAT_EQ(rotation.x, 10.f);
	ASSERT_FLOAT_EQ(rotation.y, 12.f);
	ASSERT_FLOAT_EQ(rotation.z, 14.f);
}

TEST_F(GlobalEngineTestClass, EntityScaleTest)
{
	Entity entity;

	vec3 scaling = entity.getScalingFactor();
	EXPECT_FLOAT_EQ(scaling.x, 1.f);
	EXPECT_FLOAT_EQ(scaling.y, 1.f);
	EXPECT_FLOAT_EQ(scaling.z, 1.f);

	entity.scale(vec3(4.f, 5.f, 6.f));
	scaling = entity.getScalingFactor();
	ASSERT_FLOAT_EQ(scaling.x, 4.f);
	ASSERT_FLOAT_EQ(scaling.y, 5.f);
	ASSERT_FLOAT_EQ(scaling.z, 6.f);

	entity.scale(vec3(6.f, 7.f, 8.f));
	scaling = entity.getScalingFactor();
	ASSERT_FLOAT_EQ(scaling.x, 24.f);
	ASSERT_FLOAT_EQ(scaling.y, 35.f);
	ASSERT_FLOAT_EQ(scaling.z, 48.f);
}

TEST_F(GlobalEngineTestClass, EntityMoveTest)
{
	Entity entity;

	vec3 position = entity.getPosition();
	EXPECT_FLOAT_EQ(position.x, 0.f);
	EXPECT_FLOAT_EQ(position.y, 0.f);
	EXPECT_FLOAT_EQ(position.z, 0.f);

	entity.move(vec3(4.f, 5.f, 6.f));
	position = entity.getPosition();
	ASSERT_FLOAT_EQ(position.x, 4.f);
	ASSERT_FLOAT_EQ(position.y, 5.f);
	ASSERT_FLOAT_EQ(position.z, 6.f);

	entity.move(vec3(6.f, 7.f, 8.f));
	position = entity.getPosition();
	ASSERT_FLOAT_EQ(position.x, 10.f);
	ASSERT_FLOAT_EQ(position.y, 12.f);
	ASSERT_FLOAT_EQ(position.z, 14.f);
}

int main(int argc, char ** argv)
{
	testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}

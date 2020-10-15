#include "TestApplication.h"

TestApplication::TestApplication(std::unique_ptr<GE::GlobalEngine> globalEngine) :
	GE::GameApplication(std::move(globalEngine))
{
	 init();
}

void TestApplication::init()
{
	auto vshader = GE::Shader::ShaderBuilder()
		.setSource("examples/TestApplication/vertexShader.glsl")
		.create(GL_VERTEX_SHADER);

	auto fshader = GE::Shader::ShaderBuilder()
		.setSource("examples/TestApplication/fragmentShader.glsl")
		.create(GL_FRAGMENT_SHADER);

	auto triangle = std::make_shared<GE::ShaderProgram>();
	triangle->attachShader(vshader);
	triangle->attachShader(fshader);
	triangle->setValidationStrategy(std::make_shared<GE::ValidationDefaultStrategy>());
	triangle->compile();

	float vertices[] =
	{
		-0.75f, 0.0f, 0.0f, // Left
		-0.25f, 0.0f, 0.0f, // Right
		-0.50f, 0.5f, 0.0f  // Top
	};

	unsigned int indexes[] =
	{
		2, 0, 1
	};

	float vertices1[] =
	{
		 0.25f, 0.0f, 0.0f, // Left
		 0.75f, 0.0f, 0.0f, // Right
		 0.50f, 0.5f, 0.0f  // Top
	};

	auto model1 = GE::Model::ModelBuilder()
		.addVertexBuffer(vertices, std::size(vertices))
		.addIndexBuffer(indexes, std::size(indexes))
		.create();

	auto model2 = GE::Model::ModelBuilder()
		.addVertexBuffer(vertices1, std::size(vertices1))
		.addIndexBuffer(indexes, std::size(indexes))
		.create();

	auto entity1 =
		std::make_unique<GE::Entity>(model1,
		                             triangle,
		                             glm::vec3(-0.5f, 0.25f, -1.5f),
		                             glm::vec3(0.f),
		                             glm::vec3(1.f));

	auto entity2 =
		std::make_unique<GE::Entity>(model2,
		                             triangle,
		                             glm::vec3(-0.25f, 0.25f, -1.5f),
		                             glm::vec3(0.f),
		                             glm::vec3(1.f));

	auto gameScene = std::make_unique<GE::GameScene>();
	gameScene->addGameObject(std::move(entity1));
	gameScene->addGameObject(std::move(entity2));

	m_globalEngine->setGameScene(std::move(gameScene));
}

void TestApplication::startGameLoop()
{
	m_globalEngine->startGameLoop();
}

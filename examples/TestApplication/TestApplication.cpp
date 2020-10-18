#include "TestApplication.h"

TestApplication::TestApplication(std::unique_ptr<GE::GlobalEngine> globalEngine) :
	GE::GameApplication(std::move(globalEngine))
{
	 init();
}

void TestApplication::init()
{
	auto vshader = GE::Shader::ShaderBuilder()
		.setSource("examples/TestApplication/shaders/vertexShader.glsl")
		.setValidationStrategy(std::make_shared<GE::ValidationDefaultStrategy>())
		.setShaderType(GE::ShaderType::VertexShader)
		.build();

	auto fshader = GE::Shader::ShaderBuilder()
		.setSource("examples/TestApplication/shaders/fragmentShader.glsl")
		.setValidationStrategy(std::make_shared<GE::ValidationDefaultStrategy>())
		.setShaderType(GE::ShaderType::FragmentShader)
		.build();

	auto shaderProgram = std::make_shared<GE::ShaderProgram>();
	shaderProgram->attachShader(vshader);
	shaderProgram->attachShader(fshader);
	shaderProgram->setValidationStrategy(std::make_shared<GE::ValidationDefaultStrategy>());
	shaderProgram->compile();

	float vertices[] =
	{
		-0.75f, -0.75f, 0.0f, // Left Bot  0
		-0.75f,  0.75f, 0.0f, // Left Top  1
		 0.75f, -0.75f, 0.0f, // Right Bot 2
		 0.75f,  0.75f, 0.0f  // Right Top 3
	};

	uint indexes[] =
	{
		2, 3, 0, 0, 1, 3
	};

	float textCoords[] =
	{
		0.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 0.0f,
		1.0f, 1.0f
	};

	auto cubeModel = GE::Model::ModelBuilder()
		.addVertexBuffer(vertices, std::size(vertices))
		.addIndexBuffer(indexes, std::size(indexes))
		.addTextureData(textCoords, std::size(textCoords))
		.build();

	auto wallTexture = std::make_shared<GE::GLTexture>("examples/TestApplication/res/wall.jpg");

	auto cubeTexturedModel =
		std::make_shared<GE::GLTexturedModel>(cubeModel, wallTexture);

	auto cubeEntity =
		std::make_shared<GE::Entity>(cubeTexturedModel,
		                             shaderProgram,
		                             glm::vec3(0.0f, 0.0f, -1.5f),
		                             glm::vec3(0.f),
		                             glm::vec3(1.f));

	auto gameScene = std::make_shared<GE::GameScene>();
	gameScene->addGameObject(cubeEntity);

	m_globalEngine->setGameScene(gameScene);

	auto camera = std::make_shared<GE::Camera>(glm::vec3(0.0f, 0.0f, 0.001f));

	m_globalEngine->setCamera(camera);
}

void TestApplication::startGameLoop()
{
	m_globalEngine->startGameLoop();
}

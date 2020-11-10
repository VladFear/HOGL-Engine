#include "TestApplication.h"

TestApplication::TestApplication(Unique<GlobalEngine> globalEngine) :
	GameApplication(std::move(globalEngine))
{
	 init();
}

void TestApplication::init()
{
	Shared<Shader> vshader = Shader::ShaderBuilder()
		.setSource("examples/TestApplication/shaders/vertexShader.glsl")
		.setValidationStrategy(createShared<ValidationDefaultStrategy>())
		.setShaderType(ShaderType::VertexShader)
		.build();

	Shared<Shader> fshader = Shader::ShaderBuilder()
		.setSource("examples/TestApplication/shaders/fragmentShader.glsl")
		.setValidationStrategy(createShared<ValidationDefaultStrategy>())
		.setShaderType(ShaderType::FragmentShader)
		.build();

	auto shaderProgram = createShared<ShaderProgram>();
	shaderProgram->attachShader(vshader);
	shaderProgram->attachShader(fshader);
	shaderProgram->setValidationStrategy(createShared<ValidationDefaultStrategy>());
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

	Shared<Model> cubeModel = Model::ModelBuilder()
		.addVertexBuffer(vertices, std::size(vertices))
		.addIndexBuffer(indexes, std::size(indexes))
		.addTextureData(textCoords, std::size(textCoords))
		.build();

	auto wallTexture = createShared<GLTexture>("examples/TestApplication/res/wall.jpg");

	auto cubeTexturedModel =
		createShared<GLTexturedModel>(cubeModel, wallTexture);

	auto cubeEntity =
		createShared<Entity>(cubeTexturedModel,
		                              shaderProgram,
		                              glm::vec3(0.0f, 0.0f, -1.5f),
		                              glm::vec3(0.f),
		                              glm::vec3(1.f));

	auto gameScene = createShared<GameScene>();
	gameScene->addGameObject(cubeEntity);

	m_globalEngine->setGameScene(gameScene);

	auto camera = createShared<Camera>(glm::vec3(0.0f, 0.0f, 0.001f));

	m_globalEngine->setCamera(camera);
}

void TestApplication::startGameLoop()
{
	m_globalEngine->startGameLoop();
}

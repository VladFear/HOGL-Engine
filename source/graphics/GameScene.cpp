#include <graphics/GameScene.h>

GameScene::GameScene()
{

}

GameScene::~GameScene()
{

}

void GameScene::addModel(Model * model)
{
	m_models_list.push_front(std::unique_ptr<Model>(model));
}

void GameScene::renderScene() const
{
	for (const auto& model : m_models_list)
		renderObject(model);
}

void GameScene::renderObject(const std::unique_ptr<Model> & model) const
{
	// TODO: Currently class Model doesn't have method getShaderProgramId.
	// glUseProgram(model->getShaderProgramId());
	model->draw();
	// glUseProgram(0);
}

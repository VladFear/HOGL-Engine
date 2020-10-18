#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <memory>

#include "core/GameApplication.h"
#include "core/EngineArgs.h"
#include "core/GlobalEngine.h"

#include "graphics/Entity.h"
#include "graphics/Camera.h"
#include "graphics/ShaderProgram.h"
#include "graphics/GameScene.h"
#include "graphics/ValidationDefaultStrategy.h"
#include "graphics/OpenGL/GLTexture.h"
#include "graphics/OpenGL/GLTexturedModel.h"

class TestApplication : public GE::GameApplication
{
	public:
		explicit TestApplication(std::unique_ptr<GE::GlobalEngine> globalEngine);

		// Actions
		void startGameLoop() override;

	protected:
		void init() override;
};

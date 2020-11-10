#pragma once

#include <fstream>
#include <iostream>
#include <string>

#include "core/Memory.h"
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

using namespace GE;

class TestApplication : public GameApplication
{
	public:
		explicit TestApplication(Unique<GlobalEngine> globalEngine);

		// Actions
		void startGameLoop() override;

	protected:
		void init() override;
};

#pragma once

#include <graphics/RenderEngine.h>
#include <graphics/GameScene.h>

class GlobalEngine final
{
	public:
		GlobalEngine(EngineAPI api);
		~GlobalEngine() = default;
		void startGameLoop() const;
		void addGameObject(std::unique_ptr<GameObject> game_object);

	private:
		void pollEvents() const;
		void render() const;

	private:
		std::unique_ptr<RenderEngine> m_render_engine = nullptr;
		std::unique_ptr<GameScene> m_game_scene = nullptr;
};

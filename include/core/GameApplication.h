#pragma once

#include "core/GlobalEngine.h"

namespace GE
{

	class GameApplication
	{
		public:
			GameApplication() = delete;
			virtual ~GameApplication() = default;

			explicit GameApplication(std::unique_ptr<GlobalEngine> globalEngine) :
				m_globalEngine(std::move(globalEngine))
			{ }

			// Actions
			virtual void startGameLoop() = 0;

		protected:
			virtual void init() = 0;

		protected:
			std::unique_ptr<GlobalEngine> m_globalEngine = nullptr;
	};

} // GE

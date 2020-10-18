#pragma once

#include <string>

namespace GE
{

	enum class EngineAPI: int8_t
	{
		Undefined = -1,
		OpenGL = 0,
	};

	struct EngineArgs
	{
		struct EngineArgsBuilder;

		// Should be initialized with builder
		EngineArgs() = delete;
		EngineArgs(const EngineAPI   engineAPI,
		           const std::string windowTitle,
		           const uint        windowWidth,
		           const uint        windowHeight) :
			engineAPI    { engineAPI },
			windowTitle  { windowTitle },
			windowWidth  { windowWidth },
			windowHeight { windowHeight }
		{ }

		EngineAPI   engineAPI;
		std::string windowTitle;
		uint        windowWidth;
		uint        windowHeight;
	};

	class EngineArgsBuilder
	{
		public:
			EngineArgsBuilder()
			{ }

			EngineArgsBuilder & setEngineAPI(const EngineAPI & engineAPI)
			{
				m_engineAPI = engineAPI;
				return *this;
			}

			EngineArgsBuilder & setWindowTitle(const std::string & windowTitle)
			{
				m_windowTitle = windowTitle;
				return *this;
			}

			EngineArgsBuilder & setWindowWidth(const uint windowWidth)
			{
				m_windowWidth = windowWidth;
				return *this;
			}

			EngineArgsBuilder & setWindowHeight(const uint windowHeight)
			{
				m_windowHeight = windowHeight;
				return *this;
			}

			[[nodiscard]] EngineArgs build()
			{
				return EngineArgs(m_engineAPI,
				                  m_windowTitle,
				                  m_windowWidth,
				                  m_windowHeight);
			}

		private:
			EngineAPI   m_engineAPI    { EngineAPI::Undefined };
			std::string m_windowTitle  { "GlobalEngine" };
			uint        m_windowWidth  { 1280 };
			uint        m_windowHeight { 720 };
	};

} // GE

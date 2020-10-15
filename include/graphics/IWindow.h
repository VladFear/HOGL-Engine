#pragma once

#include <string>

namespace GE
{

	class IWindow
	{
		public:
			IWindow(const std::string & title,
			        const uint width,
			        const uint height) :
				m_title  { title },
				m_width  { width },
				m_height { height }
			{ }

			virtual ~IWindow() = default;

			// Setters
			void setVisibility(const bool visibility)
			{
				m_visibility = visibility;
			}

			// Getters
			uint getWidth()  const
			{
				return m_width;
			}

			uint getHeight() const
			{
				return m_height;
			}

			bool isVisible() const
			{
				return m_visibility;
			}

		protected:
			virtual void createWindow() = 0;

		protected:
			std::string m_title;
			uint        m_width;
			uint        m_height;
			bool        m_visibility = true;
	};

} // GE

#pragma once

namespace GE
{

	class IDrawable
	{
		public:
			virtual ~IDrawable() = default;

			virtual void draw() const = 0;

			void setVisibility(bool visibility)
			{
				m_visibility = visibility;
			}

			bool isVisible() const
			{
				return m_visibility;
			}

		protected:
			bool m_visibility = true;
	};

} // GE

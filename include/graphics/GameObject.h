#pragma once

namespace GE
{

	class GameObject
	{
		public:
			virtual ~GameObject() = default;

			// Actions
			virtual void draw() const = 0;

			// Setters
			void setVisibility(bool visible)
			{
				m_visible = visible;
			}

		protected:
			bool m_visible = true;
	};

} // GE

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
			void setVisibility(bool visibility)
			{
				m_visibility = visibility;
			}

		protected:
			bool m_visibility = true;
	};

} // GE

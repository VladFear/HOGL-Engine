#pragma once

class GameObject
{
	public:
		virtual ~GameObject() = default;
		virtual void draw() const = 0;
		void setVisibility(bool visibility) { m_visible = visibility; };

	protected:
		bool m_visible = true;
};

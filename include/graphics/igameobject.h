#pragma once

class IGameObject
{
	public:
		IGameObject();
		virtual void draw() const = 0;
		void setVisibility(bool visibility) { m_visible = visibility; };

	protected:
		bool m_visible = true;
};

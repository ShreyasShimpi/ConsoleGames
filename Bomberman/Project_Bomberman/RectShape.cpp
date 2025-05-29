// internal includes
#include "RectShape.h"

CRectShape::CRectShape()
{
}

void CRectShape::SetSpriteScale(sf::Vector2f scale)
{
	m_sprite.setScale(scale);
}

void CRectShape::SetPosition(sf::Vector2f position)
{
	if (std::isnan(position.x) || std::isnan(position.y))
	{
		return;
	}
	m_position = position;
	m_sprite.setPosition(m_position);
}

void CRectShape::Render(sf::RenderTarget& target)
{
	target.draw(m_sprite);
}

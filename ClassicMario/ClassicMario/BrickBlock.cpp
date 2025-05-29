#include "BrickBlock.h"

CBrickBlock::CBrickBlock(sf::Vector2f position, CAssetManager& assetManager)
{
	m_brickBlockSprite = assetManager.GetSprite(EItems::Brick);
	m_brickBlockSprite.setPosition(position);	
}

void CBrickBlock::Draw(sf::RenderTarget& target)
{
	target.draw(m_brickBlockSprite);
}

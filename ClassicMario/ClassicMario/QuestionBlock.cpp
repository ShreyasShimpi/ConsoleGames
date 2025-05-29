// internal includes
#include "QuestionBlock.h"
#include "AssetManager.h"
#include "CAnimationManager.h"
#include "Collectible.h"

// Constructor
CQuestionBlock::CQuestionBlock(sf::Vector2f position, CAssetManager& assetManager, CAnimationManager& animationManager, ECollectible collectible)
{
	m_animationManager = &animationManager;
	m_assetManager = &assetManager;
	m_collectibleInside = collectible;
	m_isOpened = false;
	m_coinFlag = true;
	m_timePassed = 0.0f;

	// setting the sprites for question block
	m_emptyBlockSprite = assetManager.GetSprite(EItems::Empty_Block);
	m_questionBlockSprite = assetManager.GetSprite(EItems::Question_Block_1);
	m_questionBlockCoinSprite = assetManager.GetSprite(EItems::Block_Coin_1);
	
	// setting the position for the sprites
	m_position = position;
	m_emptyBlockSprite.setPosition(m_position);
	m_questionBlockSprite.setPosition(m_position);
	m_questionBlockCoinSprite.setPosition(m_position);
}

// opens the question block to reveal whats inside it
void CQuestionBlock::OpenQuestionBlock()
{
	m_isOpened = true;
}

// setter : collectible state
void CQuestionBlock::SetCollectibleState(EMarioStage& stage)
{
	if(stage == EMarioStage::small && m_collectibleInside == ECollectible::FireFlower)
	{
		m_collectibleInside = ECollectible::Growth_Power;
	}
}

// updates the question block (specifically  animation)
void CQuestionBlock::Update(const float& deltaTime)
{
	// if question block is not opened , we can continue running the flickering animation
	if (!m_isOpened)
	{
		m_animationManager->QuestionBlockAnimation(m_questionBlockSprite, deltaTime);
		m_questionBlockSprite.setPosition(m_position);
	}
	// if the question block is triggered,then make the block empty
	else
	{
		m_questionBlockSprite = m_emptyBlockSprite;
		m_questionBlockSprite.setPosition(m_position);
		
		// if the collectible inside the block is coin (most of the question blocks), 
		// then the coin bounces of from the brick and collected by the player
		// for coin to appear on top
		if(m_collectibleInside == ECollectible::Coin)
		{
			// spawning animation
			if (m_timePassed < 1.f)
			{
				m_timePassed += deltaTime;
				/*m_position.y += 32 * deltaTime;*/
				m_questionBlockCoinSprite.move(0, -32 * deltaTime);
			}
			else
			{
				m_coinFlag = false;
			}
		}
	}
}

void CQuestionBlock::Draw(sf::RenderTarget& target)
{
	// coin is only displayed is flag is true. (until the animation gets over)
	if (m_coinFlag)
	{
		target.draw(m_questionBlockCoinSprite);
	}
	target.draw(m_questionBlockSprite);
}


#include "CAnimationManager.h"
#include "SFML/Graphics.hpp"

/*
LEVEL 1 -   Small mario
LEVEL 2 -   Big Mario
LEVEL 3 -   Mario with Fire Power
*/


// loading all the sprites needed for animation to different variables using asset manager
CAnimationManager::CAnimationManager()
{

	// assigning mario state and direction 
	m_marioStage = EMarioStage::small;
	m_marioDirection = EMarioDirection::right;

	// mario damage sprite // level 2 to level 1
	m_marioDamage.push_back(m_assetManager.GetSprite(EItems::Mario_Big_Standing_R));
	m_marioDamage.push_back(m_assetManager.GetSprite(EItems::Mario_Grown));
	m_marioDamage.push_back(m_assetManager.GetSprite(EItems::Mario_Standing_R));

	// mario growth sprite
	m_marioGrowth.push_back(m_assetManager.GetSprite(EItems::Mario_Standing_R));
	m_marioGrowth.push_back(m_assetManager.GetSprite(EItems::Mario_Grown));
	m_marioGrowth.push_back(m_assetManager.GetSprite(EItems::Mario_Big_Standing_R));

	// mario power up fire power 
	m_marioFirePower.push_back(m_assetManager.GetSprite(EItems::Mario_Big_Standing_R));
	m_marioFirePower.push_back(m_assetManager.GetSprite(EItems::Mario_Fire_Standing_R));

	// death mario sprite
	m_marioDeath = m_assetManager.GetSprite(EItems::Mario_Death_R);

	// standing or static 
	m_marioStatic = m_assetManager.GetSprite(EItems::Mario_Standing_R);

	// running right
	m_marioMovement.push_back(m_assetManager.GetSprite(EItems::Mario_Running_R_1));
	m_marioMovement.push_back(m_assetManager.GetSprite(EItems::Mario_Running_R_2));
	m_marioMovement.push_back(m_assetManager.GetSprite(EItems::Mario_Running_R_3));

	// dragging 
	m_marioDrag = m_assetManager.GetSprite(EItems::Mario_Drag_R);
	m_marioJump = m_assetManager.GetSprite(EItems::Mario_Jump_R);

	// mario damage sprite // level 3 to level 1
	m_marioDamageLevelThree.push_back(m_assetManager.GetSprite(EItems::Mario_Fire_Standing_R));
	m_marioDamageLevelThree.push_back(m_assetManager.GetSprite(EItems::Mario_Big_Standing_R));
	m_marioDamageLevelThree.push_back(m_assetManager.GetSprite(EItems::Mario_Grown));
	m_marioDamageLevelThree.push_back(m_assetManager.GetSprite(EItems::Mario_Standing_R));

	// enemy
	m_goombaMovement.push_back(m_assetManager.GetSprite(EItems::Goomba_1));
	m_goombaMovement.push_back(m_assetManager.GetSprite(EItems::Goomba_2));

	m_koopaTroopaMovement.push_back(m_assetManager.GetSprite(EItems::Turtle_L_1));
	m_koopaTroopaMovement.push_back(m_assetManager.GetSprite(EItems::Turtle_L_2));

	// new things
	m_goombaStomped = m_assetManager.GetSprite(EItems::Goomba_Death);
	m_koopaTroopaShellState = m_assetManager.GetSprite(EItems::Turtle_Shell);


	//Question block
	m_questionBlocks.push_back(m_assetManager.GetSprite(EItems::Question_Block_1));
	m_questionBlocks.push_back(m_assetManager.GetSprite(EItems::Question_Block_2));
	m_questionBlocks.push_back(m_assetManager.GetSprite(EItems::Question_Block_3));
	m_questionBlocks.push_back(m_assetManager.GetSprite(EItems::Question_Block_4));

	//Fireball explosion
	m_fireBallExplosion.push_back(m_assetManager.GetSprite(EItems::Fire_Ball_Explosion_1));
	m_fireBallExplosion.push_back(m_assetManager.GetSprite(EItems::Fire_Ball_Explosion_2));
	m_fireBallExplosion.push_back(m_assetManager.GetSprite(EItems::Fire_Ball_Explosion_3));


	m_fireBall = m_assetManager.GetSprite(EItems::Fire_Ball);
	m_mushroom = m_assetManager.GetSprite(EItems::Mushroom_Red);
	m_oneUp = m_assetManager.GetSprite(EItems::Mushroom_Green);

	// flower 
	m_fireFlower.push_back(m_assetManager.GetSprite(EItems::Fire_Flower_1));
	m_fireFlower.push_back(m_assetManager.GetSprite(EItems::Fire_Flower_2));
	m_fireFlower.push_back(m_assetManager.GetSprite(EItems::Fire_Flower_3));
	m_fireFlower.push_back(m_assetManager.GetSprite(EItems::Fire_Flower_4));

	// star
	m_star.push_back(m_assetManager.GetSprite(EItems::Star_1));
	m_star.push_back(m_assetManager.GetSprite(EItems::Star_2));
	m_star.push_back(m_assetManager.GetSprite(EItems::Star_3));
	m_star.push_back(m_assetManager.GetSprite(EItems::Star_4));

	// coin
	m_coin.push_back(m_assetManager.GetSprite(EItems::Coin_1));
	m_coin.push_back(m_assetManager.GetSprite(EItems::Coin_2));
	m_coin.push_back(m_assetManager.GetSprite(EItems::Coin_3));
	m_coin.push_back(m_assetManager.GetSprite(EItems::Coin_4));

}

// show right animation
void CAnimationManager::RightMarioAnimation(sf::Sprite& mario, const float& deltaTime)
{
	// calculating the time between changing of two sprites
	float nextFrameDelay;
	nextFrameDelay = 0.50f / m_marioMovement.size();

	m_totalTime += deltaTime; // getting total time 

	// casting it into it and taking modulo to get values between the 0 and size of marioMovement vector
	int index = static_cast<int>(m_totalTime / nextFrameDelay) % m_marioMovement.size();

	mario = m_marioMovement[index]; // assigning sprite according to the index
	m_marioDirection = EMarioDirection::right; // changing direction

	//setting origin and scale
	mario.setOrigin(0.f, 0.f); 
	mario.setScale(1.f, 1.f);
}

// show left animation
void CAnimationManager::LeftMarioAnimation(sf::Sprite& mario, const float& deltaTime)
{
	m_totalTime += deltaTime;
	float nextFrameDelay;
	nextFrameDelay = 0.50f / m_marioMovement.size();
	int index = static_cast<int>(m_totalTime / nextFrameDelay) % m_marioMovement.size();
	mario = m_marioMovement[index];


	mario.setOrigin(16, 0); // setting origin to 16 ( width of sprites )
	mario.setScale(-1.0f, 1.0f); // inverting the sprite 
	m_marioDirection = EMarioDirection::left;
}

// grow up mario from big state to firepower state
sf::Sprite CAnimationManager::AnimationFirePower(const float& deltaTime)
{
	sf::Sprite mario;
	if (m_marioStage == EMarioStage::big) // go inside loop only when it is in big state
	{
		m_totalTime += deltaTime;
		float nextFrameDelay;
		nextFrameDelay = 1.50f / m_marioFirePower.size();
		int index = static_cast<int>(m_totalTime / nextFrameDelay) % m_marioFirePower.size();
		mario = m_marioFirePower[index];
	}
	return mario;
}

// converting small mario to big mario
sf::Sprite CAnimationManager::AnimationGrowth(const float& deltaTime)
{
	sf::Sprite mario;
	m_totalTime += deltaTime;
	float nextFrameDelay;
	nextFrameDelay = 1.0f / m_marioGrowth.size();
	int index = static_cast<int>(m_totalTime / nextFrameDelay) % m_marioGrowth.size();
	mario = m_marioGrowth[index];

	// mario sprites have different heights so he have to adjust position according to that
	if (index == 0)
	{
		mario.setPosition(0.0f, 16.0f);
	}
	return mario;
}

// converting big mario to small mario
sf::Sprite CAnimationManager::AnimationDamage(const float& deltaTime)
{
	sf::Sprite mario;
	if (m_marioStage == EMarioStage::big)
	{
		m_totalTime += deltaTime;
		float nextFrameDelay;
		nextFrameDelay = 1.0f / m_marioDamage.size();
		int index = static_cast<int>(m_totalTime / nextFrameDelay) % m_marioDamage.size();
		mario = m_marioDamage[index];
		if (index == 2)
		{
			mario.setPosition(0.0f, 16.0f);
		}
	}
	return mario;
}


// set death sprite
void CAnimationManager::AnimationDeath(sf::Sprite& mario)
{
	mario = m_marioDeath;
}

// set standing right mario sprite
void CAnimationManager::SetMarioRightStatic(sf::Sprite& mario)
{
	mario = m_marioStatic;
	mario.setOrigin(0.f, 0.f);
	mario.setScale(1.f, 1.f);
}

// set standing left mario sprite
void CAnimationManager::SetMarioLeftStatic(sf::Sprite& mario)
{
	mario = m_marioStatic;
	mario.setOrigin(16, 0);
	mario.setScale(-1.0f, 1.0f);
}

// set drag right mario sprite ( when direction of velocity changes )
void CAnimationManager::SetMarioRightDrag(sf::Sprite& mario)
{
	mario = m_marioDrag;
	mario.setOrigin(0.f, 0.f);
	mario.setScale(1.f, 1.f);
}

// set drag left mario sprite ( when direction of velocity changes )
void CAnimationManager::SetMarioLeftDrag(sf::Sprite& mario)
{
	mario = m_marioDrag;
	mario.setOrigin(16.0f, 0);
	mario.setScale(-1.0f, 1.0f);
}

// set mario right jump sprite
void CAnimationManager::SetMarioRightJump(sf::Sprite& mario, bool jumping)
{
	if (jumping == true)
	{
		mario = m_marioJump;
	}
	else
	{
		mario = m_marioStatic;
	}
	mario.setOrigin(0.f, 0.f);
	mario.setScale(1.f, 1.f);
}

// set mario left jump sprite
void CAnimationManager::SetMarioLeftJump(sf::Sprite& mario, bool jumping)
{
	if (jumping == true)
	{
		mario = m_marioJump;
	}
	else
	{
		mario = m_marioStatic;
	}
	mario = m_marioJump;
	mario.setOrigin(16.0f, 0);
	mario.setScale(-1.0f, 1.0f);
}

// // set mario right crouch sprite
void CAnimationManager::SetMarioRightCrouch(sf::Sprite& mario)
{
	mario = m_marioCrouch;
	mario.setOrigin(0.f, 0.f);
	mario.setScale(1.f, 1.f);
}

// set mario left crouch sprite
void CAnimationManager::SetMarioLeftCrouch(sf::Sprite& mario)
{
	mario = m_marioCrouch;
	mario.setOrigin(16.0f, 0);
	mario.setScale(-1.0f, 1.0f);
}

//// animation damage when goes from fire power to big mario
sf::Sprite CAnimationManager::AnimationDamageLevelThreeToLevelOne(const float& deltaTime)
{
	sf::Sprite mario;
	if (m_marioStage == EMarioStage::big || m_marioStage == EMarioStage::firepower)
	{
		m_totalTime += deltaTime;
		float nextFrameDelay;
		nextFrameDelay = 1.0f / m_marioDamageLevelThree.size();
		int index = static_cast<int>(m_totalTime / nextFrameDelay) % m_marioDamageLevelThree.size();
		mario = m_marioDamageLevelThree[index];
		if (index == 3)
		{
			mario.setPosition(0.0f, 16.0f);
		}
	}
	return mario;
}

// goomba movement animation
void CAnimationManager::GoombaAnimation(sf::Sprite& mario, const float& deltaTime)
{
	m_totalTime += deltaTime;
	float nextFrameDelay;
	nextFrameDelay = 1.0f / m_goombaMovement.size();
	int index = static_cast<int>(m_totalTime / nextFrameDelay) % m_goombaMovement.size();
	mario = (m_goombaMovement[index]);
}

// turtle left movement animation
void CAnimationManager::KoopaTroopaLeftAnimation(sf::Sprite& entity, const float& deltaTime)
{
	m_totalTime += deltaTime;
	float nextFrameDelay;
	nextFrameDelay = 1.0f / m_koopaTroopaMovement.size();
	int index = static_cast<int>(m_totalTime / nextFrameDelay) % m_koopaTroopaMovement.size();
	entity = m_koopaTroopaMovement[index];
	entity.setOrigin(0.0f, 0.0f);
	entity.setScale(1.0f, 1.0f);
}

// turtle right movement animation
void CAnimationManager::KoopaTroopaRightAnimation(sf::Sprite& entity, const float& deltaTime)
{
	m_totalTime += deltaTime;
	float nextFrameDelay;
	nextFrameDelay = 1.0f / m_koopaTroopaMovement.size();
	int index = static_cast<int>(m_totalTime / nextFrameDelay) % m_koopaTroopaMovement.size();
	entity = (m_koopaTroopaMovement[index]);
	entity.setOrigin(16.0f, 0.0f);
	entity.setScale(-1.0f, 1.0f);
}

// set when hit from top
void CAnimationManager::SetGoombaStomped(sf::Sprite& entity)
{
	entity = m_goombaStomped;
}

// set when killed by turtle or fire ball
void CAnimationManager::SetGoombaKilled(sf::Sprite& entity)
{
	entity.setScale(1.0f, -1.0f);
}

// change state to shell state when hit from top
void CAnimationManager::SetKoopaTroopaStomped(sf::Sprite& entity)
{
	entity = m_koopaTroopaShellState;
}

//// set when killed by another turtle or fire ball
void CAnimationManager::SetKoopaTroopaKilled(sf::Sprite& entity)
{
	entity.setScale(1.0f, -1.0f);
}

//// display flag pole
void CAnimationManager::SetMarioFlagPole(sf::Sprite& mario)
{
	mario = m_marioFlagPole;
}

// display fireball
void CAnimationManager::SetFireBall(sf::Sprite& entity)
{
	entity = m_fireBall;
}

// display mushroom
void CAnimationManager::SetMushroom(sf::Sprite& entity)
{
	entity = m_mushroom;
}

// display oneUp
void CAnimationManager::SetOneUp(sf::Sprite& entity)
{
	entity = m_oneUp;
}

// setting glittering of questionBlocks
void CAnimationManager::QuestionBlockAnimation(sf::Sprite& block, const float& deltaTime)
{
	m_totalTime += deltaTime;
	float nextFrameDelay;
	nextFrameDelay = 10.0f / m_questionBlocks.size();
	int index = static_cast<int>(m_totalTime / nextFrameDelay) % m_questionBlocks.size();
	block = m_questionBlocks[index];

}

//// when fireball thrown it collide and show animation
void CAnimationManager::FireBallExplosionAnimation(sf::Sprite& fireball, const float& deltaTime)
{
	m_totalTime += deltaTime;
	float nextFrameDelay;
	nextFrameDelay = 1.0f / m_fireBallExplosion.size();
	int index = static_cast<int>(m_totalTime / nextFrameDelay) % m_fireBallExplosion.size();
	fireball = m_fireBallExplosion[index];
}

// setting glittering of star
void CAnimationManager::StarAnimation(sf::Sprite& star, const float& deltaTime)
{
	m_totalTime += deltaTime;
	float nextFrameDelay;
	nextFrameDelay = 1.5f / m_star.size();
	int index = static_cast<int>(m_totalTime / nextFrameDelay) % m_star.size();
	star = m_star[index];
}

// setting glittering of fireFlower
void CAnimationManager::FireFlowerAnimation(sf::Sprite& fireFlower, const float& deltaTime)
{
	m_totalTime += deltaTime;
	float nextFrameDelay;
	nextFrameDelay = 1.5f / m_fireFlower.size();
	int index = static_cast<int>(m_totalTime / nextFrameDelay) % m_fireFlower.size();
	fireFlower = m_fireFlower[index];
}

// revolving of coins
void CAnimationManager::CoinAnimation(sf::Sprite& fireFlower, const float& deltaTime)
{
	m_totalTime += deltaTime;
	float nextFrameDelay;
	nextFrameDelay = 2.5f / m_coin.size();
	int index = static_cast<int>(m_totalTime / nextFrameDelay) % m_coin.size();
	fireFlower = m_coin[index];
}

// destructor
CAnimationManager::~CAnimationManager()
{
}



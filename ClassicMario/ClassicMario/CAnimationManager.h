#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "AssetManager.h"

enum class EMarioStage
{
	small, big, firepower
};

enum class EMarioDirection
{
	left, right, jump, stand, crouch
};

class CAnimationManager
{
private:
	
	//Lateral movement
	std::vector<sf::Sprite> m_marioMovement;
	sf::Sprite m_marioStatic;
	sf::Sprite m_marioDrag;

	//Vertical Movement
	sf::Sprite m_marioJump;
	sf::Sprite m_marioCrouch;

	// damage and growth
	sf::Sprite m_marioDeath;
	std::vector<sf::Sprite> m_marioDamage;
	std::vector<sf::Sprite> m_marioDamageLevelThree;

	// growth
	std::vector<sf::Sprite> m_marioFirePower;
	std::vector<sf::Sprite> m_marioGrowth;

	// enemy
	std::vector<sf::Sprite> m_goombaMovement; // mushroom enemy
	std::vector<sf::Sprite> m_koopaTroopaMovement; // turtle 
	sf::Sprite m_goombaStomped;
	sf::Sprite m_koopaTroopaShellState;

	//Blocks
	std::vector<sf::Sprite> m_questionBlocks;
	std::vector<sf::Sprite> m_coins;

	// fireball
	std::vector<sf::Sprite> m_fireBallExplosion;
	sf::Sprite m_fireBall;

	// collectibles
	sf::Sprite m_mushroom;
	sf::Sprite m_oneUp;
	std::vector<sf::Sprite> m_star;
	std::vector<sf::Sprite> m_fireFlower;
	std::vector<sf::Sprite> m_coin;
	sf::Sprite m_marioFlagPole;

	
	float m_totalTime = 0;
	CAssetManager m_assetManager;
	EMarioStage m_marioStage;
	EMarioDirection m_marioDirection;
	

public:

	CAnimationManager();

	// mario animations
	sf::Sprite AnimationDamage(const float& deltaTime);
	sf::Sprite AnimationFirePower(const float& deltaTime);
	sf::Sprite AnimationGrowth(const float& deltaTime);
	sf::Sprite AnimationDamageLevelThreeToLevelOne(const float& deltaTime);
	void AnimationDeath(sf::Sprite& mario);
	void RightMarioAnimation(sf::Sprite&, const float& deltaTime);
	void LeftMarioAnimation(sf::Sprite&, const float& deltaTime);
	void SetMarioRightStatic(sf::Sprite&);
	void SetMarioLeftStatic(sf::Sprite&);
	void SetMarioRightDrag(sf::Sprite&);
	void SetMarioLeftDrag(sf::Sprite&);
	void SetMarioRightJump(sf::Sprite&, bool);
	void SetMarioLeftJump(sf::Sprite&, bool);
	void SetMarioRightCrouch(sf::Sprite&);
	void SetMarioLeftCrouch(sf::Sprite&);

	// enemies animations
	void GoombaAnimation(sf::Sprite&, const float& deltaTime);
	void KoopaTroopaLeftAnimation(sf::Sprite&, const float& deltaTime);
	void KoopaTroopaRightAnimation(sf::Sprite&, const float& deltaTime);
	void SetKoopaTroopaStomped(sf::Sprite& entity);
	void SetKoopaTroopaKilled(sf::Sprite& entity);
	void SetGoombaStomped(sf::Sprite& entity);
	void SetGoombaKilled(sf::Sprite& entity);

	// fireball animation
	void FireBallExplosionAnimation(sf::Sprite&, const float& deltaTime);
	void SetFireBall(sf::Sprite&);

	// animation functions for collectibles
	void QuestionBlockAnimation(sf::Sprite&, const float& deltaTime);
	void StarAnimation(sf::Sprite&, const float& deltaTime);
	void FireFlowerAnimation(sf::Sprite&, const float& deltaTime);
	void SetMarioFlagPole(sf::Sprite&);
	void SetMushroom(sf::Sprite&);
	void SetOneUp(sf::Sprite&);
	void CoinAnimation(sf::Sprite& fireFlower, const float& deltaTime);
	~CAnimationManager();
};


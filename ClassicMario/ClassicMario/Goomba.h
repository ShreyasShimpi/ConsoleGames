#pragma once
#include"Enemy.h"
#include "CAnimationManager.h"

//enum for specifying different types of states that a goomba can be in 
enum class EGoombaStates { Deactivated, Normal, CrouchedDeath, NonCrouchedDeath };

class CAssetManager;

class CGoomba : public CEnemy
{
private:
	//
	EGoombaStates m_state = EGoombaStates::Deactivated;
	float m_deathTimer = 0;
	CAnimationManager m_animationManager;//used for updating animation
	CAssetManager m_assetManager;

public:

	CGoomba() = delete;
	CGoomba(sf::Vector2f pos);
	void SetState(EGoombaStates state);

	virtual void HitFromTop(CPlayer& mario) override;
	virtual void HitFromBottom(CPlayer& mario) override;
	virtual void HitFromFireball(CPlayer& mario) override;
	virtual bool IsAlive() const override;
	//virtual void TouchFromSide(CPlayer& mario) override;
	virtual void ChangeDirection() override;
	virtual void Update(float delta_time) override;
};


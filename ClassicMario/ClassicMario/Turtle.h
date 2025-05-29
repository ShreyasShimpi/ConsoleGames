#pragma once
#include "Enemy.h"
#include "CAnimationManager.h"
#include "AssetManager.h"

//enum for specifying different types of states that a goomba can be in 
enum class ETurtleStates { Deactivated, Normal, StaticShellForm, MovingShellForm, Dead };

class CTurtle :public CEnemy
{
private:

	ETurtleStates m_state = ETurtleStates::Deactivated;
	float m_deathTimer = 0;
	CAnimationManager m_animationManager;//used for updating animation
	CAssetManager m_assetManager;

public:

	CTurtle() = delete;
	CTurtle(sf::Vector2f pos);
	void SetState(ETurtleStates state);
	virtual void HitFromTop(CPlayer& mario) override;
	virtual void HitFromBottom(CPlayer& mario) override;
	virtual void HitFromFireball(CPlayer& mario) override;
	virtual bool IsAlive() const override;
	//virtual void TouchFromSide(CPlayer& mario) override;
	virtual void Update(float delta_time) override;
	virtual void ChangeDirection() override;
};


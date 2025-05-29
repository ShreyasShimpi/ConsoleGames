//Updated collision.h
//Need to include collision of player with turtle -> five types of collisions
#pragma once

#include<SFML/Graphics.hpp>
#include"Player.h"
#include"Enemy.h"
#include"Collectible.h"
class CCollision
{
public:
	CCollision(){}

	~CCollision(){}

	/*
		-->This function returns true if an object(player,enemy or collectible) is colliding with the floor
		-->overloaded for the case of floatrect for convenience 
	*/
	bool ObjectToFloorCollision(sf::Sprite& objectOne, float floorHeight); 
	bool ObjectToFloorCollision(sf::Sprite& object, sf::FloatRect ground);


	
	/*
	    -->This function returns true if the mario falls into the Pit
	*/
	bool PlayerPitCollision(CPlayer& player, sf::FloatRect pitLocation, float const& deltaTime);
	

	/*
	    -->This function returns true if two objects intersect. overloaded for the sake of multiple use cases
	*/
	bool ObjectToObjectCollision(sf::Sprite& objectOne, sf::FloatRect& objectTwo);
	bool ObjectToObjectCollision(sf::FloatRect& objectOne, sf::FloatRect& objectTwo);



    /*
	   -->This function detects and resolves collision for the case of player colliding with an obstacle( brick,stair etc) from any side except from bottom
	*/
	void PlayerObstacleCollisionExceptFromBottom(CPlayer& player, sf::FloatRect brick, const float& deltaTime);

	/*
	   -->This function detects and resolves collision when player hits the brick from bottom and also returns true.
	*/
	bool PlayerObstacleCollisionFromBottom(CPlayer& player, sf::FloatRect brick, const float& deltaTime);

	/*
	   -->This function checks for if an enemy collides with obstacle and resolves the collision
	*/
	void EnemyObstacleCollision(CEnemy& enemy, sf::FloatRect brick, const float& deltaTime);

	/* 
	   -->This function checks if an enemy collides with another and returns true if it is the case
	*/
	bool EnemyToEnemyCollision(CEnemy& enemyOne, CEnemy& enemyTwo, const float& deltaTime);

	/*
	   -->This function checks for the collision of collectible with obstacle and resolves it 
	*/
	void CollectibleObstacleCollision(CCollectible& collectible, sf::FloatRect brick, const float& deltaTime);

	


	/*
	when player jumps on the enemy from top or jump over enemy
    */
	bool PlayerEnemyCollisionFromTop(CPlayer& player, CEnemy& enemy, const float deltaTime);
	

	/*

	when enemy coolide with player from left or from rigth
	also when enemy falls on the player from top
    */
	bool PlayerEnemyCollisionExceptFromTop(CPlayer& player, CEnemy& enemy, const float deltaTime);

	/*
		player window boundary

	*/
	void PlayerWindowBoundaryCollision(sf::Sprite& player);

};



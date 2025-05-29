

#include <iostream>
#include "collision.h"


bool CCollision::ObjectToFloorCollision(sf::Sprite& object, float floorHeight)
{
	//if the bottom of the object goes below the top of the floor
	if (object.getGlobalBounds().top + object.getGlobalBounds().height > floorHeight)
	{
		return true;
	}
	return false;
}

bool CCollision::ObjectToFloorCollision(sf::Sprite& object, sf::FloatRect ground)
{
	
	if ((object.getGlobalBounds().left >=ground.left && object.getGlobalBounds().left < ground.left + ground.width - 5.f) //If the bottom of the object goes below the top of the floor
		&& object.getGlobalBounds().top + object.getGlobalBounds().height > ground.top)//and if the object lies between the x coordinates of the floor
	{
		return true;
	}
	return false;
}



bool CCollision::PlayerPitCollision(CPlayer& player, sf::FloatRect groundLocation, float const& deltaTime)
{

	//Getting the essential data
	sf::Sprite playerSprite = player.GetSprite();
	sf::FloatRect playerBounds = playerSprite.getGlobalBounds();
	sf::Vector2f offsetPosition = { player.GetVelocity().x * deltaTime,  player.GetVelocity().y * deltaTime };
	sf::FloatRect nextPos = playerBounds;

	//next posiition of the player calculated using x_next = x_current + velocity * time
	nextPos.left += offsetPosition.x;
	nextPos.top += offsetPosition.y;

	if (groundLocation.intersects(nextPos))//if the next position of the player intersects with the groundLocation
	{
		//Checking if the player collides with the left portion of the floor block
		if (playerBounds.left < groundLocation.left
			&& playerBounds.top < groundLocation.top + groundLocation.height
			&& playerBounds.top + playerBounds.height > groundLocation.top)
		{
			player.SetVelocity({ 0.0f , player.GetVelocity().y });//setting x vel to zero
			player.SetPosition({ groundLocation.left - playerBounds.width, playerBounds.top });//setting player's pos so that he is just beside the block
		}

		//Checking if the player collides with the right portion of the block
		else if (playerBounds.left > groundLocation.left
			&& playerBounds.top < groundLocation.top + groundLocation.height
			&& playerBounds.top + playerBounds.height > groundLocation.top)
		{
			player.SetVelocity({ 0.0f , player.GetVelocity().y }); // setting x vel to zero
			player.SetPosition({ groundLocation.left + groundLocation.width, playerBounds.top });//setting player's pos so that he is just beside the block
		}

    }

	if ((player.GetPosition().y  >= groundLocation.top + groundLocation.height))//if the player falls below the bottom of the ground, we return true
	{
		return true;
	}
	return false;
}


bool CCollision::ObjectToObjectCollision(sf::Sprite& objectOne, sf::FloatRect& objectTwo)
{
	if (objectOne.getGlobalBounds().intersects(objectTwo))
	{
		return true;
	}
	else return false;
}

bool CCollision::ObjectToObjectCollision(sf::FloatRect& objectOne, sf::FloatRect& objectTwo)
{
	if (objectOne.intersects(objectTwo))
	{
		return true;
	}
	else return false;
}
                                                        


void CCollision::PlayerObstacleCollisionExceptFromBottom(CPlayer& player, sf::FloatRect brick, const float& deltaTime)

{
	//Getting the essential data
	sf::Sprite playerSprite = player.GetSprite();
	sf::FloatRect playerBounds = playerSprite.getGlobalBounds();
	sf::Vector2f offsetPosition = { player.GetVelocity().x * deltaTime,  player.GetVelocity().y * deltaTime };
	sf::FloatRect nextPos = playerBounds;

	//next posiition of the player calculated using x_next = x_current + velocity * time
	nextPos.left += offsetPosition.x;
	nextPos.top += offsetPosition.y;

	if (brick.intersects(nextPos))//if the next position of the player intersects with the groundLocation
	{
		//Checking if the player collides with the top portion of the block
		if (playerBounds.top < brick.top
			&& playerBounds.top + playerBounds.height < brick.top + brick.height
			&& playerBounds.left < brick.left + brick.width
			&& playerBounds.left + playerBounds.width > brick.left)
		{
			player.SetVelocity({ player.GetVelocity().x, 0.0f });//setting y vel to zero
			if (ObjectToFloorCollision(player.GetSprite(), brick.top))
			{
				player.SetPosition({ player.GetPosition().x, brick.top - playerBounds.height });//setting player's pos so that he is just above the block
				player.m_isJumping = false;
			}
			player.SetPosition({ playerBounds.left,  brick.top - playerBounds.height });
		}

		//Checking if the player collides with the left portion of the block
		else if (playerBounds.left < brick.left
			&& playerBounds.top < brick.top + brick.height
			&& playerBounds.top + playerBounds.height > brick.top)
		{
			player.SetVelocity({ 0.0f , player.GetVelocity().y });
			player.SetPosition({ brick.left - playerBounds.width, playerBounds.top });
		}

		//Checking if the player collides with the right portion of the block
		else if (playerBounds.left > brick.left
			&& playerBounds.top < brick.top + brick.height
			&& playerBounds.top + playerBounds.height > brick.top)
		{
			player.SetVelocity({ 0.0f , player.GetVelocity().y });
			player.SetPosition({ brick.left + brick.width, playerBounds.top });
		}

	}

}

bool CCollision::PlayerObstacleCollisionFromBottom(CPlayer& player, sf::FloatRect brick, const float& deltaTime)
{

	sf::Sprite playerSprite = player.GetSprite();
	sf::FloatRect playerBounds = playerSprite.getGlobalBounds();
	sf::Vector2f offsetPosition = { player.GetVelocity().x * deltaTime,  player.GetVelocity().y * deltaTime };
	sf::FloatRect nextPos = playerBounds;

	nextPos.left += offsetPosition.x;
	nextPos.top += offsetPosition.y;
	
	float playerCenter = playerBounds.left + playerBounds.width / 2.0f;//calculating player center for accurate detection of collision


	if (brick.intersects(nextPos))
	{
		//Checking if the top of the player coincides with the bottom of the block
	   if (playerBounds.top > brick.top
		  && playerBounds.top + playerBounds.height > brick.top + brick.height
		  && playerBounds.left < brick.left + brick.width
		  && playerBounds.left + playerBounds.width > brick.left)
	   {
			player.SetVelocity({ player.GetVelocity().x, 0.0f });//setting y vel to zero 
			player.SetPosition({ playerBounds.left, brick.top + brick.height });

			if (playerCenter > brick.left && playerCenter < brick.left + brick.width)//if the player's center is inside the blocks x bounds
			{
				return true;
			}
	   }
	}
	return false;
}

void CCollision::EnemyObstacleCollision(CEnemy& enemy, sf::FloatRect brick, const float& deltaTime)
{
	sf::Sprite playerSprite = enemy.GetSprite();
	sf::FloatRect enemyBounds = playerSprite.getGlobalBounds();
	sf::Vector2f offsetPosition = { enemy.GetVelocity().x * deltaTime,  enemy.GetVelocity().y * deltaTime };
	sf::FloatRect nextPos = enemyBounds;


	nextPos.left += offsetPosition.x;
	nextPos.top += offsetPosition.y;

	if (brick.intersects(nextPos))
	{
		//top collision
		if (enemyBounds.top < brick.top
			&& enemyBounds.top + enemyBounds.height < brick.top + brick.height
			&& enemyBounds.left < brick.left + brick.width
			&& enemyBounds.left + enemyBounds.width > brick.left)
		{
			enemy.SetVelocity({ enemy.GetVelocity().x, 0.0f });

			if (ObjectToFloorCollision(enemy.GetSprite(), brick.top))
			{
				enemy.SetPosition({ enemy.GetPosition().x, brick.top - enemyBounds.height });
			}

			enemy.SetPosition({ enemyBounds.left,  brick.top - enemyBounds.height });
		}

		//left collision
		else if (enemyBounds.left < brick.left
			&& enemyBounds.top < brick.top + brick.height
			&& enemyBounds.top + enemyBounds.height > brick.top
			)
		{
			enemy.SetPosition({ brick.left - enemyBounds.width, enemyBounds.top });
			enemy.ChangeDirection();
		}

		//right collision
		else if (enemyBounds.left > brick.left
			&& enemyBounds.top < brick.top + brick.height
			&& enemyBounds.top + enemyBounds.height > brick.top
			)
		{
			enemy.SetPosition({ brick.left + brick.width, enemyBounds.top });
			enemy.ChangeDirection();
		}

	}

}

bool CCollision::EnemyToEnemyCollision(CEnemy& enemyOne, CEnemy& enemyTwo, const float& deltaTime)
{
	//getting essential data
	sf::Sprite enemyOneSprite = enemyOne.GetSprite();
	sf::Sprite enemyTwoSprite = enemyTwo.GetSprite();
	sf::FloatRect enemyOneBounds = enemyOneSprite.getGlobalBounds();
	sf::FloatRect enemyTwoBounds = enemyTwoSprite.getGlobalBounds();

	sf::Vector2f enemyOneOffsetPosition = { enemyOne.GetVelocity().x * deltaTime,  enemyOne.GetVelocity().y * deltaTime };
	sf::Vector2f EnemyTwoOffsetPosition = { enemyTwo.GetVelocity().x * deltaTime,  enemyTwo.GetVelocity().y * deltaTime };
	sf::FloatRect enemyOneNextPos = enemyOneBounds;
	sf::FloatRect enemyTwoNextPos = enemyTwoBounds;

	//finding next pos
	enemyOneNextPos.left += enemyOneOffsetPosition.x;
	enemyTwoNextPos.left += EnemyTwoOffsetPosition.x;
	enemyOneNextPos.top += enemyOneOffsetPosition.y;
	enemyTwoNextPos.top += EnemyTwoOffsetPosition.y;
	if (enemyTwoNextPos.intersects(enemyOneNextPos))
	{
		//left collision
		if (enemyOneBounds.left < enemyTwoBounds.left
			&& enemyOneBounds.top < enemyTwoBounds.top + enemyTwoBounds.height
			&& enemyOneBounds.top + enemyOneBounds.height > enemyTwoBounds.top
			)
		{
			enemyOne.SetPosition({ enemyTwoBounds.left - enemyTwoBounds.width, enemyOneBounds.top });
			enemyOne.ChangeDirection();
			enemyTwo.ChangeDirection();
			enemyTwo.SetPosition({ enemyOneBounds.left + enemyOneBounds.width, enemyTwoBounds.top });
			return true;
		}



		//right collision
		else if (enemyOneBounds.left > enemyTwoBounds.left
			&& enemyOneBounds.top < enemyTwoBounds.top + enemyTwoBounds.height
			&& enemyOneBounds.top + enemyOneBounds.height > enemyTwoBounds.top
			)
		{
			enemyOne.SetPosition({ enemyTwoBounds.left + enemyTwoBounds.width, enemyOneBounds.top });
			enemyOne.ChangeDirection();
			enemyTwo.ChangeDirection();
			enemyTwo.SetPosition({ enemyOneBounds.left - enemyOneBounds.width, enemyTwoBounds.top });
			return true;
		}

	}
	return false;
}


//This function is very similar to the player obstacle collision
void CCollision::CollectibleObstacleCollision(CCollectible& collectible, sf::FloatRect brick, const float& deltaTime)
{
	sf::Sprite playerSprite = collectible.GetSprite();
	sf::FloatRect enemyBounds = playerSprite.getGlobalBounds();
	sf::Vector2f offsetPosition = { collectible.GetVelocity().x * deltaTime,  collectible.GetVelocity().y * deltaTime };
	sf::FloatRect nextPos = enemyBounds;

	nextPos.left += offsetPosition.x;
	nextPos.top += offsetPosition.y;

	if (brick.intersects(nextPos))
	{
		//top collision
		if (enemyBounds.top < brick.top
			&& enemyBounds.top + enemyBounds.height < brick.top + brick.height
			&& enemyBounds.left < brick.left + brick.width
			&& enemyBounds.left + enemyBounds.width > brick.left
			)
		{
			collectible.SetVelocity({ collectible.GetVelocity().x, 0.0f });
			if (ObjectToFloorCollision(collectible.GetSprite(), brick.top))
			{
				collectible.SetPosition({ collectible.GetPosition().x, brick.top - enemyBounds.height });
			}
			collectible.SetPosition({ enemyBounds.left,  brick.top - enemyBounds.height });
		}

		//left collision
		else if (enemyBounds.left < brick.left
			&& enemyBounds.top < brick.top + brick.height
			&& enemyBounds.top + enemyBounds.height > brick.top)
		{
			collectible.SetPosition({ brick.left - enemyBounds.width, enemyBounds.top });
			collectible.ChangeDirection();
		}

		//right collision
		else if (enemyBounds.left > brick.left
			&& enemyBounds.top < brick.top + brick.height
			&& enemyBounds.top + enemyBounds.height > brick.top
			)
		{
			collectible.SetPosition({ brick.left + brick.width, enemyBounds.top });
			collectible.ChangeDirection();

		}

	}
}

bool CCollision::PlayerEnemyCollisionFromTop(CPlayer& player, CEnemy& enemy, const float deltaTime)
{
	//essential data
	sf::Sprite playerSprite = player.GetSprite();
	sf::Sprite enemySprite = enemy.GetSprite();
	sf::FloatRect playerBounds = playerSprite.getGlobalBounds();
	sf::FloatRect enemyBounds = enemySprite.getGlobalBounds();


	sf::Vector2f enemyOffsetPosition = { enemy.GetVelocity().x * deltaTime,  enemy.GetVelocity().y * deltaTime };
	sf::FloatRect playerNextPosition = playerBounds;
	sf::Vector2f playerOffsetPosition = { player.GetVelocity().x * deltaTime,  player.GetVelocity().y * deltaTime };
	sf::FloatRect enemyNextPosition = enemyBounds;

	//Updating next position
	playerNextPosition.left += enemyOffsetPosition.x;
	enemyNextPosition.left += playerOffsetPosition.x;
	playerNextPosition.top += enemyOffsetPosition.y;
	enemyNextPosition.top += playerOffsetPosition.y;


	if (playerNextPosition.intersects(enemyNextPosition))
	{
		//top collision
		if (playerBounds.top < enemyBounds.top
			&& playerBounds.top + playerBounds.height < enemyBounds.top + enemyBounds.height
			&& playerBounds.left < enemyBounds.left + enemyBounds.width
			&& playerBounds.left + playerBounds.width > enemyBounds.left)
		{

			if (ObjectToFloorCollision(player.GetSprite(), enemyBounds.top))
			{
				player.SetPosition({ player.GetPosition().x, enemyBounds.top - playerBounds.height });
				player.m_isJumping = false;
			}

		}
		return true;
	}
	return false;
}


bool CCollision::PlayerEnemyCollisionExceptFromTop(CPlayer& player, CEnemy& enemy, const float deltaTime)
{
	//essential data
	sf::Sprite playerSprite = player.GetSprite();
	sf::Sprite enemySprite = enemy.GetSprite();
	sf::FloatRect playerBounds = playerSprite.getGlobalBounds();
	sf::FloatRect enemyBounds = enemySprite.getGlobalBounds();

	sf::Vector2f playerOffsetPosition = { player.GetVelocity().x * deltaTime,  player.GetVelocity().y * deltaTime };
	sf::Vector2f enemyOffsetPosition = { enemy.GetVelocity().x * deltaTime,  enemy.GetVelocity().y * deltaTime };
	sf::FloatRect playerNextPosition = playerBounds;
	sf::FloatRect enemyNextPosition = enemyBounds;

	playerNextPosition.left += playerOffsetPosition.x;
	enemyNextPosition.left += enemyOffsetPosition.x;
	playerNextPosition.top += playerOffsetPosition.y;
	enemyNextPosition.top += enemyOffsetPosition.y;
	if (playerNextPosition.intersects(enemyNextPosition))
	{
		//left collision
		if (playerBounds.left < enemyBounds.left
			&& playerBounds.top < enemyBounds.top + enemyBounds.height
			&& playerBounds.top + playerBounds.height > enemyBounds.top)
		{
			player.SetPosition({ enemyBounds.left - playerBounds.width, playerBounds.top });
			return true;
		}



		//right collision
		else if (playerBounds.left > enemyBounds.left
			&& playerBounds.top < enemyBounds.top + enemyBounds.height
			&& playerBounds.top + playerBounds.height > enemyBounds.top)
		{
			player.SetPosition({ enemyBounds.left + enemyBounds.width, playerBounds.top });
			return true;
		}

		// from bottom
		if (playerBounds.top > enemyBounds.top
			&& playerBounds.top + playerBounds.height > enemyBounds.top + enemyBounds.height
			&& playerBounds.left < enemyBounds.left + enemyBounds.width
			&& playerBounds.left + playerBounds.width > enemyBounds.left)
		{
			player.SetVelocity({ player.GetVelocity().x, 0.0f });
			return true;
		}

	}

	return false;
}

void CCollision::PlayerWindowBoundaryCollision(sf::Sprite& player)
{
	//if player goes out of the window from left 
	if (player.getPosition().x < 0)
	{
		player.setPosition(0, player.getPosition().y);
	}
}

#include <iostream>
#include <thread>
#include <chrono>
#include "CSpawnManager.h"
#include "collision.h"
#include "Player.h"
#include "LevelData.h"
#include "QuestionBlock.h"
#include "BrickBlock.h"
#include <fstream>
#include "Goomba.h"
#include "Turtle.h"
#include "FireFlower.h"
#include "GrowthPower.h"
#include "OneUpPower.h"
#include "StarPower.h"
#include "Coin.h"

void CSpawnManager::AdjustView()
{
	// adjusting the camera position according to the player position
	if (m_player->GetPosition().x > m_game.GetView().getCenter().x && (m_game.GetView().getCenter().x + m_game.GetView().getSize().x/2 < 3392))
	{
		m_game.GetView().setCenter(m_player->GetPosition().x, 112.0f);
		m_game.GetRenderWindow().setView(m_game.GetView());
	}

	//Setting goomba state to normal if the diff between goomba and player is less than a pre defined value
	for (auto& goomba : m_goombas)
	{
		if (goomba->GetPosition().x - m_player->GetPosition().x <= 640.0f)
		{
			goomba->SetState(EGoombaStates::Normal);
		}
	}

	if (m_koopaTroopa->GetPosition().x - m_player->GetPosition().x <= 640.0f)
	{
		//m_koopaTroopa->SetState(ETurtleStates::Normal);
	}
}


void CSpawnManager::CheckWindowColiision()
{
	//Left boundary check
	if (m_player->GetPosition().x < (m_game.GetView().getCenter().x - m_game.GetView().getSize().x / 2))
	{
		m_player->SetPosition({ m_game.GetView().getCenter().x - m_game.GetView().getSize().x / 2, m_player->GetPosition().y });
	}

	//Right boundary check
	if (m_player->GetPosition().x + m_player->GetWidth() > (m_game.GetView().getCenter().x + m_game.GetView().getSize().x / 2))
	{
		m_player->SetPosition({m_game.GetView().getCenter().x + m_game.GetView().getSize().x/2 - m_player->GetSprite().getGlobalBounds().width, m_player->GetPosition().y});
	}
}

void CSpawnManager::CreateGoombas()
{
	//Creating goombas
	std::shared_ptr<CGoomba> enemy = std::make_shared<CGoomba>(sf::Vector2f({ 800.0f,184.0f }));
	m_goombas.push_back(enemy);
	enemy = std::make_shared<CGoomba>(sf::Vector2f({ 700.0f,184.0f }));
	m_goombas.push_back(enemy);
	enemy = std::make_shared<CGoomba>(sf::Vector2f({ 1600.0f,184.0f }));
	m_goombas.push_back(enemy);
	enemy = std::make_shared<CGoomba>(sf::Vector2f({ 1700,184.0f }));
	m_goombas.push_back(enemy);
	enemy = std::make_shared<CGoomba>(sf::Vector2f({ 300.0f,184.0f }));
	m_goombas.push_back(enemy);
	/*enemy = std::make_shared<CGoomba>(sf::Vector2f({ 850.0f,184.0f }));
	m_goombas.push_back(enemy);*/
	enemy = std::make_shared<CGoomba>(sf::Vector2f({ 1300.0f,184.0f }));
	m_goombas.push_back(enemy);
	enemy = std::make_shared<CGoomba>(sf::Vector2f({ 1330.0f,184.0f }));
	m_goombas.push_back(enemy);
	enemy = std::make_shared<CGoomba>(sf::Vector2f({ 1950.0f,184.0f }));
	m_goombas.push_back(enemy);
	enemy = std::make_shared<CGoomba>(sf::Vector2f({ 2052.0f,184.0f }));
	m_goombas.push_back(enemy);
	enemy = std::make_shared<CGoomba>(sf::Vector2f({ 2800.0f,184.0f }));
	m_goombas.push_back(enemy);
}

void CSpawnManager::UpdateCollisions(const float& deltaTime, sf::RenderWindow& window)
{
	auto groundList = m_levelData->GetObjectData(EObject::GROUND);
	auto brickList = m_levelData->GetObjectData(EObject::BRICK);
	auto pipeList = m_levelData->GetObjectData(EObject::VERTICAL_PIPE);
	auto questionList = m_levelData->GetObjectData(EObject::QUESTION);
	auto stairList = m_levelData->GetObjectData(EObject::STAIR_BLOCK);
	auto invisibleBlockList = m_levelData->GetObjectData(EObject::INVISIBLE_BLOCK);
	auto flagPoleList = m_levelData->GetObjectData(EObject::FLAG_POLE);

	for (auto ground : groundList)
	{
		// player - floor collision
		if (m_collisionManager->ObjectToFloorCollision(m_player->GetSprite(), ground))
		{
			m_player->SetPosition({ m_player->GetPosition().x, 184.f });
			m_player->m_isJumping = false;
		}

		//player - pit collision
		if (m_collisionManager->PlayerPitCollision(*m_player, ground, deltaTime))
		{
			m_player->SetMarioState(EMarioState::Dead);
		}
	}


	//player - obstacle collision
	for (auto pipe : pipeList)

	{
		m_collisionManager->PlayerObstacleCollisionExceptFromBottom(*m_player, pipe, deltaTime);
	}

	for (auto stair : stairList)

	{

		m_collisionManager->PlayerObstacleCollisionExceptFromBottom(*m_player, stair, deltaTime);
	}

	for (auto brick : brickList)
	{
		m_collisionManager->PlayerObstacleCollisionExceptFromBottom(*m_player, brick, deltaTime);
		if (m_collisionManager->PlayerObstacleCollisionFromBottom(*m_player, brick, deltaTime))
		{
			//if player hits the block from bottom, brick animation should be triggered
		}
	}

	for (auto& question : m_questionBlocks)
	{
		m_collisionManager->PlayerObstacleCollisionExceptFromBottom(*m_player, question.GetBlockBounds(), deltaTime);
		if (m_collisionManager->PlayerObstacleCollisionFromBottom(*m_player, question.GetBlockBounds(), deltaTime))
		{
			//if player hits the block from bottom, question animation should be triggered
			m_player->SetPosition({ m_player->GetSprite().getGlobalBounds().left, question.GetBlockBounds().top + question.GetBlockBounds().height });
			m_player->SetVelocity(sf::Vector2f(m_player->GetVelocity().x, 0.f));
			if (!question.IsOpened())
			{
				question.OpenQuestionBlock();

				// spawning power if exists
				// growth power
				if (question.GetCollectible() == ECollectible::Growth_Power)
				{
					m_growthPowers.emplace_back(CGrowthPower({ question.GetBlockBounds().left, question.GetBlockBounds().top }, m_assetManager->GetSprite(EItems::Mushroom_Red), *m_animationManager));
				}

				// fire flower
				if (question.GetCollectible() == ECollectible::FireFlower)
				{
					// condition to check if mario is in the bigger state
					if (m_player->GetHeight() > 16)
						m_fireflowers.emplace_back(CFireFlower({ question.GetBlockBounds().left, question.GetBlockBounds().top }, m_assetManager->GetSprite(EItems::Fire_Flower_1), *m_animationManager));
					else
						m_growthPowers.emplace_back(CGrowthPower({ question.GetBlockBounds().left, question.GetBlockBounds().top }, m_assetManager->GetSprite(EItems::Mushroom_Red), *m_animationManager));
				}

			}
		}
	}

	for (auto invBlock : invisibleBlockList)
	{
		m_collisionManager->PlayerObstacleCollisionExceptFromBottom(*m_player, invBlock, deltaTime);
		if (m_collisionManager->PlayerObstacleCollisionFromBottom(*m_player, invBlock, deltaTime))
		{
			//if player hits the block from bottom, question animation should be triggered
		}
	}

	for (auto flagPole : flagPoleList)
	{

		if (m_collisionManager->ObjectToObjectCollision(m_player->GetSprite(), flagPole))
		{
			//if player touches the flag pole
		}
	}


	// **** Enemy - static block collision **** //
	for (auto goomba : m_goombas)
	{
		for (auto brick : brickList)
		{
			m_collisionManager->EnemyObstacleCollision(*goomba, brick, deltaTime);
		}
		for (auto question : questionList)
		{
			m_collisionManager->EnemyObstacleCollision(*goomba, question, deltaTime);
		}
		for (auto stair : stairList)
		{
			m_collisionManager->EnemyObstacleCollision(*goomba, stair, deltaTime);
		}
		for (auto pipe : pipeList)
		{
			m_collisionManager->EnemyObstacleCollision(*goomba, pipe, deltaTime);
		}
	}

	for (auto brick : brickList)
	{
		m_collisionManager->EnemyObstacleCollision(*m_koopaTroopa, brick, deltaTime);
	}
	for (auto question : questionList)
	{
		m_collisionManager->EnemyObstacleCollision(*m_koopaTroopa, question, deltaTime);
	}
	for (auto stair : stairList)
	{
		m_collisionManager->EnemyObstacleCollision(*m_koopaTroopa, stair, deltaTime);
	}
	for (auto pipe : pipeList)
	{
		m_collisionManager->EnemyObstacleCollision(*m_koopaTroopa, pipe, deltaTime);
	}

	// **** Player - Enemy Collision ***** //

	for (auto goomba : m_goombas)
	{
		if (m_collisionManager->PlayerEnemyCollisionExceptFromTop(*m_player, *goomba, deltaTime))
		{
			m_player->SetMarioState(EMarioState::Dead);
			m_player->MakeDead();
		}
		else if (m_collisionManager->PlayerEnemyCollisionFromTop(*m_player, *goomba, deltaTime))
		{
			//if player hits the block from bottom, brick animation should be triggered
		}
	}

	if (m_collisionManager->PlayerEnemyCollisionExceptFromTop(*m_player, *m_koopaTroopa, deltaTime))
	{
		m_player->SetMarioState(EMarioState::Dead);
		m_player->MakeDead();
	}
	else if (m_collisionManager->PlayerEnemyCollisionFromTop(*m_player, *m_koopaTroopa, deltaTime))
	{
		//if player hits the block from bottom, brick animation should be triggered
	}


	// **** Enemy - Enemy Collision **** //

	// turtle with all goomba

	for (auto gooma : m_goombas)
	{
		m_collisionManager->EnemyToEnemyCollision(*m_koopaTroopa, *gooma, deltaTime);
	}


	// goomba with all goomba 
	for (int i = 0; i < m_goombas.size(); i++)
	{
		for (int j = 0; j < m_goombas.size(); j++)
		{
			if (i != j)
			{
				m_collisionManager->EnemyToEnemyCollision(*m_goombas[i], *m_goombas[j], deltaTime);
			}
		}
	}


	// **** Enemy - static block collision **** //

	for (auto goomba : m_goombas)
	{
		for (auto brick : brickList)
		{
			m_collisionManager->EnemyObstacleCollision(*goomba, brick, deltaTime);
		}
		for (auto question : questionList)
		{
			m_collisionManager->EnemyObstacleCollision(*goomba, question, deltaTime);
		}
		for (auto stair : stairList)
		{
			m_collisionManager->EnemyObstacleCollision(*goomba, stair, deltaTime);
		}
	}

	// **** Collectible - static block collision **** //

	// growth mushroom
	for (auto& growthPower : m_growthPowers)
	{
		for (auto& brick : brickList)
		{
			m_collisionManager->CollectibleObstacleCollision(growthPower, brick, deltaTime);
		}
		for (auto& question : questionList)
		{
			if (growthPower.GetPosition().y + growthPower.GetSprite().getGlobalBounds().height < question.top)
			{
				m_collisionManager->CollectibleObstacleCollision(growthPower, question, deltaTime);
			}
		}
		for (auto& stair : stairList)
		{
			m_collisionManager->CollectibleObstacleCollision(growthPower, stair, deltaTime);
		}
		for (auto& ground : groundList)
		{
			if (m_collisionManager->ObjectToFloorCollision(growthPower.GetSprite(), ground))
			{
				growthPower.GetSprite().setPosition(growthPower.GetPosition().x, ground.top - growthPower.GetSprite().getGlobalBounds().height);
			}
		}
	}

	// player-question block collision ( trigger the collectible)
	for (auto questionBlock : m_questionBlocks)
	{
		if (m_collisionManager->PlayerObstacleCollisionFromBottom(*m_player, questionBlock.GetBlockBounds(), deltaTime))
		{
			m_player->SetPosition({ m_player->GetSprite().getGlobalBounds().left, questionBlock.GetBlockBounds().top + questionBlock.GetBlockBounds().height });
			m_player->SetVelocity(sf::Vector2f(m_player->GetVelocity().x, 0.f));
			if (!questionBlock.IsOpened())
			{
				questionBlock.OpenQuestionBlock();
			}
		}
	}

	// window collision
	CheckWindowColiision();
}

CSpawnManager::CSpawnManager(CGame& game) 
	:m_game(game)
{
	m_assetManager = std::make_shared<CAssetManager>();
	m_animationManager = std::make_shared<CAnimationManager>();
	m_player = std::make_shared<CPlayer>(*m_assetManager, game, *m_animationManager); // player class obj 
	m_collisionManager = std::make_shared<CCollision>();
	this->m_levelData = std::make_shared<CLevelData>();


	CreateGoombas();

	//Creating turtle
	m_koopaTroopa = std::make_shared<CTurtle>(sf::Vector2f({ 950.0f,176.0f }));


	// setting position of question blocks
	for (auto& m_collectibleData : m_levelData->GetCollectibleData())
	{
		m_questionBlocks.push_back(CQuestionBlock(m_collectibleData.first, *m_assetManager, *m_animationManager, m_collectibleData.second));
	}

	for (auto& brickBlocksData : m_levelData->GetObjectData(EObject::BRICK))
	{
		m_brickBlocks.push_back(CBrickBlock({ brickBlocksData.left, brickBlocksData.top }, *m_assetManager));
	}
}

CSpawnManager::~CSpawnManager()
{
	std::cout << " Spawn Manager Destructor Called\n";
}

void CSpawnManager::Update(const float& deltaTime, sf::RenderWindow& window)
{

	//******* Updating game based on the state of mario *******//

	switch (m_player->GetMarioState())
	{
	case EMarioState::Alive:
	{
		UpdateAlive(deltaTime, window);
		break;
	}
	case EMarioState::Dead:
	{
		m_player->UpdateDeath(deltaTime);
		break;
	}
	case EMarioState::Growing:
		break;
	case EMarioState::FallenInPit:
		break;
	case EMarioState::OnFire:
		break;
	default:
		break;

	}
}

void CSpawnManager::UpdateAlive(const float& deltaTime, sf::RenderWindow& window)
{
	// updates
	// player
	// enemy
	// collectibles
	// collectibles update
	// question block (for animation)
	for (auto& questionBlock : m_questionBlocks)
	{
		questionBlock.Update(deltaTime);
	}

	// player update
	m_player->Update(deltaTime); // update velocity of players and check for save and load as well

	for (auto goomba : m_goombas)
	{
		goomba->Update(deltaTime);

	}

	m_koopaTroopa->Update(deltaTime);

	// update collectibles

	for (auto& growthPower : m_growthPowers)
	{
		growthPower.Update(deltaTime);
	}

	for (auto& fireFlower : m_fireflowers)
	{
		fireFlower.Update(deltaTime);
	}

	for (auto& starPower : m_stars)
	{
		starPower.Update(deltaTime);
	}

	UpdateCollisions(deltaTime,window);

	// adjust camera view according to player position
	AdjustView();
}


void DrawBlocks(sf::RenderWindow& window, CLevelData& levelData, CAssetManager& assetManager)
{
	// draws question blocks
	sf::Sprite questionBlock(assetManager.GetSprite(EItems::Question_Block_1));;

	for (const sf::FloatRect& rect : levelData.GetObjectData(EObject::QUESTION))
	{
		questionBlock.setPosition(rect.left, rect.top);
		window.draw(questionBlock);
	}

	// draws brick blocks
	sf::Sprite brickBlock(assetManager.GetSprite(EItems::Brick));

	for (const sf::FloatRect& rect : levelData.GetObjectData(EObject::BRICK))
	{
		brickBlock.setPosition(rect.left, rect.top);
		window.draw(brickBlock);
	}

	// drawing flag
	sf::Sprite flag(assetManager.GetSprite(EItems::Flag));
	sf::Sprite flagPole(assetManager.GetSprite(EItems::Flag_Pole));
	for (const sf::FloatRect& rect : levelData.GetObjectData(EObject::FLAG_POLE))
	{
		flagPole.setPosition(rect.left, rect.top);
		flagPole.setScale(1.f, 8.5);
		window.draw(flagPole);
	}

	//drawing flagball
	sf::Sprite flagBall(assetManager.GetSprite(EItems::Flag_Ball_Top));
	for (const sf::FloatRect& rect : levelData.GetObjectData(EObject::FLAG_BALL))
	{
		flagBall.setPosition(rect.left, rect.top);
		window.draw(flagBall);
	}
}

void CSpawnManager::Draw()
{
	// background
	// bricks
	// enemies
	// collectibles
	// player
	// fireball

	m_game.GetRenderWindow().draw(m_assetManager->GetSprite(EItems::Background_1_1));

	//drawing flagpole
	sf::Sprite flagPole(m_assetManager->GetSprite(EItems::Flag_Pole));
	for (const sf::FloatRect& rect : m_levelData->GetObjectData(EObject::FLAG_POLE))
	{
		flagPole.setPosition(rect.left, rect.top);
		flagPole.setScale(1.f, 9.f);
		m_game.GetRenderWindow().draw(flagPole);
	}

	//Drawing flagboll
	sf::Sprite flagBall(m_assetManager->GetSprite(EItems::Flag_Ball_Top));
	for (const sf::FloatRect& rect : m_levelData->GetObjectData(EObject::FLAG_BALL))
	{
		flagBall.setPosition(rect.left, rect.top);
		m_game.GetRenderWindow().draw(flagBall);
	}

	// draw collectibles
	for (auto& growthPower : m_growthPowers)
	{
		growthPower.Draw(m_game.GetRenderWindow());
	}

	for (auto& fireFlower : m_fireflowers)
	{
		fireFlower.Draw(m_game.GetRenderWindow());
	}

	// draw question blocks
	for (auto& questionBlock : m_questionBlocks)
	{
		questionBlock.Draw(m_game.GetRenderWindow());
	}

	// draw brick blocks
	for (auto& brickBlock : m_brickBlocks)
	{
		brickBlock.Draw(m_game.GetRenderWindow());
	}

	// draw player 
	m_player->Render(m_game.GetRenderWindow());

	for (auto& goomba : m_goombas)
	{
		goomba->Draw(m_game.GetRenderWindow());
	}

	m_koopaTroopa->Draw(m_game.GetRenderWindow());

}



#pragma once
#include"PowerUps.h"
#include"Game.h"
#include "Enemyships.h"
//NukePowerUp Class Derived from PowerUps
class NukePowerUp : public PowerUps
{
public:
	/***************************
	*       CONSTRUCTORS      *
	****************************/
													NukePowerUp(std::unique_ptr<SpaceShip>& spaceS,
													std::vector<std::unique_ptr<Asteroids>>& asteroidsEnimies,
													std::vector<std::unique_ptr<Enemyships>>& enemyShips_,
													sf::Texture powerUpTex);
	/***************************
	*	OVERRIDEN FUNCTIONS	   *
	****************************/
	virtual sf::Sprite&								getPowerUpSprite()override;
	virtual void									powerUpTakeEffect()override;
	virtual void									setPowerUpTextAttributes() override;
	virtual Type									getType() override;

private:
	/***************************
	*PRIVATE POWERUP VARIABLES *
	****************************/

	bool											destroyAsteroidFlag;
	std::vector<std::unique_ptr<Asteroids>>&		enimiesAsteroids;
	std::vector<std::unique_ptr<Enemyships>>&		enemyShips;

	sf::Font										font;
};


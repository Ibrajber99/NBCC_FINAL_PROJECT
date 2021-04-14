#pragma once
#include"PowerUps.h"
#include"Game.h"
//healthPowerUp Class Derived from PowerUps
class HealthPowerUp : public PowerUps
{
public:
	/***************************
	 *       CONSTRUCTORS      *
	****************************/

														HealthPowerUp
														(std::unique_ptr<SpaceShip>& spaceS,
														std::vector<std::unique_ptr<Asteroids>>& enimies,
														sf::Texture powerUpTex);
	/***************************
	*	OVERRIDEN FUNCTIONS	   *
	****************************/
	virtual sf::Sprite&									getPowerUpSprite()override;
	virtual void										powerUpTakeEffect()override;
	virtual Type										getType() override;
	virtual void										setPowerUpTextAttributes() override;

private:
	/***************************
	*PRIVATE POWERUP VARIABLES *
	****************************/
	std::vector<std::unique_ptr<Asteroids>>&			enimiesAsteroids;

};


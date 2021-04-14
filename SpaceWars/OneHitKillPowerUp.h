#pragma once
#include"PowerUps.h"
#include"Game.h"
//OneHitKillPowerUp Class Derived from PowerUps
class OneHitKillPowerUp : public PowerUps
{
public:
	/***************************
	*       CONSTRUCTORS      *
	****************************/
													OneHitKillPowerUp(std::unique_ptr<SpaceShip>& spaceS,
													std::vector<std::unique_ptr<Asteroids>>& enimies,
													sf::Texture powerUpTex);
	
	/***************************
	*	OVERRIDEN FUNCTIONS	   *
	****************************/
    sf::Sprite&										getPowerUpSprite()override;
	virtual void									powerUpTakeEffect()override;
	virtual void									oneHitKillPowerUpTakeEffect(std::unique_ptr<Asteroids>&a);
	virtual Type									getType() override;
	virtual void									setPowerUpTextAttributes() override;

private:
	/***************************
	*PRIVATE POWERUP VARIABLES *
	****************************/
	std::vector<std::unique_ptr<Asteroids>>&		enimiesAsteroids;
	sf::Font										font;
};


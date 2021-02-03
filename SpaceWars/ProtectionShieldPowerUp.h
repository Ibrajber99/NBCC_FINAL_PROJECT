#pragma once
#include"PowerUps.h"
#include"Game.h"
//ProtectionShieldPowerUp Class Derived from PowerUps
class ProtectionShieldPowerUp : public PowerUps
{
public:
	/***************************
	*       CONSTRUCTORS      *
	****************************/
								ProtectionShieldPowerUp(std::unique_ptr<SpaceShip>& spaceS, std::vector<std::unique_ptr<Asteroids>>& enimies,sf::Texture powerUpTex);
	/***************************
	*	OVERRIDEN FUNCTIONS	   *
	****************************/
	sf::Sprite&					getPowerUpSprite()override;
    void						powerUpTakeEffect()override;
	virtual Type				getType() override;
	virtual void				setPowerUpTextAttributes() override;
private:
	/***************************
	*PRIVATE POWERUP VARIABLES *
	****************************/
	std::vector<std::unique_ptr<Asteroids>>& enimiesAsteroids;

};


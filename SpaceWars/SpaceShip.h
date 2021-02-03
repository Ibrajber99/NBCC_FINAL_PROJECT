#pragma once
#include "TextureAssests.h"
#include "Animation.h"
#include "Bullets.h"
#include <memory>
#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<iostream>

class PowerUpsHolder;

class SpaceShip {
public:
	/***************************
	*       CONSTRUCTOR        *
	****************************/

	SpaceShip(std::unique_ptr<TextureAssets>& textureHolder,
		sf::RenderWindow& window);

	enum class PowerUpType {
		None,
		Nuke,
		OneHitKill,
		Shield,
		Health,
		Radar
	};

	enum class Direction {
		LEFT,
		RIGHT,
		IDLE
	};


	/***************************
	*PUBLIC SPACESHIP FUNCTIONS *
	****************************/
	void								   draw();
	void								   update(std::unique_ptr<PowerUpsHolder>& powerUpsManager);
	sf::Vector2f						   getSpaceShipSpawnPosition();
	sf::Sprite&							   getSpaceShipSprite();
	std::vector<sf::Sprite>&			   getHealthMeter();
										   
	sf::Vector2f						   getSpaceShipCurrentPostion();
	sf::Vector2f						   getSpaceCenterPos();
	size_t								   getCurrHealth() const;
										   
	PowerUpType							   getCurrrentSpaceShipPowerUpType();
	void								   setDirection(Direction dir);
										   
	void								   moveSpaceShip(float dt);
	void								   beginSpaceShipAnimation();
	void								   setAnimationTrigger(bool b);
	void								   getHit();
	void								   setShipDestroyedState(bool b);
	void								   setShipImmunity(bool b);
	void								   setHealth(size_t m);
	void								   pushProjectiles();
	void								   flushProjectiles();
	void								   moveProjectiles();
	void								   pushProjectilesTimer();
	void								   setPowerUpType(PowerUpType type);
	void								   updateSpaceShipPowerType
										   (std::unique_ptr<PowerUpsHolder>& powerUpsManager);
										   
	bool								   isAnimationFinished();
	bool								   checkifAlive() const;
	bool								   isDestroyedStatus() const ;
	bool								   isShipImmune() const;


	std::vector<std::unique_ptr<PlayerBullets>>& getProjectilesMagazine();


private:
	sf::Vector2f						   getAccordingSpaceShipPosition();
	sf::Sprite&							   getAccordingSprite();
	std::vector<sf::Sprite>&			   generateHealthMeter();
	void								   pushAccordingProjectile();
	Direction							   getDirection() const;
	void								   updateSpriteOnDirection();
	void								   resetLifeBar();
	void								   decreaseLifeBar();

	/***************************		   
	*PRIVATE ASTEROID VARIABLES *		   
	****************************/		   
	std::unique_ptr<Animation>             spaceShipExplosionAnimation;
	std::vector<std::unique_ptr<PlayerBullets>>  projectilesMagazine;
										   
										   
	sf::Sprite							   spaceShipSprite;
	sf::Sprite							   spaceShipShieldedSprite;
	sf::Sprite							   spaceShipExplosionSprite;
										   
	sf::Texture							   spaceShipTexture;
	sf::Texture							   healthBarTexture;
										   
	sf::Texture							   normalBulletTex;
	sf::Texture							   animatedBulletTex;
	sf::Texture							   specialBulletCollisionTex;
	sf::Texture							   normalBulletCollisionTex;
	std::vector<sf::Sprite>				   playerHealth;
	std::map<Direction,sf::Texture>		   spaceShipTexturesMap;

	size_t								   health;
										   
	sf::Clock							   clockDirection;
										   
	sf::RenderWindow& window;			   
										   
	bool								   isAlive;
	bool								   movingForward;
	bool								   isShipDestroyed;
	bool								   animationFinished;
	bool								   animationBegan;
	bool								   shipImmunity;
	bool								   shipInvincibility;
										   
	sf::Clock							   clock;
	sf::Clock							   clock1;
	sf::Clock							   invincibilityClock;
	PowerUpType							   currentPowerUp;
	Direction							   currDirection;
	sf::RectangleShape					   lifeBar;

	bool canMoveUp();
	bool canMoveDown();
	bool canMoveLeft();
	bool canMoveRight();
};
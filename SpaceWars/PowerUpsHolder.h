#pragma once
#include <memory>
#include "PowerUps.h"
#include "Saucer.h"
#include "Enemyships.h"
class PowerUpsHolder
{

public:
	PowerUpsHolder(std::unique_ptr<SpaceShip>& spaceS
		, std::vector<std::unique_ptr<Asteroids>>& asteroidsEnimies
		, std::vector<std::unique_ptr<Enemyships>>& enemyShips
		,std::unique_ptr<Saucer>&saucer
		,std::unique_ptr<TextureAssets> &textureHolder
		, sf::RenderWindow& window);

	void															draw();
	void															drawPowerUps();
	void															update();
	void															movePowerUps();
	void															powerUpTrigger();
	void															fillPowerUps();
	void															loadPowerUpQueue();
	void															drawPowerUpHud();
	void															flushConsumedPowerUps();
	void															initializePowerUpHud(sf::Sprite& hudPowerUp);
	std::vector<std::pair<std::unique_ptr<PowerUps>, bool>>&		getPowerUpContainer();
private:
	void															flushPowerUpContainer();
	bool															isCurrentPowerUpInBounds();

	sf::RenderWindow&												window;
	std::deque<std::unique_ptr<PowerUps>>							powerUpQueue;
	std::vector<std::pair<std::unique_ptr<PowerUps>, bool>>			powerUpContainer;
	std::unique_ptr<SpaceShip>&										spaceShip;
	std::unique_ptr<Saucer>&										saucerObj;
	std::vector<std::unique_ptr<Asteroids>>&						asteroid;
	std::vector<std::unique_ptr<Enemyships>>&						enemyShips;
	sf::Texture														nukePowerUpTex;
	sf::Texture														shieldPowerUpTex;
	sf::Texture														healthPowerUpTex;
	sf::Texture														oneHitKillPowerUpTex;
	sf::Texture														radarPowerUpTex;
	sf::Sprite														PowerUpHud;
	std::random_device												rd;
	sf::Clock														clock;
	sf::Clock														fillPowerUpClock;
};
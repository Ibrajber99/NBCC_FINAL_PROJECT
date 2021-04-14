#pragma once
#include <memory>
#include "PowerUps.h"
#include "Saucer.h"
#include "Enemyships.h"
class PowerUpsHolder
{

public:
	PowerUpsHolder(
		  std::unique_ptr<SpaceShip>& spaceS
		, std::vector<std::unique_ptr<Asteroids>>& asteroidsEnimies
		, std::vector<std::unique_ptr<Enemyships>>& enemyShips
		, std::unique_ptr<Saucer>&saucer
		, std::unique_ptr<TextureAssets> &textureHolder
		, sf::RenderWindow& window);

	void															draw();
	void															update();
	std::vector<std::pair<std::unique_ptr<PowerUps>, bool>>&		getPowerUpContainer();
	void															fillPowerUps();

private:
	void															drawPowerUps();
	void															movePowerUps();
	void															powerUpTrigger();
	void															loadPowerUpQueue();
	void															drawPowerUpHud();
	void															flushConsumedPowerUps();
	void															initializePowerUpHud(sf::Sprite& hudPowerUp);
	void															flushPowerUpContainer();
	bool															isCurrentPowerUpInBounds();

	std::vector<std::pair<std::unique_ptr<PowerUps>, bool>>			powerUpContainer;
	sf::RenderWindow&												window;
	std::deque<std::unique_ptr<PowerUps>>							powerUpQueue;
	std::unique_ptr<SpaceShip>&										spaceShip;
	std::unique_ptr<Saucer>&										saucerObj;
	std::vector<std::unique_ptr<Asteroids>>& asteroid;
	std::vector<std::unique_ptr<Enemyships>>& enemyShips;

	sf::Texture														nukePowerUpTex;
	sf::Texture														shieldPowerUpTex;
	sf::Texture														healthPowerUpTex;
	sf::Texture														oneHitKillPowerUpTex;
	sf::Texture														radarPowerUpTex;

	sf::Sprite														powerUpHud;
	sf::Sprite														powerUpHudBlock;

	std::random_device												rd;
	sf::Clock														clock;
	sf::Clock														fillPowerUpClock;
};
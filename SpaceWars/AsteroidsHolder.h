#pragma once
#include "Asteroids.h"
#include "LargeAsteroid.h"
#include "SmallAsteroid.h"
#include <SFML/Graphics.hpp>

class AsteroidsHolder
{
public:
									    AsteroidsHolder(std::unique_ptr<TextureAssets>&textureHolder
									   	 , sf::RenderWindow& window);


public:
	void								update();
	void								createSmallAsteroids(sf::Vector2f coords);
	void								createLargeAsteroids(sf::Vector2f coords);
	void								loadAsteroid();
	void								flushDestroyedAsteroids();
	void								updateAsteroidAnimation();
	void								drawAsteroids();
	void								moveAsteroids();
	void								clearAsteroids();
	void								lockUpdateMovement();
	void								unlockUpdateMovement();
	void								destroyAsteroids();
	std::vector<std::unique_ptr<Asteroids>>    asteroidsContainer;
private:
	void								pushAsteroids();
	void								generateSpawnPositions(size_t size);

	sf::RenderWindow&					window;
	
	std::random_device					rd;

	//Textures
	sf::Texture							smallAsteroidTex;
	sf::Texture							largeAsteroidTex;
	sf::Texture							smallAsteroidExplosionTex;
	sf::Texture							largeAsteroidExplosionTex;
	sf::Clock							clock;
	sf::Clock							asteroidMoveClock;
	bool								movementFlag;
	sf::IntRect							spawnGrid;
	std::map<int, int>					gridCoords;
};


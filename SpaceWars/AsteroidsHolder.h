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

void									loadAsteroid();
void									destroyAsteroids();
void									drawAsteroids();
void									update();
void									lockUpdateMovement();
void									unlockUpdateMovement();

std::vector<std::unique_ptr<Asteroids>> asteroidsContainer;
public:
	void								createSmallAsteroids(sf::Vector2f coords);
	void								createLargeAsteroids(sf::Vector2f coords);
	void								flushDestroyedAsteroids();
	void								updateAsteroidAnimation();
	void								moveAsteroids();
	void								clearAsteroids();
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


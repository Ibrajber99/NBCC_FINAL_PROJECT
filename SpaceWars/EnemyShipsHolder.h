#pragma once
#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include "TextureAssests.h"
#include "Enemyships.h"
#include <vector>
#include <random>

class EnemyShipsHolder
{

public:

	EnemyShipsHolder(std::unique_ptr<TextureAssets>& textureHolder,
		sf::RenderWindow& w);

	void update();
	void draw();

	std::vector<std::unique_ptr<Enemyships>>
												& getEnemyShipsContainer();
	std::vector<std::unique_ptr<Enemyships>>	enemyShipsContainer;

	void										destroyShips();
private:
	void flushDestroyedObjects();
	void loadEnemyShips();
	void generateSpawnPositions(size_t size);
	void pushEnemySpaceShips();
	void createShip(sf::Vector2f pos);

private:
	sf::Texture	enemySpaceShipTexture;
	sf::IntRect spawnGrid;
	TextureAssets& textureholderRef;
	sf::RenderWindow& windowRef;

	std::map<float, float>gridCoords;
	std::random_device rd;

	sf::Clock    loadTimer;

};


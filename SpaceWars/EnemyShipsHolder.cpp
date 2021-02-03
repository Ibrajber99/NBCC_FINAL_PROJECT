#include "EnemyShipsHolder.h"


EnemyShipsHolder::EnemyShipsHolder(std::unique_ptr<TextureAssets>& textureHolder, sf::RenderWindow& w)
	: enemyShipsContainer()
	, spawnGrid(0, 0, 0, 0)
	, textureholderRef(*textureHolder.get())
	, windowRef(w)
	, loadTimer(sf::Clock())
{
	enemySpaceShipTexture = textureholderRef.getSmallEnemyTex();
}

void EnemyShipsHolder::update()
{
	loadEnemyShips();
	for (auto& ships : enemyShipsContainer) {
		ships->update();
	}
	flushDestroyedObjects();
}

void EnemyShipsHolder::draw()
{
	for (auto& ships : enemyShipsContainer) {
		ships->draw();
	}
}

void EnemyShipsHolder::destroyShips()
{
	for (auto& enemyShips : enemyShipsContainer) {
		enemyShips->damage(3);
		enemyShips->flushBullets();
	}
}

void EnemyShipsHolder::flushDestroyedObjects()
{
	enemyShipsContainer.erase(
		std::remove_if(enemyShipsContainer.begin(), enemyShipsContainer.end(),
			[](auto& ship) {
				return ship->isOutofBounds() ||
					ship->isDestroyed();
			}), enemyShipsContainer.end());
}

void EnemyShipsHolder::loadEnemyShips()
{
	if (loadTimer.getElapsedTime().asSeconds() > 10.f) {
		pushEnemySpaceShips();
		loadTimer.restart();
	}
}

void EnemyShipsHolder::generateSpawnPositions(size_t size)
{

	spawnGrid.width = windowRef.getSize().x / enemySpaceShipTexture.getSize().x;
	spawnGrid.height = windowRef.getSize().y / enemySpaceShipTexture.getSize().y;

	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distribX(0, spawnGrid.width - 1);
	std::uniform_int_distribution<> distribY(0, spawnGrid.height - 1);

	while (gridCoords.size() < size) {
		gridCoords[distribX(gen)] = distribY(gen);
	}
}

void EnemyShipsHolder::pushEnemySpaceShips()
{
	std::mt19937 gen(rd());
	std::uniform_int_distribution<>distrAmount(5, 10);
	int size = distrAmount(gen);

	generateSpawnPositions(size);
	auto coordsItr = gridCoords.begin();
	for (int i = 0; i < size; i++) {
		createShip(sf::Vector2f(coordsItr->first, coordsItr->second));
		coordsItr++;
	}
}

void EnemyShipsHolder::createShip(sf::Vector2f pos)
{
	enemyShipsContainer.push_back(std::make_unique<Enemyships>
		(textureholderRef.getSmallEnemyTex(), textureholderRef.getSmallEnemyBulletTex(),
			textureholderRef.getSmallEnemyShipExplosion(), windowRef));

	enemyShipsContainer.back()->
		setPosition(sf::Vector2f(pos.x * enemySpaceShipTexture.getSize().x
			, -pos.y * enemySpaceShipTexture.getSize().y));
}

std::vector<std::unique_ptr<Enemyships>>& EnemyShipsHolder::getEnemyShipsContainer()
{
	return enemyShipsContainer;
}

#include "AsteroidsHolder.h"


//Constructor
AsteroidsHolder::AsteroidsHolder(
	std::unique_ptr<TextureAssets>& textureHolder,
	sf::RenderWindow& window)
	:window(window)
	,asteroidsContainer()
	,movementFlag(true)
{
	smallAsteroidTex = std::move(textureHolder->getSmallAsteroid());
	largeAsteroidTex = std::move(textureHolder->getLargeAsteroid());

	smallAsteroidExplosionTex = 
		std::move(textureHolder->getSmallAsteroidExplosion());

	largeAsteroidExplosionTex = 
		std::move(textureHolder->getLargeAsteroidExplosion());
}

void AsteroidsHolder::pushAsteroids()
{
	std::mt19937 gen(rd());
	std::uniform_int_distribution<>distrAmount(5, 10);
	int size = distrAmount(gen);

	generateSpawnPositions(size);

	auto coordsItr = gridCoords.begin();
	for (int i = 0; i < size; i++) {
		i % 2 == 0 ? 
			createLargeAsteroids
			(sf::Vector2f(coordsItr->first, coordsItr->second))
			: createSmallAsteroids
			(sf::Vector2f(coordsItr->first, coordsItr->second));

		coordsItr++;
	}
}

void AsteroidsHolder::update()
{
	updateAsteroidAnimation();
	unlockUpdateMovement();
	moveAsteroids();
	loadAsteroid();
	flushDestroyedAsteroids();
}

void AsteroidsHolder::createSmallAsteroids(sf::Vector2f coords)
{
	asteroidsContainer.push_back(std::make_unique<SmallAsteroid>
		(smallAsteroidExplosionTex, smallAsteroidTex));

	asteroidsContainer.back()->setAsteroidPos
	(sf::Vector2f(coords.x * largeAsteroidTex.getSize().x,
		-coords.y * largeAsteroidTex.getSize().y));
}

void AsteroidsHolder::createLargeAsteroids(sf::Vector2f coords)
{

	asteroidsContainer.push_back(std::make_unique<LargeAsteroid>
		(largeAsteroidExplosionTex, largeAsteroidTex));

	asteroidsContainer.back()->setAsteroidPos
	(sf::Vector2f(coords.x* largeAsteroidTex.getSize().x,
		-coords.y * largeAsteroidTex.getSize().y));
}

void AsteroidsHolder::loadAsteroid()
{
	if (clock.getElapsedTime().asSeconds() > 10.f) {
		pushAsteroids();
		clock.restart();
	}
}

void AsteroidsHolder::flushDestroyedAsteroids()
{
	asteroidsContainer.erase(std::remove_if(
		asteroidsContainer.begin(), asteroidsContainer.end(),
		[&](auto& asteroid)
		{
			return asteroid->isAsteroidReadyToFlush(window);
		}),asteroidsContainer.end() );
}

void AsteroidsHolder::updateAsteroidAnimation()
{
	std::for_each(asteroidsContainer.begin(), 
		asteroidsContainer.end(), [&](auto& asteroid) {

		if (asteroid->isAsteroidDestroyed()) {
			asteroid->beginAsteroidAnimation();
		}
	});
}

void AsteroidsHolder::drawAsteroids()
{
	for (auto& asteroid : asteroidsContainer) {
		asteroid->drawAsteroid(window);
	}
}

void AsteroidsHolder::moveAsteroids()
{	for (auto& asteroid : asteroidsContainer) {
		if (!movementFlag) {
			asteroid->moveAsteroid(0);
		}
		else {
			asteroid->moveAsteroid(sf::seconds(1.f / 60.f).asSeconds());
		}
	}
}

void AsteroidsHolder::clearAsteroids()
{
	asteroidsContainer.clear();
}

void AsteroidsHolder::lockUpdateMovement()
{
	movementFlag = false;
}

void AsteroidsHolder::unlockUpdateMovement()
{
	movementFlag = true;
}

void AsteroidsHolder::destroyAsteroids()
{
	for (auto& asteroid : asteroidsContainer) {
		asteroid->setIsDestroyed(true);
	}
}

//This function slices the view to a grid and genrates postions where asteroids won't overlap
void AsteroidsHolder::generateSpawnPositions(size_t size) {
	spawnGrid.width = window.getSize().x / largeAsteroidTex.getSize().x;
	spawnGrid.height = window.getSize().y / largeAsteroidTex.getSize().y;

	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distribX(0,spawnGrid.width-1);
	std::uniform_int_distribution<> distribY(0,spawnGrid.height-1);

	while (gridCoords.size() < size) {
		gridCoords[distribX(gen)] = distribY(gen);
	} 
}

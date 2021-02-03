#include "EnemySpaceShip.h"



float EnemySpaceShip::speed = 4.5f;
float EnemySpaceShip::bulletSpeed = 6.f;


//EnemySpaceShip constructor that takes a reference to the texture of the ship, the bullet and the explosion of the ship textures.
EnemySpaceShip::EnemySpaceShip(std::unique_ptr<TextureAssets>& textureHolder)
	:bulletAnimation(std::make_unique<Animation>
		(textureHolder->getEnemyBullet()
			, sf::Vector2u(2, 3), .3f))
	, shipExplosionAnimation(std::make_unique<Animation>
		(textureHolder->getEnemyShipExplosion()
			, sf::Vector2u(5, 4), .3f))

	, spaceShip(textureHolder->getEnemySpaceSHip())
	, texturesHolder(*textureHolder.get())
	, shipAlive(true)
	, readyToSpawn(0)
	, lifeCounter(15)
	, isRight(true)
	, isLeft(true)
	, moveFlag(true)
	, canShootBullets(true)
{

	setSpaceShipToSpawnPos();
	spaceShipExplosion.setPosition(spaceShip.getPosition());
}

//returns spaceShip sprite.
sf::Sprite& EnemySpaceShip::getSpaceShip()
{
	return spaceShip;
}

void EnemySpaceShip::draw(sf::RenderWindow& window)
{
	drawBullets(window);
	drawSpaceShip(window);
}

//moves the enemy space ship from the left to the right on the renderWindow accordingly to the window size
void EnemySpaceShip::moveSpaceShip(sf::RenderWindow& w)
{
	if (isShipAlive()) {
		if (spaceShip.getPosition().x +
			spaceShip.getGlobalBounds().width > w.getSize().x) {
			isLeft = 1;
			isRight = 0;
		}
		if (spaceShip.getPosition().x +
			spaceShip.getGlobalBounds().width < 0) {
			isLeft = 0;
			isRight = 1;
		}
		if (isLeft) {
			moveLeft();
		}

		if (isRight) {
			moveRight();
		}
	}
}

//sets the bullet direction
void EnemySpaceShip::setBulletDirection(sf::Vector2f playerSpaceShip)
{
	sf::Vector2f aimDir;
	aimDir = playerSpaceShip - spaceShip.getPosition();
	sf::Vector2f aimDirNorm;
	aimDirNorm = aimDir / (float)sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2));
	currVelocity = aimDirNorm * bulletSpeed;

	pushBullets(currVelocity);
}

//moves bullet sprite into the magazine Vector
void EnemySpaceShip::moveBullet()
{
	if (moveFlag) {
		for (auto& i : bulletMagazine) {
			i.first.move(i.second);
		}
	}
}

//initializes bullet position  and sets the scale
void EnemySpaceShip::initBullets()
{
	for (auto& bullets : bulletMagazine) {
		sf::Vector2f pos;
		pos.x = bullets.first.getPosition().x;
		pos.y = bullets.first.getPosition().y;
		if (bulletAnimation->isAnimationFinished()) {
			bulletAnimation->reSetIterations();
		}
		bulletAnimation->update();
		bullets.first = std::move(bulletAnimation->getCurrAnimation(pos));
		bullets.first.setScale(1.3f, 1.3f);
	}
}

//starts the ship explosion animation
void EnemySpaceShip::beginShipExplosion()
{
	if (!isShipAlive()) {
		sf::Vector2f pos;
		pos.x = spaceShip.getPosition().x;
		pos.y = spaceShip.getPosition().y;
		if (shipExplosionAnimation->isAnimationFinished()) {
			shipAlive = 1;
			lifeCounter = 15;
		}
		else {
			shipExplosionAnimation->update();
			spaceShipExplosion = std::move(shipExplosionAnimation->getCurrAnimation(pos));
		}
	}
}

void EnemySpaceShip::resetDifficulty()
{
	speed = 4.5f;
	bulletSpeed = 6.f;
}

//draws the initialized and scaled bullets on the render window.
void EnemySpaceShip::drawBullets(sf::RenderWindow& w)
{
	initBullets();
	for (auto& bullets : bulletMagazine) {
		w.draw(bullets.first);
	}

}

//draws the spaceship, if spaceship is not alive then draws the explosion animation on the window.
void EnemySpaceShip::drawSpaceShip(sf::RenderWindow& w)
{
	beginShipExplosion();
	if (isShipAlive())
		w.draw(getSpaceShip());
	else
		w.draw(spaceShipExplosion);
}

//flushes bullets from the render view.
void EnemySpaceShip::flushBullets(sf::RenderWindow& w)
{
	if (!bulletMagazine.empty()) {
		bulletMagazine.erase(std::remove_if(bulletMagazine.begin(), bulletMagazine.end(),
			[&](std::pair<sf::Sprite, sf::Vector2f>& p) {
				return p.first.getPosition().y - p.first.getGlobalBounds().height
			> w.getSize().y;
			}), bulletMagazine.end());
	}
}

void EnemySpaceShip::update(sf::RenderWindow& w)
{
	moveSpaceShip(w);
	moveBullet();
	unlockUpdateMovement();
	flushBullets(w);

	if (!isShipAlive()) {
		setShipIsReadyToSpawn();
	}

	if (isShipReadyToSpawn()
		&& isAnimationFinished() &&!isShipAlive()) {
		this->setSpaceShipToSpawnPos();
		this->shipAlive = true;
		moveFlag = true;
	}
}

//enemy spaceship gets hit and loses a life
void EnemySpaceShip::getHit()
{
	lifeCounter -= 1;
	if (lifeCounter <= 0) {
		shipAlive = 0;
	}
}

//moves the bullet off screen
void EnemySpaceShip::flushBulletAt(size_t i)
{
	bulletMagazine.at(i).first.move(0.0f, 1000.f);
}

//returns shipAlive 
bool EnemySpaceShip::isShipAlive()
{
	return shipAlive;
}

//returns readyToSpawn
bool EnemySpaceShip::isShipReadyToSpawn()
{
	return readyToSpawn;
}

void EnemySpaceShip::setShipIsReadyToSpawn()
{
	readyToSpawn = true;
}

void EnemySpaceShip::clearMagazine()
{
	bulletMagazine.clear();
}

bool EnemySpaceShip::isAnimationFinished()
{
	return shipExplosionAnimation->isAnimationFinished();
}

void EnemySpaceShip::lockUpdateMovement()
{
	moveFlag = false;
}

void EnemySpaceShip::unlockUpdateMovement()
{
	moveFlag = true;
}

bool EnemySpaceShip::isCanShootBullets()
{
	return canShootBullets;
}

void EnemySpaceShip::lockBulletsMovement()
{
	canShootBullets = false;
}

void EnemySpaceShip::releaseBullets()
{
	if (!isCanShootBullets() &&
		shootBulletClock.getElapsedTime().asSeconds() > 4.f) {
		canShootBullets = true;
	}

}

void EnemySpaceShip::setSpaceShipToSpawnPos()
{
	spaceShip.setPosition(getSpaceShipSpawnPostion());
}

void EnemySpaceShip::destroyShip()
{
	shipAlive = false;
}

void EnemySpaceShip::resetSpaceShipAttributes()
{
	resetDifficulty();
}

//returns bulletMagazine
std::vector<std::pair<sf::Sprite, sf::Vector2f>>& EnemySpaceShip::getBulletMagazine()
{
	return bulletMagazine;
}

//returns  center of the spaceShip position
sf::Vector2f EnemySpaceShip::getSpaceShipCenter()
{
	return spaceShip.getPosition();
}

sf::Vector2f EnemySpaceShip::getSpaceShipSpawnPostion()
{
	return sf::Vector2f(120.f, 20.0f);
}

//sets movement towards left
void EnemySpaceShip::moveLeft()
{

	if (moveFlag) {
		float delta = moveClock.restart().asSeconds();

		spaceShip.move(-400.2f * delta, 0.0f);
		moveClock.restart();
	}
	else {
		moveClock = sf::Clock();
	}

}

//sets movevement towards right
void EnemySpaceShip::moveRight()
{
	if (moveFlag) {
		float delta = moveClock.restart().asSeconds();
		spaceShip.move(400.2f * delta, 0.0f);
		moveClock.restart();
	}
	else {
		moveClock = sf::Clock();
	}
}

//pushes bullets in the vector
void EnemySpaceShip::pushBullets(sf::Vector2f& shootDir)
{
	if (clock.getElapsedTime().asSeconds() > speed && isShipAlive() && moveFlag) {
		sf::Sprite tmp;
		tmp = bulletSprite;
		tmp.setPosition(spaceShip.getPosition().x, spaceShip.getPosition().y);
		bulletMagazine.push_back({ tmp,shootDir });


		speed -= 0.16;
		if (speed < 0.0f) {
			speed = 1.5f;
		}
		bulletSpeed += 0.1;
		clock.restart();
	}
}


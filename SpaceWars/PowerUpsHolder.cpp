#include "PowerUpsHolder.h"
#include "HealthPowerUp.h"
#include "OneHitKillPowerUp.h"
#include "NukePowerUp.h"
#include "ProtectionShieldPowerUp.h"
#include "RadarPowerUp.h"


PowerUpsHolder::PowerUpsHolder(std::unique_ptr<SpaceShip>& spaceS,
	std::vector<std::unique_ptr<Asteroids>>& asteroidsEnimies,
	std::vector<std::unique_ptr<Enemyships>>& enemyShips,
	std::unique_ptr<Saucer>& saucer,
	std::unique_ptr<TextureAssets>& textureHolder,
	sf::RenderWindow& window)

	: window(window)
	, asteroid(asteroidsEnimies)
	, spaceShip(spaceS)
	, saucerObj(saucer)
	, enemyShips(enemyShips)
	, clock(sf::Clock())
{
	nukePowerUpTex = std::move(textureHolder->getNukePowerUp());
	shieldPowerUpTex = std::move(textureHolder->getProtectionShieldPowerUp());
	oneHitKillPowerUpTex = std::move(textureHolder->getOneHitKillPowerUp());
	healthPowerUpTex = std::move(textureHolder->getHealthRegainPowerUp());
	radarPowerUpTex = std::move(textureHolder->getRadarPowerUp());

	powerUpHudBlock.setTexture(textureHolder->getPowerUpHudBlock());
	powerUpHudBlock.setScale(0.4f, 0.5f);
	powerUpHudBlock.setPosition(sf::Vector2f(1700.0f, 860.f));
}

void PowerUpsHolder::draw()
{
	drawPowerUps();
	window.draw(powerUpHudBlock);
	drawPowerUpHud();
}


void PowerUpsHolder::drawPowerUps()
{
	if (!getPowerUpContainer().empty()) {
		if (getPowerUpContainer().back().second == true) {
			window.draw(getPowerUpContainer().
				back().first->getPowerUpText());
		}
	}
	for (auto& powerUp : powerUpContainer) {
		window.draw(powerUp.first->getPowerUpSprite());
	}
}


void PowerUpsHolder::update()
{
	powerUpTrigger();
	movePowerUps();
	flushConsumedPowerUps();
}


void PowerUpsHolder::movePowerUps()
{
	if (!getPowerUpContainer().empty()) {
		if (getPowerUpContainer().back().second == true) {
			getPowerUpContainer().
				back().first->movePowerUpText(-30.f);
			
			getPowerUpContainer().
				back().first->flushText();
		}
	}

	for (auto& powerUp : powerUpContainer) {
		powerUp.first->movePowerUpOnScreen();
	}
}


void PowerUpsHolder::powerUpTrigger()
{
	if (!powerUpQueue.empty() && powerUpContainer.size() < 1) {
		clock.restart();
		powerUpContainer.push_back({ std::move(powerUpQueue.front()),0 });
		powerUpQueue.pop_front();
	}
	if (powerUpQueue.empty())
		fillPowerUps();
}


void PowerUpsHolder::fillPowerUps()
{
	if (powerUpQueue.empty()) {
		if (fillPowerUpClock.getElapsedTime().asSeconds() > 20.f) {
			loadPowerUpQueue();
			std::for_each(std::execution::par, powerUpQueue.begin(), powerUpQueue.end(),
				[&](auto& powerUp) {
					powerUp->setpowerUpSpawnPos(window);
					powerUp->initPowerUpTextPos();
				});
			fillPowerUpClock.restart();
		}
	}
	std::mt19937 g(rd());
	std::shuffle(powerUpQueue.begin(), powerUpQueue.end(), g);
}


void PowerUpsHolder::loadPowerUpQueue()
{

  	powerUpQueue.
		push_back(std::make_unique<HealthPowerUp>(spaceShip, asteroid, healthPowerUpTex));
	powerUpQueue.
		push_back(std::make_unique<OneHitKillPowerUp>(spaceShip, asteroid, oneHitKillPowerUpTex));
	powerUpQueue
		.push_back(std::make_unique<NukePowerUp>(spaceShip, asteroid, enemyShips,nukePowerUpTex));
	powerUpQueue
		.push_back(std::make_unique<ProtectionShieldPowerUp>(spaceShip, asteroid, shieldPowerUpTex));
	powerUpQueue
		.push_back(std::make_unique<RadarPowerUp>(saucerObj, radarPowerUpTex));
}


void PowerUpsHolder::drawPowerUpHud()
{
	if (!getPowerUpContainer().empty()) {
		initializePowerUpHud(powerUpHud);
		if (getPowerUpContainer()[0].second == 1) {
			window.draw(powerUpHud);
		}
	}
}


void PowerUpsHolder::flushConsumedPowerUps()
{
	if (!isCurrentPowerUpInBounds()
		&& getPowerUpContainer().back().second == false) {
		flushPowerUpContainer();
	}

	if (!getPowerUpContainer().empty()
		&& getPowerUpContainer().back().second == true) {

		if (clock.getElapsedTime().asSeconds() > 30.f) {
			flushPowerUpContainer();
			clock.restart();
		}
	}

}


void PowerUpsHolder::initializePowerUpHud(sf::Sprite& hudPowerUp)
{
	hudPowerUp = std::move
	(powerUpContainer[0].first.get()->getPowerUpSprite());

	hudPowerUp.setPosition(sf::Vector2f(1700.0f, 864.f));
}


std::vector<std::pair<std::unique_ptr<PowerUps>, bool>>&
PowerUpsHolder::getPowerUpContainer()
{
	return powerUpContainer;
}


void PowerUpsHolder::flushPowerUpContainer()
{
	if (!getPowerUpContainer().empty()) {

		if ((getPowerUpContainer().front().first->getType() == PowerUps::Type::sheild
			|| getPowerUpContainer().front().first->getType() == PowerUps::Type::Radar)
			&& getPowerUpContainer().front().second == 1)
		{
			getPowerUpContainer().front().first->powerUpTakeEffect();
		}

		getPowerUpContainer().pop_back();
	}
}


bool PowerUpsHolder::isCurrentPowerUpInBounds()
{
	if (!getPowerUpContainer().empty()) {
		return getPowerUpContainer().back().first->getPowerUpSprite().getPosition().y
			+ getPowerUpContainer().back().first->getPowerUpSprite().getGlobalBounds().height
			< window.getSize().y;
	}
	else {
		return true;
	}
}

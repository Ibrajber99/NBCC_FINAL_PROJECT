#include "Enemyships.h"

Enemyships::Enemyships(sf::Texture& shipTex, sf::Texture& bulletTex,
	sf::Texture& destructionAnimation, sf::RenderWindow& w)
	: window(w)
	, hitpoints(3)
	, bounds(1000.f)
	, movePerSec(sf::seconds(1.f / 60.f))
	, shipSpeed(300.f)
	, shootingTimer(sf::Clock())
	, destructionBegan(false)
{
	spaceShipsprite.setTexture(std::move(shipTex));
	bulletTexture = std::move(bulletTex);

	animation = std::make_unique<Animation>
		(destructionAnimation, sf::Vector2u(17, 1), .1f);
}

sf::Sprite& Enemyships::getShipSprite()
{
	return spaceShipsprite;
}


void Enemyships::setPosition(sf::Vector2f pos)
{
	getShipSprite().setPosition(pos);
}


bool Enemyships::isOutofBounds()
{
	return getShipSprite().getPosition().y >= bounds;
}


bool Enemyships::isDestructionAnimationFinished()
{
	return animation->isAnimationFinished();
}


bool Enemyships::isDestructionAnimationBegan()
{
	return destructionBegan;
}


int Enemyships::getHitPoints()
{
	return hitpoints;
}


std::vector<sf::Sprite>& Enemyships::getBulletsContainer()
{
	return bulletsMagazine;
}


void Enemyships::flushBullets()
{
	if (destroyed) {
		std::for_each(bulletsMagazine.begin(), bulletsMagazine.end(),
			[&](sf::Sprite& bullet) {return bullet.move(sf::Vector2f(0, 1000.f)); });

		bulletsMagazine.clear();
	}

	bulletsMagazine.erase(std::remove_if(bulletsMagazine.begin(), bulletsMagazine.end(),
		[&](sf::Sprite& bullet) {
			return bullet.getPosition().y > bounds;
		}), bulletsMagazine.end());
}


void Enemyships::beginShipDestruction()
{

	destructionBegan = true;
	sf::Vector2f pos;
	pos.x = getShipSprite().getPosition().x;
	pos.y = getShipSprite().getPosition().y;

	if (!animation->isAnimationFinished()) {
		animation->update();
		spaceShipsprite =
			std::move(animation->getCurrAnimation(pos));
	}
}


void Enemyships::update()
{
	if (destroyed)
		beginShipDestruction();
	else {
		updateMovmentPattern();
		pushBullets();
	}

	flushBullets();
}


void Enemyships::draw()
{
	window.draw(spaceShipsprite);
	for (auto& bullet : bulletsMagazine) {
		window.draw(bullet);
	}
}


void Enemyships::damage(int hit)
{
	hitpoints -= hit;
	if (hitpoints <= 0)
		destroyed = true;
}


bool Enemyships::isDestroyed() const
{
	return (destroyed) && animation->isAnimationFinished();
}


void Enemyships::pushBullets()
{
	if (shootingTimer.getElapsedTime().asSeconds() > 2.f) {
		sf::Sprite bullet;
		bullet.setTexture(bulletTexture);
		bullet.setPosition(spaceShipsprite.getPosition().x,
			spaceShipsprite.getPosition().y);

		bulletsMagazine.push_back(bullet);
		shootingTimer.restart();
	}
}


void Enemyships::updateMovmentPattern()
{
	sf::Vector2f moveSpeed;
	moveSpeed.x = 0;
	moveSpeed.y = movePerSec.asSeconds() * shipSpeed;
	spaceShipsprite.move(moveSpeed);

	for (auto& bullet : bulletsMagazine) {
		bullet.move(0, movePerSec.asSeconds() * 700.f);
	}
}


#include "Bullets.h"

//Player bullet constructor takes normalBulletTexture as a reference and the animatedBullet texture
PlayerBullets::PlayerBullets(
	sf::Texture& normalBulletTexture,
	sf::Texture& bulletCollisionAnime)
{
	bulletTravelDistance = 800.f;
	bulletSprite.setTexture(normalBulletTexture);
	bulletAnime_flag = 0;
	bulletsCollided = 0;

	bulletCollisionAnimation = std::make_unique<Animation>(bulletCollisionAnime,
		sf::Vector2u(8, 1), .3f);
}


PlayerBullets::PlayerBullets(
	sf::Texture animatedBullet,
	sf::Texture bulletCollisionAnime,
	bool isBulletAnimated)
{
	bulletTravelDistance = 800.f;
	bulletAnime_flag = isBulletAnimated;
	bulletsCollided = false;
	bulletFiredAnimation = std::make_unique<Animation>(animatedBullet,
		sf::Vector2u(2, 3), .3f);

	bulletCollisionAnimation = std::make_unique<Animation>(bulletCollisionAnime,
		sf::Vector2u(10, 1), .3f);
}


//Enemy bullet constructor that takes in Vector2f aimDirNorm
//this is done to shoot the last know location of the mouse to hit the player.
PlayerBullets::PlayerBullets(sf::Vector2f aimDirNorm)
{
	bulletTravelDistance = 800.f;
	bulletAnime_flag = 0;
	aimDirectionNormalized = aimDirNorm / (float)sqrt(pow(aimDirNorm.x, 2) + pow(aimDirNorm.y, 2));		

}


sf::Sprite PlayerBullets::getBulletSprite()
{
	return bulletSprite;
}

//starts the shooting animation of the bullet
void PlayerBullets::beginBulletFiredAnimation()
{
	//records the coordinates of the bullet shot
	sf::Vector2f tmp;
	tmp.x = bulletSprite.getPosition().x;
	tmp.y = bulletSprite.getPosition().y;
	//if the bullet is off screen then sets the bullet coordinates to currPos
	if (tmp.x <= 0.f && tmp.y <= 0.f) {
		tmp = currPos;
	}

	//checks if the animation is not finished
	if (!bulletFiredAnimation->isAnimationFinished()) {
		bulletFiredAnimation->update();
		bulletSprite = std::move(bulletFiredAnimation->getCurrAnimation(tmp));
	}
	else {
		//animation is finished
		bulletFiredAnimation->reSetIterations();
	}
}

void PlayerBullets::beginBulletCollisionAnimation()
{

	sf::Vector2f tmp;
	tmp.x = bulletSprite.getPosition().x;
	tmp.y = bulletSprite.getPosition().y;

	//if the bullet is off screen then sets the bullet coordinates to currPos
	if (tmp.x <= 0.f && tmp.y <= 0.f) {
		tmp = currPos;
	}

	//checks if the animation is not finished
	if (!bulletCollisionAnimation->isAnimationFinished()) {
		bulletCollisionAnimation->update();
		bulletSprite = std::move(bulletCollisionAnimation->getCurrAnimation(tmp));

		if (isBulletAnimated())
			bulletSprite.setScale(2.f, 2.f);
	}


}

//returns bulletAnime_flag
bool PlayerBullets::isBulletAnimated()
{
	return bulletAnime_flag;
}

bool PlayerBullets::isBulletsCollided()
{
	return bulletsCollided;
}

void PlayerBullets::triggerBulletCollision()
{
	bulletsCollided = true;
}

bool PlayerBullets::isBulletAlive()
{
	return bulletDistanceClock.getElapsedTime().asSeconds() < 0.9f;
}

//the the bullet's intial position
void PlayerBullets::setSpawnPosition(sf::Vector2f& pos)
{
	currPos = pos;
	bulletSprite.setPosition(std::move(pos));
}

void PlayerBullets::moveBullets()
{
	if (isBulletAnimated()) {
		float delta = clock.restart().asSeconds();
		bulletSprite.move(0.0f, -600.f * delta);
	}
	else {
		float delta = clock.restart().asSeconds();
		bulletSprite.move(0.0f, -400.f * delta);
	}

}

void PlayerBullets::flushBullets()
{
	bulletSprite.move(0.0, -1000.f);
}

bool PlayerBullets::isBulletCollisionAnimationFinished()
{
	return bulletCollisionAnimation->isAnimationFinished();
}



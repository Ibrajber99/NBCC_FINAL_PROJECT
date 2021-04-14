#include "Saucer.h"

Saucer::Saucer(
	std::unique_ptr<TextureAssets>& textureHolder,
	sf::RenderWindow& window)
	: window(window)
	, health(2)
	, destroyed(false)
	, clock()
	, bulletHitSaucer(false)
	, saucerInvisible(true)
{
	saucerTex = std::move(textureHolder->getSaucer());

	saucerSprite.setTexture(saucerTex);

	suckBulletAnimation = (std::make_unique<Animation>
						  (textureHolder->getSuckBulletSaucer(),
						  sf::Vector2u(11, 1), 0.07f));

	setSaucerPosition(sf::Vector2f(0.f, window.getSize().y / 2.f));
}

void Saucer::update()
{
	moveSaucer();
	beginSuckBulletAnimation();
	updateSaucerPosition();
}

void Saucer::moveSaucer()
{
	float dt = clock.restart().asSeconds();
	saucerSprite.move(50.f * dt, 0.0f);
}

void Saucer::setSaucerPosition(sf::Vector2f pos)
{
	saucerSprite.setPosition(pos);
}

void Saucer::generateNewSaucerSprite()
{
	saucerInvisible == false ? setOriginalSaucerSprite() : assignNewSpriteToSaucer();
}

void Saucer::assignNewSpriteToSaucer()
{
	sf::Vector2f tmp(saucerSprite.getPosition());
	sf::IntRect rect(saucerSprite.getGlobalBounds());
	saucerSprite = sf::Sprite();
	saucerSprite.setPosition(tmp);
	saucerSprite.setTextureRect(rect);
}

void Saucer::setOriginalSaucerSprite()
{
	sf::Sprite tmp;
	tmp.setTexture(saucerTex);
	tmp.setPosition(saucerSprite.getPosition());

	saucerSprite = std::move(tmp);
}

void Saucer::flushSaucer()
{
	saucerSprite.move(1000.f, 0.0f);
}

void Saucer::drawSaucer()
{
	window.draw(saucerSprite);
}

void Saucer::getHit()
{
	health--;
	if (health <= 0) {
		destroyed = true;
	}
}

bool Saucer::isSaucerDestroyed()
{
	return destroyed;
}

void Saucer::triggerBulletHitSaucer()
{
	bulletHitSaucer = true;
}

void Saucer::beginSuckBulletAnimation()
{
    //sets animation began to true indicating that it has started.
	if (bulletHitSaucer) {
		sf::Vector2f pos;
		//collects the position(X,Y) of the current sprite
		pos.x = saucerSprite.getPosition().x;
		pos.y = saucerSprite.getPosition().y;

		//if the animation is not finished
		if (!suckBulletAnimation->isAnimationFinished()) {
			//updates animation and moves the animation on the position of the asteroid at the time it was destroyed.
			suckBulletAnimation->update();
			saucerSprite = std::move(suckBulletAnimation->getCurrAnimation(pos));
		}
		//if the animation is finished
		else {
			bulletHitSaucer = false;
			if (!saucerInvisible) {
				generateNewSaucerSprite();
			}
			//set proper flags of animation finishing being true and it is no longer in action.
			//saucerSprite.setTexture(saucerTex);
			saucerSprite.setPosition(pos);
			suckBulletAnimation->reSetIterations();
			bulletHitSaucer = false;
		}
	}
}

void Saucer::updateSaucerPosition()
{

	if (saucerSprite.getPosition().x + saucerSprite.getGlobalBounds().width > window.getSize().x) {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> distribY(10.f, window.getSize().y / 1.5f);
		saucerSprite.setPosition(0.0f, distribY(gen));
	}
}

void Saucer::flipSaucerVisiblity()
{
	saucerInvisible = !saucerInvisible;
	generateNewSaucerSprite();
}

sf::Sprite& Saucer::getSaucerSprite()
{
	return saucerSprite;
}

#include "Asteroids.h"
#include "TextureAssests.h"

//Abstract Class Asteroids
//Children LargeAsteroid, SmallAsteroid

Asteroids::Asteroids()
{
}

Asteroids::~Asteroids()
{
}

//returns asteroid sprite.
sf::Sprite Asteroids::getAsteroidSprite() const
{
    return asteroidSprite;
}

//decrease health if this variable reaches 0 sets isDestroyed to be true.
void Asteroids::getHit()
{
}

//starts asteroid animation.
void Asteroids::beginAsteroidAnimation()
{
}

bool Asteroids::isAsteroidReadyToFlush
    (sf::RenderWindow& window)
{
    return isAnimationFinished() ||
        getAsteroidSprite().getPosition().y
        - getAsteroidSprite().getGlobalBounds().height
           > window.getSize().y;
}

//draw the asteroid after checking if the sprite is within the bounds of the view
void Asteroids::drawAsteroid(sf::RenderWindow& window)
{
    if (getAsteroidSprite().getPosition().y +
        getAsteroidSprite().getGlobalBounds().height > 0.f) {
        window.draw(getAsteroidSprite());
    }
}

//returns true if animation is finished.
bool Asteroids::isAnimationFinished()
{
    return animationFinished;
}

//returns true if animation has begun.
bool Asteroids::isAnimationBegan()
{
    return animationBegan;
}

//returns if an asteroid is destroyed or not.
bool Asteroids::isAsteroidDestroyed()
{
    return isDestroyed;
}

void Asteroids::lockUpdateMovement()
{
    movementFlag = false;
}

void Asteroids::unlockUpdateMovement()
{
    movementFlag = true;
}

Asteroids::AsteroidType Asteroids::getType()
{
    return AsteroidType::Base;
}

//stores time elapsed as delta and moves asteroid accordingly so asteroid movements are frame independent.
void Asteroids::moveAsteroid(float dt)
{
    sf::FloatRect bounds = asteroidSprite.getLocalBounds();
    asteroidSprite.setOrigin(std::floor(bounds.left + bounds.width / 2.f),
    std::floor(bounds.top + bounds.height / 2.f));
    asteroidSprite.move(0.0f, 100.f * dt);
    asteroidSprite.rotate(10.f * dt);
}

//asteroid position is passed in to the function and the position of the asteroid is set accordingly.
void Asteroids::setAsteroidPos(sf::Vector2f pos)
{
    asteroidSprite.setPosition(pos);
}

//flips isDestroyed bool variable
void Asteroids::setIsDestroyed(bool b)
{
    isDestroyed = b;
}



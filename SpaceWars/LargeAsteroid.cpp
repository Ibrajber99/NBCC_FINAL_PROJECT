#include "LargeAsteroid.h"

LargeAsteroid::LargeAsteroid
(sf::Texture& asteroidExplosion, sf::Texture& asteroidTexture)
	:health(2)
    , isDestroyed(false)
    , animationFinished(false)
    , animationBegan(false)
    , movementFlag(true)
{
    animation2 = (std::make_unique<Animation>(asteroidExplosion, sf::Vector2u(4, 2), 0.07f));
    asteroidSprite.setTexture(asteroidTexture);

}

sf::Sprite LargeAsteroid::getAsteroidSprite() const
{
    return asteroidSprite;
}

void LargeAsteroid::getHit()
{
    health--;
    if (health <= 0) {
        isDestroyed = 1;
    }
}

bool LargeAsteroid::isAnimationFinished()
{
    return animationFinished;
}

bool LargeAsteroid::isAnimationBegan()
{
    return animationBegan;
}

bool LargeAsteroid::isAsteroidDestroyed()
{
    return isDestroyed;
}

void LargeAsteroid::lockUpdateMovement()
{
    movementFlag = false;
}

void LargeAsteroid::unlockUpdateMovement()
{
    movementFlag = true;
}

void LargeAsteroid::beginAsteroidAnimation()
{
    //sets animation began to true indicating that it has started.
    animationBegan = 1;
    sf::Vector2f pos;
    //collects the position(X,Y) of the current sprite
    pos.x = asteroidSprite.getPosition().x;
    pos.y = asteroidSprite.getPosition().y;
    //if the animation is not finished
    if (!animation2->isAnimationFinished()) {
        //updates animation and moves the animation on the position of the asteroid at the time it was destroyed.
        animation2->update();
        asteroidSprite = std::move(animation2->getCurrAnimation(pos));
    }
    //if the animation is finished
    else {
        //set proper flags of animation finishing being true and it is no longer in action.
        animationFinished = 1;
        animationBegan = 0;

    }
}

void LargeAsteroid::setIsDestroyed(bool b)
{
    isDestroyed = b;
}

bool LargeAsteroid::isAsteroidReadyToFlush
     (sf::RenderWindow& window)
{
    return isAnimationFinished() ||
        getAsteroidSprite().getPosition().y
        - getAsteroidSprite().getGlobalBounds().height
           > window.getSize().y;
}

LargeAsteroid::AsteroidType LargeAsteroid::getType()
{
    return AsteroidType::Large;
}





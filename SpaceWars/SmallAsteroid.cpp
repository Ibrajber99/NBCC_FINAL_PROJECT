#include "SmallAsteroid.h"

SmallAsteroid::SmallAsteroid(sf::Texture& asteroidExplosion, sf::Texture& asteroidTexture)
    :health(1)
    , isDestroyed(false)
    , animationFinished(false)
    , animationBegan(false)
    , movementFlag(true)
{

    animation2 = (std::make_unique<Animation>
   (asteroidExplosion, sf::Vector2u(20, 1), 0.07f));

    asteroidSprite.setTexture(asteroidTexture);
}

sf::Sprite SmallAsteroid::getAsteroidSprite() const
{
    return asteroidSprite;
}

void SmallAsteroid::getHit()
{
    health--;
    if (health <= 0) {
        isDestroyed = 1;
    }
}

bool SmallAsteroid::isAnimationFinished()
{
    return animationFinished;
}

bool SmallAsteroid::isAnimationBegan()
{
    return animationBegan;
}

bool SmallAsteroid::isAsteroidDestroyed()
{
    return isDestroyed;
}

void SmallAsteroid::lockUpdateMovement()
{
    movementFlag = false;
}

void SmallAsteroid::unlockUpdateMovement()
{
    movementFlag = true;
}

void SmallAsteroid::setIsDestroyed(bool b)
{
    isDestroyed = b;
}

void SmallAsteroid::beginAsteroidAnimation()
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

//checks if the asterodis is good to flush
bool SmallAsteroid::isAsteroidReadyToFlush
            (sf::RenderWindow& window)
{
    return isAnimationFinished() ||
        getAsteroidSprite().getPosition().y
        - getAsteroidSprite().getGlobalBounds().height
           > window.getSize().y;
}

//gets type of atseroid
SmallAsteroid::AsteroidType SmallAsteroid::getType()
{
    return AsteroidType::Small;
}



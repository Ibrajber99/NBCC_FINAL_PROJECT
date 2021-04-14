#pragma once
#include "Asteroids.h"

class SmallAsteroid : public Asteroids

{
public:
    SmallAsteroid(sf::Texture& asteroidExplosion, sf::Texture& asteroidTexture);
    sf::Sprite                      getAsteroidSprite()const override;

    virtual void                    getHit() override;
    bool                            isAnimationFinished()override;
    bool                            isAnimationBegan()override;
    bool                            isAsteroidDestroyed()override;
    void                            lockUpdateMovement()override;
    void                            unlockUpdateMovement()override;
    void                            setIsDestroyed(bool b)override;
    void                            beginAsteroidAnimation()override;
    bool                            isAsteroidReadyToFlush
                                    (sf::RenderWindow& window)override;
    AsteroidType					getType()override;

private:
    size_t                          health;
    bool                            isDestroyed;
    bool                            animationFinished;
    bool                            animationBegan;
    bool                            movementFlag;
};


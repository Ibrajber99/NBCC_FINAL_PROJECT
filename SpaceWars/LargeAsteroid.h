#pragma once

#include "Asteroids.h"
class LargeAsteroid : public Asteroids
	
{
public:
	LargeAsteroid(sf::Texture& asteroidExplosion, sf::Texture& asteroidTexture);
    sf::Sprite                      getAsteroidSprite()const override;
    virtual void                    getHit() override;
    bool                            isAnimationFinished()override;
    bool                            isAnimationBegan()override;
    bool                            isAsteroidDestroyed()override;
    void                            lockUpdateMovement()override;
    void                            unlockUpdateMovement()override;
    void                            beginAsteroidAnimation()override;
    void                            setIsDestroyed(bool b)override;
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




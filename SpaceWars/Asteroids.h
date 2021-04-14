#pragma once
#include "TextureAssests.h"
#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<iostream>
#include<random>
#include<memory>
#include "Animation.h";

//Asteroid Class
class Asteroids {
public:
    enum class AsteroidType {
        Base,Small,Large
    };

public:
                                            Asteroids();
                                            virtual ~Asteroids();
public:
    virtual sf::Sprite                      getAsteroidSprite()const =0;
    virtual void                            getHit();
    virtual void                            beginAsteroidAnimation();
    virtual bool                            isAsteroidReadyToFlush
                                            (sf::RenderWindow& window);

    virtual void                            drawAsteroid
                                            (sf::RenderWindow& window);

    virtual bool                            isAnimationFinished();
    virtual bool                            isAnimationBegan();
    virtual bool                            isAsteroidDestroyed();
    virtual void                            lockUpdateMovement();
    virtual void                            unlockUpdateMovement();
    virtual void                            setIsDestroyed(bool b);
    virtual AsteroidType					getType();


    void                                    moveAsteroid(float dt);
    void                                    setAsteroidPos(sf::Vector2f pos);
protected:
    size_t                                  health;
    sf::Sprite                              asteroidSprite;
    std::unique_ptr<Animation>              animation2;
    sf::Clock                               clock;
    bool                                    isDestroyed;
    bool                                    animationFinished;
    bool                                    animationBegan;
    bool                                    movementFlag;
};


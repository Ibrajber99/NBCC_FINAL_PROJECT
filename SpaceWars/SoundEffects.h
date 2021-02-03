#pragma once
#include "TextureAssests.h"
#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<iostream>
//SoundEffects Class
class SoundEffects {
public:
    /***************************
    *       CONSTRUCTOR        *
    ****************************/

                                    SoundEffects();

    /*******************************
    *PUBLIC SOUND EFFECT FUNCTIONS *
    ********************************/

    void                            shootBullet();
    void                            hitTarget();
    void                            hitTargetNoDestruction();
    void                            spaceShipDestruction();
    void                            specialBulletClashSound();
    void                            normalBulletClashSound();
    void                            saucerSuckSound();
    sf::Music&                      getGameMusicTheme();

private:
   

    /*********************************
    * PRIVATE SOUND EFFECT VARIABLES *
    **********************************/
    sf::SoundBuffer                 bulletShot;
    sf::SoundBuffer                 bulletHit;
    sf::SoundBuffer                 bulletHitAsteroid;
    sf::SoundBuffer                 spaceExplosion;
    sf::SoundBuffer                 specialBulletCollision;
    sf::SoundBuffer                 normalBulletCollision;
    sf::SoundBuffer                 saucerSuck;

    sf::Sound                       bulletShotSound;
    sf::Sound                       bulletHitSound;
    sf::Sound                       bulletHitAsteroidSound;
    sf::Sound                       spaceExplosionSound;
    sf::Sound                       specialBulletCollisionSound;
    sf::Sound                       normalBulletCollisionSound;
    sf::Sound                       suacerSuckSound;

    sf::Music                       gameTheme;

    

};


#pragma once
#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<iostream>

//TextureAssets class
class TextureAssets {
public:

                                    TextureAssets();

    sf::Texture&                    getSpaceShipTexture();
    sf::Font&                       getFont();
    sf::Text                        showMessage(sf::RenderWindow& window);
    sf::Texture&                    getLargeAsteroid();
    sf::Texture&                    getSmallAsteroid();
    sf::Texture&                    getBullets();
                                    
    sf::Texture&                    getHealthBarTexture();
    sf::Texture&                    getEnemySpaceSHip();
    
    sf::Texture&                    getSpaceShipExplosion();
    sf::Texture&                    getBulletFired();
    sf::Texture&                    getLargeAsteroidExplosion();
    sf::Texture&                    getSmallAsteroidExplosion();
    sf::Texture&                    getHealthRegainPowerUp();
    sf::Texture&                    getOneHitKillPowerUp();
    sf::Texture&                    getNukePowerUp();
    sf::Texture&                    getProtectionShieldPowerUp();
    sf::Texture&                    getRadarPowerUp();
    sf::Texture&                    getEnemyBullet();
    sf::Texture&                    getEnemyShipExplosion();
    sf::Texture&                    getpauseBackgroundTexture();
    sf::Texture&                    getSpecialBulletCollisionAnimation();
    sf::Texture&                    getNormalBulletCollisionAnimation();
    sf::Texture&                    getSaucer();
    sf::Texture&                    getSuckBulletSaucer();
    sf::Texture&                    getSpaceShipProtectionShield();
    sf::Texture&                    getSmallEnemyTex();
    sf::Texture&                    getSmallEnemyBulletTex();
    sf::Texture&                    getSmallEnemyShipExplosion();

    std::vector<sf::Texture>&       getScenePlanets();
    std::vector<sf::Texture>&       getSceneClouds();
    std::vector<sf::Texture>&       getBackgrounds();
    std::vector<sf::Texture>&       getStars();
    std::vector<sf::Texture>&       getSpaceShipTextures();

    sf::Texture&                    getPlayerLifeBarHud();
    sf::Texture&                    getHudBar();
    sf::Texture&                    getPowerUpHudBlock();


private:
    void                            fillBackgroundContainer();
    void                            fillSpaceCloudsContainer();
    void                            fillSpaceStarsContainer();
    void                            fillPlanetsContainer();
    void                            fillSpaceShipTextures();

private:
#pragma region Textures Variables

    //Sprite sheets Animations
    sf::Texture                     spaceShipExplosion;
    sf::Texture                     asteroidExplosion;
    sf::Texture                     smallAsteroidExplosion;
    sf::Texture                     plasmaBulletFired;

    //Game object main Textures

    sf::Texture                     spaceShipTexture;
    sf::Texture                     spaceShipProtectionShieldTexture;
    sf::Texture                     spaceShipFlames;
    sf::Texture                     asteroidTexture;
    sf::Texture                     smallAsteroidTexture;
    sf::Texture                     bulletsTexture;
    sf::Texture                     heartHealthTexture;

    sf::Font                        font;
    sf::Text                        text;




    std::vector<sf::Texture>        planetContainer;
    std::vector<sf::Texture>        cloudsContainer;
    std::vector<sf::Texture>        backgroundsContainer;
    std::vector<sf::Texture>        smallStarsContainer;
    std::vector<sf::Texture>        spaceShipTexturesContainer;

    //Powerups Textures
    sf::Texture                     healthRegainPowerUpTex;
    sf::Texture                     oneHitKillPowerUpTex;
    sf::Texture                     nukePowerUpTex;
    sf::Texture                     protectionSheildPowerUpTex;
    sf::Texture                     radarPowerUpTex;
    sf::Texture                     powerUpHudBlock;

    //Enemy Space ship
    sf::Texture                     enemySpaceShipTex;
    sf::Texture                     smallEnemyShipTex;
    sf::Texture                     smallEnemyShipBulletTex;

    //Bullet Animation Enemey Space ship
    sf::Texture                     enemyBulletAnimation;

    sf::Texture                     enemySpaceShipExplosion;

    //Pause Menu
    sf::Texture                     pauseBackgroundTexture;

    sf::Texture                     specialBulletCollisionAnimation;
    sf::Texture                     normalBulletCollisionAnimation;


    //Saucer textures
    sf::Texture                     saucer;
    sf::Texture                     suckBulletSaucerTexture;

    sf::Texture                     smallEnemyShipExplosion;

    sf::Texture                     playerLifeBarHud;
    sf::Texture                     hudBar;

#pragma endregion
};


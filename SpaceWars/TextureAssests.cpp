#include "TextureAssests.h"
#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<iostream>


//TextureAssets constructor loads all textures from file and sets them to be smooth
TextureAssets::TextureAssets()
{

	fillBackgroundContainer();
	fillSpaceCloudsContainer();
	fillSpaceStarsContainer();
	fillPlanetsContainer();
	fillSpaceShipTextures();


	saucer.loadFromFile("Media/spaceships/saucer.png");
	saucer.setSmooth(true);

	spaceShipProtectionShieldTexture.loadFromFile("Media/spaceships/PlayerSpaceShip/ghostShip.png");
	spaceShipProtectionShieldTexture.setSmooth(true);

	smallAsteroidTexture.loadFromFile("Media/other/smallAsteroid.png");
	smallAsteroidTexture.setSmooth(true);

	asteroidTexture.loadFromFile("Media/other/asteroidTesting.png");
	asteroidTexture.setSmooth(true);

	bulletsTexture.loadFromFile("Media/bullets/bullet.png");
	bulletsTexture.setSmooth(true);

	heartHealthTexture.loadFromFile("Media/other/heart.png");
	heartHealthTexture.setSmooth(true);

	spaceShipExplosion.loadFromFile("Media/animations/SpaceShipExplosion.png");
	spaceShipExplosion.setSmooth(true);

	asteroidExplosion.loadFromFile("Media/animations/asteroidExplosion1.png");
	asteroidExplosion.setSmooth(true);

	smallAsteroidExplosion.loadFromFile("Media/animations/small_asteroid-Explosion.png");
	smallAsteroidExplosion.setSmooth(true);

	healthRegainPowerUpTex.loadFromFile("Media/other/heartPowerUpTexture.png");
	healthRegainPowerUpTex.setSmooth(true);

	oneHitKillPowerUpTex.loadFromFile("Media/other/skull.png");
	oneHitKillPowerUpTex.setSmooth(true);

	nukePowerUpTex.loadFromFile("Media/other/nuke.png");
	nukePowerUpTex.setSmooth(true);

	protectionSheildPowerUpTex.loadFromFile("Media/other/shield.png");
	protectionSheildPowerUpTex.setSmooth(true);

	radarPowerUpTex.loadFromFile("Media/other/radar.png");
	radarPowerUpTex.setSmooth(true);

	plasmaBulletFired.loadFromFile("Media/bullets/bulletSpriteAnimation2.png");
	plasmaBulletFired.setSmooth(true);

	enemyBulletAnimation.loadFromFile("Media/bullets/enemySpaceShip_bullet.png");
	enemyBulletAnimation.setSmooth(true);

	enemySpaceShipTex.loadFromFile("Media/spaceships/spaceShip_TaeKim.png");
	enemySpaceShipTex.setSmooth(true);

	enemySpaceShipExplosion.loadFromFile("Media/animations/enemySpaceExplosion.png");
	enemySpaceShipExplosion.setSmooth(true);

	pauseBackgroundTexture.loadFromFile("Media/background/PauseBackground.png");
	pauseBackgroundTexture.setSmooth(true);

	specialBulletCollisionAnimation.loadFromFile("Media/animations/bulletCollisionSpark.png");
	specialBulletCollisionAnimation.setSmooth(true);

	normalBulletCollisionAnimation.loadFromFile("Media/animations/NormalBulletRegularImpact.png");
	normalBulletCollisionAnimation.setSmooth(true);

	suckBulletSaucerTexture.loadFromFile("Media/animations/SaucerAnimated.png");
	suckBulletSaucerTexture.setSmooth(true);

	smallEnemyShipTex.loadFromFile("Media/spaceships/smallEnemyShip.png");
	smallEnemyShipTex.setSmooth(true);

	smallEnemyShipBulletTex.loadFromFile("Media/bullets/smallEnemyShipBullets.png");
	smallEnemyShipBulletTex.setSmooth(true);

	smallEenmyShipExplosion.loadFromFile("Media/animations/BlueExplosion.png");
	smallEenmyShipExplosion.setSmooth(true);

	//loading the font
	if (!font.loadFromFile("Media/other/test.ttf")) {
		std::cout << -1;
	}
}


sf::Font& TextureAssets::getFont()
{
	return font;
}

sf::Text TextureAssets::showMessage(sf::RenderWindow& window)
{
	text.setFont(font);
	text.setCharacterSize(30);
	text.setStyle(sf::Text::Bold);
	text.setPosition(sf::Vector2f((float)window.getSize().x / 2, 0.0f));
	text.setFillColor(sf::Color::Red);

	return text;
}

sf::Texture& TextureAssets::getSpaceShipTexture()
{
	return spaceShipTexture;
}

sf::Texture& TextureAssets::getLargeAsteroid()
{
	return asteroidTexture;
}

sf::Texture& TextureAssets::getSmallAsteroid()
{
	return smallAsteroidTexture;
}

sf::Texture& TextureAssets::getBullets()
{
	return bulletsTexture;
}

sf::Texture& TextureAssets::getHealthBarTexture()
{
	return heartHealthTexture;
}

sf::Texture& TextureAssets::getEnemySpaceSHip()
{
	return enemySpaceShipTex;
}

sf::Texture& TextureAssets::getSpaceShipExplosion()
{
	return spaceShipExplosion;
}

sf::Texture& TextureAssets::getBulletFired()
{
	return plasmaBulletFired;
}

sf::Texture& TextureAssets::getLargeAsteroidExplosion()
{
	return asteroidExplosion;
}

sf::Texture& TextureAssets::getSmallAsteroidExplosion()
{
	return smallAsteroidExplosion;
}

sf::Texture& TextureAssets::getHealthRegainPowerUp()
{
	return healthRegainPowerUpTex;
}

sf::Texture& TextureAssets::getOneHitKillPowerUp()
{
	return oneHitKillPowerUpTex;
}

sf::Texture& TextureAssets::getNukePowerUp()
{
	return nukePowerUpTex;
}

sf::Texture& TextureAssets::getProtectionShieldPowerUp()
{
	return protectionSheildPowerUpTex;
}

sf::Texture& TextureAssets::getRadarPowerUp()
{
	return radarPowerUpTex;
}

sf::Texture& TextureAssets::getEnemyBullet()
{
	return enemyBulletAnimation;
}

sf::Texture& TextureAssets::getEnemyShipExplosion()
{
	return enemySpaceShipExplosion;
}

sf::Texture& TextureAssets::getpauseBackgroundTexture()
{
	return pauseBackgroundTexture;
}

sf::Texture& TextureAssets::getSpecialBulletCollisionAnimation()
{
	return specialBulletCollisionAnimation;
}

sf::Texture& TextureAssets::getNormalBulletCollisionAnimation()
{
	return normalBulletCollisionAnimation;
}

sf::Texture& TextureAssets::getSaucer()
{
	return saucer;
}

sf::Texture& TextureAssets::getSuckBulletSaucer()
{
	return suckBulletSaucerTexture;
}

sf::Texture& TextureAssets::getSpaceShipProtectionShield()
{
	return spaceShipProtectionShieldTexture;
}

sf::Texture& TextureAssets::getSmallEnemyTex()
{
	return smallEnemyShipTex;
}

sf::Texture& TextureAssets::getSmallEnemyBulletTex()
{
	return smallEnemyShipBulletTex;
}

sf::Texture& TextureAssets::getSmallEnemyShipExplosion()
{
	return smallEenmyShipExplosion;
}

std::vector<sf::Texture>& TextureAssets::getScenePlanets()
{
	return planetContainer;
}

std::vector<sf::Texture>& TextureAssets::getSceneClouds()
{
	return cloudsContainer;
}

std::vector<sf::Texture>& TextureAssets::getBackgrounds()
{
	return backgroundsContainer;
}

std::vector<sf::Texture>& TextureAssets::getStars()
{
	return smallStarsContainer;
}

std::vector<sf::Texture>& TextureAssets::getSpaceShipTextures()
{
	return spaceShipTexturesContainer;
}

void TextureAssets::fillBackgroundContainer()
{
	sf::Texture backGroundTexture1;
	backGroundTexture1.loadFromFile("Media/background/Nebula Aqua-Pink.png");
	backGroundTexture1.setSmooth(true);

	sf::Texture backGroundTexture2;
	backGroundTexture2.loadFromFile("Media/background/Nebula Blue.png");
	backGroundTexture2.setSmooth(true);

	sf::Texture backGroundTexture3;
	backGroundTexture3.loadFromFile("Media/background/Nebula Red.png");
	backGroundTexture3.setSmooth(true);

	backgroundsContainer.push_back(backGroundTexture1);
	backgroundsContainer.push_back(backGroundTexture2);
	backgroundsContainer.push_back(backGroundTexture3);
}

void TextureAssets::fillSpaceCloudsContainer()
{
	sf::Texture spaceCloud1;
	spaceCloud1.loadFromFile("Media/spaceClouds/spaceCloud1.png");
	sf::Texture spaceCloud2;
	spaceCloud2.loadFromFile("Media/spaceClouds/spaceCloud2.png");
	sf::Texture spaceCloud3;
	spaceCloud3.loadFromFile("Media/spaceClouds/spaceCloud3.png");
	sf::Texture spaceCloud4;
	spaceCloud4.loadFromFile("Media/spaceClouds/spaceCloud4.png");
	sf::Texture spaceCloud5;
	spaceCloud5.loadFromFile("Media/spaceClouds/spaceCloud5.png");

	cloudsContainer.push_back(spaceCloud1);
	cloudsContainer.push_back(spaceCloud2);
	cloudsContainer.push_back(spaceCloud3);
	cloudsContainer.push_back(spaceCloud4);
	cloudsContainer.push_back(spaceCloud5);
}

void TextureAssets::fillSpaceStarsContainer()
{

	sf::Texture spaceStars1;
	spaceStars1.loadFromFile("Media/spaceClouds/smallStars1.png");

	sf::Texture  spaceStars2;
	spaceStars2.loadFromFile("Media/spaceClouds/smallStars2.png");
	sf::Texture spaceStars3;
	spaceStars3.loadFromFile("Media/spaceClouds/smallStars3.png");
	sf::Texture spaceStars4;
	spaceStars4.loadFromFile("Media/spaceClouds/smallStars4.png");

	smallStarsContainer.push_back(spaceStars1);
	smallStarsContainer.push_back(spaceStars2);
	smallStarsContainer.push_back(spaceStars3);
	smallStarsContainer.push_back(spaceStars4);
}

void TextureAssets::fillPlanetsContainer()
{

	sf::Texture star_Sun_1_Texture;
	star_Sun_1_Texture.loadFromFile("Media/planets/sun1.png");
	star_Sun_1_Texture.setSmooth(true);

	sf::Texture star_Sun_2_Texture;
	star_Sun_2_Texture.loadFromFile("Media/planets/sun2.png");
	star_Sun_2_Texture.setSmooth(true);

	sf::Texture  planet_Shape_1_Texture;
	planet_Shape_1_Texture.loadFromFile("Media/planets/planet1.png");
	planet_Shape_1_Texture.setSmooth(true);

	sf::Texture planet_Shape_2_Texture;
	planet_Shape_2_Texture.loadFromFile("Media/planets/planet2.png");
	planet_Shape_2_Texture.setSmooth(true);

	sf::Texture planet_Shape_3_Texture;
	planet_Shape_3_Texture.loadFromFile("Media/planets/planet3.png");
	planet_Shape_3_Texture.setSmooth(true);

	sf::Texture planet_Shape_4_Texture;
	planet_Shape_4_Texture.loadFromFile("Media/planets/planet4.png");
	planet_Shape_4_Texture.setSmooth(true);

	sf::Texture planet_Shape_5_Texture;
	planet_Shape_5_Texture.loadFromFile("Media/planets/Terran1.png");
	planet_Shape_5_Texture.setSmooth(true);

	planetContainer.push_back(star_Sun_1_Texture);
	planetContainer.push_back(star_Sun_2_Texture);
	planetContainer.push_back(planet_Shape_1_Texture);
	planetContainer.push_back(planet_Shape_2_Texture);
	planetContainer.push_back(planet_Shape_3_Texture);
	planetContainer.push_back(planet_Shape_4_Texture);
	planetContainer.push_back(planet_Shape_5_Texture);
}

void TextureAssets::fillSpaceShipTextures()
{
	sf::Texture idelTexture;
	idelTexture.loadFromFile("Media/spaceships/PlayerSpaceShip/idelShip.png");
	idelTexture.setSmooth(true);

	sf::Texture leftTexture;
	leftTexture.loadFromFile("Media/spaceships/PlayerSpaceShip/shipLeft.png");
	leftTexture.setSmooth(true);

	sf::Texture rightTexture;
	rightTexture.loadFromFile("Media/spaceships/PlayerSpaceShip/shipRight.png");
	rightTexture.setSmooth(true);

	spaceShipTexturesContainer.push_back(idelTexture);
	spaceShipTexturesContainer.push_back(leftTexture);
	spaceShipTexturesContainer.push_back(rightTexture);
}



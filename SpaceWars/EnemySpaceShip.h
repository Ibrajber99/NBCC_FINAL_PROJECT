#pragma once
#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<time.h>
#include <iostream>
#include <windows.h>
#include <mmsystem.h>
#include <tchar.h>
#include <conio.h>
#include <Mmsystem.h>
#include <mciapi.h>
#include <time.h>
#include <vector>
#include <cmath>
#include <fstream>
#include <memory>
#include <cstring>
#include <locale> 
#include <sstream>
#include <iomanip>
#include <functional>
#include <numeric>
#include <ostream>
#include<fstream>
#include <windows.graphics.h>
#include <istream>
#include <utility>
#include <array>
#include<set>
#include<map>
#include<list>
#include<iterator>
#include<forward_list>
#include <algorithm>
#include <cctype>
#include <cstring>
#include <numeric>
#include <thread>
#include <bitset>
#include<unordered_set>
#include <deque>
#include <cstdlib>
#include <cstdio>
#include <clocale>
#include <ctime>
#include <cwchar>
#include <random>
#include <iterator>
#include <regex>
#include<unordered_map>
#include<unordered_set>
#include <variant>
#include <ctime>
#include "Animation.h"
#include "TextureAssests.h"



class EnemySpaceShip
{
public:
								EnemySpaceShip(std::unique_ptr<TextureAssets>&textureHolder);

	sf::Sprite&					getSpaceShip();
	void						draw(sf::RenderWindow& window);
	void						moveSpaceShip(sf::RenderWindow& w);
	void						setBulletDirection(sf::Vector2f playerSpaceShip);
	void						moveBullet();
	void						drawBullets(sf::RenderWindow& w);
	void						drawSpaceShip(sf::RenderWindow& w);
	void						flushBullets(sf::RenderWindow& w);
	void						update(sf::RenderWindow& w);
	void						getHit();
	void						flushBulletAt(size_t i);
	bool						isShipAlive();
	bool						isShipReadyToSpawn();
	void						setShipIsReadyToSpawn();
	void						clearMagazine();
	void						resetDifficulty();
	bool						isAnimationFinished();
	void						lockUpdateMovement();
	void						unlockUpdateMovement();
	bool						isCanShootBullets();
	void						lockBulletsMovement();
	void						releaseBullets();
	void						setSpaceShipToSpawnPos();
	void						destroyShip();
	void						resetSpaceShipAttributes();


	std::vector<std::pair<sf::Sprite, sf::Vector2f>>& getBulletMagazine();

	sf::Vector2f				getSpaceShipCenter();
	sf::Vector2f				getSpaceShipSpawnPostion();
private:
	void						moveLeft();
	void						moveRight();
	void						pushBullets(sf::Vector2f& shootDir);
	void						initBullets();
	void						beginShipExplosion();

private:
	std::unique_ptr<Animation>  bulletAnimation;
	std::unique_ptr<Animation>  shipExplosionAnimation;

	sf::Sprite				    spaceShip;
	sf::Sprite				    spaceShipExplosion;
	sf::Sprite				    bulletSprite;

	size_t						lifeCounter;

	sf::Vector2f				currVelocity;

	std::vector<std::pair<sf::Sprite,sf::Vector2f>>bulletMagazine;

	sf::Clock					clock;
	sf::Clock					moveClock;
	sf::Clock					shootBulletClock;

	TextureAssets&				texturesHolder;

	bool						isRight;
	bool						isLeft;
	static float				bulletSpeed;
	bool						shipAlive;
	bool						readyToSpawn;
	static float				speed;
	bool						moveFlag;
	bool						canShootBullets;
};


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
#include "TextureAssests.h"
#include"SpaceShip.h"
#include "SoundEffects.h"
#include"Asteroids.h"
#include "PowerUps.h"
#include "HealthPowerUp.h"
#include "OneHitKillPowerUp.h"
#include "NukePowerUp.h"
#include "ProtectionShieldPowerUp.h"
#include "RadarPowerUp.h"
#include "Bullets.h"
#include <execution>
#include <future> 
#include <mutex> 
#include "EnemySpaceShip.h"
#include "AsteroidsHolder.h"
#include "BackgroundDynamics.h"
#include"PowerUpsHolder.h"
#include "Saucer.h"
#include "Enemyships.h"

class Game;

class CollisionManager
{
public:
	CollisionManager(Game &game_);
	void manageCollisions();
private:
	void projectileHitsAsteroid(std::unique_ptr<PlayerBullets>& bullet,
		std::unique_ptr<Asteroids>& asteroid);

	void asteroidHitsSpaceShip(std::unique_ptr<Asteroids>& asteroid);

	void enemyPojectileHitsSpaceShip(size_t index);

	void projectileHitSmallShips(std::unique_ptr<PlayerBullets>& bullet,
		std::unique_ptr<Enemyships>& enemySmallShip);

	void smallEnemySpaceShipHitSpaceShip(std::unique_ptr<Enemyships>& enemySmallShip);

	void projectileHitsEnemySpaceShip(std::unique_ptr<PlayerBullets>& bullet);

	void collideBullets(size_t index, std::unique_ptr<PlayerBullets>& playerBullets);

	void asteroidHitSpaceShip();

	void enemyProjectileHItSpaceShip();

	void triggerPowerUpPickUp();

	void checkProjectileHitAsteroid();

	void checkAsteroidHitSpaceShip();

	void checkBulletHitSaucer();
	
	void checkEnemyProjectileHitSpaceShip();

	void checkProjectileHitEnemySpaceShip();

	void checkProjectileHitSmallShips();

	void checkSmallEnemyShipsProjectileHitSpaceShip();

	void checkSmallShipsHitSpaceShip();

	bool checkPowerUpsHitSpaceShip();

	void bulletHitSaucer(std::unique_ptr<PlayerBullets>& bullet);

	void isBullets_Colliding();

	bool isObjectsColliding(sf::Sprite objA, sf::Sprite objB);

	void determineHitAsteroidScore
	(std::unique_ptr<Asteroids>& asteroid,
		std::unique_ptr<PlayerBullets>& bullet);

	void hitSpaceShipEffect();
private:
	Game& game;

};


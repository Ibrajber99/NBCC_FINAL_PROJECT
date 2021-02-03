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
#include "Animation.h"
//Bullets Class
class PlayerBullets
{
public:
								PlayerBullets(sf::Texture& normalBulletTexture, sf::Texture& bulletCollisionAnime);
								PlayerBullets(sf::Texture animatedBullet,sf::Texture bulletCollisionAnime,bool isBulletAnimated);
								PlayerBullets(sf::Vector2f aimDirNorm);

	sf::Sprite					getBulletSprite();
	void						beginBulletFiredAnimation();
	void						beginBulletCollisionAnimation();
	void						setSpawnPosition(sf::Vector2f& pos);
	void						moveBullets();
	void						flushBullets();
	bool						isBulletCollisionAnimationFinished();
	bool						isBulletAnimated();
	bool						isBulletsCollided();
	void						triggerBulletCollision();
	bool						isBulletAlive();


private:
	sf::Sprite				    bulletSprite;
	sf::Sprite					animatedBulletFired;
	std::unique_ptr<Animation>  bulletFiredAnimation;
	std::unique_ptr<Animation>	bulletCollisionAnimation;

	bool						bulletAnime_flag;
	bool						bulletsCollided;
	sf::Vector2f				currPos;
	sf::Vector2f				aimDirectionNormalized;
	sf::Clock					clock;
	sf::Clock					bulletDistanceClock;

	float						bulletTravelDistance;
};


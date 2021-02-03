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
//Super class PowerUps 
class PowerUps
{
public:
	enum class Type {
		Base,Nuke, sheild, Radar, OneHit, Health
	};
public:
					/***************************
					* PUBLIC VIRTUAL FUNCTIONS *
					****************************/
	virtual sf::Sprite&										getPowerUpSprite()=0;
	virtual sf::Text&									    getPowerUpText();
	sf::Font&												getFont();
    void													setpowerUpSpawnPos(sf::RenderWindow& w);
    void													movePowerUpOnScreen();
	void													movePowerUpOutOfScreen();
	virtual void											movePowerUpText(float y);
    void													drawPowerUpText
															(sf::RenderWindow &window);
    void													flushText();
	void													initPowerUpTextPos();
	virtual void											setPowerUpTextAttributes();
	virtual void											powerUpTakeEffect();
	virtual Type											getType();


					/***************************
					* PUBLIC VIRTUAL DESTRUCTOR *
					****************************/
	virtual													~PowerUps();



protected:
					/***************************
					* PROTECTED VARIABLES      *
					****************************/
	sf::Sprite												powerUpSprite;
	sf::Texture												powerUpTexture;
	sf::Text												powerUpText;

	Asteroids*												asteroids;
	SpaceShip*												spaceShip;
	sf::Clock												clock;
	sf::Font												font;
	

};


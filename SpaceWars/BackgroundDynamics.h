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

//BacgroundDynamics Class
class BackgroundDynamics
{
public:

								BackgroundDynamics(sf::RenderWindow &win,
								std::unique_ptr<TextureAssets>&textureHolder);
	
	sf::Sprite&					getCurrPlanet(sf::RenderWindow &window);
	sf::Sprite&					getCurrCloud(sf::RenderWindow& window);
	sf::Sprite&					getPauseBackgroundSprite();
	sf::Sprite&					getGameBackGround();


	void						moveSceneObjects();
	void						assignRandomBackground();
	void						lockUpdateMovement();
	void						unlockUpdateMovement();
	void						draw();
	void						update();

private:
	void						movePlanets();
	void						moveClouds();
	void						moveStars();
	void						flushStarsOutofView();
	void						flushPlanetsOutOfView();
	void						initializePlanets();
	void						InitializeBackgrounds();
	void						initializeStars();
	void						initializeClouds();
	void						flushCloudsOutOfView();

	void						initializeSceneObjects();
	void						neturalizeBackgroundindex();

private:
	std::vector<sf::Sprite>		planetContainer;
	std::vector<sf::Sprite>		cloudsContainer;
	std::vector<sf::Texture>	backgroundsContainer;
	std::vector<sf::Sprite>		starsContainer;

	sf::Sprite					pauseBackgroundSprite;
	sf::Sprite					gameBackGroundSprite;

	sf::Clock					clock;
	sf::Clock					cloc2;
	sf::Clock					movePlanetClock;
	sf::Clock					moveCloudsClock;
	sf::RenderWindow&			window;

	sf::Sprite					mockSprite;
	bool						movementFlag;
	size_t						currentBackgroundIndex;
	sf::Time					updatePerFrame;
};


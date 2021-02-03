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
#include "CollisionManager.h"
#include "EnemyShipsHolder.h"


class CollisionManager;

//Game Class
class Game
{
public:
																	Game();
	void															run();
public:
	void															processEvents();
	void															update(float dt);
	void															render();
	void															resetGame();
	void															determineGameScene();
	void															updateMessagepopUp();
	void															setHighScoreText();
	void															applyHighScoreMessage();

	//Game logic and functionality 
	void															enableControls();
	void															disableControls();
	void															incrementScore(size_t valToIncrement);
	size_t															getScore();
	void															reSetScore();
	void															initializeAssets();
	void															updateAllWorldObjects();
	void															createNewGameObjects();

	//Game control functions
	void															on_SpaceClick_KeyPress();
	void															on_ESCAPE_KeyPress();
	void															on_ENTER_KeyPress();
	void															on_Key_Press_doIt();
	int																getHighScoreData();
	bool															saveHighScoreData();

	std::unique_ptr<TextureAssets>									textureGenerator;
	std::unique_ptr<SpaceShip>										spaceShip;
	std::unique_ptr<AsteroidsHolder>								asteroidsManager;
	std::unique_ptr<SoundEffects>									gameSound;
	std::unique_ptr< EnemySpaceShip>								enemySpaceS;
	std::unique_ptr<PowerUpsHolder>									powerUpsManager;
	std::unique_ptr<CollisionManager>								collisionManager;
	std::unique_ptr<BackgroundDynamics>								backGroundTexturesManager;
	std::unique_ptr<EnemyShipsHolder>								enemyShipsManager;
	std::unique_ptr<Saucer>											saucerObject;
	std::vector<sf::Sprite>											playerHealth;
	sf::Clock														clock;


public:
	/***************************************
	* PRIVATE GAME FUNCTIONS FOR DRAWING   *
	****************************************/
	//Drawing fucntion
	sf::Text														getMessagePopUp();
		
private:

	/*******************************************
	* PRIVATE GAME VARIABLES FOR TIMING AND HUD *
	********************************************/
	//Game related Variables

	sf::Clock														clock6;
	size_t															score;//Score variable
	sf::Text														gameStateText;//Text Object
	sf::Text														highScoreText;
	sf::Sprite														healthRegainPowerUp;
	bool															buttonsDisabled;
	sf::Music														gameTheme;

public:
	/***************************************
	* PRIVATE GAME VARIABLES FOR GAME STATE *
	****************************************/
	//Enum STATE to retrive and assign Game STATE
	enum class STATE
	{
	  PLAYING, GAME_END, PAUSED
	};
	STATE															GAME_STATE;//STATE object
	sf::Event														GameEvent;//Event object
	sf::RenderWindow												window;//Render window object 
};



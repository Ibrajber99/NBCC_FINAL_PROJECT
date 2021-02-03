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

//Animation Class
class Animation
{
public:

									Animation(sf::Texture texture,sf::Vector2u imageCount,float switchTime);
									~Animation();

public:

	void							update();
	void							reSetIterations();

	bool							isAnimationFinished();

	sf::Texture&					getCurrTexture();
	void							setImageCount(sf::Vector2f coords);

	sf::Sprite&						getCurrAnimation(sf::Vector2f& pos);

	sf::IntRect						getCurrentRectTexture();
public:
	sf::IntRect						uvRect;
private:
	sf::Vector2u					imageCount;
	sf::Vector2u					currentImage;

	sf::Clock						clock;

	sf::Sprite						spriteAnime;

	sf::Texture						currTexture;

	size_t							iterations = 0;

	float							totalTime;
	float							switchTime;

	bool							animationDone = 0;
};


#include "BackgroundDynamics.h"


//constructor that takes in renderWindow,planets,spaceClouds,and background textures.
BackgroundDynamics::BackgroundDynamics(
	sf::RenderWindow& win,
	std::unique_ptr<TextureAssets>& textureHolder)
	: window(win)
	, pauseBackgroundSprite(textureHolder->getpauseBackgroundTexture())
	, gameBackGroundSprite()
	, currentBackgroundIndex(0)
	, movementFlag(true)
	, updatePerFrame(sf::seconds(1.f / 60.f))
{
	//store planets
	for (auto& planetTextures : textureHolder->getScenePlanets()) {
		planetContainer.push_back(sf::Sprite(planetTextures));
	}

	//store clouds
	for (auto& cloudTexture : textureHolder->getSceneClouds()) {
		cloudsContainer.push_back(sf::Sprite(cloudTexture));
	}

	for (auto& background : textureHolder->getBackgrounds()) {
		backgroundsContainer.push_back(std::move(background));
	}

	for (auto& star : textureHolder->getStars()) {
		starsContainer.push_back(sf::Sprite(star));
	}


	//initialize components
	initializeSceneObjects();
	assignRandomBackground();
}


//sets the route in which the background planets will be moving.
void BackgroundDynamics::movePlanets()
{
	if (movementFlag) {
		if (movePlanetClock.getElapsedTime().asSeconds() > 20.f) {
			float dt = clock.restart().asSeconds();
			planetContainer.back().move(1.f, 2.f * dt);
			planetContainer.back().rotate(.3f);
			clock.restart();
		}
	}
	else {
		clock = sf::Clock();
	}
  flushPlanetsOutOfView();
}

//returns last element of the planetContainer
sf::Sprite& BackgroundDynamics::getCurrPlanet(sf::RenderWindow& window)
{
	if (planetContainer.back().getPosition().x + 
		planetContainer.back().getGlobalBounds().width > 0) {

		return planetContainer.back();
	}
	else {
		return mockSprite;
	}
}

//sets the route of the clouds to come from the top and travel down
void BackgroundDynamics::moveClouds()
{
	if (movementFlag) {
		if (moveCloudsClock.getElapsedTime().asSeconds() > 20.f) {
			float dt = cloc2.restart().asSeconds();
			cloudsContainer.back().move(0.8f * dt, 1.f);
			cloc2.restart();
			std::cout << cloudsContainer.back().getPosition().x << " " << cloudsContainer.back().getPosition().y << std::endl;
		}
	}
	else {
		cloc2 = sf::Clock();
	}

	flushCloudsOutOfView();
}

void BackgroundDynamics::moveStars()
{
	if (movementFlag) {
		float dt = cloc2.restart().asSeconds();
		for (auto& star : starsContainer) {
			star.move(0, 100.8f * sf::seconds(1.f / 60.f).asSeconds());
			cloc2.restart();
		}
	}
	else {
		cloc2 = sf::Clock();
	}
	flushStarsOutofView();
}

//returns the last element in the cloudContainer.
sf::Sprite& BackgroundDynamics::getCurrCloud(sf::RenderWindow& window)
{
	if (cloudsContainer.back().getPosition().x +
		cloudsContainer.back().getGlobalBounds().width > 0) {
		return cloudsContainer.back();
	}
	else {
		return mockSprite;
	}
}

//returns pauseBackgroundSprite
sf::Sprite& BackgroundDynamics::getPauseBackgroundSprite()
{
	return pauseBackgroundSprite;
}

//returns gameBackGroundSprite
sf::Sprite& BackgroundDynamics::getGameBackGround()
{
	return gameBackGroundSprite;
}

void BackgroundDynamics::moveSceneObjects()
{
	moveClouds();
	movePlanets();
	moveStars();
}

void BackgroundDynamics::InitializeBackgrounds()
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::shuffle(backgroundsContainer.begin(), 
		backgroundsContainer.end(), mt);
}

//initializes planets and randomly chooses one
void BackgroundDynamics::initializePlanets()
{
	std::random_device rd;
	std::mt19937 mt(rd());
	
	std::shuffle(planetContainer.begin(), planetContainer.end(), mt);
	
	for (auto& cloud : planetContainer) {
		std::uniform_int_distribution<int> distribX(-700, -500);
		std::uniform_int_distribution<int> distribY(30, window.getSize().y - 
			cloud.getGlobalBounds().height);

		cloud.setPosition(sf::Vector2f(distribX(mt), distribY(mt)));
	}
}

//initializes clouds and picks a random one
void BackgroundDynamics::initializeClouds()
{
	std::random_device rd;
	std::mt19937 mt(rd());

	std::shuffle(cloudsContainer.begin(), cloudsContainer.end(), mt);

	for (auto& cloud : cloudsContainer) {
		std::uniform_real_distribution<float> distribX(0, window.getSize().x);
		std::uniform_real_distribution<float> distribY(-200, 0);
		cloud.setPosition(sf::Vector2f(distribX(mt), -1000));
		cloud.setOrigin
		(cloud.getGlobalBounds().width / 2, 
		cloud.getGlobalBounds().height / 2);
	}
}

void BackgroundDynamics::initializeStars()
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<float> distribX(0, window.getSize().x);
	auto &firstElem = starsContainer.front();

	firstElem.setPosition(sf::Vector2f(0, -4000));
	starsContainer.at(1).setPosition(sf::Vector2f(0, firstElem.getPosition().y*2));
	starsContainer.at(2).setPosition(sf::Vector2f(0,firstElem.getPosition().y * 3));
}

//flush clouds out of view
void BackgroundDynamics::flushCloudsOutOfView()
{
	if (cloudsContainer.back().getPosition().y>1500) {
		moveCloudsClock.restart();
		initializeClouds();
	}
}

//flush planets out of view
void BackgroundDynamics::flushPlanetsOutOfView()
{
	if (planetContainer.back().getPosition().x -
		planetContainer.back().getGlobalBounds().height >
		window.getSize().x) {

		movePlanetClock.restart();
		initializePlanets();
	}
}

void BackgroundDynamics::flushStarsOutofView()
{
	if (std::all_of(starsContainer.begin(), starsContainer.end(),
		[&](sf::Sprite& curr) {
		return curr.getPosition().y > 
			window.getPosition().y + curr.getGlobalBounds().height;}))
	{
		initializeStars();
	}
}

void BackgroundDynamics::initializeSceneObjects()
{
	initializeClouds();
	initializePlanets();
	InitializeBackgrounds();
	initializeStars();
}

void BackgroundDynamics::assignRandomBackground()
{
	gameBackGroundSprite.
	setTexture(backgroundsContainer
	[currentBackgroundIndex]);

	neturalizeBackgroundindex();
}

void BackgroundDynamics::lockUpdateMovement()
{
	movementFlag = false;
}

void BackgroundDynamics::unlockUpdateMovement()
{
	movementFlag = true;
}

void BackgroundDynamics::draw()
{
	window.draw(getGameBackGround());
	window.draw(getCurrPlanet(window));
	window.draw(getCurrCloud(window));
	for (auto& star : starsContainer) {
		window.draw(star);
	}
}

void BackgroundDynamics::update()
{
	moveSceneObjects();
	unlockUpdateMovement();
}

//Sets the backgroudn index to zero if it exceeds the backgroudn container limit
void BackgroundDynamics::neturalizeBackgroundindex()
{
	currentBackgroundIndex++;
	if (currentBackgroundIndex > 
		backgroundsContainer.size()-1) {
		currentBackgroundIndex = 0;
	}
	
}



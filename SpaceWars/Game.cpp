#include "Game.h"
#include <type_traits>

Game::Game()

	: window(sf::VideoMode(1900, 900), "Space Wars")
	, GAME_STATE(STATE::PAUSED)
	, textureGenerator(std::make_unique<TextureAssets>())
	, spaceShip(std::make_unique<SpaceShip>(textureGenerator, window))
	, asteroidsManager(std::make_unique<AsteroidsHolder>(textureGenerator, window))
	, gameSound(std::make_unique<SoundEffects>())
	, enemySpaceS(std::make_unique<EnemySpaceShip>(textureGenerator))
	, collisionManager(std::make_unique<CollisionManager>(*this))
	, enemyShipsManager(std::make_unique<EnemyShipsHolder>(textureGenerator,window))
	, score(0)
	, buttonsDisabled(false)
{
	gameSound->getGameMusicTheme().setLoop(true);
	gameSound->getGameMusicTheme().setVolume(20.f);
	gameSound->getGameMusicTheme().play();


	powerUpsManager = std::make_unique <PowerUpsHolder>(spaceShip, asteroidsManager->asteroidsContainer,
		enemyShipsManager->enemyShipsContainer, saucerObject, textureGenerator, window);

	backGroundTexturesManager = std::make_unique<BackgroundDynamics>(window,textureGenerator);
	saucerObject = std::make_unique<Saucer>(textureGenerator,window);

	hudBar.setTexture(textureGenerator->getHudBar());


	window.setFramerateLimit(60);
	initializeAssets();
}

void Game::run()
{
	sf::Time timeSincelastUpdate = sf::Time::Zero;
	sf::Time timePerFrame = sf::seconds(1.f / 60.f);
	while (window.isOpen()) {
		timeSincelastUpdate += clock6.restart();
		while (timeSincelastUpdate > timePerFrame) {
			timeSincelastUpdate -= timePerFrame;

			update(timeSincelastUpdate.asSeconds());
			processEvents();
		}
		render();
	}
}

#pragma region Game Initializers 

void Game::initializeAssets()
{
	spaceShip->getSpaceShipSprite().setPosition(spaceShip->getSpaceShipSpawnPosition());
	highScoreText = textureGenerator->showMessage(window);
	highScoreText.setPosition(250.f, 0.0f);
	hudBar.setPosition(sf::Vector2f(window.getSize().x / 2-50.f, 0.0f));
	gameStateText = textureGenerator->showMessage(window);
	gameStateText.setString("Score: " + std::to_string(getScore()));
	powerUpsManager->fillPowerUps();
	setHighScoreText();
	asteroidsManager->loadAsteroid();
}

void Game::resetGame()
{
	createNewGameObjects();
	GAME_STATE = STATE::PAUSED;
	asteroidsManager->destroyAsteroids();
	powerUpsManager->getPowerUpContainer().clear();
	enemyShipsManager->destroyShips();
	backGroundTexturesManager->assignRandomBackground();
	enemySpaceS->resetSpaceShipAttributes();
	setHighScoreText();
	enableControls();
	initializeAssets();
	reSetScore();
}

#pragma endregion

#pragma region KeyPresses Functions

void Game::on_SpaceClick_KeyPress()
{

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) &&
		!buttonsDisabled && GAME_STATE == STATE::PLAYING) {
		spaceShip->pushProjectilesTimer();
		gameSound->shootBullet();

	}
}

void Game::on_ESCAPE_KeyPress()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)
		&& !buttonsDisabled) {
		GAME_STATE = STATE::PAUSED;
	}
}

void Game::on_ENTER_KeyPress()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
		if (GAME_STATE == STATE::PAUSED && !buttonsDisabled)
			GAME_STATE = STATE::PLAYING;

		else if (GAME_STATE == STATE::GAME_END) {
			resetGame();
		}
	}
}

void Game::on_Key_Press_doIt()
{
	on_SpaceClick_KeyPress();
	on_ESCAPE_KeyPress();
	on_ENTER_KeyPress();
}

#pragma endregion

#pragma region Draw call functions

void Game::determineGameScene()
{
	if (GAME_STATE == STATE::PLAYING) {
		//======================Drawing the scene

		backGroundTexturesManager->draw();
		spaceShip->draw();
		asteroidsManager->drawAsteroids();
		powerUpsManager->draw();
		window.draw(getMessagePopUp());
		enemySpaceS->draw(window);
		window.draw(highScoreText);
		saucerObject->drawSaucer();
		window.draw(hudBar);
		enemyShipsManager->draw();

	}
	else if (GAME_STATE == STATE::PAUSED) {
		window.draw(backGroundTexturesManager->
		getPauseBackgroundSprite());

		window.draw(getMessagePopUp());
	}
	else {
		window.draw(backGroundTexturesManager->
		getPauseBackgroundSprite());

		window.draw(getMessagePopUp());
		window.draw(highScoreText);
	}
}

void Game::render()
{
	window.clear();

	determineGameScene();

	window.display();
}

#pragma endregion

#pragma region Getters functions for various game objects and functionality 
//returns gameStateText
sf::Text Game::getMessagePopUp()
{
	return gameStateText;
}

void Game::setHighScoreText()
{
	highScoreText.setString("HighScore: " + std::to_string(getHighScoreData()));
}

size_t Game::getScore()
{
	return score;
}

int Game::getHighScoreData()
{
	std::string scoreLine;
	std::ifstream readFile("Media/savedData/highScore.txt");

	if (readFile.is_open()) {
		std::getline(readFile, scoreLine);
	}
	readFile.close();
	return std::stoi(scoreLine);

}

bool Game::saveHighScoreData()
{
	if (getHighScoreData() < score) {
		applyHighScoreMessage();

		std::ofstream writeToFile("Media/savedData/highScore.txt", std::ios::trunc);
		if (writeToFile.is_open())
			writeToFile << score;
		else
			return false;

		writeToFile.close();
		return true;
	}
	return false;
}

void Game::reSetScore()
{
	score = 0;
}

void Game::enableControls()
{
	buttonsDisabled = false;
}

void Game::disableControls()
{
	buttonsDisabled = true;
}

void Game::incrementScore(size_t valToIncrement)
{
	score += valToIncrement;
}

void Game::createNewGameObjects()
{
	spaceShip = std::make_unique<SpaceShip>(textureGenerator,window);
	saucerObject = std::make_unique<Saucer>(textureGenerator, window);
	powerUpsManager = std::make_unique <PowerUpsHolder>
		(spaceShip, asteroidsManager->asteroidsContainer, 
		enemyShipsManager->enemyShipsContainer,saucerObject
			,textureGenerator, window);
}
#pragma endregion

#pragma region Update functions for the game objects also (ProcessEvents and render)
//displays the message according to the game state
void Game::updateMessagepopUp()
{

	if (GAME_STATE == STATE::PLAYING) {
		gameStateText.setPosition(sf::Vector2f(window.getSize().x / 2+68.f, 10.0f));
		gameStateText.setString("Score: " + std::to_string(score));
	}
	else if (GAME_STATE == STATE::GAME_END) {
		gameStateText.setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2));
		gameStateText.setString("GAME OVER \n Press Enter to Play again");
	}
	else {
		gameStateText.setPosition(sf::Vector2f(window.getSize().x / 2 -
			gameStateText.getGlobalBounds().width, window.getSize().y / 2
			- gameStateText.getGlobalBounds().height));

		gameStateText.setString("PAUSED \n Press Enter to Continue");
	}
}

void Game::applyHighScoreMessage()
{
	highScoreText.setCharacterSize(60.f);
	highScoreText.setString("Yay!! New HighScore " + std::to_string(score));
}

void Game::updateAllWorldObjects()
{
	asteroidsManager->update();	
	powerUpsManager->update();

	if (spaceShip->isDestroyedStatus()) {
		!spaceShip->isAnimationFinished() ?
			spaceShip->beginSpaceShipAnimation() :
			enableControls();
	}

	spaceShip->update(powerUpsManager);
	backGroundTexturesManager->update();
	enemySpaceS->update(window);
	saucerObject->update();
	collisionManager->manageCollisions();
	enemyShipsManager->update();
}

//updates view.
void Game::update(float dt)
{
	updateMessagepopUp();
	if (GAME_STATE == STATE::PLAYING) {
		updateAllWorldObjects();

		if (!buttonsDisabled) {
			spaceShip->moveSpaceShip(dt);
		}
		if (clock.getElapsedTime().asSeconds() > 6.f) {
			enemySpaceS->setBulletDirection
			(spaceShip->getSpaceShipSprite().getPosition());
		}

	}
	if (GAME_STATE == STATE::GAME_END) {
		saveHighScoreData();
		
	}
	if (GAME_STATE == STATE::PAUSED) {
		enemySpaceS->lockUpdateMovement();
		asteroidsManager->lockUpdateMovement();
		backGroundTexturesManager->lockUpdateMovement();
		clock6.restart();
	}
}

//processes key press events.
void Game::processEvents()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)
			&& (GAME_STATE == STATE::GAME_END || GAME_STATE == STATE::PAUSED))
			window.close();

		on_Key_Press_doIt();
	}
}
#pragma endregion


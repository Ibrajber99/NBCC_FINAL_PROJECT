#include "SpaceShip.h"
#include "PowerUps.h"
#include "PowerUpsHolder.h"
//spaceShip constructor which accepts texture for 
//spaceship,texture for explosion of the spaceship
//and the texture for the healthbar

SpaceShip::SpaceShip(
	std::unique_ptr<TextureAssets>& textureHolder,
	sf::RenderWindow& window)

	//Constructor initialization list 
	:window(window)
	, isAlive(true)
	, movingForward(false)
	, isShipDestroyed(false)
	, animationFinished(false)
	, animationBegan(false)
	, shipImmunity(false)
	, isButtonActionEnabled(true)
	, health(2)
	, spaceShipTexture(std::move(textureHolder->getSpaceShipTexture()))
	, healthBarTexture(std::move(textureHolder->getHealthBarTexture()))
	, animationManager
	(std::make_unique<Animation>(textureHolder->getSpaceShipExplosion(), sf::Vector2u(17, 1), .1f))
	, currDirection(Direction::IDLE)


{
	//set texture of the spaceship instance to the texture of the spaceship
	spaceShipTexturesMap.insert({ Direction::IDLE,textureHolder->getSpaceShipTextures().at(0) });
	spaceShipTexturesMap.insert({ Direction::LEFT,textureHolder->getSpaceShipTextures().at(1) });
	spaceShipTexturesMap.insert({ Direction::RIGHT,textureHolder->getSpaceShipTextures().at(2) });
	spaceShipTexturesMap.insert({ Direction::DASH_RIGHT_NORMAL,textureHolder->getSpaceShipTextures().at(3) });
	spaceShipTexturesMap.insert({ Direction::DASH_LEFT_NORMAL,textureHolder->getSpaceShipTextures().at(4) });
	spaceShipTexturesMap.insert({ Direction::DASH_LEFT_SHIELDED,textureHolder->getSpaceShipTextures().at(5) });
	spaceShipTexturesMap.insert({ Direction::DASH_RIGHT_SHIELDED,textureHolder->getSpaceShipTextures().at(6) });


	shieldedSpaceShipTexture = std::move(textureHolder->getSpaceShipProtectionShield());
	spaceShipShieldedSprite.setTexture(shieldedSpaceShipTexture);
	spaceShipShieldedSprite.setScale(0.23, 0.23);


	dashRightAnimationManager = std::make_unique<Animation>
		(spaceShipTexturesMap[Direction::DASH_RIGHT_NORMAL], sf::Vector2u(9, 1), .1f);

	dashLeftAnimationManager = std::make_unique<Animation>
		(spaceShipTexturesMap[Direction::DASH_LEFT_NORMAL], sf::Vector2u(9, 1), .1f);

	normalBulletTex = std::move(textureHolder->getBullets());
	animatedBulletTex = std::move(textureHolder->getBulletFired());

	specialBulletCollisionTex = std::move(textureHolder->getSpecialBulletCollisionAnimation());
	normalBulletCollisionTex = std::move(textureHolder->getNormalBulletCollisionAnimation());

	lifeBar.setSize(sf::Vector2f(240.f, 16.f));
	lifeBar.setFillColor(sf::Color::Green);
	lifeBar.setPosition(1635.f,848.f);

	sf::Vector2f middlePoint;

	middlePoint.x = std::floor(lifeBar.getLocalBounds().left + lifeBar.getLocalBounds().width / 2.f);
	middlePoint.y = std::floor(lifeBar.getLocalBounds().top + lifeBar.getLocalBounds().height / 2.f);

	lifeBar.setOrigin(middlePoint);
	lifeBar.rotate(180);

	playerHealthBarHUDTexture = (std::move(textureHolder->getPlayerLifeBarHud()));

	playerHealthHUDSprite.setTexture(playerHealthBarHUDTexture);
	playerHealthHUDSprite.setScale(0.7f, .7f);
	playerHealthHUDSprite.setPosition(1500.f, 780.f);
}


void SpaceShip::draw()
{
	for (auto& projectile : projectilesMagazine) {
		window.draw(projectile->getBulletSprite());
	}

	window.draw(getSpaceShipSprite());

	for (auto& playerBar : getHealthMeter())
		window.draw(playerBar);

	window.draw(playerHealthHUDSprite);
	window.draw(lifeBar);
}

void SpaceShip::update(std::unique_ptr<PowerUpsHolder>& powerUpsManager)
{
	updateSpaceShipPowerType(powerUpsManager);
	moveProjectiles();
	flushProjectiles();
	updateSpriteOnDirection();
	beginDashRightAnimation();
	beginDashLeftAnimation();


	if (isDestroyedStatus()) {
		if (!isAnimationFinished())
			beginSpaceShipAnimation();
		else {
			getSpaceShipSprite().setPosition(getSpaceShipSpawnPosition());
			setShipDestroyedState(false);
			setAnimationTrigger(false);
		}
	}
}

#pragma region Getters and setters
sf::Vector2f SpaceShip::getSpaceShipSpawnPosition()
{
	return sf::Vector2f(window.getSize().x / 2 -
		spaceShipSprite.getGlobalBounds().width,
		window.getSize().y - spaceShipSprite.getGlobalBounds().height);
}

//returns a reference to the spaceShip sprite.
sf::Sprite& SpaceShip::getSpaceShipSprite()
{
	return getAccordingSprite();
}

sf::Sprite& SpaceShip::getAccordingSprite()
{
	if (isDestroyedStatus()
		&& !isAnimationFinished()) {
		return spaceShipExplosionSprite;
	}
	else {

		if (getCurrrentSpaceShipPowerUpType()
			!= SpaceShip::PowerUpType::Shield) {
			spaceShipSprite.
				setPosition(getSpaceShipCurrentPostion());
			return spaceShipSprite;
		}
		else {
			spaceShipShieldedSprite.
				setPosition(getSpaceShipCurrentPostion());
			return spaceShipShieldedSprite;
		}
	}
}

std::vector<sf::Sprite>& SpaceShip::getHealthMeter() {
	return generateHealthMeter();
}

std::vector<sf::Sprite>& SpaceShip::generateHealthMeter()
{

	if (checkifAlive()) {
		playerHealth.clear();
		float tmpPos = 40.f;
		for (int i = 0; i < getCurrHealth(); i++) {
			playerHealth.push_back(sf::Sprite(healthBarTexture));

			playerHealth.back().setPosition(tmpPos, 
			window.getSize().y-healthBarTexture.getSize().y);

			tmpPos += 40.f;
		};
	}
	return playerHealth;
}

sf::Vector2f SpaceShip::getSpaceShipCurrentPostion()
{
	return getAccordingSpaceShipPosition();
}

sf::Vector2f SpaceShip::getAccordingSpaceShipPosition()
{

	if (getCurrrentSpaceShipPowerUpType()
		!= SpaceShip::PowerUpType::Shield) {

		spaceShipShieldedSprite.
			setPosition(spaceShipSprite.getPosition());

		return spaceShipSprite.getPosition();
	}
	else {
		spaceShipSprite.
			setPosition(spaceShipShieldedSprite.getPosition());

		return spaceShipShieldedSprite.getPosition();
	}
}

sf::Vector2f SpaceShip::getSpaceCenterPos()
{
	return sf::Vector2f((float)(getSpaceShipSprite().getPosition().x + getSpaceShipSprite().getGlobalBounds().width / 3.3),
		((float)getSpaceShipSprite().getPosition().y + getSpaceShipSprite().getGlobalBounds().height) - 30.f);
}

void SpaceShip::beginSpaceShipAnimation()
{

	sf::Vector2f  currPos = spaceShipSprite.getPosition();
	if (!animationManager->isAnimationFinished()) {
		animationManager->update();

		spaceShipExplosionSprite = 
		std::move(animationManager->getCurrAnimation(currPos));
	}
	else {
		animationFinished = 1;
		animationManager->reSetIterations();

	}
}

void SpaceShip::beginDashRightAnimation()
{
	if (getDirection() == Direction::DASH_RIGHT_NORMAL ||
		getDirection() == Direction::DASH_RIGHT_SHIELDED) {


		sf::Vector2f  currPos = spaceShipSprite.getPosition();
		if (!dashRightAnimationManager->isAnimationFinished()) {
			dashRightAnimationManager->update();

			getSpaceShipSprite() =
				std::move(dashRightAnimationManager->getCurrAnimation(currPos));

			getSpaceShipSprite().setScale(0.23, 0.23);

			if(canMoveRight())
				getSpaceShipSprite().move(sf::seconds(1.f / 60.f).asSeconds() * 580.f, 0.0f);
		}
		else {
			dashRightAnimationManager->reSetIterations();
			setDirection(Direction::IDLE);

			getSpaceShipSprite() = sf::Sprite();
			getSpaceShipSprite().setPosition(currPos.x +40.f,currPos.y);

			isButtonActionEnabled = true;
		}
	}
}

void SpaceShip::beginDashLeftAnimation()
{
	if (getDirection() == Direction::DASH_LEFT_NORMAL ||
		getDirection() == Direction::DASH_LEFT_SHIELDED) {

		sf::Vector2f  currPos = spaceShipSprite.getPosition();
		if (!dashLeftAnimationManager->isAnimationFinished()) {
			dashLeftAnimationManager->update();

			getSpaceShipSprite()=
				std::move(dashLeftAnimationManager->getCurrAnimation(currPos));

			getSpaceShipSprite().setScale(0.23, 0.23);

			if (canMoveLeft())
				getSpaceShipSprite().move(sf::seconds(1.f / 60.f).asSeconds() * -580.f, 0.0f);
		}
		else {
			dashLeftAnimationManager->reSetIterations();
			setDirection(Direction::IDLE);

			getSpaceShipSprite() = sf::Sprite();
			getSpaceShipSprite().setPosition(currPos.x, currPos.y);

			isButtonActionEnabled = true;
		}
	}
}

//returns animationFinsihed flag.
bool SpaceShip::isAnimationFinished()
{
	return animationFinished;
}

//sets the animationFinished flag to the specified state
void SpaceShip::setAnimationTrigger(bool b)
{
	animationFinished = b;
}

//returns isAlive 
bool SpaceShip::checkifAlive()const {
	return isAlive;
}

//reduces spaceShip health and filps isAlive if the ship runs out of health.
void SpaceShip::getHit() {

	decreaseLifeBar();
	if (lifeBar.getSize().x <= 0) {
		setShipDestroyedState(true);
		health--;

		if (health > 0)resetLifeBar();
	}

	if (health <= 0) {
		isAlive = 0;
		shipInvincibility = true;
	}
}

//returns health
size_t SpaceShip::getCurrHealth()const {
	return health;
}

SpaceShip::PowerUpType SpaceShip::getCurrrentSpaceShipPowerUpType()
{
	return currentPowerUp;
}

void SpaceShip::setDirection(Direction dir)
{
	currDirection = dir;
}

SpaceShip::Direction SpaceShip::getDirection() const
{
	return currDirection;
}

void SpaceShip::updateSpriteOnDirection()
{
	if (getCurrrentSpaceShipPowerUpType() != PowerUpType::Shield) {
		switch (currDirection)
		{
		case SpaceShip::Direction::LEFT:
			spaceShipSprite.setTexture(spaceShipTexturesMap[Direction::LEFT]);
			spaceShipSprite.setScale(0.23, 0.23);
			break;
		case SpaceShip::Direction::RIGHT:
			spaceShipSprite.setTexture(spaceShipTexturesMap[Direction::RIGHT]);
			spaceShipSprite.setScale(0.23, 0.23);
			break;
		case SpaceShip::Direction::IDLE:
			spaceShipSprite.setTexture(spaceShipTexturesMap[Direction::IDLE]);
			spaceShipSprite.setScale(0.23, 0.23);
			break;
		default:
			break;
		}
	}
	else {
		if (SpaceShip::Direction::DASH_LEFT_SHIELDED != currDirection
			&& SpaceShip::Direction::DASH_RIGHT_SHIELDED != currDirection) {
			spaceShipShieldedSprite.setTexture(shieldedSpaceShipTexture);
			spaceShipShieldedSprite.setScale(0.23, 0.23);
		}
	}
}

void SpaceShip::resetLifeBar()
{
	lifeBar.setSize(sf::Vector2f(230.f, 16.f));
}

void SpaceShip::decreaseLifeBar()
{
	lifeBar.setSize(sf::Vector2f
	(lifeBar.getSize().x - 18.5f, lifeBar.getSize().y));
}

//sets isShipDestroyed flag to specified state
void SpaceShip::setShipDestroyedState(bool b)
{
	isShipDestroyed = b;
}

//returns isShipDestroyed flag.
bool SpaceShip::isDestroyedStatus() const
{
	return isShipDestroyed;
}

//returns shipImmunity flag
bool SpaceShip::isShipImmune()const
{
	return shipImmunity;
}

//sets shipImmunity flag to specified state
void SpaceShip::setShipImmunity(bool b)
{
	shipImmunity = b;
}

//sets health to the passed in health value
void SpaceShip::setHealth(size_t m)
{
	if (health < 4) {
		health += m;
		resetLifeBar();
	}
}

#pragma endregion

#pragma region  spaceShip move functions

bool SpaceShip::canMoveUp()
{
	return getSpaceShipSprite().getPosition().y -
		getSpaceShipSprite().getGlobalBounds().height > 0;
}

bool SpaceShip::canMoveDown()
{
	return getSpaceShipSprite().getPosition().y +
		getSpaceShipSprite().getGlobalBounds().height < window.getSize().y;
}

bool SpaceShip::canMoveLeft()
{
	return getSpaceShipSprite().getPosition().x > 0;
}

bool SpaceShip::canMoveRight()
{
	return getSpaceShipSprite().getPosition().x +
		getSpaceShipSprite().getGlobalBounds().width
		< window.getSize().x;
}

void SpaceShip::moveSpaceShip(float dt)
{
	if (checkifAlive() && isButtonActionEnabled) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
			&& canMoveUp()) {
			getSpaceShipSprite().move(0.0f, sf::seconds(1.f / 60.f).asSeconds() * -480.f);
			setDirection(Direction::IDLE);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)
			&& canMoveDown()) {
			getSpaceShipSprite().move(0.0f, sf::seconds(1.f / 60.f).asSeconds() * 480.f);
			setDirection(Direction::IDLE);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)
			&& canMoveLeft()) {
			getSpaceShipSprite().move(sf::seconds(1.f / 60.f).asSeconds() * -480.f, 0.0f);
			setDirection(Direction::LEFT);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)
			&& canMoveRight()) {
			getSpaceShipSprite().move(sf::seconds(1.f / 60.f).asSeconds() * 480.f, 0.0f);
			setDirection(Direction::RIGHT);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			isButtonActionEnabled = false;

			if (currentPowerUp == PowerUpType::Shield) {
				setDirection(Direction::DASH_RIGHT_SHIELDED);
				dashRightAnimationManager->setTexture
				(spaceShipTexturesMap[Direction::DASH_RIGHT_SHIELDED]);
			}
			else {
				setDirection(Direction::DASH_RIGHT_NORMAL);
				dashRightAnimationManager->setTexture
				(spaceShipTexturesMap[Direction::DASH_RIGHT_NORMAL]);
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			isButtonActionEnabled = false;
			if (currentPowerUp == PowerUpType::Shield) {
				setDirection(Direction::DASH_LEFT_SHIELDED);
				dashLeftAnimationManager->setTexture
				(spaceShipTexturesMap[Direction::DASH_LEFT_SHIELDED]);
			}
			else {
				setDirection(Direction::DASH_LEFT_NORMAL);
				dashLeftAnimationManager->setTexture
				(spaceShipTexturesMap[Direction::DASH_LEFT_NORMAL]);
			}
		}
	}

}

#pragma endregion

#pragma region Projectile related functions
std::vector<std::unique_ptr<PlayerBullets>>&
SpaceShip::getProjectilesMagazine()
{
	return projectilesMagazine;
}

void SpaceShip::pushProjectiles()
{
	pushAccordingProjectile();
}

void SpaceShip::pushAccordingProjectile()
{
	sf::Vector2f spawnPosition = sf::Vector2f
	(getSpaceCenterPos().x,
		getSpaceCenterPos().y - 100.f);

	if (currentPowerUp == PowerUpType::OneHitKill) {

		projectilesMagazine.push_back(std::make_unique<PlayerBullets>(animatedBulletTex,
			specialBulletCollisionTex, 1));

		projectilesMagazine.back()->setSpawnPosition(spawnPosition);
	}
	else {
		projectilesMagazine.push_back(std::make_unique<PlayerBullets>
		(normalBulletTex, normalBulletCollisionTex));

		projectilesMagazine.back()->setSpawnPosition(spawnPosition);
	}
}

void SpaceShip::flushProjectiles()
{
	projectilesMagazine.erase(std::remove_if(projectilesMagazine.begin(), projectilesMagazine.end(),
		[&](std::unique_ptr<PlayerBullets>& p) {
			return p->isBulletCollisionAnimationFinished() || p->getBulletSprite().getPosition().y < 0 ||
				p->getBulletSprite().getPosition().y > window.getSize().y;

		}), projectilesMagazine.end());
}

void SpaceShip::moveProjectiles()
{
	for (auto& bullet : projectilesMagazine) {
		if (bullet->isBulletAnimated()) {
			bullet->beginBulletFiredAnimation();
		}
		if (bullet->isBulletsCollided()
			|| (!bullet->isBulletAlive() && !bullet->isBulletAnimated())) {
			bullet->beginBulletCollisionAnimation();
		}
		else {
			bullet->moveBullets();
		}
	}
}

void SpaceShip::pushProjectilesTimer()
{
	if (clock1.getElapsedTime().asSeconds() > 0.1f) {
		pushProjectiles();
		clock1.restart();
	}
}
#pragma endregion

void SpaceShip::updateSpaceShipPowerType
(std::unique_ptr<PowerUpsHolder>& powerUpsManager)
{
	if (powerUpsManager->getPowerUpContainer().empty()) {
		setPowerUpType(SpaceShip::PowerUpType::None);
		return;
	}
	if (powerUpsManager->getPowerUpContainer().back().second == true) {

		PowerUps::Type tmpType =
			powerUpsManager->getPowerUpContainer().back().first->getType();

		switch (tmpType) {
		case PowerUps::Type::Nuke:
			setPowerUpType(SpaceShip::PowerUpType::Nuke);
			break;
		case PowerUps::Type::OneHit:
			setPowerUpType(SpaceShip::PowerUpType::OneHitKill);
			break;
		case PowerUps::Type::sheild:
			setPowerUpType(SpaceShip::PowerUpType::Shield);
			break;
		case PowerUps::Type::Health:
			setPowerUpType(SpaceShip::PowerUpType::Health);
			break;
		case PowerUps::Type::Radar:
			setPowerUpType(SpaceShip::PowerUpType::Radar);
			break;

		default:
			setPowerUpType(SpaceShip::PowerUpType::None);
			break;
		}
	}
	else {
		setPowerUpType(SpaceShip::PowerUpType::None);
	}
}

void SpaceShip::setPowerUpType(PowerUpType type)
{
	currentPowerUp = type;
}

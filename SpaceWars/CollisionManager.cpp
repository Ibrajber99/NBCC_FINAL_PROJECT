#include "CollisionManager.h"
#include "Game.h"

//This class is for managin all world objects collisions

CollisionManager::CollisionManager(Game& game_)
	:game(game_){}


void CollisionManager::determineHitAsteroidScore
					(std::unique_ptr<Asteroids>& asteroid,
					std::unique_ptr<PlayerBullets>& bullet)
{
	if (!asteroid->isAnimationBegan()) {
		asteroid->getHit();
		if (asteroid->isAsteroidDestroyed()) {
			game.gameSound->hitTarget();

			asteroid->getType() ==Asteroids::AsteroidType::Large ?
			game.incrementScore(2) : game.incrementScore(1);
		}
		else {
			game.gameSound->hitTargetNoDestruction();
		}

		bullet->flushBullets();
	}

}


void CollisionManager::hitSpaceShipEffect()
{
	game.spaceShip->getHit();
	if (game.spaceShip->isDestroyedStatus()) {
		game.gameSound->spaceShipDestruction();
		game.enemyShipsManager->destroyShips();
		game.disableControls();
		game.asteroidsManager->destroyAsteroids();
		//clock to freeze enemy bullets
		game.clock.restart();
	}


	if (!game.spaceShip->checkifAlive()) {
		game.GAME_STATE = Game::STATE::GAME_END;
	}
}

void CollisionManager::projectileHitsAsteroid
	(std::unique_ptr<PlayerBullets>& bullet,
	std::unique_ptr<Asteroids>& asteroid)
{
	if (!bullet->isBulletAnimated()) {

		//asteroid animation is not in action
		determineHitAsteroidScore(asteroid, bullet);
	}
	else {
		if (!game.powerUpsManager->getPowerUpContainer().empty()) {
			if ((game.powerUpsManager->
				getPowerUpContainer().back().first)->getType() == PowerUps::Type::OneHit
				&& game.powerUpsManager->getPowerUpContainer().back().second == true) {

				dynamic_cast<OneHitKillPowerUp*>(game.powerUpsManager->getPowerUpContainer().back().
					first.get())->oneHitKillPowerUpTakeEffect(asteroid);
				determineHitAsteroidScore(asteroid, bullet);
			}
		}
	}

}


void CollisionManager::asteroidHitsSpaceShip
	(std::unique_ptr<Asteroids>& asteroid)
{
	if (!game.spaceShip->isShipImmune() && !asteroid->isAsteroidDestroyed()) {
		asteroid->setIsDestroyed(true);
		asteroidHitSpaceShip();
	}
	//spaceship is immune
	else {
		asteroid->setIsDestroyed(1);
	}
}


void CollisionManager:: enemyPojectileHitsSpaceShip
	(size_t index)
{
	game.enemySpaceS->flushBulletAt(index);
	enemyProjectileHItSpaceShip();
}


void CollisionManager::projectileHitSmallShips(std::unique_ptr<PlayerBullets>& bullet,
	std::unique_ptr<Enemyships>& enemySmallShip)
{
	if (!enemySmallShip->isDestructionAnimationBegan()) {
		if (bullet->isBulletAnimated()) {
			enemySmallShip->damage(3);
		}
		else {
			enemySmallShip->damage(1);
		}
		if (enemySmallShip->getHitPoints() <= 0)
			game.incrementScore(2);

		bullet->flushBullets();
	}

}


void CollisionManager::smallEnemySpaceShipHitSpaceShip
(std::unique_ptr<Enemyships>& enemySmallShip)
{
	if (!enemySmallShip->isDestructionAnimationBegan()) {

		enemySmallShip->damage(3);

		if (game.spaceShip->getCurrrentSpaceShipPowerUpType() != SpaceShip::PowerUpType::Shield) {
			hitSpaceShipEffect();
		}
	}
}


void CollisionManager::projectileHitsEnemySpaceShip
	(std::unique_ptr<PlayerBullets>& bullet)
{
	if (bullet->isBulletAnimated()) {
		game.enemySpaceS->getHit();
		game.enemySpaceS->getHit();
		game.enemySpaceS->getHit();
	}
	else {
		game.enemySpaceS->getHit();
	}
	bullet->flushBullets();
}


void CollisionManager::collideBullets
	(size_t index, 
	std::unique_ptr<PlayerBullets>& playerBullets)
{
	playerBullets->triggerBulletCollision();
	if (playerBullets->isBulletAnimated()) {
		game.enemySpaceS->flushBulletAt(index);
	}
}


void CollisionManager::asteroidHitSpaceShip()
{
	hitSpaceShipEffect();
}


void CollisionManager::enemyProjectileHItSpaceShip()
{
	hitSpaceShipEffect();
}


void CollisionManager::triggerPowerUpPickUp()
{
	if (!game.powerUpsManager->getPowerUpContainer().empty()) {

		if (game.powerUpsManager->
			getPowerUpContainer().back().first->getType()
			== PowerUps::Type::Nuke) {

			game.powerUpsManager->getPowerUpContainer().back().first->powerUpTakeEffect();

			game.incrementScore(game.enemyShipsManager->getEnemyShipsContainer().size());
			game.incrementScore(game.asteroidsManager->asteroidsContainer.size());
		}
		else {
			game.powerUpsManager->getPowerUpContainer().back().first->powerUpTakeEffect();
		}
		game.powerUpsManager->getPowerUpContainer().
			back().second = true;
		game.powerUpsManager->getPowerUpContainer().
			back().first->movePowerUpOutOfScreen();
	}

}



void CollisionManager::checkProjectileHitAsteroid()
{
	for (auto& bullet : game.spaceShip->getProjectilesMagazine()) {
		for (auto& asteroid : game.asteroidsManager->asteroidsContainer) {
			//asteroid is hit
			if (isObjectsColliding(bullet->getBulletSprite(),
				asteroid->getAsteroidSprite())) {
				//special bullet is not being used
				projectileHitsAsteroid(bullet, asteroid);
			}
		}
	}
}



void CollisionManager::checkAsteroidHitSpaceShip()
{
	//spaceship is alive
	if (!game.spaceShip->isDestroyedStatus()) {
		//finds the asteroid that collided with the ship
		for (auto& asteroid : game.asteroidsManager->asteroidsContainer) {
			//spaceship collieds with an asteroid
			if (isObjectsColliding(game.spaceShip->getSpaceShipSprite(), asteroid->getAsteroidSprite())) {
				asteroidHitsSpaceShip(asteroid);
			}
		}
	}
}


void CollisionManager::checkBulletHitSaucer()
{
	for (auto& bullet : game.spaceShip->getProjectilesMagazine()) {
		if (isObjectsColliding(bullet->getBulletSprite(), game.saucerObject->getSaucerSprite())) {
			bulletHitSaucer(bullet);
			game.gameSound->saucerSuckSound();
		}
	}
}


void CollisionManager::checkEnemyProjectileHitSpaceShip()
{
	//spaceship is not destroyed
	if (!game.spaceShip->isDestroyedStatus()) {
		//find the bullet that hit the ship
		for (auto bulletItr = game.enemySpaceS->getBulletMagazine().begin();
			bulletItr != game.enemySpaceS->getBulletMagazine().end(); bulletItr++) {
			//bullet collides with the ship
			if (isObjectsColliding(game.spaceShip->getSpaceShipSprite(), bulletItr->first)) {
				std::size_t bulletIndex = std::distance(game.enemySpaceS->getBulletMagazine().begin(), bulletItr);
				enemyPojectileHitsSpaceShip(bulletIndex);
			}
		}
	}
}


bool CollisionManager::checkPowerUpsHitSpaceShip()
{
	if (!game.powerUpsManager->getPowerUpContainer().empty()) {
		if (isObjectsColliding(game.spaceShip->getSpaceShipSprite(),
			game.powerUpsManager->getPowerUpContainer().back().first->getPowerUpSprite())) {
			triggerPowerUpPickUp();
			return true;
		}
	}
	return false;
}


void CollisionManager::checkProjectileHitEnemySpaceShip()
{
	//find player bullet that hit the spaceship
	for (auto& bullet : game.spaceShip->getProjectilesMagazine()) {
		//bullet did hit the enemy ship
		if (isObjectsColliding(bullet->getBulletSprite(), game.enemySpaceS->getSpaceShip())) {
			//bullet is animated
			projectileHitsEnemySpaceShip(bullet);
		}
	}
}


void CollisionManager::checkProjectileHitSmallShips()
{
	int spaceShipSizeBefore = game.enemyShipsManager->getEnemyShipsContainer().size();
	for (auto& bullet : game.spaceShip->getProjectilesMagazine()) {
		for (auto& enemyShip : game.enemyShipsManager->getEnemyShipsContainer()) {
			if (isObjectsColliding(bullet->getBulletSprite(),
				enemyShip->getShipSprite())) {
				projectileHitSmallShips(bullet, enemyShip);
			}
		}
	}
}


void CollisionManager::checkSmallEnemyShipsProjectileHitSpaceShip()
{
	for (auto& enemyShip : game.enemyShipsManager->enemyShipsContainer) {
		for (auto& enemyShipBullets : enemyShip->getBulletsContainer()) {
			if (isObjectsColliding(game.spaceShip->getSpaceShipSprite(),
				enemyShipBullets)) {
				enemyShipBullets.move(0, 1000.f);
				enemyProjectileHItSpaceShip();
				break;
			}
		}
	}

}


void CollisionManager::checkSmallShipsHitSpaceShip()
{
	for (auto& enemyShip : game.enemyShipsManager->enemyShipsContainer) {
		if (isObjectsColliding(enemyShip->getShipSprite(),
			game.spaceShip->getSpaceShipSprite())) {
			smallEnemySpaceShipHitSpaceShip(enemyShip);
		}
	}
}


void CollisionManager::bulletHitSaucer
	(std::unique_ptr<PlayerBullets>& bullet)
{
	bullet->flushBullets();
	game.saucerObject->triggerBulletHitSaucer();
}


void CollisionManager::isBullets_Colliding()
{
	for (auto& playerBullets : game.spaceShip->getProjectilesMagazine()) {

		for (auto enemyBulletItr = game.enemySpaceS->getBulletMagazine().begin();
			enemyBulletItr != game.enemySpaceS->getBulletMagazine().end(); enemyBulletItr++) {


			if (isObjectsColliding(playerBullets->getBulletSprite(), enemyBulletItr->first)) {

				auto enemyBulletIndex =
					std::distance(game.enemySpaceS->getBulletMagazine().begin(), enemyBulletItr);

				collideBullets(enemyBulletIndex, playerBullets);

				if (playerBullets->isBulletAnimated())
					game.gameSound->specialBulletClashSound();
				else
					game.gameSound->normalBulletClashSound();
			}
		}
	}
}


bool CollisionManager::isObjectsColliding
	(sf::Sprite objA, sf::Sprite objB)
{
	return objA.getGlobalBounds().intersects(objB.getGlobalBounds());
}


void CollisionManager::manageCollisions()
{
	checkProjectileHitAsteroid();
	checkAsteroidHitSpaceShip();
	checkPowerUpsHitSpaceShip();
	checkEnemyProjectileHitSpaceShip();
	checkProjectileHitEnemySpaceShip();
	isBullets_Colliding();
	checkBulletHitSaucer();
	checkProjectileHitSmallShips();
	checkSmallEnemyShipsProjectileHitSpaceShip();
	checkSmallShipsHitSpaceShip();
}


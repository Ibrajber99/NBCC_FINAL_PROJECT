#include "NukePowerUp.h"
#include "Utility.h"

//constructor that takes a reference to the spaceShip, asteriod and power up texture.

NukePowerUp::NukePowerUp
(std::unique_ptr<SpaceShip>& spaceS,
    std::vector<std::unique_ptr<Asteroids>>& enimies,
    std::vector<std::unique_ptr<Enemyships>>& enemyShips_,
    sf::Texture powerUpTex)

    : enimiesAsteroids(enimies)
    , enemyShips(enemyShips_)
    , destroyAsteroidFlag(false)
{

    //assigns passed in values to the variables in the super class
    spaceShip = spaceS.get();

    //sets texture of the powerup.
    powerUpTexture = std::move(powerUpTex);
    powerUpSprite.setTexture(powerUpTexture);

    setPowerUpTextAttributes();
}

//returns powerUpSprite for the oneHitKill pickup powerup.
sf::Sprite& NukePowerUp::getPowerUpSprite()
{
    return powerUpSprite;
}

void NukePowerUp::powerUpTakeEffect()
{
    for (auto& aster : enimiesAsteroids) {
        aster->setIsDestroyed(1);
    }
    for (auto& enemShip : enemyShips) {

        enemShip->damage(3);
    }
}

void NukePowerUp::setPowerUpTextAttributes()
{
    powerUpText.setFont(getFont());
    powerUpText.setString("NUKE");
    centerOrigin(powerUpText);
    powerUpText.setCharacterSize(50);
    powerUpText.setFillColor(sf::Color(150.f, 255.f, 150.f, 100.f));
}

NukePowerUp::Type NukePowerUp::getType()
{
    return Type::Nuke;
}


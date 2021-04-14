#include "NukePowerUp.h"
#include "Utility.h"

NukePowerUp::NukePowerUp
(
    std::unique_ptr<SpaceShip>& spaceS,
    std::vector<std::unique_ptr<Asteroids>>& enimies,
    std::vector<std::unique_ptr<Enemyships>>& enemyShips_,
    sf::Texture powerUpTex)

    : enimiesAsteroids(enimies)
    , enemyShips(enemyShips_)
    , destroyAsteroidFlag(false)
{

    spaceShip = spaceS.get();

    powerUpTexture = std::move(powerUpTex);
    powerUpSprite.setTexture(powerUpTexture);

    setPowerUpTextAttributes();
}

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
    powerUpText.setFillColor(sf::Color::Yellow);
}

NukePowerUp::Type NukePowerUp::getType()
{
    return Type::Nuke;
}


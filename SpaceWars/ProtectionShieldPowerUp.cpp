#include "ProtectionShieldPowerUp.h"
#include "Utility.h"

//constructor

//constructor that takes a reference to the spaceShip, asteriod and power up texture;
ProtectionShieldPowerUp::ProtectionShieldPowerUp
(std::unique_ptr<SpaceShip>& spaceS,
    std::vector<std::unique_ptr<Asteroids>>& enimies,
    sf::Texture powerUpTex)

    :enimiesAsteroids(enimies)
{

    //assigns passed in values to the variables in the super class
    spaceShip = spaceS.get();
    //sets texture of the powerup.
    powerUpTexture = std::move(powerUpTex);
    powerUpSprite.setTexture(powerUpTexture);

    setPowerUpTextAttributes();
}
//returns powerUpSprite for the protection Shield pickup powerup.
sf::Sprite& ProtectionShieldPowerUp::getPowerUpSprite()
{
    return powerUpSprite;
}

void ProtectionShieldPowerUp::powerUpTakeEffect()
{
    spaceShip->setShipImmunity(!spaceShip->isShipImmune());
}

ProtectionShieldPowerUp::Type ProtectionShieldPowerUp::getType()
{
    return Type::sheild;
}

void ProtectionShieldPowerUp::setPowerUpTextAttributes()
{
    powerUpText.setFont(getFont());
    powerUpText.setString("PROTECTION SHEILD");
    centerOrigin(powerUpText);
    powerUpText.setCharacterSize(50);
    powerUpText.setFillColor(sf::Color(105.f, 163.f, 174.f, 255.f));
}



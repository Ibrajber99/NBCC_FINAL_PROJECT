#include "HealthPowerUp.h"
#include "Utility.h"

//constructor that takes in a pointer to spaceShip, asteroid and texture for the powerup
HealthPowerUp::HealthPowerUp(std::unique_ptr<SpaceShip> &spaceS, 
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
//returns powerUpSprite for the health pickup powerup.
sf::Sprite &HealthPowerUp::getPowerUpSprite()
{
    return powerUpSprite;
}

void HealthPowerUp::powerUpTakeEffect()
{
    spaceShip->setHealth(1);
}

HealthPowerUp::Type HealthPowerUp::getType()
{
    return Type::Health;
}

void HealthPowerUp::setPowerUpTextAttributes()
{
    powerUpText.setFont(getFont());
    powerUpText.setString("HEALTH");
    centerOrigin(powerUpText);
    powerUpText.setCharacterSize(50);
    powerUpText.setFillColor(sf::Color(255.f, 140.f, 180.f, 120.f));
}



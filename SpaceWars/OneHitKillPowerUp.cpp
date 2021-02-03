#include "OneHitKillPowerUp.h"
#include "Utility.h"

//constructor that takes a reference to the spaceShip, asteriod and power up texture.
OneHitKillPowerUp::OneHitKillPowerUp
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
//returns powerUpSprite for the oneHitKill pickup powerup.
sf::Sprite& OneHitKillPowerUp::getPowerUpSprite()
{
	
	return powerUpSprite;

}

void OneHitKillPowerUp::powerUpTakeEffect()
{
   
}
//puts the powerup on effect by changing the amount of hits it takes to destroy an asteroid.
void OneHitKillPowerUp::oneHitKillPowerUpTakeEffect(std::unique_ptr<Asteroids>& a)
{
    a->setIsDestroyed(1);
}

OneHitKillPowerUp::Type OneHitKillPowerUp::getType()
{
    return Type::OneHit;
}

void OneHitKillPowerUp::setPowerUpTextAttributes()
{
    powerUpText.setFont(getFont());
    powerUpText.setString("ONE HIT KILL");
    centerOrigin(powerUpText);
    powerUpText.setCharacterSize(50);
    powerUpText.setFillColor
    (sf::Color(150.f, 255.f, 150.f, 100.f));
}


#include "RadarPowerUp.h"
#include "Utility.h"

RadarPowerUp::RadarPowerUp
(std::unique_ptr<Saucer>& saucer,
sf::Texture powerUpTex)
{
	saucerObj = saucer.get();
	powerUpTexture = std::move(powerUpTex);
	powerUpSprite.setTexture(powerUpTexture);

	setPowerUpTextAttributes();
}

sf::Sprite& RadarPowerUp::getPowerUpSprite()
{
	return powerUpSprite;
}

void RadarPowerUp::powerUpTakeEffect()
{
	saucerObj->flipSaucerVisiblity();
}

RadarPowerUp::Type RadarPowerUp::getType()
{
	return Type::Radar;
}

void RadarPowerUp::setPowerUpTextAttributes()
{
	powerUpText.setFont(getFont());
	powerUpText.setString("RADAR");
	centerOrigin(powerUpText);
	powerUpText.setCharacterSize(50);
	powerUpText.setFillColor(sf::Color(30.f, 188.f, 30.f, 255.f));
}

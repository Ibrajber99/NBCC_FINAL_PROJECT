#include "PowerUps.h"

enum class Type;



//returns the sprite for the power up 
sf::Sprite &PowerUps::getPowerUpSprite()
{
    return powerUpSprite;
}

sf::Text& PowerUps::getPowerUpText()
{
    return powerUpText;
}

sf::Font& PowerUps::getFont()
{
    //loading the font
    if (!font.loadFromFile("Media/other/test.ttf")) {}
    return font;
}

//needs to be overriden by the derived class
void PowerUps::setpowerUpSpawnPos(sf::RenderWindow &w)
{
    //create random number
    std::random_device rd;
    std::mt19937 gen(rd());
    //specify range for x and y coordinates
    std::uniform_int_distribution<> distribX(0, w.getSize().x);
    std::uniform_int_distribution<> distribY(-200, 0);
    sf::Vector2f pos;
    //pick a random number between the range specified
    //assign it to the powerup coordinates and set the position of the powerup
    pos.x = static_cast<float>(distribX(gen));
    pos.y = static_cast<float>(distribY(gen));
    powerUpSprite.setPosition(pos);
}

//moves the power up to be on the specified position on the screen (override)
void PowerUps::movePowerUpOnScreen()
{
    powerUpSprite.move(0.0f,sf::seconds(1/60.f).asSeconds()* 170.9f);
}

void PowerUps::movePowerUpOutOfScreen()
{
    powerUpSprite.move(0.0f, 1000.f);
}

void PowerUps::movePowerUpText(float y)
{
    if (clock.getElapsedTime().asSeconds() > 0.2) {
        float dt = clock.getElapsedTime().asSeconds();
        powerUpText.move(0.f, 
            sf::seconds(1 / 60.f).asSeconds() *-600.f);
        clock.restart();
    }
}

void PowerUps::drawPowerUpText
(sf::RenderWindow& window)
{
    window.draw(powerUpText);
}

void PowerUps::flushText()
{
    if (powerUpText.getPosition().y < 150.f) {
        powerUpText.move(0.f, -1000.f);
    }
}

void PowerUps::initPowerUpTextPos()
{
    powerUpText.setPosition(950.f, 450.f);
}

void PowerUps::setPowerUpTextAttributes()
{
}

void PowerUps::powerUpTakeEffect()
{
    //Virtual Dervied method
}

PowerUps::Type PowerUps::getType()
{
    return PowerUps::Type::Base;
    
}

PowerUps::~PowerUps()
{
}


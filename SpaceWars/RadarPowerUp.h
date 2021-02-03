#pragma once
#include "PowerUps.h"
#include "Saucer.h"
class RadarPowerUp :
    public PowerUps
{

public:
    RadarPowerUp(std::unique_ptr<Saucer>& saucer, sf::Texture powerUpTex);

    virtual sf::Sprite&         getPowerUpSprite()override;
    virtual void				powerUpTakeEffect()override;
    virtual Type				getType() override;
    virtual void                setPowerUpTextAttributes() override;

private:
    Saucer*                     saucerObj;

};


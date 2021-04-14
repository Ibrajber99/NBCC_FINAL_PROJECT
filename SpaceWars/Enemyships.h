#pragma once
#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include "TextureAssests.h"
#include "Animation.h"

class Enemyships
{
public:
								Enemyships
								(sf::Texture& shipTex,
								sf::Texture& bulletTex,
								sf::Texture& destructionAnimation
								, sf::RenderWindow& w);

	void						update();
	void						draw();
	void						damage(int hit);
	bool						isDestroyed() const;
	sf::Sprite&					getShipSprite();
	void						setPosition(sf::Vector2f pos);
	bool						isOutofBounds();
	bool						isDestructionAnimationFinished();
	bool						isDestructionAnimationBegan();
	int							getHitPoints();
	std::vector<sf::Sprite>& getBulletsContainer();
	void						flushBullets();
private:
	void						pushBullets();
	void						updateMovmentPattern();
	void						beginShipDestruction();

private:
	sf::RenderWindow&			window;
	sf::Sprite				    spaceShipsprite;
	sf::Texture				    bulletTexture;
	std::vector<sf::Sprite>		bulletsMagazine;
	std::unique_ptr<Animation>  animation;
	size_t						hitpoints;
	bool						destroyed;
	float						bounds;
	sf::Time					movePerSec;
	float						shipSpeed;
	sf::Clock					shootingTimer;
	bool						destructionBegan;

};


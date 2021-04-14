#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Animation.h"
#include "TextureAssests.h"
#include <memory>
#include <vector>

class Saucer
{
public:
	Saucer(
		std::unique_ptr<TextureAssets>&textureHolder,
		sf::RenderWindow &window);

	void													update();
	void													moveSaucer();
	void													flushSaucer();
	void													drawSaucer();
	void													getHit();
	bool													isSaucerDestroyed();
	void													triggerBulletHitSaucer();
	void													beginSuckBulletAnimation();
	void													updateSaucerPosition();
	void													flipSaucerVisiblity();
	sf::Sprite&												getSaucerSprite();

private:
	void													setSaucerPosition(sf::Vector2f pos);
	void													generateNewSaucerSprite();
	void													assignNewSpriteToSaucer();
	void													setOriginalSaucerSprite();

private:
	sf::Sprite												saucerSprite;
	sf::Texture												saucerTex;
	bool													destroyed;
	size_t													health;
	sf::Clock												clock;

	std::unique_ptr<Animation>								suckBulletAnimation;

	bool													bulletHitSaucer;
	bool													saucerInvisible;

	sf::RenderWindow&										window;

};


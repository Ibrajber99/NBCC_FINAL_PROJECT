#include "Animation.h"


//constructor for animation takes animation texture, image count(Vector2u) and switchTime as float.
Animation::Animation(sf::Texture texture, sf::Vector2u imageCount, float switchTime)
    //Initialization list
    :imageCount(imageCount)
    ,switchTime(switchTime)
{

        currTexture = texture;

        totalTime = 0.0f;
        currentImage.x = 0;
        currentImage.y = 0;


        sf::Sprite tmp(currTexture, uvRect);
        spriteAnime = std::move(tmp);
        spriteAnime.setTextureRect(uvRect);

        //getting width and heigth of the spritesheet for slicing
        uvRect.width = currTexture.getSize().x / (float)(imageCount.x);
        uvRect.height = currTexture.getSize().y / (float)(imageCount.y);
}


//destructor
Animation::~Animation(){
    
}



void Animation::update(){
    if (clock.getElapsedTime().asSeconds() > 0.07f) {
        if (currentImage.x >= imageCount.x) {
            currentImage.x = 0;
            currentImage.y++;
        }
        uvRect.left = currentImage.x * uvRect.width;
        uvRect.top = currentImage.y * uvRect.height;
        currentImage.x++;
        if (currentImage.y >= imageCount.y) {
            animationDone = true;
        }
        spriteAnime.setTextureRect(uvRect);
        clock.restart();
    }
}


bool Animation::isAnimationFinished(){
    return animationDone;
}



sf::Texture& Animation::getCurrTexture(){
    return currTexture;
}


void Animation::setImageCount(sf::Vector2f coords)
{
    uvRect.width = currTexture.getSize().x / (float)(coords.x);
    uvRect.height = currTexture.getSize().y / (float)(coords.y);
}


void Animation::setTexture(sf::Texture texture)
{
    currTexture = std::move(texture);
    sf::Sprite tmp(currTexture, uvRect);
    spriteAnime = std::move(tmp);
    spriteAnime.setTextureRect(uvRect);
}



sf::IntRect Animation::getCurrentRectTexture(){
    return uvRect;
}


void Animation::reSetIterations(){
    currentImage.x = 0;
    currentImage.y = 0;
    animationDone = 0;
}


sf::Sprite& Animation::getCurrAnimation(sf::Vector2f &pos){
    spriteAnime.setTextureRect(uvRect);
    spriteAnime.setPosition(pos);
    return spriteAnime;
}

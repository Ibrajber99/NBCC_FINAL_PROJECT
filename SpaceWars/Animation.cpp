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


//updates animation
void Animation::update(){
    if (clock.getElapsedTime().asSeconds() > 0.07f) {
        if (currentImage.x >= imageCount.x) {
            //moves to next row.
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


//return animationDone flag
bool Animation::isAnimationFinished(){
    return animationDone;
}


//return currTexture
sf::Texture& Animation::getCurrTexture(){
    return currTexture;
}


void Animation::setImageCount(sf::Vector2f coords)
{
    uvRect.width = currTexture.getSize().x / (float)(coords.x);
    uvRect.height = currTexture.getSize().y / (float)(coords.y);
}


//return uvRect
sf::IntRect Animation::getCurrentRectTexture(){
    return uvRect;
}

//resets the animation so it can be replayed for different instance if necessary.
void Animation::reSetIterations(){
    currentImage.x = 0;
    currentImage.y = 0;
    animationDone = 0;
}

//returns spriteAnime which is the current animation being displayed.
sf::Sprite& Animation::getCurrAnimation(sf::Vector2f &pos){
    spriteAnime.setTextureRect(uvRect);
    spriteAnime.setPosition(pos);
    return spriteAnime;
}

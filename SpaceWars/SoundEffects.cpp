#include "SoundEffects.h"

//constructor for soundEffects object
SoundEffects::SoundEffects()
{
        //loads sounds effects and stores them in sound buffers.
        bulletShot.loadFromFile("Media/sound/BulletShotSound.wav");
        bulletHit.loadFromFile("Media/sound/eat.wav");
        bulletHitAsteroid.loadFromFile("Media/sound/bullet_Collision_Asteroid.wav");
        spaceExplosion.loadFromFile("Media/sound/spaceShipExplosion.wav");
        specialBulletCollision.loadFromFile("Media/sound/bulletCollision.wav");
        saucerSuck.loadFromFile("Media/sound/saucerSuckSoundEffect.wav");
        normalBulletCollision.loadFromFile("Media/sound/normalBulletCollisionSound.wav");

        //Loading the Music for the Game theme
        gameTheme.openFromFile("Media/sound/gameMusicTheme.ogg");

        //sets buffers for sound effects.
        bulletShotSound.setBuffer(bulletShot);
        bulletHitSound.setBuffer(bulletHit);
        bulletHitAsteroidSound.setBuffer(bulletHitAsteroid);
        spaceExplosionSound.setBuffer(spaceExplosion);
        specialBulletCollisionSound.setBuffer(specialBulletCollision);
        normalBulletCollisionSound.setBuffer(normalBulletCollision);
        suacerSuckSound.setBuffer(saucerSuck);
}

//play bulletShot sound
void SoundEffects::shootBullet() {
    
    bulletShotSound.play();
}

//play bulletHit sound
void SoundEffects::hitTarget() {
  
    bulletHitSound.play();
}

//play bulletHitAsteroid sound
void SoundEffects::hitTargetNoDestruction()
{
    
    bulletHitAsteroidSound.play();
}

//play spaceExplosion sound
void SoundEffects::spaceShipDestruction()
{
    
    spaceExplosionSound.play();
}

void SoundEffects::specialBulletClashSound()
{
    specialBulletCollisionSound.play();
}

void SoundEffects::normalBulletClashSound()
{
    normalBulletCollisionSound.setVolume(20.f);
    normalBulletCollisionSound.play();
}

void SoundEffects::saucerSuckSound()
{
    suacerSuckSound.play();
}

sf::Music& SoundEffects::getGameMusicTheme()
{
    return gameTheme;
}


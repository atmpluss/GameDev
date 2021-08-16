#include "Enemy.h"
#include "raymath.h"
#include <iostream>

 Enemy::Enemy(Vector2 pos, Texture2D idle_tex, Texture2D run_tex)
{

    worldPos = pos;
    texture = idle_tex;
    idle = idle_tex;
    run = run_tex;
    width = texture.width/maxFrame;
    height = texture.height;
    speed = 3.f;
}

void Enemy::tick(float dt){
    if(!getAlive()) return;
    
 
    velocity = Vector2Subtract((*target).getScreenPos(), getScreenPos());
    if(Vector2Length(velocity) < radius) velocity = {}; // if we remove this knight and goblin oveerlap, and we see flicking on the game
    //normalize it
    (Vector2Length(velocity)>0)?velocity = Vector2Normalize(velocity):velocity=Vector2{0.f,0.};
  
    BaseCharacter::tick(dt);
    if(CheckCollisionRecs((*target).getCollisionRec(), getCollisionRec()))
    {
        (*target).takeDamage(damagePerSecond*dt);
    }
}
void Enemy::tick_(float dt){
    if(!getAlive()) return;
    worldPosLastFrame = worldPos;

    runnigTime += dt;
    if (runnigTime >= updateTime)
    {
        frame++;
        runnigTime = 0;
        if (frame > maxFrame)
            frame = 0;
    }

    Rectangle knightSource{frame * width, 0.0f, leftRight * width, height};
    Rectangle knightDest{this->getScreenPos().x, this->getScreenPos().y, width * scale, height * scale};
    DrawTexturePro(texture, knightSource, knightDest, {-20.0f, -20.0f}, 0.0f, WHITE);
}

Vector2 Enemy::getScreenPos()
{
    return Vector2Subtract(worldPos,(*target).getWorldPos() );
}

void Enemy::undoMovementEnemy(){
    worldPos = Vector2Scale(worldPosLastFrame, 1.01f) ;
}




#include "BaseCharacter.h"
#include "raymath.h"


BaseCharacter::BaseCharacter(){

}

void BaseCharacter::undoMovement(){
    worldPos = worldPosLastFrame;
}

Rectangle BaseCharacter::getCollisionRec()
{
    return Rectangle{this->getScreenPos().x,this->getScreenPos().y, width * scale, height*scale};
}

void BaseCharacter:: tick(float dt){ 
    worldPosLastFrame = worldPos;

    runnigTime += dt;
    if (runnigTime >= updateTime)
    {
        frame++;
        runnigTime = 0;
        if (frame > maxFrame)
            frame = 0;
    }

    if (Vector2Length(velocity) != 0)
    {
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(velocity), speed));
        velocity.x < 0 ? leftRight = -1 : leftRight = 1;
        texture = run;
    }
    else
    {
        texture = idle;
    }
    velocity = {};

    Rectangle knightSource{frame * width, 0.0f, leftRight * width, height};
    Rectangle knightDest{getScreenPos().x, getScreenPos().y, width * scale, height * scale};
    DrawTexturePro(texture, knightSource, knightDest, {0.0f, 0.0f}, 0.0f, WHITE);
}

#include "Character.h"
#include "raymath.h"
Character::Character(int winwidth_, int winHeight_,Texture2D idle_tex, Texture2D run_tex):windowWidth(winwidth_), windowHeight(winHeight_)
{
    
    texture = idle_tex;
    idle = idle_tex;
    run = run_tex;
    width = texture.width/maxFrame;
    height = texture.height;
    
  
  
}
 Vector2 Character::getScreenPos() {
     return Vector2{
        // it is called staic cast, it is from cpp and it prevents us to cast unmatched type variables to each other
        static_cast<float> (windowWidth) / 2.0f - width/ 6.0f * scale, // we multyply it by 4 becasue we wanna scale to 4. the actual size is very small
        static_cast<float> (windowHeight) / 2.0f - height * scale
        };
 }

void Character::tick(float dt)
{

    
    if(!getAlive()) return;
    
    if (IsKeyDown(KEY_A))
        velocity.x -= 1;
    if (IsKeyDown(KEY_D))
        velocity.x += 1;
    if (IsKeyDown(KEY_W))
        velocity.y -= 1;
    if (IsKeyDown(KEY_S))
        velocity.y += 1;
    
    BaseCharacter::tick(dt);
    Vector2 origin{};
    Vector2 offset{};
    float rotation{};
    if(leftRight >= 0)
    {
        origin = {0.f, (float)sword.height * scale};
        offset = {35.f, 55.f};
        swordRecCollision = {getScreenPos().x + offset.x, getScreenPos().y + offset.y - sword.height * scale, (float)sword.width * scale, (float)sword.height * scale};
        rotation = 35.f;
        IsMouseButtonDown(MOUSE_LEFT_BUTTON)?rotation = 35.f:rotation = 0.f;
    }
    else
    {
        origin = {(float)sword.width*scale, (float)sword.height * scale};
        offset = {25.f, 55.f};
        swordRecCollision = {getScreenPos().x + offset.x - sword.width*scale, getScreenPos().y + offset.y - sword.height * scale, (float)sword.width * scale, (float)sword.height * scale};
        IsMouseButtonDown(MOUSE_LEFT_BUTTON)?rotation = -35.f:rotation = 0.f;

    }


    Rectangle swordSource{0.f, 0.f, leftRight * (float)sword.width, (float)sword.height};
    Rectangle swordDest{getScreenPos().x + offset.x, getScreenPos().y + offset.y, (float)sword.width * scale, (float)sword.height * scale};
    DrawTexturePro(sword, swordSource, swordDest, origin, rotation, WHITE);
    // a
                     

    
}

void Character::takeDamage(float damage){
    health -= damage;
    if(health < 0){
        setAlive(false);
    }
}


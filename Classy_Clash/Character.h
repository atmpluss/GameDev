#ifndef character_h
#define character_h
#include "raylib.h"
#include "BaseCharacter.h"
class Character : public BaseCharacter
{
public:
    Character(int winwidth_, int winHeight_,Texture2D idle_tex, Texture2D run_tex);
    // Vector2 getScreenPos(){return screenPos;}
    virtual void tick(float dt) override;
    virtual Vector2 getScreenPos() override;
    Rectangle getSwordRecCollision(){return swordRecCollision; }
    // get health
    float getHealth() const {return health;}
    // take damage
    void takeDamage(float damage);
private:
 int windowWidth{};
 int windowHeight{};
 Texture2D sword{LoadTexture("characters/weapon_sword.png")};
 Rectangle swordRecCollision{getScreenPos().x , getScreenPos().y , (float)sword.width * scale, (float)sword.height * scale};
 float health{100.f};
  

};
#endif
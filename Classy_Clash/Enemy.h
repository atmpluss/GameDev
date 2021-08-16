// #ifndef enemy_h
// #define enemy_h
#include "Character.h" 
#include "raylib.h"
#include "BaseCharacter.h"



class Enemy: public BaseCharacter
{
public:
    Enemy(Vector2 pos, Texture2D idle_tex, Texture2D run_tex);
    void tick_(float dt);
    void setTarget(Character* character){target = character;}
    virtual void tick(float dt) override;
    virtual Vector2 getScreenPos() override;
    void undoMovementEnemy();

    
   
private:
Character* target = nullptr ;
float damagePerSecond = 10.f;
float radius = 25.f;

 

// #endif


     
};


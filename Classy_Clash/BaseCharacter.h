#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H
#include "raylib.h"

class BaseCharacter{

public:
    BaseCharacter();
    Vector2 getWorldPos() { return worldPos; }
    void undoMovement();
    Rectangle getCollisionRec();
    virtual void tick(float dt);
    virtual Vector2 getScreenPos() = 0;
    bool getAlive(){return alive;}
    void setAlive(bool isAlive){alive = isAlive;}

protected:
    Texture2D texture{};
    Texture2D idle{};
    Texture2D run{};
    // Vector2 screenPos{0.f,0.f};
    Vector2 worldPos{0.f,0.f};
    Vector2 worldPosLastFrame{0.f,0.f};
    float leftRight = 1;
    int frame{};
    float runnigTime = 0;
    int maxFrame{6};
    float updateTime{1.f / 12.f};
    float speed{4.f};
    float width{};
    float height{};
    float scale{4.f};
    Vector2 velocity{0.f,0.f};
private:
    bool alive{true};

};

#endif
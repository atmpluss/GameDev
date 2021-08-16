#include"Prop.h"
#include "raymath.h"

Prop::Prop(Vector2 pos,Texture2D tex):
    worldPos(pos),texture(tex) 
{

}

void Prop::Render(Vector2 knightPos)
{
    //rockworld pos - knight world pos gives the rock screen pos
    screenPos = Vector2Subtract(worldPos, knightPos);
    DrawTextureEx(texture,screenPos,0,scale,WHITE);
}

Rectangle Prop::getCollisionRec(Vector2 knightPos)
{
    screenPos = Vector2Subtract(worldPos, knightPos);
    return Rectangle{screenPos.x, screenPos.y, texture.width * scale,texture.height * scale }; // it is struct it has be initilaized with curly braces
}

#include "raylib.h"
#include "raymath.h"
#include <iostream>
#include <string>
#include "Character.h"
#include "Prop.h"
#include "Enemy.h"
#include "BaseCharacter.h"

int main()
{
    const int Windowwidth{384};
    const int Windowheight{384};
    InitWindow(Windowwidth, Windowheight, "Classy Clash!");

    //nebula variables
    // /Users/mohammadsanayei/Desktop/GameDev/dapper-dasher/textures/12_nebula_spritesheet.png
    Texture2D background = LoadTexture("nature_tileset/mymap.png");
    Vector2 bacPos{0.0, 0.0};
    const float mapScale{4.f};

    Character knight{Windowwidth, Windowheight, LoadTexture("characters/knight_idle_spritesheet.png"), LoadTexture("characters/knight_run_spritesheet.png")};
    Enemy goblin(Vector2{500.f, 700.f}, LoadTexture("characters/goblin_idle_spritesheet.png"), LoadTexture("characters/goblin_run_spritesheet.png"));
    Enemy slime(Vector2{800.f, 300.f}, LoadTexture("characters/slime_idle_spritesheet.png"), LoadTexture("characters/slime_run_spritesheet.png") );    
    Enemy *enemies[2];
    enemies[0] = &goblin;
    enemies[1] = &slime;

    // Prop rock{Vector2{1.f,1.f}, LoadTexture("nature_tileset/Rock.png")};
    Prop props[2]{Prop{Vector2{600.f, 600.f}, LoadTexture("nature_tileset/Rock.png")},
                  Prop{Vector2{400.f, 500.f}, LoadTexture("nature_tileset/Log.png")}};

    SetTargetFPS(60); // frame per second
    while (!WindowShouldClose())
    {

        BeginDrawing();         //setup our canvas
        ClearBackground(WHITE); //clear background to avoid flickering

        const float dt = GetFrameTime();
        // bacPos = Vector2Scale(knight.getWorldPos(), -1.f);
        DrawTextureEx(background, Vector2Scale(knight.getWorldPos(), -1.f), 0.0, mapScale, WHITE);
        // slime.setTarget(&knight);

        for(auto enemy: enemies){
            enemy->setTarget(&knight);
        }

        

        knight.tick(dt);

        // goblin.target = &knight;

        //check amp bounds:
        if (knight.getWorldPos().x < 0.f ||
            knight.getWorldPos().y < 0.f ||
            knight.getWorldPos().x + Windowwidth > background.width * mapScale ||
            knight.getWorldPos().y + Windowheight > background.height * mapScale)
        {
            // if we hot the bound we have to restore the position to the previous world pos
            knight.undoMovement();
        }
        //displaying Damage:
        if (!knight.getAlive())
        {
            DrawText("GAME OVER!", 40, 40, 40, RED);
            EndDrawing();
            continue;
        }
        else
        {
            std::string message = "health: ";
            message.append(std::to_string(knight.getHealth()), 0, 3);
            DrawText(message.c_str(), 40, 40, 40, RED);
        }

        //check props collision

        for (auto pr : props)
        {
            if (CheckCollisionRecs(pr.getCollisionRec(knight.getWorldPos()), knight.getCollisionRec()))
            {
                knight.undoMovement();
            }
        }

        // drawing props
        for (auto pr : props)
        {
            pr.Render(knight.getWorldPos());
        }


        for (auto enemy : enemies)
        {
            enemy->tick(dt);
        }

        for(int i = 1; i>0;i--){
            if (CheckCollisionRecs(enemies[i]->getCollisionRec(), enemies[i-1]->getCollisionRec()))
            {
                enemies[i]->undoMovement();
            }
        }
        

      
        // checking the collision betweeen sword and Goblin:
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            for (auto enemy : enemies)
            {
                if (CheckCollisionRecs(knight.getSwordRecCollision(), enemy->getCollisionRec()))
                {
                    enemy->setAlive(false);
                }
            }
        }

        EndDrawing();
    }

    UnloadTexture(background);

    CloseAudioDevice();
    CloseWindow();
}
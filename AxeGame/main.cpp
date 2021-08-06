// #include <cstdio>
// #include <iostream>
#include "raylib.h"
int main()
{
    //width height title
    int height{450};
    int width{850};
    InitWindow(width,height,"Matakichi"); 
    int crircle_x{175};
    int crircle_y{100};
    int circule_radius{25}; 
    int l_cricule_x = crircle_x - circule_radius;
    int r_cricule_x = crircle_x + circule_radius;
    int u_cricule_y = crircle_y - circule_radius;
    int b_cricule_y = crircle_y + circule_radius;

    int axe_x{400};
    int axe_y{0};
    int axe_length{50};
    //axe edges
    int l_axe_x = axe_x; 
    int r_axe_x = axe_x + axe_length; 
    int u_axe_y = axe_y;
    int b_axe_y = axe_y + axe_length;  

    int direction{10};
    

    bool collision_with_axe = (l_cricule_x <= r_axe_x) && (l_axe_x <= r_cricule_x) && (u_cricule_y <= b_axe_y) && (b_cricule_y >= u_axe_y);
    SetTargetFPS(30); // frame per second
    while(WindowShouldClose() == false){

        BeginDrawing();//setup our canvas
        ClearBackground(WHITE);//clear background to avoid flickering
        
        
        if(collision_with_axe == true){
            DrawText("Game Over!", 400,200,20,RED);
        }
        else{
           
        DrawCircle(crircle_x,crircle_y,circule_radius,BLUE);
        //posX posY width height color (posX and posY are for upper left cornor)
        DrawRectangle(axe_x,axe_y, axe_length,axe_length,RED);
        axe_y += direction;

        if(axe_y > height || axe_y < 0){
            direction *= -1;
        }
        if(IsKeyDown(KEY_D) && crircle_x<width){
            crircle_x += 10;
            

        }
        if(IsKeyDown(KEY_A)&& crircle_x>0){
            crircle_x -= 10;

        }
        
        }


        l_cricule_x = crircle_x - circule_radius;
        r_cricule_x = crircle_x + circule_radius;
        u_cricule_y = crircle_y - circule_radius;
        b_cricule_y = crircle_y + circule_radius;

        l_axe_x = axe_x; 
        r_axe_x = axe_x + axe_length; 
        u_axe_y = axe_y;
        b_axe_y = axe_y + axe_length; 

        collision_with_axe = (l_cricule_x <= r_axe_x) && (l_axe_x <= r_cricule_x) && (u_cricule_y <= b_axe_y) && (b_cricule_y >= u_axe_y);

        EndDrawing();

        
           
    }
    

}
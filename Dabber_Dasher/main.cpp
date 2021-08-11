//velocity in raylib has the unit of pixels/frames so if the speed is 10 (p/f) and we set 
//60(f/s)-> 600(f/s) 

// we have to add the effect of gravity, because the subject after jump needs to comeback on the ground
// we modifzy the velocity after pressing the space, but we have to prevent double jump,
// that is why we check if the subject is on the ground we apply the change otherweise
// there will be no change
// sprite 2d image get drawn on the screen of the game
// sprite sheets, multiple images
//each pixel of the sprite has the vlue of: red, green, blue, alpha(how transparent)DrawTextureRec, allows 
//us to draw part of the sprite sheet: DrawTextureRec(tecture, source, position, tint)
// texture: sprite sheet image, source: is a section in the sprite sheet it is rectangle
//position: location on the window vector2D tint: is the color, no modification -> white

#include "raylib.h"
#include <iostream>

struct AnimData{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};

void updateAnimData(AnimData &data, float dt, int maxFrame){
    data.runningTime +=dt;
            // it animates scarfy sprite sheet
    if(data.runningTime >= data.updateTime){
        data.runningTime = 0.;
        // we update scarfyRect then using DrawTextureRec different form of scarfy gets animated
        data.rec.x = data.frame * data.rec.width;
        data.frame++;
        if(data.frame > maxFrame) data.frame = 0;
    }
}

int main()
{
    const int Windowwidth{512};
    const int Windowheight{380};
    InitWindow(Windowwidth,Windowheight,"Dapper_Dasher");

    //nebula variables
    // /Users/mohammadsanayei/Desktop/GameDev/dapper-dasher/textures/12_nebula_spritesheet.png
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    // AnimData nebData{
    //     {0,0,(float)nebula.width/8,(float)nebula.height/8 }, // Rectangle rec
    //     {Windowwidth,Windowheight - nebData.rec.height}, // vector2 pos
    //     (int)0, // frame
    //     (float)1./12., //updateframe
    //     (float)0 //runningtime
    // };


    const int nebSize = 10;
    AnimData nebArray[nebSize]{};
    for(int i=0;i<nebSize;i++){
        nebArray[i].rec.x =0.0;
        nebArray[i].rec.y =0.0;
        nebArray[i].rec.width =(float)nebula.width/8;
        nebArray[i].rec.height =(float)nebula.height/8;
        nebArray[i].pos.x = Windowwidth + ((i+1)*300);
        nebArray[i].pos.y = Windowheight - nebArray[i].rec.height;
        nebArray[i].frame = 0;
        nebArray[i].updateTime = 0;
        nebArray[i].runningTime = 0;
    }
    
    int nebVel{-200}; //pixels per second
    float finishLine = nebArray[nebSize - 1].pos.x;
  
    
    
    //scarfy variables
    //width height title
    Texture2D scarfy = LoadTexture("textures/scarfy.png"); // when we load a texture we need to unload it at the end
    AnimData scarfyData;
    scarfyData.rec.width = scarfy.width/6;
    scarfyData.rec.height = scarfy.height;
    scarfyData.rec.x = 0;
    scarfyData.rec.y = 0;
    scarfyData.pos.x = Windowwidth/2  - scarfyData.rec.width/2;
    scarfyData.pos.y = Windowheight  - scarfyData.rec.height;
    scarfyData.frame = 0;
    scarfyData.updateTime = 1./12.;
    scarfyData.runningTime = 0;
    
    // Rectangle scarfyRec;
    // scarfyRec.width = scarfy.width/6;
    // scarfyRec.height = scarfy.height;
    // scarfyRec.x = 0; // it determines which sprit from the sheet is going to be shown
    // scarfyRec.y = 0;
    // int frame{}; // to update scarfy sheet in the while loop
    // //update scarfy 1 in every 12 of second
    // const float updateTime = 1./12.;
    // float runingTime{};
    // Vector2 scarfyPos;
    // scarfyPos.x =  Windowwidth/2  - scarfyRec.width/2; 
    // scarfyPos.y =  Windowheight  - scarfyRec.height; 



     

    //rec dim
    // const int width{50};
    // const int height{80};
    
    // int posY = Windowheight - height;
    int velocity{0};

    int graivity{1'000}; // pix/sec/sec
    bool isInAir = false;
    const int jumbVel = -600; // pix/sec;


    Texture2D background = LoadTexture("textures/far-buildings.png");
    float bgX = 0.0;

    Texture2D midground = LoadTexture("textures/back-buildings.png");
    float mgX = 0.0;

    Texture2D foreground = LoadTexture("textures/foreground.png");
    float fgX = 0.0;

    bool collision = false; 

    //voices
    InitAudioDevice();
    Sound jumpSound = LoadSound("sounds/jump.wav");
    Sound backSound = LoadSound("sounds/chase.mp3");
    Sound vicSound = LoadSound("sounds/Pandemia.mp3");
    PlaySound(backSound);

    SetTargetFPS(60); // frame per second
    while(!WindowShouldClose()){

        BeginDrawing();//setup our canvas
        ClearBackground(WHITE);//clear background to avoid flickering
        const float dt = GetFrameTime();

        // drawing background
        Vector2 bg1Pos{bgX,0.0};
        Vector2 bg2Pos{bgX + background.width*2,0.0}; // *2 because we are drawing in 2 scale
        DrawTextureEx(background,bg1Pos,0.0,2,WHITE );
        DrawTextureEx(background,bg2Pos,0.0,2,WHITE );
        bgX -= 20 * dt;
        if(bgX <= -background.width*2 ){
            bgX = 0.0;
        }
        //scroll midground

        Vector2 mg1Pos{mgX,0.0};
        Vector2 mg2Pos{mgX + midground.width*2,0.0}; // *2 because we are drawing in 2 scale
        DrawTextureEx(midground,mg1Pos,0.0,2,WHITE );
        DrawTextureEx(midground,mg2Pos,0.0,2,WHITE );
        mgX -= 40 * dt;
        if(mgX <= -midground.width*2 ){
            mgX = 0.0;
        }
        //scroll foreground
        Vector2 fg1Pos{fgX,0.0};
        Vector2 fg2Pos{fgX + foreground.width*2,0.0}; // *2 because we are drawing in 2 scale
        DrawTextureEx(foreground,fg1Pos,0.0,2,WHITE );
        DrawTextureEx(foreground,fg2Pos,0.0,2,WHITE );
        fgX -= 80 * dt;
        if(fgX <= -foreground.width*2 ){
            fgX = 0.0;
        }

    

        


        for(int i =0; i<nebSize ; i++){
  
            updateAnimData(nebArray[i], dt, 7);
        }
        
      
        
        
        
        if(!isInAir){ // we want to freeze scarfy when it is on the air
           updateAnimData(scarfyData, dt, 5);
        }
       
 
        if (scarfyData.pos.y < Windowheight - scarfyData.rec.height)
        {
            //on the air, it only modifies the velocity because of the influence of gravity
           velocity += graivity * dt ;
           isInAir = true;
        }
        else{
            velocity = 0;
            isInAir = false;
        }

        if(IsKeyPressed(KEY_SPACE) && (!isInAir)){
            // this changes the velocity because we have pressd space buttom
            //scarfy is on the ground
            PlaySound(jumpSound);
            velocity +=jumbVel ;
        }
        
        
        // update nebula position
        for(int i =0 ; i<nebSize; i++){
             nebArray[i].pos.x += nebVel * dt;
            // if(nebArray[i].pos.x  <= 0){
            //     nebArray[i].pos.x  = Windowwidth;
            // }
        }
        finishLine += nebVel * dt; 
       
        
        //update scarfy postion

        scarfyData.pos.y += velocity * dt;
        //collision detection
        
        for(AnimData nebula_ : nebArray)
        {
            float pad = 50; // because rec has some white area around nebula and if scarfy hit this white area, collision willl be detected which is false
            Rectangle nebRec = {
            nebula_.pos.x + pad, // shifted to the right by 20
            nebula_.pos.y + pad, // shifted down by 20
            nebula_.rec.width - 2 * pad,
            nebula_.rec.height -2 * pad
            };
            Rectangle scarfyRec = {
                scarfyData.pos.x,
                scarfyData.pos.y,
                scarfyData.rec.width,
                scarfyData.rec.height
            };
            if(CheckCollisionRecs(nebRec, scarfyRec))
            {
                collision = true;
            }
        }

        if(collision)
        {
            DrawText("Game Over!", Windowwidth/4, Windowheight/2,30,RED);
        }
        else if(scarfyData.pos.x >= finishLine)
        {
            PlaySound(backSound);
            DrawText("You Win!", Windowwidth/4, Windowheight/2,30,RED);
        }
        else{
            // //Draw textureRec for nebula
        // DrawTextureRec(nebula, nebArray[0].rec, nebArray[0].pos, WHITE);
        for(int i = 0 ; i<nebSize; i++){
            //Draw textureRec for nebula
            DrawTextureRec(nebula, nebArray[i].rec, nebArray[i].pos, WHITE);
            
        }
        
        // DrawRectangle(Windowwidth/2, scarfyPos.y,scarfyRec.width , scarfyRec.height, BLUE);
        DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);
        }
        
        
        
        EndDrawing();

        
           
    }
    UnloadSound(backSound);
    UnloadSound(vicSound);
    UnloadSound(jumpSound);

    UnloadTexture(nebula);
    UnloadTexture(scarfy);
    UnloadTexture(background);
    UnloadTexture(midground);
    UnloadTexture(foreground);

    CloseAudioDevice();
    CloseWindow();

}

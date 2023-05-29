#include "raylib.h"
#include "movement.h"

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "not really a gaem");

    //load textures & ball
    Texture2D player = LoadTexture("resources/player.png");
    Texture2D blueNet = LoadTexture("resources/blue_net.png");
    Texture2D redNet = LoadTexture("resources/red_net.png");
    Rectangle ball = {screenWidth/2 + 50, screenHeight/2, 16 , 16};

    //set starting positions
    Vector2 playerPosition = {screenWidth/2, screenHeight/2};
    Vector2 redNetPosition = {0, screenHeight/2 - redNet.height/2};
    Vector2 blueNetPosition = {screenWidth - blueNet.width, screenHeight/2 - blueNet.height/2};

    int movementSpeed = 2;
    bool sprint = false;
    int sprintBonus = 1;
    int score1 = 0;
    int score2 = 0;

    SetTargetFPS(60);

    // Main game loop
    while (!WindowShouldClose())  
    {
        //Set Hitboxes
        Rectangle playerArea = {playerPosition.x + player.width/2 - 5, playerPosition.y + player.height/2 - 6, player.width, player.height};
        Rectangle blueNetArea = {blueNetPosition.x + blueNet.width/2, blueNetPosition.y, blueNet.width/2, blueNet.height};
        Rectangle redNetArea = {redNetPosition.x, redNetPosition.y, redNet.width/2, redNet.height};

        checkMovement(sprint, sprintBonus, playerPosition, playerArea, movementSpeed, ball);

        //Dev Tools
        if(IsKeyDown(KEY_G)){
            DrawText(TextFormat("Mouse Position:%f%s%f",GetMousePosition().x, ", ", GetMousePosition().y), 0, 0, 30, RED);  
        }
    
        BeginDrawing();

            ClearBackground(RAYWHITE);

            //Draw Ball and Nets
            DrawTextureEx(blueNet, blueNetPosition, 0, 1, WHITE);
            DrawTextureEx(redNet, redNetPosition, 0, 1, WHITE);
            DrawRectangleRec(ball, GRAY);

            //Draw Score
            DrawText(TextFormat("Team 1 - %i", score1), 0, screenHeight - 40, 20, RED);
            DrawText(TextFormat("Team 2 - %i", score2), 0, screenHeight - 20, 20, RED);

            //Draw Player
            DrawTextureEx(player, playerPosition, 0, 1.7, WHITE);

            //Check Collisions with ball
            if(CheckCollisionRecs(playerArea, ball)){
                DrawText("Press X to shoot!", 0, 0, 30, RED);
                DrawLine(playerPosition.x + player.width/2, playerPosition.y + player.height/2, GetMousePosition().x, GetMousePosition().y, GRAY);
            }

            if(CheckCollisionRecs(ball, redNetArea)){
                score2++;                
                ball.x = screenWidth/2 + ball.width/2;
                ball.y = screenHeight/2 + ball.height/2;
                playerPosition.x = blueNetArea.width*2;
                playerPosition.y = screenHeight/2;
            } else if(CheckCollisionRecs(ball, blueNetArea)){
                score1++;
                ball.x = screenWidth/2 + ball.width/2;
                ball.y = screenHeight/2 + ball.height/2;
                playerPosition.x = blueNetArea.width*2;
                playerPosition.y = screenHeight/2;
            }

        EndDrawing();
    }

    //Unload stuff
    score1 = 0;
    score2 = 0;

    UnloadTexture(player);
    UnloadTexture(redNet);
    UnloadTexture(blueNet);

    CloseWindow();                

    return 0;
}
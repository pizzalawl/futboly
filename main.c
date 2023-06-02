#include "raylib.h"

struct Player {
    Texture2D texture;
    Vector2 position;
    Vector2 * positionPointer;
    int rotation;
    int scale;
    Rectangle area;
    int movementSpeed;
    bool sprint;
    bool * sprintptr;
    int keySet[5];
};

void checkWallCollision(Vector2 *playerPosition, int screenWidth, int screenHeight){

    while(playerPosition->y > screenHeight){
        playerPosition->y--;
    }

    while(playerPosition->y < 0){
        playerPosition->y++;
    }

    while(playerPosition->x > screenWidth){
        playerPosition->x--;
    }

    while(playerPosition->x < 0){
        playerPosition->x++;
    }
}

void checkMovement(bool * sprint, int sprintBonus, Vector2 * playerPosition, Rectangle playerArea, int movementSpeed, int keySet[5]){
        if(IsKeyPressed(keySet[0])) {
            *sprint = true;
        }

        if(IsKeyReleased(keySet[0])){
            *sprint = false;
        }

        if (IsKeyDown(keySet[1])) {
            playerPosition->x += movementSpeed;
            if(*sprint){
                playerPosition->x += sprintBonus;
            }
        }

        if (IsKeyDown(keySet[2])) {
            playerPosition->x -= movementSpeed;
            if(*sprint){
                playerPosition->x -= sprintBonus;
            }
        }

        if (IsKeyDown(keySet[3])) {
            playerPosition->y -= movementSpeed;
            if(*sprint){
                playerPosition->y -= sprintBonus;
            }
        }

        if (IsKeyDown(keySet[4])) {
            playerPosition->y += movementSpeed;
            if(*sprint){
                playerPosition->y += sprintBonus;
            }
        }
}

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "futboly");

    struct Player P1;
    P1.texture = LoadTexture("resources/player1.png");
    P1.position = (Vector2){screenWidth/2, screenHeight/2};
    P1.rotation = 0;
    P1.scale = 1.7;
    P1.area = (Rectangle){P1.position.x + P1.texture.width/2 - 5, P1.position.y + P1.texture.height/2 - 6, P1.texture.width, P1.texture.height};
    P1.positionPointer = &P1.position;
    P1.movementSpeed = 2;
    P1.sprint = false;
    P1.sprintptr = &P1.sprint;
    P1.keySet[0] = KEY_LEFT_SHIFT;
    P1.keySet[1] = KEY_D;
    P1.keySet[2] = KEY_A;
    P1.keySet[3] = KEY_W;
    P1.keySet[4] = KEY_S;

    struct Player P2;
    P2.texture = LoadTexture("resources/player2.png");
    P2.position = (Vector2){screenWidth/2 + 50, screenHeight/2};
    P2.rotation = 0;
    P2.scale = 1.7;
    P2.area = (Rectangle){P2.position.x + P2.texture.width/2 - 5, P2.position.y + P2.texture.height/2 - 6, P2.texture.width, P2.texture.height};
    P2.positionPointer = &P2.position;
    P2.movementSpeed = 2;
    P2.sprint = false;
    P2.sprintptr = &P2.sprint;
    P2.keySet[0] = KEY_RIGHT_SHIFT;
    P2.keySet[1] = KEY_RIGHT;
    P2.keySet[2] = KEY_LEFT;
    P2.keySet[3] = KEY_UP;
    P2.keySet[4] = KEY_DOWN;


    //load nets & balls
    Texture2D blueNet = LoadTexture("resources/blue_net.png");
    Texture2D redNet = LoadTexture("resources/red_net.png");
    Rectangle ball = {screenWidth/2 + 50, screenHeight/2, 16 , 16};

    //Set net positions
    Vector2 redNetPosition = {0, screenHeight/2 - redNet.height/2};
    Vector2 blueNetPosition = {screenWidth - blueNet.width, screenHeight/2 - blueNet.height/2};

    //Set net hitboxes
    Rectangle blueNetArea = {blueNetPosition.x + blueNet.width/2, blueNetPosition.y, blueNet.width/2, blueNet.height};
    Rectangle redNetArea = {redNetPosition.x, redNetPosition.y, redNet.width/2, redNet.height};

    int sprintBonus = 1;
    int score1 = 0;
    int score2 = 0;

    SetTargetFPS(60);

    // Main game loop
    while (!WindowShouldClose())  
    {
        checkMovement(P1.sprintptr, sprintBonus, P1.positionPointer, P1.area, P1.movementSpeed, P1.keySet);
        checkMovement(P2.sprintptr, sprintBonus, P2.positionPointer, P2.area, P2.movementSpeed, P2.keySet);

        //Dev Tools
        if(IsKeyDown(KEY_G)){
            DrawText(TextFormat("Mouse Position:%f%s%f",GetMousePosition().x, ", ", GetMousePosition().y), 0, 0, 30, RED);  
        }
        if(IsKeyDown(KEY_X)){
            ball.x = GetMousePosition().x;
            ball.y = GetMousePosition().y;
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

            //Draw Players
            DrawTextureEx(P1.texture, P1.position, 0, 1.7, WHITE);
            DrawTextureEx(P2.texture, P2.position, 0, 1.7, WHITE);

            //Check collision with the walls
            checkWallCollision(P1.positionPointer, screenWidth, screenHeight);
            checkWallCollision(P2.positionPointer, screenWidth, screenHeight);

            //Check ball collision with the net
            if(CheckCollisionRecs(ball, redNetArea)){
                score2++;                
                ball.x = screenWidth/2 + ball.width/2;
                ball.y = screenHeight/2 + ball.height/2;
                P1.position.x = blueNetArea.width*2;
                P1.position.y = screenHeight/2;
            } else if(CheckCollisionRecs(ball, blueNetArea)){
                score1++;
                ball.x = screenWidth/2 + ball.width/2;
                ball.y = screenHeight/2 + ball.height/2;
                P1.position.x = blueNetArea.width*2;
                P1.position.y = screenHeight/2;
            }
            if(CheckCollisionRecs(ball, redNetArea)){
                score2++;                
                ball.x = screenWidth/2 + ball.width/2;
                ball.y = screenHeight/2 + ball.height/2;
                P2.position.x = blueNetArea.width*2;
                P2.position.y = screenHeight/2;
            } else if(CheckCollisionRecs(ball, blueNetArea)){
                score1++;
                ball.x = screenWidth/2 + ball.width/2;
                ball.y = screenHeight/2 + ball.height/2;
                P2.position.x = blueNetArea.width*2;
                P2.position.y = screenHeight/2;
            }

        EndDrawing();
    }

    //Unload stuff
    score1 = 0;
    score2 = 0;

    UnloadTexture(P1.texture);
    UnloadTexture(redNet);
    UnloadTexture(blueNet);

    CloseWindow();                

    return 0;
}
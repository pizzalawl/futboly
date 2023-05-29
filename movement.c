#include "raylib.h"

void checkMovement(bool sprint, int sprintBonus, Vector2 playerPosition, Rectangle playerArea, int movementSpeed, Rectangle ball){
            // Controls
        if(IsKeyPressed(KEY_LEFT_SHIFT) || IsKeyPressed(KEY_RIGHT_SHIFT)) {
            sprint = true;
        }

        if(IsKeyReleased(KEY_LEFT_SHIFT) || IsKeyReleased(KEY_RIGHT_SHIFT)){
            sprint = false;
        }

        if (IsKeyDown(KEY_D)) {
            playerPosition.x += movementSpeed;
            if(sprint){
                playerPosition.x += sprintBonus;

                if(CheckCollisionRecs(playerArea, ball) && !IsKeyDown(KEY_F)){
                    ball.x += sprintBonus;
                }
            }

            if(CheckCollisionRecs(playerArea, ball) && !IsKeyDown(KEY_F)){
                ball.x += movementSpeed;
            }
        }

        if (IsKeyDown(KEY_A)) {
            playerPosition.x -= movementSpeed;
            if(sprint){
                playerPosition.x -= sprintBonus;

                if(CheckCollisionRecs(playerArea, ball) && !IsKeyDown(KEY_F)){
                    ball.x -= sprintBonus;
                }
            }
            
            if(CheckCollisionRecs(playerArea, ball) && !IsKeyDown(KEY_F)){
                ball.x -= movementSpeed;
            }
        }

        if (IsKeyDown(KEY_W)) {
            playerPosition.y -= movementSpeed;
            if(sprint){
                playerPosition.y -= sprintBonus;

                if(CheckCollisionRecs(playerArea, ball) && !IsKeyDown(KEY_F)){
                    ball.y -= sprintBonus;
                }
            }

            if(CheckCollisionRecs(playerArea, ball) && !IsKeyDown(KEY_F)){
                ball.y -= movementSpeed;
            }
        }

        if (IsKeyDown(KEY_S)) {
            playerPosition.y += movementSpeed;
            if(sprint){
                playerPosition.y += sprintBonus;

                if(CheckCollisionRecs(playerArea, ball) && !IsKeyDown(KEY_F)){
                    ball.y += sprintBonus;
                }
            }

            if(CheckCollisionRecs(playerArea, ball) && !IsKeyDown(KEY_F)){
                ball.y += movementSpeed;
            }
        }

        if(IsKeyDown(KEY_X)){
            if(CheckCollisionRecs(playerArea, ball)){

                ball.x = GetMousePosition().x;
                ball.y = GetMousePosition().y;
            }
        }
}
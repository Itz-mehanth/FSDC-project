#include <stdlib.h>
#include <stdio.h>
#include <raylib.h>
#include "raylib_functions.h"
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600


void ShowErrorMessage(const char* errorMessage)
{
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw error message box
        int boxWidth = 400;
        int boxHeight = 200;
        int boxX = (SCREEN_WIDTH - boxWidth) / 2;
        int boxY = (SCREEN_HEIGHT - boxHeight) / 2;

        DrawRectangle(boxX, boxY, boxWidth, boxHeight, LIGHTGRAY);
        DrawRectangleLines(boxX, boxY, boxWidth, boxHeight, DARKGRAY);

        // Draw error message text
        DrawText(errorMessage, boxX + 20, boxY + 40, 20, RED);
        DrawText("Press any key to close this message...", boxX + 20, boxY + 140, 20, DARKGRAY);

        EndDrawing();

        // Check for any key press
        if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_ESCAPE) || GetKeyPressed() != 0)
        {
            break;  // Exit the loop and close the window
        }
    }
}

int pop_error(char *message){
    // Initialization
    char *message = "error da maapla";
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Error Message Example");

    ShowErrorMessage(message);

    // Close window and OpenGL context
    CloseWindow();

    return 0;
}
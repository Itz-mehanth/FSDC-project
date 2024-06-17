#include <raylib.h>
#include <stdio.h>

#define NUM_FRAMES 60  // Number of frames in the animation
#define FRAME_RATE 30   // Desired frame rate for the animation

int main() {
    // Initialization
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Lottie Animation Example");

    // Load the animation frames
    Texture2D frames[NUM_FRAMES];
    for (int i = 0; i < NUM_FRAMES; i++) {
        char filename[50];
        sprintf(filename, "Frames/%d.png", i + 1);  // Adjust index to start from 1
        frames[i] = LoadTexture(filename);
    }
    // Calculate scaling factors to fit frames to window
    float scaleX = (float)screenWidth / frames[0].width;
    float scaleY = (float)screenHeight / frames[0].height;

    int currentFrame = 0;
    float frameTime = 0.0f;
    float frameSpeed = 1.0f / FRAME_RATE;  // Time per frame

    SetTargetFPS(60);  // Set the frame rate
    int i=0;
    while (i<(NUM_FRAMES*3)) {
        // Update
        i++;
        frameTime += GetFrameTime();

        // Update frame based on frameTime
        if (frameTime >= frameSpeed) {
            frameTime = 0.0f;
            currentFrame++;
            if (currentFrame >= NUM_FRAMES) currentFrame = 0;
        }

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw the current frame scaled to fit the window
        DrawTexturePro(frames[currentFrame],
                       (Rectangle){0, 0, frames[currentFrame].width, frames[currentFrame].height},  // Source rectangle
                       (Rectangle){0, 0, screenWidth, screenHeight},  // Destination rectangle (whole window)
                       (Vector2){0, 0},  // Origin offset
                       0.0f,  // Rotation
                       WHITE);  // Tint color

        EndDrawing();
    }

    // De-Initialization
    for (int i = 0; i < NUM_FRAMES; i++) {
        UnloadTexture(frames[i]);  // Unload each frame texture
    }
    CloseWindow();  // Close the window and release resources

    return 0;
}

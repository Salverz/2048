#include <stdio.h>
#include "raylib.h"

const int screenWidth = 800;
const int screenHeight = 1000;
int tiles[16];

void drawBackground(void) {
    DrawRectangle(0, 0, screenWidth, screenHeight, BEIGE);
    DrawText("2048", 20, 5, 200, BLACK);
    DrawRectangle(0, screenHeight - screenWidth, screenWidth, screenWidth, LIGHTGRAY);
    for (int i = 0; i < 5; i++) {
        Vector2 verticalLineStart = {i * 200, 200};
        Vector2 verticalLineEnd = {i * 200, 1000};
        Vector2 horizontalLineStart = {0, 200 + i * 200};
        Vector2 horizontalLineEnd = {screenWidth, 200 + i * 200};
        DrawLineEx(verticalLineStart, verticalLineEnd, 20.0f, BLACK);
        DrawLineEx(horizontalLineStart, horizontalLineEnd, 20.0f, BLACK);
    }
}

void drawTiles(void) {
    for (int i = 0; i < 16; i++) {
        if (tiles[i] != 0) {
            // Convert number to string
            char number[5];
            sprintf(number, "%d", tiles[i]);

            // Determine text offset based on text length
            int offset;
            for (int i = 0; i < 5; i++) {
                if (number[i] == '\0') {
                    break;
                }
                offset = (i + 1) * -13 + 100;
            }

            DrawText(number, (i % 4) * 200 + offset, (i / 4) * 200 + 280, 50, DARKGRAY);
        }
    }
}

void placeRandomTile(void) {
    // Find empty tiles
    int zeroTiles = 0;
    for (int i = 0; i < 16; i++) {
        if (tiles[i] == 0) zeroTiles++;
    }

    // Pick random tile
    int randomTile = GetRandomValue(1, zeroTiles);

    // Fill the random tile
    for (int i = 0; i < 16; i++) {
        if (tiles[i] == 0) randomTile--;
        if (randomTile == 0) {
            tiles[i] = 2;
            break;
        }
    }
}

void resetGame(void) {
    for (int i = 0; i < 16; i++) {
        tiles[i] = 0;
    }
}

void handleInput(void) {
    if (IsKeyPressed(KEY_LEFT)) {
        for (int i = 0; i < 16; i++) {  
            int currentMoveTilePos = i / 4 + (i % 4) * 4;
            int movePosition = currentMoveTilePos;
            bool multiplyTiles = false;
            for (int j = currentMoveTilePos - 1; j > (currentMoveTilePos / 4) * 4 - 1; j--) {
                if (tiles[j] == 0) {
                    movePosition = j;
                } else if (tiles[currentMoveTilePos] == tiles[j]) {
                    movePosition = j;
                    multiplyTiles = true;
                    break;
                } else {
                    break;
                }
            }
            if (multiplyTiles) {
                tiles[movePosition] *= 2;
            }
            if (tiles[movePosition] == 0) {
                tiles[movePosition] = tiles[currentMoveTilePos];
            }
            if (currentMoveTilePos != movePosition) {
                tiles[currentMoveTilePos] = 0;
            }
        }
        placeRandomTile();
    }

    if (IsKeyPressed(KEY_RIGHT)) {
        for (int i = 0; i < 16; i++) {
            int movePosition = i;
            for (int j = i; j < (i / 4) * 4 + 4; j++) {
                if (tiles[j] == 0) {
                    movePosition = j;
                }
            }
            tiles[movePosition] = tiles[i];
            if (i != movePosition) {
                tiles[i] = 0;
            }
        }
        placeRandomTile();
    }

    if (IsKeyPressed(KEY_UP)) {
        for (int i = 0; i < 16; i++) {
            int movePosition = i;
            for (int j = i; j > -1; j -= 4) {
                if (tiles[j] == 0) {
                    movePosition = j;
                }
            }
            tiles[movePosition] = tiles[i];
            if (i != movePosition) {
                tiles[i] = 0;
            }
        }
        placeRandomTile();
    }

    if (IsKeyPressed(KEY_DOWN)) {
        for (int i = 0; i < 16; i++) {
            int movePosition = i;
            for (int j = i; j < 16; j += 4) {
                if (tiles[j] == 0) {
                    movePosition = j;
                }
            }
            tiles[movePosition] = tiles[i];
            if (i != movePosition) {
                tiles[i] = 0;
            }
        }
        placeRandomTile();
    }

    if (IsKeyPressed(KEY_SPACE)) {
        resetGame();
    };
}

int main(void) {
    InitWindow(screenWidth, screenHeight, "Game window");
    SetTargetFPS(60);

    // Game initialization
    resetGame();
    placeRandomTile();

    // Game loop
    while (!WindowShouldClose()) {
        //Code
        handleInput();

        // Draw
        BeginDrawing();
        drawBackground();
        drawTiles();
        EndDrawing();
    }


    CloseWindow();
    return 0;
}
#include <stdio.h>
#include "raylib.h"

const int screenWidth = 800;
const int screenHeight = 1000;
int tiles[16];
int lastTilesState[16];

void drawBackground(void) {
    DrawRectangle(0, 0, screenWidth, screenHeight, BEIGE);
    DrawText("", 20, 5, 200, BLACK);
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

Color getColorForTile(int tileValue) {
    Color tileColor;
    tileColor.a = 255;
    switch (tileValue) {
        case 2:
            tileColor.r = 255;
            tileColor.g = 251;
            tileColor.b = 194;
            break;
        case 4:
            tileColor.r = 219;
            tileColor.g = 212;
            tileColor.b = 134;
            break;
        case 8:
            tileColor.r = 222;
            tileColor.g = 184;
            tileColor.b = 95;
            break;
        case 16:
            tileColor.r = 219;
            tileColor.g = 160;
            tileColor.b = 70;
            break;
        case 32:
            tileColor.r = 219;
            tileColor.g = 151;
            tileColor.b = 61;
            break;
        case 64:
            tileColor.r = 212;
            tileColor.g = 87;
            tileColor.b = 42;
            break;
        case 128:
            tileColor.r = 255;
            tileColor.g = 255;
            tileColor.b = 9;
            break;
        case 256:
            tileColor.r = 245;
            tileColor.g = 245;
            tileColor.b = 59;
            break;
        case 512:
            tileColor.r = 214;
            tileColor.g = 214;
            tileColor.b = 26;
            break;
        case 1024:
            tileColor.r = 227;
            tileColor.g = 220;
            tileColor.b = 16;
            break;
        case 2048:
            tileColor.r = 214;
            tileColor.g = 203;
            tileColor.b = 0;
            break;
    }
    return tileColor;
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

            DrawRectangle((i % 4) * 200 + 10, (i / 4) * 200 + 210, 180, 180, getColorForTile(tiles[i]));
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
    placeRandomTile();
}

void updateLastTilesState(void) {
    for (int i = 0; i < 16; i++) {
        lastTilesState[i] = tiles[i];
    }
}

bool sameAsLastState(void) {
    for (int i = 0; i < 16; i++) {
        if (tiles[i] != lastTilesState[i]) {
            return false;
        }
    }
    return true;
}

void handleInput(void) {
    if (IsKeyPressed(KEY_LEFT)) {
        updateLastTilesState();
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
        if (!sameAsLastState()) {
            placeRandomTile();
        }
    }

    if (IsKeyPressed(KEY_RIGHT)) {
        updateLastTilesState();
        for (int i = 15; i >= 0; i--) {  
            int currentMoveTilePos = i / 4 + (i % 4) * 4;
            int movePosition = currentMoveTilePos;
            bool multiplyTiles = false;
            for (int j = currentMoveTilePos + 1; j < (currentMoveTilePos / 4) * 4 + 4; j++) {
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
        if (!sameAsLastState()) {
            placeRandomTile();
        }
    }

    if (IsKeyPressed(KEY_UP)) {
        updateLastTilesState();
        for (int i = 0; i < 16; i++) {
            int movePosition = i;
            bool multiplyTiles = false;
            for (int j = i - 4; j >= 0; j -= 4) {
                if (tiles[j] == 0) {
                    movePosition = j;
                } else if (tiles[i] == tiles[j]) {
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
                tiles[movePosition] = tiles[i];
            }
            if (i != movePosition) {
                tiles[i] = 0;
            }
        }
        if (!sameAsLastState()) {
            placeRandomTile();
        }
    }

    if (IsKeyPressed(KEY_DOWN)) {
        updateLastTilesState();
        for (int i = 15; i >= 0; i--) {
            int movePosition = i;
            bool multiplyTiles = false;
            for (int j = i + 4; j < 16; j += 4) {
                if (tiles[j] == 0) {
                    movePosition = j;
                } else if (tiles[i] == tiles[j]) {
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
                tiles[movePosition] = tiles[i];
            }
            if (i != movePosition) {
                tiles[i] = 0;
            }
        }
        if (!sameAsLastState()) {
            placeRandomTile();
        }
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
#include "raylib.h"
#include "win32_helper.h"

int main(void) {
    SetConfigFlags(FLAG_WINDOW_TRANSPARENT | FLAG_WINDOW_UNDECORATED
                 | FLAG_WINDOW_TOPMOST | FLAG_WINDOW_UNFOCUSED);
    InitWindow(800, 450, "Love Virus");

    int posX, posY, screenWidth, screenHeight;
    GetDesktopWorkArea(&posX, &posY, &screenWidth, &screenHeight);
    SetWindowSize(screenWidth, screenHeight);
    SetWindowPosition(posX, posY);

    void *windowHandle = GetWindowHandle();

    SetTargetFPS(60);

    Rectangle square = { 100, 100, 50, 50 };
    Vector2 velocity = { 4.0f, 3.0f };

    while (!WindowShouldClose()) {
        square.x += velocity.x;
        square.y += velocity.y;
        if (square.x <= 0 || square.x + square.width >= screenWidth)   velocity.x *= -1;
        if (square.y <= 0 || square.y + square.height >= screenHeight) velocity.y *= -1;

        int mouseX, mouseY;
        GetCursorPositionInWindow(windowHandle, &mouseX, &mouseY);
        bool overSquare = CheckCollisionPointRec(
            (Vector2){ (float)mouseX, (float)mouseY }, square);

        if (overSquare) ClearWindowState(FLAG_WINDOW_MOUSE_PASSTHROUGH);
        else            SetWindowState(FLAG_WINDOW_MOUSE_PASSTHROUGH);

        BeginDrawing();
            ClearBackground(BLANK);
            DrawRectangleRec(square, RED);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
#include "raylib.h"

#define Rectangle Rectangle_win32
#define CloseWindow CloseWindow_win32
#define ShowCursor ShowCursor_win32

#include <windows.h>

#undef Rectangle
#undef CloseWindow
#undef ShowCursor

int main(void) {
    SetConfigFlags(FLAG_WINDOW_TRANSPARENT | FLAG_WINDOW_UNDECORATED | FLAG_WINDOW_TOPMOST);
    InitWindow(800, 450, "Love Virus");

    // Ask Windows for the usable desktop area (excludes taskbar)
    RECT workArea;
    SystemParametersInfo(SPI_GETWORKAREA, 0, &workArea, 0);
    int screenWidth  = workArea.right - workArea.left;
    int screenHeight = workArea.bottom - workArea.top;

    SetWindowSize(screenWidth, screenHeight);
    SetWindowPosition(workArea.left, workArea.top);

    SetTargetFPS(60);

    Rectangle square = { 100, 100, 50, 50 };
    Vector2 velocity = { 4.0f, 3.0f };

    while (!WindowShouldClose()) {
        square.x += velocity.x;
        square.y += velocity.y;

        if (square.x <= 0 || square.x + square.width >= screenWidth) {
            velocity.x *= -1;
        }
        if (square.y <= 0 || square.y + square.height >= screenHeight) {
            velocity.y *= -1;
        }

        BeginDrawing();
            ClearBackground(BLANK);
            DrawRectangleRec(square, RED);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
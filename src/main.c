#include "raylib.h"
#include "win32_helper.h"
#include <math.h>
#include <time.h>

#define MAX_SQUARES 64
#define SQUARE_SIZE 50

typedef struct {
    Rectangle rect;
    Vector2 velocity;
} BouncingSquare;

static Vector2 RandomVelocity(void) {
    float speedX = (float)GetRandomValue(2, 6);
    float speedY = (float)GetRandomValue(2, 6);
    if (GetRandomValue(0, 1) == 0) speedX *= -1;
    if (GetRandomValue(0, 1) == 0) speedY *= -1;
    return (Vector2){ speedX, speedY };
}

int main(void) {
    SetConfigFlags(FLAG_WINDOW_TRANSPARENT | FLAG_WINDOW_UNDECORATED
                 | FLAG_WINDOW_TOPMOST | FLAG_WINDOW_UNFOCUSED);
    InitWindow(800, 450, "Love Virus");
    SetRandomSeed((unsigned int)time(NULL));

    int posX, posY, screenWidth, screenHeight;
    GetDesktopWorkArea(&posX, &posY, &screenWidth, &screenHeight);
    SetWindowSize(screenWidth, screenHeight);
    SetWindowPosition(posX, posY);

    void *windowHandle = GetWindowHandle();

    SetTargetFPS(60);

    BouncingSquare squares[MAX_SQUARES];
    int squareCount = 1;
    squares[0].rect = (Rectangle){ 100, 100, SQUARE_SIZE, SQUARE_SIZE };
    squares[0].velocity = (Vector2){ 4.0f, 3.0f };

    while (!WindowShouldClose()) {
        for (int i = 0; i < squareCount; i++) {
            squares[i].rect.x += squares[i].velocity.x;
            squares[i].rect.y += squares[i].velocity.y;

            if (squares[i].rect.x <= 0 || squares[i].rect.x + squares[i].rect.width >= screenWidth)
                squares[i].velocity.x *= -1;
            if (squares[i].rect.y <= 0 || squares[i].rect.y + squares[i].rect.height >= screenHeight)
                squares[i].velocity.y *= -1;
        }

        for (int i = 0; i < squareCount; i++) {
            for (int j = i + 1; j < squareCount; j++) {
                if (CheckCollisionRecs(squares[i].rect, squares[j].rect)) {
                    Vector2 temp = squares[i].velocity;
                    squares[i].velocity = squares[j].velocity;
                    squares[j].velocity = temp;

                    float overlapX = fminf(squares[i].rect.x + squares[i].rect.width, squares[j].rect.x + squares[j].rect.width)
                                    - fmaxf(squares[i].rect.x, squares[j].rect.x);
                    float overlapY = fminf(squares[i].rect.y + squares[i].rect.height, squares[j].rect.y + squares[j].rect.height)
                                    - fmaxf(squares[i].rect.y, squares[j].rect.y);

                    if (overlapX < overlapY) {
                        float push = overlapX / 2.0f;
                        if (squares[i].rect.x < squares[j].rect.x) { squares[i].rect.x -= push; squares[j].rect.x += push; }
                        else                                       { squares[i].rect.x += push; squares[j].rect.x -= push; }
                    } else {
                        float push = overlapY / 2.0f;
                        if (squares[i].rect.y < squares[j].rect.y) { squares[i].rect.y -= push; squares[j].rect.y += push; }
                        else                                       { squares[i].rect.y += push; squares[j].rect.y -= push; }
                    }
                }
            }
        }

        int mouseX, mouseY;
        GetCursorPositionInWindow(windowHandle, &mouseX, &mouseY);
        Vector2 cursor = { (float)mouseX, (float)mouseY };

        int hoveredIndex = -1;
        for (int i = 0; i < squareCount; i++) {
            if (CheckCollisionPointRec(cursor, squares[i].rect)) {
                hoveredIndex = i;
                break;
            }
        }

        if (hoveredIndex != -1) ClearWindowState(FLAG_WINDOW_MOUSE_PASSTHROUGH);
        else                    SetWindowState(FLAG_WINDOW_MOUSE_PASSTHROUGH);

        if (hoveredIndex != -1 && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && squareCount < MAX_SQUARES) {
            squares[squareCount].rect = squares[hoveredIndex].rect;
            squares[squareCount].velocity = RandomVelocity();
            squareCount++;

            squares[hoveredIndex].velocity = RandomVelocity();
        }

        BeginDrawing();
            ClearBackground(BLANK);
            for (int i = 0; i < squareCount; i++) {
                DrawRectangleRec(squares[i].rect, RED);
            }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
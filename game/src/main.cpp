#include "raylib.h"
#include <stdbool.h>
#include <time.h>

void DrawCircle(Vector2 position, float radius, Color color);
void ShowCustomCursor(void);
void DrawBackgroundLines(int screenWidth, int screenHeight, int spacing, Color color);

int main()
{
    const int screenWidth = 1280;
    const int screenHeight = 720;
    const int lineSpacing = 10;
    const Color lineColor = LIGHTGRAY;

    InitWindow(screenWidth, screenHeight, "lab1");


    SetTargetFPS(60);

    // Moving circle changes color while overlapping

    Vector2 circlePosition = { screenWidth / 2, screenHeight / 4 };
    float circleRadius = 50;
    Color circle1Color = ORANGE;
    Color circle2Color = BLACK;

    // Adding a triangle

    Vector2 trianglePoint1 = { screenWidth / 8, screenHeight / 8 - 50 };
    Vector2 trianglePoint2 = { screenWidth / 8 - 50, screenHeight / 8 + 50 };
    Vector2 trianglePoint3 = { screenWidth / 8 + 50, screenHeight / 8 + 50 };

    // Adding a rectangle

    Rectangle rectangle = { screenWidth / 8 - 50, screenHeight / 8 + 70, 100, 50 };
    Color rectangleColor = GREEN;

    int randomNumber = 0;
    double elapsedTime = 0;
    double interval = 2.0; // 2 seconds

    while (!WindowShouldClose())
    {
        // Update
        if (IsKeyDown(KEY_RIGHT))
        {
            circlePosition.x += 5;
        }
        else if (IsKeyDown(KEY_LEFT))
        {
            circlePosition.x -= 5;
        }
        else if (IsKeyDown(KEY_UP))
        {
            circlePosition.y -= 5;
        }
        else if (IsKeyDown(KEY_DOWN))
        {
            circlePosition.y += 5;
        }

        Vector2 mousePosition = GetMousePosition();

        bool isOverlapping = CheckCollisionCircles(circlePosition, circleRadius, mousePosition, circleRadius);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw the background lines
        DrawBackgroundLines(screenWidth, screenHeight, lineSpacing, lineColor);

        // Draw the first stationary circle
        DrawCircle(circlePosition, circleRadius, circle1Color);

        // Draw the second circle at the mouse cursor position
        if (isOverlapping)
        {
            DrawCircle(mousePosition, circleRadius, circle2Color);
        }
        else
        {
            DrawCircle(mousePosition, circleRadius, circle1Color);
        }

        // Draw the triangle
        DrawTriangle(trianglePoint1, trianglePoint2, trianglePoint3, BLUE);

        // Draw the rectangle
        DrawRectangleRec(rectangle, rectangleColor);

        // Draw a horizontal line
        DrawLine(0, screenHeight / 2, screenWidth, screenHeight / 2, RED);

        // Generate random number every 2 seconds
        elapsedTime += GetFrameTime();
        if (elapsedTime >= interval)
        {
            randomNumber = GetRandomValue(0, 100);
            elapsedTime = 0;
        }

        // Display the random number
        DrawText(TextFormat("Random Number: %d", randomNumber), 10, 10, 20, BLACK);

        // Display the current FPS
        DrawText(TextFormat("FPS: %d", GetFPS()), 10, 40, 20, BLACK);

        // Show custom cursor
        ShowCustomCursor();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}

void DrawCircle(Vector2 position, float radius, Color color)
{
    DrawCircleV(position, radius, color);
}

void ShowCustomCursor()
{
    DrawRectangle(GetMouseX(), GetMouseY(), 10, 10, RED);
}

void DrawBackgroundLines(int screenWidth, int screenHeight, int spacing, Color color)
{
    for (int i = 0; i < screenWidth; i += spacing)
    {
        DrawLine(i, 0, i, screenHeight, color);
    }

    for (int j = 0; j < screenHeight; j += spacing)
    {
        DrawLine(0, j, screenWidth, j, color);
    }
}

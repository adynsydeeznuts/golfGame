#include <iostream>
#include <cmath>
#include <raylib.h>
#include <raymath.h>
#include <vector>

#include "Ball.h"
#include "Wall.h"
#include "CurvedWall.h"
#include "Line.h"
#include "Hole.h"

using namespace std;

double lastUpdateTime = 0;

Ball ball(Vector2{540, 480}, Vector2{0.0f, 0.0f}); // Initial position at the center of the screen

Wall wall1(Vector2{200, 560}, 200, 20, 50);
CurvedWall wall2(Vector2{300, 300}, "parabola", 100, 50, BROWN, 2.0f, 0, 0); // Example of a curved wall

vector<Line> wall1Lines = wall1.ConvertToLines();
vector<Line> wall2Lines = wall2.ConvertToLines();

vector<vector<Line>> wallLines = {};
vector<Wall> wallRects = {};

bool eventTriggered(double interval) {
    double currentTime = GetTime();
    if(currentTime - lastUpdateTime >= interval) {
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}

int main () {
    const int SCREEN_WIDTH = 1080;
    const int SCREEN_HEIGHT = 960;

    Vector2 startMousePos = {0, 0};
    Vector2 endMousePos = {0, 0};

    wallLines.push_back(wall1Lines);
    wallLines.push_back(wall2Lines);
    wallRects.push_back(wall1);

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "golf game");
    SetTargetFPS(180);

    const Image backdrop = LoadImage("./images/grass.png");
    Texture2D backdropTexture = LoadTextureFromImage(backdrop);
    UnloadImage(backdrop);

    while (WindowShouldClose() == false){

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            startMousePos = GetMousePosition();
        }
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            endMousePos = GetMousePosition();
            ball.Hit(startMousePos, endMousePos);

        }
        ball.updatePosition();
        
        for(long long unsigned int i = 0; i < wallLines.size(); i++) {
            for(long long unsigned int j = 0; j < wallLines[i].size(); j++) {
                ball.CheckCollision(wallLines[i][j]);
            }
        }
        
        
        BeginDrawing();
            DrawTexture(backdropTexture, 0, 0, WHITE);
            ball.Draw();
            wall2.Draw();
            for (Wall& wall : wallRects) {
                wall.Draw();
            }
            for (vector<Line>& lines : wallLines) {
                for (Line& line : lines) {
                    line.Draw();
                }
            }

        EndDrawing();
    }

    CloseWindow();
}
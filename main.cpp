#include <iostream>
#include <cmath>
#include <raylib.h>
#include <raymath.h>
#include "Ball.h"
#include "Wall.h"
#include <vector>

using namespace std;

double lastUpdateTime = 0;

Ball ball(Vector2{540, 480}, Vector2{0.0f, 0.0f}); // Initial position at the center of the screen

Wall wall1(Vector2{200, 560}, 200, 20, 50);
vector<Wall> walls = {};

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

    walls.push_back(wall1);

    cout << "Hello World" << endl;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "My first RAYLIB program!");
    SetTargetFPS(60);

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
        for(long long unsigned int i = 0; i < walls.size(); i++) {
            ball.reflectBall(walls[i]);
        }
        
        
        BeginDrawing();
            DrawTexture(backdropTexture, 0, 0, WHITE);
            ball.Draw();
            for (Wall& wall : walls) {
                wall.Draw();
            }
        EndDrawing();
    }

    CloseWindow();
}
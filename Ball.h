#ifndef BALL_H
#define BALL_H

#include <iostream>
#include <raylib.h>
#include <raymath.h>
#include <cmath>
#include "Wall.h"

using namespace std;

class Ball {
private:
    float radius = 10.0f; // Default radius
    Vector2 position;
    Vector2 velocity;
    float drag = 2.0f; // Default drag value
    const int SCREEN_WIDTH = 1080;
    const int SCREEN_HEIGHT = 960;
    const int buffer = 10;

    float toRadians(float degrees) const {
        return degrees * static_cast<float>(PI) / 180.0f;
    }

public:
    // Constructor
    Ball(Vector2 position = {540, 480}, Vector2 velocity = {0.0f, 0.0f})
        : position(position), velocity(velocity) {}

    // Getters
    Vector2 getPosition() const { return position; }
    Vector2 getVelocity() const { return velocity; }
    float getDrag() const { return drag; }
    const float getRadius() const { return radius; }

    // Setters
    void setPosition(float posX, float posY) {
        position = {posX, posY};
    }

    void setVelocity(float velX, float velY) {
        velocity = {velX, velY};
    }

    void updatePosition() {
        float deltaTime = GetFrameTime();

        if(Vector2Length(velocity) > drag * 5) {
            velocity.x -= velocity.x * drag * deltaTime;
            velocity.y -= velocity.y * drag * deltaTime;
        }
        else {
            velocity = {0.0f, 0.0f};
        }
        position = Vector2Add(position, Vector2Scale(velocity, deltaTime));
        CheckCollisionWithBorders();
    }

    void Draw() {
        DrawCircle(position.x, position.y, radius, WHITE);
    }

    void CheckCollisionWithBorders() {
        if(position.x + radius >= SCREEN_WIDTH || position.x - radius <= 0)
        {
            position.x = (position.x + radius >= SCREEN_WIDTH) ? SCREEN_WIDTH - radius : radius;
            velocity.x *= -0.8f;
        }

        if(position.y + radius >= SCREEN_HEIGHT || position.y - radius <= 0)
        {
            position.y = (position.y + radius >= SCREEN_HEIGHT) ? SCREEN_HEIGHT - radius : radius;
            velocity.y *= -0.8f;
        }
    }

    void CheckCollision(Line line) {
        Vector2 lineVec = Vector2Subtract(line.getPoint2(), line.getPoint1());
        Vector2 lineNormal = Vector2Normalize(Vector2{-lineVec.y, lineVec.x});
        Vector2 ballToLine = Vector2Subtract(position, line.getPoint1());

        // Ensure the normal points away from the ball
        if (Vector2DotProduct(ballToLine, lineNormal) < 0) {
            lineNormal = Vector2Scale(lineNormal, -1.0f);
        }

        float distance = Vector2DotProduct(ballToLine, lineNormal);

        if (distance <= radius) {
            float projection = Vector2DotProduct(ballToLine, Vector2Normalize(lineVec));
            float lineLength = Vector2Length(lineVec);

            if (projection >= 0 && projection <= lineLength) {
                float dotProduct = Vector2DotProduct(velocity, lineNormal);
                Vector2 reflection = Vector2Subtract(velocity, Vector2Scale(lineNormal, 2 * dotProduct));

                Vector2 tempV = Vector2Scale(reflection, 0.8f);
                setVelocity(tempV.x, tempV.y);

                Vector2 correction = Vector2Scale(lineNormal, radius - distance + 0.1f);
                Vector2 tempP = Vector2Add(position, correction);
                setPosition(tempP.x, tempP.y);

                cout << "Collision Normal: " << lineNormal.x << ", " << lineNormal.y << std::endl;
                cout << "Distance: " << distance << std::endl;
            }
        }
    }

    void Hit(Vector2 startMousePos, Vector2 endMousePos) {
        Vector2 power = {startMousePos.x - endMousePos.x, startMousePos.y - endMousePos.y};
        power = Vector2Scale(power, 2.0f);
        setVelocity(power.x, power.y);
    }
};

#endif
#ifndef BALL_H
#define BALL_H

#include <iostream>
#include <raylib.h>
#include <raymath.h>
#include <cmath>
#include "Wall.h"

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

    bool CheckCollision(Wall wall) {
        // Translate ball position to wall's local coordinate system
        float rad = toRadians(wall.getRotation());
        float cosTheta = cos(rad);
        float sinTheta = sin(rad);

        float localBallX = cosTheta * (position.x - wall.getPosition().x) + sinTheta * (position.y - wall.getPosition().y);
        float localBallY = -sinTheta * (position.x - wall.getPosition().x) + cosTheta * (position.y - wall.getPosition().y);

        // Adjust for ball's radius in the bounding box check
        float halfWidth = wall.getWidth() / 2.0f;
        float halfHeight = wall.getHeight() / 2.0f;

        return (localBallX + radius >= -halfWidth && localBallX - radius <= halfWidth &&
                localBallY + radius >= -halfHeight && localBallY - radius <= halfHeight);
    }

    void reflectBall(Wall wall) {
        if (CheckCollision(wall)) {
            // Translate velocity to wall's local coordinate system
            float rad = toRadians(wall.getRotation());
            float cosTheta = cos(rad);
            float sinTheta = sin(rad);

            float localVelX = cosTheta * velocity.x + sinTheta * velocity.y;
            float localVelY = -sinTheta * velocity.x + cosTheta * velocity.y;

            // Reflect velocity in the local coordinate system
            if (abs(localVelX) > abs(localVelY)) {
                localVelX = -localVelX; // Reverse X velocity
            } else {
                localVelY = -localVelY; // Reverse Y velocity
            }

            // Transform velocity back to global coordinate system
            setVelocity(cosTheta * localVelX - sinTheta * localVelY, sinTheta * localVelX + cosTheta * localVelY);

            // Move the ball slightly outside the wall to prevent it from getting stuck
            float overlapX = (localVelX > 0) ? radius : -radius;
            float overlapY = (localVelY > 0) ? radius : -radius;

            position.x += cosTheta * overlapX - sinTheta * overlapY;
            position.y += sinTheta * overlapX + cosTheta * overlapY;
        } else {
            std::cout << "No collision" << std::endl;
        }
    }

    void Hit(Vector2 startMousePos, Vector2 endMousePos) {
        Vector2 power = {startMousePos.x - endMousePos.x, startMousePos.y - endMousePos.y};
        setVelocity(power.x, power.y);
        std::cout << "Hit! Power: " << Vector2Length(power) << std::endl;
        std::cout << power.x << " " << power.y << std::endl;
    }
};

#endif
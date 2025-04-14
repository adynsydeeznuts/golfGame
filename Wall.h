#ifndef WALL_H
#define WALL_H

#include <iostream>
#include <raylib.h>
#include <raymath.h>
#include <cmath>
#include "Ball.h"
#include "Line.h"

class Wall {
private:
    Vector2 position; // Position of the wall's center
    float width; // Width of the wall
    float height; // Height of the wall
    float rotation; // Rotation angle of the wall in degrees

    Color color = BROWN;

public:
    // Constructor
    Wall(Vector2(position), float width, float height, float rotation = 0.0f)
        : position(position), width(width), height(height), rotation(rotation) {}

    // Getters
    Vector2 getPosition() const { return position; }
    float getWidth() const { return width; }
    float getHeight() const { return height; }
    float getRotation() const { return rotation; }

    void Draw() {
        DrawRectanglePro({position.x, position.y, width, height}, position, rotation, color);
    }


};

#endif
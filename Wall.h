#ifndef WALL_H
#define WALL_H

#include <iostream>
#include <raylib.h>
#include <raymath.h>
#include <cmath>
#include "Ball.h"
#include "Line.h"
#include <vector>

using namespace std;

class Wall {
private:
    Vector2 position; // Position of the wall's center
    float width; // Width of the wall
    float height; // Height of the wall
    float rotation; // Rotation angle of the wall in degrees
    Vector2 origin = {width / 2, height / 2};

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
        DrawRectanglePro(Rectangle{position.x, position.y, width, height}, origin, rotation, color);
    }

    vector<Line> ConvertToLines() {
        // Calculate the four corners of the rectangle before rotation
        Vector2 topLeft = {position.x - width / 2, position.y - height / 2};
        Vector2 topRight = {position.x + width / 2, position.y - height / 2};
        Vector2 bottomLeft = {position.x - width / 2, position.y + height / 2};
        Vector2 bottomRight = {position.x + width / 2, position.y + height / 2};

        // Apply rotation to each corner around the center position
        topLeft = Vector2Rotate(Vector2Subtract(topLeft, position), rotation * DEG2RAD);
        topLeft = Vector2Add(topLeft, position);

        topRight = Vector2Rotate(Vector2Subtract(topRight, position), rotation * DEG2RAD);
        topRight = Vector2Add(topRight, position);

        bottomLeft = Vector2Rotate(Vector2Subtract(bottomLeft, position), rotation * DEG2RAD);
        bottomLeft = Vector2Add(bottomLeft, position);

        bottomRight = Vector2Rotate(Vector2Subtract(bottomRight, position), rotation * DEG2RAD);
        bottomRight = Vector2Add(bottomRight, position);

        // Create lines for the rotated rectangle
        Line line1(topLeft, topRight);
        Line line2(topRight, bottomRight);
        Line line3(bottomRight, bottomLeft);
        Line line4(bottomLeft, topLeft);

        return {line1, line2, line3, line4};
    }


};

#endif
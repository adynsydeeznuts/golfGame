#ifndef CURVEDWALL_H
#define CURVEDWALL_H

#include <raylib.h>
#include <raymath.h>
#include <vector>

#include "Ball.h"
#include "Wall.h"
#include "Line.h"

using namespace std;

class CurvedWall {
private:
Vector2 origin;
string curveType;   
int maxPoints; 
float width;
Color color;  
float a;
float b;
float c;

vector<Vector2> points;


public:
    // Constructor
    CurvedWall(Vector2(origin), string curveType, int maxPoints, float width, Color color, float a = 0.0f, float b = 0.0f, float c = 0.0f)
        : origin(origin), curveType(curveType), maxPoints(maxPoints), color(color), width(width), a(a), b(b), c(c), points() {
        points.resize(maxPoints); // Resize the points vector to hold the specified number of points
    }

    // Create a curved wall using a cubic Bezier curve
    vector<Vector2> CreateParaboola(float a, float b, float c) { 
        for (int i = 0; i < maxPoints; i++) {
            float t = (float)i / (maxPoints - 1); // Normalize t to [0, 1]
            points[i].x = t; // Quadratic equation
            points[i].y = pow((t-0.5), 2) * a + t * b + c; // y-coordinate is constant for a parabola
        }
        for (int i = 0; i < maxPoints; i++) {
            //float t = (float)i / (maxPoints - 1); // Normalize t to [0, 1]
            points[i].x = (points[i].x * maxPoints) + origin.x; // Quadratic equation
            points[i].y = (points[i].y * maxPoints) + origin.y; // y-coordinate is constant for a parabola
        }
        return points;
    }

    vector<Line> ConvertToLines() { 
        vector<Line> lines; // Vector to hold the lines of the curve
        if(curveType == "parabola") {
            vector<Vector2> points = CreateParaboola(a, b, c);
            for (size_t i = 0; i < points.size() - 1; i++) {
                Line line(points[i], points[i + 1]);
                lines.push_back(line); // Add the line to the vector of lines
            }
        }
        else cout << "Invalid curve type!" << endl; // Debug output for invalid curve type
        return lines;
    }

    // Draw the curved wall
    void Draw() {
        for (long long unsigned int i = 0; i < points.size() - 1; i++) {
            DrawTriangle(points[i], points[i + 1], {points[i].x, width}, color);
        }
    };

    // Check collision with a ball
    bool CheckCollision(const Ball& ball) const;

};

#endif // CURVEDWALL_H
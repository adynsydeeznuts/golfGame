#ifndef CURVEDWALL_H
#define CURVEDWALL_H

#include <raylib.h>
#include <raymath.h>
#include <vector>

#include "Ball.h"
#include "Wall.h"
#include "Line.h"

using namespace std;


class CurvedWall : public Wall {
private:
    string curveType;   
    int maxPoints; 
    float a;
    float b;
    float c;

    vector<Vector2> points;

public:
    // Constructor
    CurvedWall(Vector2 position, string curveType, int maxPoints, float width, Color color, float a = 0.0f, float b = 0.0f, float c = 0.0f)
        : Wall(position, width, 0.0f, 0.0f, color), // Call the Wall constructor
          curveType(curveType), maxPoints(maxPoints), a(a), b(b), c(c) {
        points.resize(maxPoints); // Resize the points vector to hold the specified number of points
    }

    void Draw() override {
        for (size_t i = 0; i < points.size() - 1; i++) {
            if (i < (points.size()) / 2) {
                DrawTriangle(points[i + 1], points[i], {points[0].x, points[0].y + getWidth()}, getColor()); // Draw triangle between 2 points and the bottom left corner of the wall
            } else {
                DrawTriangle(points[i + 1], points[i], {points[points.size() - 1].x, points[points.size() - 1].y + getWidth()}, getColor()); // Draw triangle between 2 points and the bottom left corner of the wall
            }
        }
        DrawTriangle(points[(points.size()) / 2], {points[0].x, points[0].y + getWidth()}, {points[points.size() - 1].x, points[points.size() - 1].y + getWidth()}, getColor());
    }

    // Create a curved wall using a cubic Bezier curve
    vector<Vector2> CreateParaboola(float a, float b, float c) { 
        for (int i = 0; i < maxPoints; i++) {
            float t = (float)i / (maxPoints - 1); // Normalize t to [0, 1]
            points[i].x = t; // Quadratic equation
            points[i].y = pow((t - 0.5), 2) * a + t * b + c; // y-coordinate is constant for a parabola
        }
        for (int i = 0; i < maxPoints; i++) {
            points[i].x = (points[i].x * maxPoints) + getPosition().x;
            points[i].y = (points[i].y * maxPoints) + getPosition().y;
        }
        return points;
    }

    vector<Vector2> createArc(float a, float b) {
        
        return points;
    }

    vector<Line> ConvertToLines() { 
        vector<Line> lines; // Vector to hold the lines of the curve
        if (curveType == "parabola") {
            vector<Vector2> points = CreateParaboola(a, b, c);
            for (size_t i = 0; i < points.size() - 1; i++) {
                Line line(points[i], points[i + 1]);
                lines.push_back(line); // Add the line to the vector of lines
            }
            Line line1(points[points.size() - 1], Vector2{points[points.size() - 1].x, points[points.size() - 1].y + getWidth()});
            Line line2(line1.getPoint2(), Vector2{points[0].x, points[0].y + getWidth()});
            Line line3(line2.getPoint2(), Vector2{points[0].x, points[0].y});

            lines.push_back(line1);
            lines.push_back(line2); 
            lines.push_back(line3);
        }
        else if (curveType == "arc") {
            vector<Vector2> points = createArc(a, b); // Example values for center and radius
            for (size_t i = 0; i < points.size() - 1; i++) {
                Line line(points[i], points[i + 1]);
                lines.push_back(line); // Add the line to the vector of lines
                cout << points[i].x << " " << points[i].y << endl; // Debug output for points
            }
        }
        else {
            cout << "Invalid curve type!" << endl; // Debug output for invalid curve type
        }
        return lines;
    }
};

#endif // CURVEDWALL_H
#pragma once
#include <iostream>

struct Pos2D
{
    // signed integers because we can have moveDelta Pos2D objects (which can be negative)
    int8_t x, y;

    Pos2D();

    Pos2D(int8_t x, int8_t y);

    // returns true if given pos is out of bounds (< 0 or > 7)
    static bool outOfBounds(const Pos2D& pos);

    // takes a position string (ex: "e2") and returns Pos2D object representing that position
    static Pos2D getPos2D(const std::string& posString);

    // returns positive integers (ex: { -1, 4 }.abs() -> { 1, 4 })
    Pos2D abs();

    bool operator==(const Pos2D& pos);

    Pos2D operator-(const Pos2D& pos);

    Pos2D operator+(const Pos2D& pos);
};
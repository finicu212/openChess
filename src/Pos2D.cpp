#include "Pos2D.h"

Pos2D::Pos2D() : x(0), y(0) {};

Pos2D::Pos2D(int8_t x, int8_t y) : x(x), y(y) {};

bool Pos2D::outOfBounds(const Pos2D& pos)
{
    return (pos.x < 0 || pos.x > 7 || pos.y < 0 || pos.y > 7);
}

Pos2D Pos2D::getPos2D(const std::string& posString)
{
    Pos2D newPos;
    newPos.y = tolower(posString[0]) - 'a';
    newPos.x = posString[1] - 49;

    return newPos;
}

Pos2D Pos2D::abs()
{
    return Pos2D(x < 0 ? -x : x, y < 0 ? -y : y);
}

bool Pos2D::operator==(const Pos2D& pos)
{
    return (x == pos.x) && (y == pos.y);
}

Pos2D Pos2D::operator-(const Pos2D& pos)
{
    return Pos2D(x - pos.x, y - pos.y);
}

Pos2D Pos2D::operator+(const Pos2D& pos)
{
    return Pos2D(x + pos.x, y + pos.y);
}
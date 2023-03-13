#pragma once

class Rect
{
public:
    constexpr Rect(int x_, int y_, int width, int height) : x1 { x_ }, y1 { y_ }, x2 { x_ + width }, y2 { y_ + height }
    {
    }

    constexpr int x() const { return x1; }
    constexpr int y() const { return y1; }
    constexpr int width() const { return x2 - x1; }
    constexpr int height() const { return y2 - y1; }
    constexpr int bottom() const { return y2; }

private:
    int x1 = -1;
    int y1 = -1;
    int x2 = -1;
    int y2 = -1;
};

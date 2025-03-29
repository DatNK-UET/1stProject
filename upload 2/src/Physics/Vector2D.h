#ifndef VECTOR2D_H
#define VECTOR2D_H

class Vector2D {
public:
    float X, Y;

    Vector2D(float x = 0, float y = 0) : X(x), Y(y) {}

    Vector2D operator+(const Vector2D& other) const {
        return Vector2D(X + other.X, Y + other.Y);
    }

    Vector2D operator*(float scalar) const {
        return Vector2D(X * scalar, Y * scalar);
    }
};

#endif

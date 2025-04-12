#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Vector2D.h"
#include "SDL.h"

class Transform {
public:
    Transform() : m_Position(0, 0) {}

    void setPosition(const Vector2D& position) {
        m_Position = position;
    }

    float X() const { return m_Position.X; }
    float Y() const { return m_Position.Y; }

    void Log() {
        SDL_Log("Transform Position: (%f, %f)", m_Position.X, m_Position.Y);
    }

private:
    Vector2D m_Position;
};

#endif

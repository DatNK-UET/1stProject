#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "Vector2D.h"

#define FORWARD 1;
#define BACKWARD -1

#define UPWARD 1
#define DOWNWARD -1

class RigidBody {
public:
    RigidBody() : m_Position(0, 0), m_Gravity(0), m_Velocity(0, 0), m_Force(0, 0) {}

    void Update(float dt) {
        m_Velocity = m_Velocity + m_Force * dt;
        m_Velocity.Y += m_Gravity * dt;
        m_Position = m_Position + m_Velocity * dt;
    }

    void SetGravity(float gravity) { m_Gravity = gravity; }
    void ApplyForceX(float forceX) { m_Force.X = forceX; }
    void ApplyForceY(float forceY) { m_Force.Y = forceY; }
    void UnSetForce() { m_Force = Vector2D(0, 0); }

    Vector2D& Position() { return m_Position; }
    Vector2D& Velocity() { return m_Velocity; }

private:
    Vector2D m_Position;
    float m_Gravity;    // Đặt trước m_Velocity để khớp với thứ tự khởi tạo
    Vector2D m_Velocity;
    Vector2D m_Force;
};

#endif

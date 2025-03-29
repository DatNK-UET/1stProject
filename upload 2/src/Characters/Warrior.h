// Warrior.h (assumed - please verify)
#ifndef WARRIOR_H
#define WARRIOR_H

#include "Character.h"
#include "Point.h"
#include "Vector2D.h"

#define JUMP_TIME 3.0f
#define JUMP_FORCE 5.0f

class Warrior : public Character {
public:
    Warrior(Properties* props);
    ~Warrior();

    void Draw() override;
    void Update(float dt) override;
    void Clean() override;

    RigidBody* GetRigidBody() { return m_RigidBody; }
    inline Point* GetOrigin() { return m_Origin; }

private:
    bool m_IsJumping = false;
    bool m_IsGrounded = true;
    float m_JumpTime;
    float m_JumpForce;

    Collider* m_Collider;
    Animation* m_Animation;
    RigidBody* m_RigidBody;
    Point* m_Origin;
    Transform* m_Transform;
    Vector2D _LastSafePosition;  // Match the original header naming
};

#endif

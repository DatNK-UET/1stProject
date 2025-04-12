#ifndef CHARACTER_H
#define CHARACTER_H

#include "Transform.h"
#include <string>
#include "GameObject.h"

#include "RigidBody.h"   // Thêm
#include "Collider.h"    // Thêm
#include "Animation.h"   // Thêm
#include "Vector2D.h"    // Thêm



class Character : public GameObject {
public:
    Character(Properties* props) : GameObject(props) {}

    virtual ~Character() {

    }

    virtual void Draw() = 0; // Hàm ảo thuần túy
    virtual void Update(float dt) = 0; // Hàm ảo thuần túy
    virtual void Clean() = 0; // Hàm ảo thuần túy

protected:
    RigidBody* m_RigidBody = nullptr;
    Collider* m_Collider = nullptr;
    Vector2D m_LastSafePosition;
    Animation* m_Animation = nullptr;
    bool m_IsJumping = false;
    bool m_IsGrounded = true;
    float m_JumpTime = 0.0f;
    float m_JumpForce = 0.0f;
};

#endif

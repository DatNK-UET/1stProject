// Warrior.h (assumed - please verify)
#ifndef WARRIOR_H
#define WARRIOR_H

#include "Character.h"
#include "Animation.h"
#include "RigidBody.h"
#include "Point.h"
#include "Vector2D.h"
#include "Collider.h"
#include "Transform.h"
#include "SpriteAnimation.h"
#include <iostream>

#define JUMP_TIME 2.0f
#define JUMP_FORCE 2.0f

class Warrior : public Character {
public:
    Warrior(Properties* props);
    virtual ~Warrior();

    void Draw() override;
    void Update(float dt) override;
    void Clean() override;

    RigidBody* GetRigidBody() { return m_RigidBody; }
    Point* GetOrigin();

private:
    bool m_IsAttacking = false;
    bool m_IsCrounching = false;

    Collider* m_Collider;
    SpriteAnimation* m_Animation;
    RigidBody* m_RigidBody;
    Point* m_Origin;
     std::string m_CurrentState;
};

#endif

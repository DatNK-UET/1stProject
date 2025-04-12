#ifndef ENEMY_H
#define ENEMY_H

#include "Character.h"
#include "RigidBody.h"
#include "Collider.h"
#include "SeqAnimation.h"
#include "SpriteAnimation.h"
#include "Vector2D.h"

class Enemy : public Character {
public:
    Enemy(Properties* props);

virtual void Draw() override; // Sửa từ virtual void Draw()
    virtual void Clean() override; // Sửa từ virtual void Clean()
    virtual void Update(float dt) override; // Sửa từ virtual void Update(float dt)

private:
    Collider* m_Collider;
    RigidBody* m_RigidBody;
    SeqAnimation* m_Animation;
    Vector2D m_LastSafePosition;
};

#endif // ENEMY_H

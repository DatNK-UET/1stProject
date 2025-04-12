#include "Enemy.h"
#include "Camera.h"
#include "CollisionHandler.h"
#include <iostream>
#include "../Factory/ObjectFactory.h"
#include "SeqAnimation.h"
#include "GameObject.h"


static RegisterType<Enemy> enemyReg("Enemy");

Enemy::Enemy(Properties* props) : Character(props) {
    m_RigidBody = new RigidBody();
    m_RigidBody->SetGravity(3.5f);
    m_Collider = new Collider();

    m_Animation = new SeqAnimation(false);
    m_Animation->Parse("assets/animation.aml");
    m_Animation->SetCurrentSeq("boss_appear");
}

void Enemy::Draw() {
    m_Animation->DrawFrame(m_Transform->X(), m_Transform->Y(), 0.3f, 0.3f, m_Flip);
}

void Enemy::Update(float dt) {
    // X-Axis movements
    m_RigidBody->Update(dt);
    m_LastSafePosition.X = m_Transform->X();
    m_Transform->setPosition(Vector2D(m_Transform->X() + m_RigidBody->Position().X, m_Transform->Y())); // Sửa cú pháp
    m_Collider->Set(static_cast<int>(m_Transform->X()), static_cast<int>(m_Transform->Y()), 140, 100); // Ép kiểu sang int

    if (CollisionHandler::GetInstance()->MapCollision(m_Collider->Get())) {
        m_Transform->setPosition(Vector2D(m_LastSafePosition.X, m_Transform->Y()));
    }

    // Y-Axis movements
    m_RigidBody->Update(dt);
    m_LastSafePosition.Y = m_Transform->Y();
    m_Transform->setPosition(Vector2D(m_Transform->X(), m_Transform->Y() + m_RigidBody->Position().Y)); // Sửa cú pháp
    m_Collider->Set(static_cast<int>(m_Transform->X()), static_cast<int>(m_Transform->Y()), 140, 100); // Ép kiểu sang int

    if (CollisionHandler::GetInstance()->MapCollision(m_Collider->Get())) {
        m_Transform->setPosition(Vector2D(m_Transform->X(), m_LastSafePosition.Y));
    }

    m_Animation->Update(dt);

    if (m_Animation->IsEnded()) {
        m_Animation->SetRepeat(true);
        m_Animation->SetCurrentSeq("boss_attack");
    }
}

void Enemy::Clean() {
    delete m_RigidBody;
    delete m_Collider;
    delete m_Animation;
}

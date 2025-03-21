#include "Warrior.h"
#include "TextureManager.h"
#include "SDL.h"
#include "Engine.h"
#include <iostream>
#include "Input.h"
#include "SDL_image.h"

Warrior::Warrior(Properties* props) : Character(props) {
    m_Animation = new Animation();
    m_Animation->SetProps(m_TextureID, 1, 6, 100, SDL_FLIP_NONE); // 4 frame, tốc độ 200ms

    m_RigidBody = new RigidBody();
    m_RigidBody->Position() = Vector2D(m_transform->getX(), m_transform->getY());
    m_RigidBody->SetGravity(0.00f); // Trọng lực (có thể điều chỉnh)
}

Warrior::~Warrior() {
    delete m_Animation;
    delete m_RigidBody;
}

void Warrior::Draw() {
    std::cout << "Drawing at: (" << m_transform->getX() << ", " << m_transform->getY() << ")" << std::endl;
    m_Animation->Draw(m_transform->getX(), m_transform->getY(), m_Width, m_Height);
}

void Warrior::Update(float dt) {

   m_Animation->SetProps("player", 1, 4, 100, SDL_FLIP_NONE);
    m_RigidBody->UnSetForce();
   if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A)){
        m_RigidBody->ApplyForceX(-1.0f);
        m_Animation->SetProps("run", 1, 6, 100, SDL_FLIP_HORIZONTAL);
   }
   if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D)){
        m_RigidBody->ApplyForceX(1.0f);
        m_Animation->SetProps("run", 1, 6, 100, SDL_FLIP_NONE);
   }



    // Cập nhật vật lý và vị trí
    m_RigidBody->Update(dt);
    m_transform->setPosition(m_RigidBody->Position());

    // Giới hạn vị trí khi chạm đất
    if (m_transform->getY() > SCREEN_HEIGHT - 64) {
        m_transform->setPosition(Vector2D(m_transform->getX(), SCREEN_HEIGHT - 64));
        m_RigidBody->Position() = Vector2D(m_transform->getX(), m_transform->getY());
        m_RigidBody->ApplyForceY(0);
    }

    // Cập nhật hoạt ảnh
    m_Animation->Update();
}

void Warrior::Clean() {
    delete m_Animation;
    delete m_RigidBody;
    TextureManager::GetInstance()->Clean();
}

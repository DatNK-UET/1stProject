#include "Warrior.h"
#include "Animation.h"
#include "RigidBody.h"
#include "Collider.h"
#include "Transform.h"
#include "TextureManager.h"
#include "SDL.h"
#include "Engine.h"
#include <iostream>
#include "Input.h"
#include "SDL_image.h"
#include "CollisionHandler.h"
#include "Camera.h"

Warrior::Warrior(Properties* props) : Character(props) {
    m_JumpForce = JUMP_FORCE;
    m_JumpTime = JUMP_TIME;

    m_Collider = new Collider();
    m_Collider->SetBuffer(0, 0, 0, 0);

    m_Animation = new Animation();
    m_Animation->SetProps(m_TextureID, 1, 6, 100, SDL_FLIP_NONE);

    m_RigidBody = new RigidBody();
    m_RigidBody->Position() = Vector2D(100.0f, 100.0f);
    m_RigidBody->SetGravity(3.0f);

    m_Origin = new Point();
    m_Transform = new Transform();  // Default constructor
    m_Transform->setPosition(Vector2D(props->X, props->Y));  // Use setPosition
    _LastSafePosition = Vector2D(props->X, props->Y);
}

Warrior::~Warrior() {
    delete m_Animation;
    delete m_RigidBody;
    delete m_Origin;
    delete m_Transform;
    delete m_Collider;
}

void Warrior::Draw() {
    m_Animation->Draw(m_Transform->getX(), m_Transform->getY(), m_Width, m_Height);

    Vector2D cam = Camera::GetInstance()->GetPosition();
    SDL_Rect box = m_Collider->Get();

    box.x -= cam.X;
    box.y -= cam.Y;

    SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &box);
}

void Warrior::Update(float dt) {
    // Cài đặt mặc định cho hoạt ảnh
    m_Animation->SetProps("player", 1, 4, 100, SDL_FLIP_NONE);
    m_RigidBody->UnSetForce();

    // Xử lý di chuyển ngang
    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A)) {
        m_RigidBody->ApplyForceX(-1.0f);
        m_Animation->SetProps("run", 1, 6, 100, SDL_FLIP_HORIZONTAL);
    }
    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D)) {
        m_RigidBody->ApplyForceX(1.0f);
        m_Animation->SetProps("run", 1, 6, 100, SDL_FLIP_NONE);
    }

    // Xử lý nhảy
    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_SPACE) && m_IsGrounded) {
        m_IsJumping = true;
        m_IsGrounded = false;
        m_RigidBody->ApplyForceY(-m_JumpForce); // Áp dụng lực nhảy lên trên
        m_Animation->SetProps("jump", 1, 4, 150, SDL_FLIP_NONE);
    }

    // Tiếp tục áp dụng lực nhảy trong khoảng thời gian nhất định
    if (m_IsJumping && m_JumpTime > 0) {
        m_JumpTime -= dt;
        m_RigidBody->ApplyForceY(-m_JumpForce);
    } else {
        m_IsJumping = false;
        m_JumpTime = JUMP_TIME; // Reset thời gian nhảy
    }

    // Cập nhật vị trí từ RigidBody
    m_RigidBody->Update(dt);
    Vector2D newPosition = m_RigidBody->Position();
    float newX = newPosition.X;
    float newY = newPosition.Y;

    // Định nghĩa kích thước màn hình và collider
    const float SCREEN_WIDTH = 800.0f;
    const float SCREEN_HEIGHT = 600.0f;
    const float COLLIDER_WIDTH = 96.0f;
    const float COLLIDER_HEIGHT = 96.0f;

    // Kiểm tra va chạm với biên màn hình
    bool collisionDetected = false;

    // Tường trái
    if (newX < 0) {
        newX = 0;
        m_RigidBody->ApplyForceX(0.0f);
        collisionDetected = true;
    }
    // Tường phải
    if (newX + COLLIDER_WIDTH > SCREEN_WIDTH) {
        newX = SCREEN_WIDTH - COLLIDER_WIDTH;
        m_RigidBody->ApplyForceX(0.0f);
        collisionDetected = true;
    }
    // Sàn (tường dưới)
    if (newY + COLLIDER_HEIGHT > SCREEN_HEIGHT) {
        newY = SCREEN_HEIGHT - COLLIDER_HEIGHT;
        m_RigidBody->ApplyForceY(0.0f);
        m_RigidBody->UnSetForce();
        m_IsGrounded = true; // Nhân vật chạm đất
        m_IsJumping = false;
        collisionDetected = true;
    }
    // Trần (tường trên, tùy chọn)
    if (newY < 0) {
        newY = 0;
        m_RigidBody->ApplyForceY(0.0f);
        collisionDetected = true;
    }

    // Kiểm tra va chạm với tile map
    m_Collider->Set(newX, newY, COLLIDER_WIDTH, COLLIDER_HEIGHT);
    if (!collisionDetected && CollisionHandler::GetInstance()->MapCollision(m_Collider->Get())) {
        newX = _LastSafePosition.X;
        newY = _LastSafePosition.Y;
        m_RigidBody->ApplyForceX(0.0f);
        m_RigidBody->ApplyForceY(0.0f);
        m_IsGrounded = true; // Giả định va chạm từ dưới
    } else {
        _LastSafePosition = Vector2D(newX, newY); // Lưu vị trí an toàn
    }

    // Cập nhật vị trí cuối cùng
    m_Transform->setPosition(Vector2D(newX, newY));
    m_RigidBody->Position() = Vector2D(newX, newY);
    m_Collider->Set(newX, newY, COLLIDER_WIDTH, COLLIDER_HEIGHT);

    // Cập nhật hoạt ảnh khi nhảy
    if (m_IsJumping || !m_IsGrounded) {
        m_Animation->SetProps("jump", 1, 4, 150, SDL_FLIP_NONE);
    }

    // Cập nhật tâm nhân vật
    m_Origin->X = newX + m_Width / 2;
    m_Origin->Y = newY + m_Height / 2;

    // Cập nhật hoạt ảnh
    m_Animation->Update();
}
void Warrior::Clean() {
    TextureManager::GetInstance()->Clean();
}

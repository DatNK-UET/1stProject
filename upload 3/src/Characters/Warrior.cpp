#include "Warrior.h"
#include "TextureManager.h"
#include "SDL.h"
#include "Engine.h"
#include <iostream>
#include "Input.h"
#include "SDL_image.h"
#include "CollisionHandler.h"
#include "Camera.h"
#include "Collider.h"
#include "../Factory/ObjectFactory.h"
#include "SpriteAnimation.h"
#include <cmath>

static RegisterType<Warrior> warriorReg("Warrior");

Warrior::Warrior(Properties* props) : Character(props) {
    m_JumpForce = JUMP_FORCE;
    m_JumpTime = JUMP_TIME;

    m_Collider = new Collider();
    m_Collider->SetBuffer(0, 0, 0, 0);
    m_Collider->Set(m_Transform->X(), m_Transform->Y(), m_Width, m_Height);

    m_Animation = new SpriteAnimation();
    m_Animation->SetProps(m_TextureID, 1, 6, 100, SDL_FLIP_NONE);

    m_RigidBody = new RigidBody();
    m_RigidBody->Position() = Vector2D(props->X, props->Y);
    m_RigidBody->SetGravity(0.05f);

    m_Origin = new Point(props->X + m_Width / 2, props->Y + m_Height / 2);
    m_Transform->setPosition(Vector2D(props->X, props->Y));
    m_LastSafePosition = Vector2D(props->X, props->Y);

    std::cout << "Warrior initialized at origin: (" << m_Origin->X << ", " << m_Origin->Y << ")" << std::endl;
}

Warrior::~Warrior() {
    delete m_Animation;
    delete m_RigidBody;
    delete m_Origin;
    delete m_Transform;
    delete m_Collider;
}

void Warrior::Draw() {
    Vector2D cam = Camera::GetInstance()->GetPosition();
    m_Animation->Draw(m_Transform->X() - cam.X, m_Transform->Y() - cam.Y, m_Width, m_Height);

    SDL_Rect box = m_Collider->Get();
    box.x -= cam.X;
    box.y -= cam.Y;
    SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &box);
}

void Warrior::Update(float dt) {
    m_RigidBody->UnSetForce();

    std::string newState = "idle";

    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A)) {
        m_RigidBody->ApplyForceX(-0.5f);
        newState = (m_IsGrounded) ? "run" : "jump";
        m_Flip = SDL_FLIP_HORIZONTAL;
    }
    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D)) {
        m_RigidBody->ApplyForceX(0.5f);
        newState = (m_IsGrounded) ? "run" : "jump";
        m_Flip = SDL_FLIP_NONE;
    }
    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_J) && m_IsGrounded) {
        m_IsJumping = true;
        m_IsGrounded = false;
        m_RigidBody->ApplyForceY(-m_JumpForce);
        newState = "jump";
    }
    if (m_IsJumping && m_JumpTime > 0) {
        m_JumpTime -= dt;
        m_RigidBody->ApplyForceY(-m_JumpForce);
    } else if (m_IsJumping) {
        m_IsJumping = false;
        m_JumpTime = JUMP_TIME;
        m_RigidBody->ApplyForceY(0);
    }

    m_RigidBody->Update(dt);

    const float maxSpeed = 5.0f;
    Vector2D velocity = m_RigidBody->Velocity();
    if (velocity.X > maxSpeed) velocity.X = maxSpeed;
    if (velocity.X < -maxSpeed) velocity.X = -maxSpeed;
    m_RigidBody->Velocity() = velocity;

    if (m_IsGrounded) {
        float friction = 0.85f;
        velocity.X *= friction;
        if (std::abs(velocity.X) < 0.01f) velocity.X = 0;
        m_RigidBody->Velocity() = velocity;
    }

    Vector2D currentPosition(m_Transform->X(), m_Transform->Y());
    Vector2D newPosition = currentPosition + (m_RigidBody->Velocity() * dt);
    const int tileSize = 32;

    m_Collider->Set(newPosition.X, currentPosition.Y, 64, 64);
    if (CollisionHandler::GetInstance()->MapCollision(m_Collider->Get())) {
        if (velocity.X > 0) {
            int tileX = static_cast<int>(newPosition.X + 64) / tileSize;
            newPosition.X = tileX * tileSize - 64 - 0.1f;
        } else if (velocity.X < 0) {
            int tileX = static_cast<int>(newPosition.X) / tileSize;
            newPosition.X = tileX * tileSize + tileSize + 0.1f;
        }
        velocity.X = 0;
        m_RigidBody->Velocity() = velocity;
    }

    m_Collider->Set(newPosition.X, newPosition.Y, 64, 64);
    if (CollisionHandler::GetInstance()->MapCollision(m_Collider->Get())) {
        if (velocity.Y > 0) {
            int tileY = static_cast<int>(newPosition.Y + 64) / tileSize;
            newPosition.Y = tileY * tileSize - 64 - 0.1f;
            m_IsGrounded = true;
            m_IsJumping = false;
            m_JumpTime = JUMP_TIME;
        } else if (velocity.Y < 0) {
            int tileY = static_cast<int>(newPosition.Y) / tileSize;
            newPosition.Y = tileY * tileSize + tileSize + 0.1f;
            m_IsJumping = false;
            m_JumpTime = JUMP_TIME;
        }
        velocity.Y = 0;
        m_RigidBody->Velocity() = velocity;
    } else {
        m_IsGrounded = false;
    }

    const int mapWidth = 1920;
    const int mapHeight = 640;
    if (newPosition.X < 0) newPosition.X = 0;
    if (newPosition.X + m_Width > mapWidth) newPosition.X = mapWidth - m_Width;
    if (newPosition.Y < 0) newPosition.Y = 0;
    if (newPosition.Y + m_Height > mapHeight) newPosition.Y = mapHeight - m_Height;

    m_Transform->setPosition(newPosition);
    m_RigidBody->Position() = newPosition;
    m_LastSafePosition = newPosition;

    if (newState != m_CurrentState) {
        m_CurrentState = newState;
        if (m_CurrentState == "idle") {
            m_Animation->SetProps("player", 1, 4, 200, m_Flip);
        } else if (m_CurrentState == "run") {
            m_Animation->SetProps("run", 1, 6, 150, m_Flip);
        } else if (m_CurrentState == "jump") {
            m_Animation->SetProps("jump", 1, 4, 250, m_Flip);
        }
    }
    m_Animation->Update(dt);

    std::cout << "Before updating origin - Transform: (" << m_Transform->X() << ", " << m_Transform->Y() << ")" << std::endl;

    m_Origin->X = m_Transform->X() + m_Width / 2;
    m_Origin->Y = m_Transform->Y() + m_Height / 2;
    std::cout << "Warrior origin updated: (" << m_Origin->X << ", " << m_Origin->Y << ")" << std::endl;
}

void Warrior::Clean() {
    TextureManager::GetInstance()->Clean();
}

Point* Warrior::GetOrigin() {
    std::cout << "GetOrigin called, returning address: " << m_Origin << ", Position: (" << m_Origin->X << ", " << m_Origin->Y << ")" << std::endl;
    return m_Origin;
}

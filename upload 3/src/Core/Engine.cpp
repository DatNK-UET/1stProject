#include "Engine.h"
#include "TextureManager.h"
#include "MapParser.h"
#include "GameObject.h"
#include "Warrior.h"
#include "Enemy.h"
#include "Camera.h"
#include "Timer.h"
#include "Input.h"
#include "../Factory/ObjectFactory.h"
#include <iostream>

Engine* Engine::s_Instance = nullptr;

Engine::Engine() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cout << "SDL_Init failed: " << SDL_GetError() << std::endl;
        m_IsRunning = false;
        return;
    }

    m_Window = SDL_CreateWindow("SoftEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if (!m_Window) {
        std::cout << "SDL_CreateWindow failed: " << SDL_GetError() << std::endl;
        m_IsRunning = false;
        return;
    }

    m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED);
    if (!m_Renderer) {
        std::cout << "SDL_CreateRenderer failed: " << SDL_GetError() << std::endl;
        m_IsRunning = false;
        return;
    }

    if (IMG_Init(IMG_INIT_PNG) == 0) {
        std::cout << "IMG_Init failed: " << IMG_GetError() << std::endl;
        m_IsRunning = false;
        return;
    }

    m_IsRunning = true;
    m_LevelMap = nullptr;
}

Engine::~Engine() {
    Clean();
}

bool Engine::Init() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cout << "SDL_Init failed: " << SDL_GetError() << std::endl;
        return false;
    }

    m_Window = SDL_CreateWindow("SoftEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if (!m_Window) {
        std::cout << "SDL_CreateWindow failed: " << SDL_GetError() << std::endl;
        return false;
    }
    std::cout << "Window created with size: (" << SCREEN_WIDTH << ", " << SCREEN_HEIGHT << ")" << std::endl;

    m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED);
    if (!m_Renderer) {
        std::cout << "SDL_CreateRenderer failed: " << SDL_GetError() << std::endl;
        return false;
    }

    if (IMG_Init(IMG_INIT_PNG) == 0) {
        std::cout << "IMG_Init failed: " << IMG_GetError() << std::endl;
        return false;
    }

    if (!MapParser::GetInstance()->Load()) {
        std::cout << "Failed to load map" << std::endl;
        return false;
    }

    m_LevelMap = MapParser::GetInstance()->GetMap("MAP");
    if (m_LevelMap == nullptr) {
        std::cout << "Failed to get map 'MAP'" << std::endl;
        return false;
    }

    Camera::GetInstance()->SetSceneLimit(Vector2D(m_LevelMap->GetWidth(), m_LevelMap->GetHeight()));
    std::cout << "Camera scene limit set to: (" << m_LevelMap->GetWidth() << ", " << m_LevelMap->GetHeight() << ")" << std::endl;

    TextureManager::GetInstance()->ParseTextures("assets/textures.xml");
    GameObject* player = ObjectFactory::GetInstance()->CreateObject("Warrior", new Properties("player_idle", 100, 200, 64, 64));
    m_GameObjects.push_back(player);

    Point* origin = player->GetOrigin();
    if (origin) {
        std::cout << "Setting camera target to Warrior origin at address: " << origin << ", Position: (" << origin->X << ", " << origin->Y << ")" << std::endl;
        Camera::GetInstance()->SetTarget(origin);
    } else {
        std::cout << "Error: Warrior origin is nullptr!" << std::endl;
    }

    m_IsRunning = true;
    return true;
}

void Engine::Render() {
    SDL_SetRenderDrawColor(m_Renderer, 124, 218, 254, 255);
    SDL_RenderClear(m_Renderer);

    TextureManager::GetInstance()->Draw("bg", 0, 0, 2100, 1050, 1, 1, 0.4);
    if (m_LevelMap) m_LevelMap->Render();

    for (auto* obj : m_GameObjects) {
        obj->Draw();
    }

    SDL_RenderPresent(m_Renderer);
}

void Engine::Update() {
    float dt = Timer::GetInstance()->GetDeltaTime();

    int warriorCount = 0;
    for (auto* obj : m_GameObjects) {
        if (dynamic_cast<Warrior*>(obj)) {
            warriorCount++;
        }
    }
    if (warriorCount > 1) {
        std::cout << "Warning: Multiple Warriors detected! Count: " << warriorCount << std::endl;
    }

    Camera::GetInstance()->Update(dt);
    if (m_LevelMap) m_LevelMap->Update();
    for (auto* obj : m_GameObjects) {
        obj->Update(dt);
    }
}

void Engine::Events() {
    Input::GetInstance()->Listen();
}

bool Engine::Clean() {
    for (auto* obj : m_GameObjects) {
        obj->Clean();
        delete obj;
    }
    m_GameObjects.clear();

    TextureManager::GetInstance()->Clean();
    MapParser::GetInstance()->Clean();

    SDL_DestroyRenderer(m_Renderer);
    SDL_DestroyWindow(m_Window);
    IMG_Quit();
    SDL_Quit();
    return true;
}

void Engine::Run() {
    const float targetFrameTime = 1.0f / 60.0f;
    while (m_IsRunning) {
        float startTime = SDL_GetTicks() / 1000.0f;

        Events();
        Update();
        Render();

        float frameTime = (SDL_GetTicks() / 1000.0f) - startTime;
        if (frameTime < targetFrameTime) {
            SDL_Delay((targetFrameTime - frameTime) * 1000.0f);
        }
    }
}

void Engine::Quit() {
    m_IsRunning = false;
}

void Engine::PushState(GameState* current) {
    m_States.push_back(current);
}

void Engine::PopState() {
    if (!m_States.empty()) {
        delete m_States.back();
        m_States.pop_back();
    }
}

void Engine::ChangeState(GameState* target) {
    if (!m_States.empty()) {
        delete m_States.back();
        m_States.pop_back();
    }
    m_States.push_back(target);
}

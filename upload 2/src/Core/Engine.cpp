#include "Engine.h"
#include "SDL.h"
#include "SDL_image.h"
#include "TextureManager.h"
#include "Warrior.h"
#include "Transform.h"
#include "Input.h"
#include "Timer.h"
#include "MapParser.h"
#include <iostream>
#include "Camera.h"
using namespace std;

Engine* Engine::s_Instance = nullptr;
Warrior* player = nullptr;

bool Engine::Init() {
    cout << "Initializing SDL..." << endl;
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
        return false;
    }

    cout << "Initializing SDL_image..." << endl;
    if (IMG_Init(IMG_INIT_PNG) == 0) {
        SDL_Log("Failed to initialize SDL_image: %s", SDL_GetError());
        return false;
    }

    cout << "Creating window..." << endl;
    m_Window = SDL_CreateWindow("Soft Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if (m_Window == nullptr) {
        SDL_Log("Failed to create Window: %s", SDL_GetError());
        return false;
    }

    cout << "Creating renderer..." << endl;
    m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (m_Renderer == nullptr) {
        SDL_Log("Failed to create Renderer: %s", SDL_GetError());
        return false;
    }

    cout << "Loading map..." << endl;
    if (!MapParser::GetInstance()->Load()) {
        cout << "Failed to load map" << endl;
        return false;
    }
    m_LevelMap = MapParser::GetInstance()->GetMap("MAP");
    if (m_LevelMap == nullptr) {
        cout << "Error: Map 'MAP' not found in MapParser" << endl;
        return false;
    }

    cout << "Loading textures..." << endl;
    if (!TextureManager::GetInstance()->Load("player", "assets/breathing.png")) {
        cout << "Failed to load texture: assets/breathing.png" << endl;
        return false;
    }
    if (!TextureManager::GetInstance()->Load("run", "assets/running.png")) {
        cout << "Failed to load texture: assets/running.png" << endl;
        return false;
    }
    if (!TextureManager::GetInstance()->Load("jump", "assets/jump.png")) {
        cout << "Failed to load texture: assets/jump.png" << endl;
        return false;
    }
       if (!TextureManager::GetInstance()->Load("bg", "assets/bg.png")) {
        cout << "Failed to load texture: assets/bg.png" << endl;
        return false;
    }

    cout << "Initializing Warrior..." << endl;
    player = new Warrior(new Properties("player", 50, 50, 64, 64));

    cout << "Setting camera target..." << endl;
    Camera::GetInstance()->SetTarget(player->GetOrigin());
    cout << "Initialization complete!" << endl;
    return m_IsRunning = true;
}

void Engine::Update() {
    float dt = Timer::GetInstance()->GetDeltaTime();
    m_LevelMap->Update();
    player->Update(dt);
    Camera::GetInstance()->Update(dt);
}

void Engine::Render() {
    SDL_SetRenderDrawColor(m_Renderer, 124, 218, 254, 255);
    SDL_RenderClear(m_Renderer);

    TextureManager::GetInstance()->Draw("bg", 0, 0 , 1920, 960);
    m_LevelMap->Render();
    player->Draw();
    SDL_RenderPresent(m_Renderer);
}

void Engine::Events() {
    Input::GetInstance()->Listen();
}

bool Engine::Clean() {
    TextureManager::GetInstance()->Clean();
    SDL_DestroyRenderer(m_Renderer);
    SDL_DestroyWindow(m_Window);
    IMG_Quit();
    SDL_Quit();
    return true;
}

void Engine::Quit() {
    m_IsRunning = false;
}

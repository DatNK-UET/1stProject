#include "Play.h"
#include "Menu.h"
#include "TextureManager.h"
#include "MapParser.h"
#include "CollisionHandler.h"
#include "Camera.h"
#include "Warrior.h"
#include "Input.h"

Play::Play() {

}

bool Play::Init() {
    m_EditMode = false;
    m_Ctxt = Engine::GetInstance()->GetRenderer();

    TextureManager::GetInstance()->ParseTextures("assets/textures.xml");
    if (!MapParser::GetInstance()->Load()) {
        std::cout << "Failed to load map" << std::endl;
        return false;
    }

    m_LevelMap = MapParser::GetInstance()->GetMap("MAP");
    TileLayer* collisionLayer = (TileLayer*)m_LevelMap->GetLayers().back();
    int tilesize = collisionLayer->GetTileSize();
    int width = collisionLayer->GetColCount() * tilesize; // 60 * 32 = 1920
    int height = collisionLayer->GetRowCount() * tilesize; // 20 * 32 = 640

    // Thiết lập giới hạn cảnh cho camera
    Camera::GetInstance()->SetSceneLimit(Vector2D(width, height));
    std::cout << "Scene limit set to: (" << width << ", " << height << ")" << std::endl;
    CollisionHandler::GetInstance()->SetCollisionMap(collisionLayer->GetTilemap(), tilesize);

    // Tạo warrior và thiết lập target cho camera
    Warrior* warrior = new Warrior(new Properties("player_idle", 100, 200, 136, 96, SDL_FLIP_NONE));
    Point* origin = warrior->GetOrigin();
    std::cout << "Initial warrior origin address: " << origin
              << ", Position: (" << origin->X << ", " << origin->Y << ")" << std::endl;
    Camera::GetInstance()->SetTarget(origin);
    m_GameObjects.push_back(warrior);

    // Kiểm tra và log target của camera sau khi thiết lập
    Point* currentTarget = Camera::GetInstance()->GetTarget();
    if (currentTarget == nullptr) {
        std::cout << "Error: Camera target is nullptr after SetTarget!" << std::endl;
    } else {
        std::cout << "Camera target after SetTarget: " << currentTarget
                  << ", Position: (" << currentTarget->X << ", " << currentTarget->Y << ")" << std::endl;
    }

    std::cout << "play initialized!" << std::endl;
    return true;
}

void Play::Render() {
    SDL_SetRenderDrawColor(m_Ctxt, 48, 96, 130, 255);
    SDL_RenderClear(m_Ctxt);

    // Log vị trí camera khi render
    Vector2D cam = Camera::GetInstance()->GetPosition();
    std::cout << "Camera offset: (" << cam.X << ", " << cam.Y << ")" << std::endl;

    m_LevelMap->Render(-cam.X, -cam.Y);

    for (auto* gameobj : m_GameObjects) {
        gameobj->Draw();
    }

    SDL_RenderPresent(m_Ctxt);
}

void Play::Update() {
    Events();

    if (m_EditMode) {
        float dt = Timer::GetInstance()->GetDeltaTime();
        for (auto* gameobj : m_GameObjects) {
            gameobj->Update(dt);
        }
        Camera::GetInstance()->Update(dt);
        m_LevelMap->Update();
    }
}

void Play::Events() {
    if (m_EditMode && Input::GetInstance()->GetKeyDown(SDL_SCANCODE_ESCAPE)) {
        m_EditMode = !m_EditMode;
    }
    if (m_EditMode && Input::GetInstance()->GetKeyDown(SDL_SCANCODE_F5)) {
        m_EditMode = false;
    }
    SDL_Delay(100);
}

bool Play::Exit() {
    m_LevelMap->Update();
    delete m_LevelMap;

    for (auto*gameobj : m_GameObjects) {
        gameobj->Clean();
        delete gameobj;
    }

    m_GameObjects.clear();
    TextureManager::GetInstance()->Clean();
    std::cout << "exit play" << std::endl;
    return true;
}

// Callback actions
void Play::OpenMenu() {
    Engine::GetInstance()->ChangeState(new Menu());
}

void Play::PauseGame() {
    // Có thể thêm logic để tạm dừng game.
}

#ifndef ENGINE_H
#define ENGINE_H

#include "SDL.h"
#include "GameMap.h"

const int SCREEN_WIDTH = 800;  // Dòng 7
const int SCREEN_HEIGHT = 600;  // Dòng 8

class Warrior;
class TextureManager;
class Camera;
class CollisionHandler;
class MapParser;
class Timer;
class Input;

class Engine {
public:
    static Engine* GetInstance() {
        return s_Instance = (s_Instance != nullptr) ? s_Instance : new Engine();
    }

    bool Init();
    void Update();
    void Render();
    void Events();
    bool Clean();
    void Quit();

    inline SDL_Renderer* GetRenderer() { return m_Renderer; }
    inline bool IsRunning() { return m_IsRunning; }
    inline GameMap* GetMap() { return m_LevelMap; }

private:
    Engine() {}
    bool m_IsRunning;
    SDL_Window* m_Window;
    SDL_Renderer* m_Renderer;
    GameMap* m_LevelMap;
    static Engine* s_Instance;
};

#endif // ENGINE_H

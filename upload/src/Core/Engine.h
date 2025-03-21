#ifndef ENGINE_H
#define ENGINE_H

#include "SDL.h"

#define SCREEN_WIDTH 800  // Định nghĩa chiều rộng màn hình
#define SCREEN_HEIGHT 600 // Định nghĩa chiều cao màn hình

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

    SDL_Renderer* GetRenderer() { return m_Renderer; }
    bool IsRunning() { return m_IsRunning; } // Thêm getter cho m_IsRunning

private:
    Engine() {}
    bool m_IsRunning;
    SDL_Window* m_Window;
    SDL_Renderer* m_Renderer;
    static Engine* s_Instance;
};

#endif

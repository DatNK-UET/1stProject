#ifndef INPUT_H
#define INPUT_H

#include "SDL.h"

class Input {
public:
    static Input* GetInstance() {
        return s_Instance = (s_Instance != nullptr) ? s_Instance : new Input();
    }

    void Listen();
    bool GetKeyDown(SDL_Scancode key);

private:
    Input();
    void KeyDown();
    void KeyUp();

    const Uint8* m_KeyStates;
    static Input* s_Instance;
};

#endif

#ifndef PLAY_H
#define PLAY_H

#include <iostream>
#include "GameMap.h"
#include "GameObject.h"
#include "GameState.h"
#include "Enemy.h"
#include "Warrior.h"
#include "Timer.h"
#include "Menu.h"
#include "Input.h"
#include "Camera.h"
#include "MapParser.h"
#include "TileLayer.h"
#include "../Factory/ObjectFactory.h"
#include "GameObject.h"
#include "CollisionHandler.h"
#include "SDL.h"

class Play : public GameState {
public:
    Play();

    void Events();
    virtual bool Init();
    virtual bool Exit();
    virtual void Update();
    virtual void Render();

    // Inline
    inline GameMap* GetMap() { return m_LevelMap; }

private:
    static void OpenMenu();
    static void PauseGame();

private:
    bool m_EditMode;
    GameMap* m_LevelMap;
    std::vector<GameObject*> m_GameObjects;
    SDL_Renderer* m_Ctxt = nullptr;
};

#endif // PLAY_H

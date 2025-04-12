#ifndef STATES_H
#define STATES_H

#include <SDL.h>

class GameState {
public:
    virtual bool Init() = 0;
    virtual bool Exit() = 0;
    virtual void Update() = 0;
    virtual void Render() = 0;
    virtual ~GameState() = default;

protected:
    SDL_Renderer* m_Ctxt;

};

#endif // STATES_H

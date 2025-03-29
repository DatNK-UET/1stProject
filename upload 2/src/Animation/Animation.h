#ifndef ANIMATION_H
#define ANIMATION_H

#include "TextureManager.h"  // Di chuyển vào trong include guards
#include <string>
#include "SDL.h"

class Animation {
public:
    Animation();

    void Update();
    void Draw(float x, float y, int spriteWidth, int spriteHeight);
    void SetProps(std::string textureID, int spriteRow, int frameCount, int animSpeed, SDL_RendererFlip flip);

private:
    std::string m_TextureID;
    int m_SpriteRow;
    int m_SpriteFrame;
    int m_AnimSpeed;
    int m_FrameCount;
    SDL_RendererFlip m_Flip;
};

#endif

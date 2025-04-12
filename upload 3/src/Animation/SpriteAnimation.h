#ifndef SPRITEANIMATION_H
#define SPRITEANIMATION_H

#include <string>
#include "SDL.h"
#include "Animation.h"

class SpriteAnimation : public Animation {
public:
    SpriteAnimation(bool repeat = true) : Animation(repeat), m_ElapsedTime(0.0f) {}

    virtual void Update(float dt) override;
    void Draw(float x, float y, int spriteWidth, int spriteHeight,
              float xScale = 1, float yScale = 1,
              SDL_RendererFlip flip = SDL_FLIP_NONE);
    void SetProps(const std::string& textureID, int spriteRow, int frameCount, int speed, SDL_RendererFlip flip = SDL_FLIP_NONE);

    int GetCurrFrame() const { return m_CurrentFrame; }
    int GetCurrSpriteRow() const { return m_SpriteRow; }

    void SetSpriteRow(int row) { m_SpriteRow = row; }
    void IncrSpriteRow() { ++m_SpriteRow; }
    void DecrSpriteRow() { --m_SpriteRow; }

private:
    float m_ElapsedTime;
    int m_Speed;
    int m_SpriteRow;
    int m_FrameCount;
    std::string m_TextureID;
    SDL_RendererFlip m_Flip;

};

#endif // SPRITEANIMATION_H

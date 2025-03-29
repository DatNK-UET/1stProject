#include "Animation.h"
#include "TextureManager.h"

Animation::Animation() {
    m_SpriteRow = 0;
    m_SpriteFrame = 0;
    m_AnimSpeed = 0;
    m_FrameCount = 0;
    m_TextureID = "";
    m_Flip = SDL_FLIP_NONE;
}

void Animation::Update() {
    m_SpriteFrame = (SDL_GetTicks() / m_AnimSpeed) % m_FrameCount;
}

void Animation::Draw(float x, float y, int spriteWidth, int spriteHeight) {
    TextureManager::GetInstance()->DrawFrame(m_TextureID, x, y, spriteWidth, spriteHeight, m_SpriteRow, m_SpriteFrame, m_Flip);
}

void Animation::SetProps(std::string textureID, int spriteRow, int frameCount, int animSpeed, SDL_RendererFlip flip) {
    m_TextureID = textureID;
    m_SpriteRow = spriteRow;
    m_FrameCount = frameCount;
    m_AnimSpeed = animSpeed;
    m_Flip = flip;
    m_SpriteFrame = 0;
}

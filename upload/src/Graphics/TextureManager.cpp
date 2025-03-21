#include "TextureManager.h"
#include "Engine.h"
#include "SDL_image.h"

TextureManager* TextureManager::s_Instance = nullptr;

bool TextureManager::Load(std::string id, std::string filename) {
    SDL_Surface* surface = IMG_Load(filename.c_str());
    if (surface == nullptr) {
        SDL_Log("Failed to load texture: %s, %s", filename.c_str(), SDL_GetError());
        return false;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(Engine::GetInstance()->GetRenderer(), surface);
    SDL_FreeSurface(surface);

    if (texture == nullptr) {
        SDL_Log("Failed to create texture: %s", SDL_GetError());
        return false;
    }

    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    m_TextureMap[id] = texture;
    return true;
}

void TextureManager::Draw(std::string id, int x, int y, int width, int height, SDL_RendererFlip flip) {
    SDL_Rect dstRect = {x - width / 2, y - height / 2, width, height};
    SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_TextureMap[id], nullptr, &dstRect, 0, nullptr, flip);
}

void TextureManager::DrawFrame(std::string id, int x, int y, int width, int height, int row, int frame, SDL_RendererFlip flip) {
    SDL_Rect srcRect = {frame * width, (row - 1) * height, width, height}; // Cắt frame từ spritesheet
    SDL_Rect dstRect = {x - width / 2, y - height / 2, width, height};     // Vẽ tại vị trí (x, y), căn giữa
    SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_TextureMap[id], &srcRect, &dstRect, 0, nullptr, flip);
}

void TextureManager::Clean() {
    for (auto& pair : m_TextureMap) {
        SDL_DestroyTexture(pair.second);
    }
    m_TextureMap.clear();
}

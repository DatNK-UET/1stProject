#include "TextureManager.h"
#include "Engine.h"
#include "SDL_image.h"
#include "Camera.h"
#include <cmath>
#include <iostream>
#include "../Vendor/tinyxml2/tinyxml2.h"

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

void TextureManager::Draw(std::string id, int x, int y, int width, int height,float scaleX , float scaleY , float scrollRatio, SDL_RendererFlip flip) {
    if (m_TextureMap.find(id) == m_TextureMap.end()) {
        std::cout << "Error: Texture '" << id << "' not found!" << std::endl;
        return;
    }
    Vector2D cam = Camera::GetInstance()->GetPosition()*scrollRatio;
    SDL_Rect dstRect = {
        static_cast<int>(std::round(x - cam.X)),
        static_cast<int>(std::round(y - cam.Y)),
        static_cast<int>(width*scaleX),
        static_cast<int>(height*scaleY)
    };
    SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_TextureMap[id], nullptr, &dstRect, 0, nullptr, flip);
}

void TextureManager::DrawFrame(std::string id, int x, int y, int width, int height, int row, int frame, SDL_RendererFlip flip) {
    if (m_TextureMap.find(id) == m_TextureMap.end()) {
        std::cout << "Error: Texture '" << id << "' not found!" << std::endl;
        return;
    }
    Vector2D cam = Camera::GetInstance()->GetPosition();
    SDL_Rect srcRect = {frame * width, (row - 1) * height, width, height};
    SDL_Rect dstRect = {
        static_cast<int>(x - cam.X),
        static_cast<int>(y - cam.Y),
        width,
        height
    };
    SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_TextureMap[id], &srcRect, &dstRect, 0, nullptr, flip);
}

void TextureManager::DrawTile(std::string tilesetID, int tileSize, int x, int y, int row, int frame, SDL_RendererFlip flip) {
    if (m_TextureMap.find(tilesetID) == m_TextureMap.end()) {
        std::cout << "Error: Tileset '" << tilesetID << "' not found!" << std::endl;
        return;
    }
    SDL_Rect srcRect = {frame * tileSize, row * tileSize, tileSize, tileSize};
    Vector2D cam = Camera::GetInstance()->GetPosition();
    SDL_Rect dstRect = {
        static_cast<int>(std::round(x - cam.X)),
        static_cast<int>(std::round(y - cam.Y)),
        tileSize,
        tileSize
    };
    SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_TextureMap[tilesetID], &srcRect, &dstRect, 0, nullptr, flip);
}

void TextureManager::Clean() {
    for (auto& pair : m_TextureMap) {
        SDL_DestroyTexture(pair.second);
    }
    m_TextureMap.clear();
}

bool TextureManager::ParseTextures(const std::string& source) {
    tinyxml2::XMLDocument xml;
    if (xml.LoadFile(source.c_str()) != tinyxml2::XML_SUCCESS) {
        std::cout << "Failed to load: " << source << std::endl;
        return false;
    }

    tinyxml2::XMLElement* root = xml.RootElement();
    for (tinyxml2::XMLElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
        if (e->Value() == std::string("texture")) {
            std::string id = e->Attribute("id");
            std::string src = e->Attribute("source");
            Load(id, src);
        }
    }
    std::cout << "Textures Parse success!" << std::endl;
    return true;
}

void TextureManager::Drop(const std::string& id) {
    SDL_DestroyTexture(m_TextureMap[id]);
    m_TextureMap.erase(id);
}



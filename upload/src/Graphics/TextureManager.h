#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <string>
#include <map>
#include "SDL.h"

class TextureManager {
public:
    static TextureManager* GetInstance() {
        return s_Instance = (s_Instance != nullptr) ? s_Instance : new TextureManager();
    }

    bool Load(std::string id, std::string filename);
    void Draw(std::string id, int x, int y, int width, int height, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void DrawFrame(std::string id, int x, int y, int width, int height, int row, int frame, SDL_RendererFlip flip);
    void Clean();

private:
    TextureManager() {}
    std::map<std::string, SDL_Texture*> m_TextureMap;
    static TextureManager* s_Instance;
};

#endif

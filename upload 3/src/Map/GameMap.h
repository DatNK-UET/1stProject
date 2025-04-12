#ifndef GAMEMAP_H
#define GAMEMAP_H

#include <vector>
#include "Layer.h"

class GameMap {
public:
    GameMap() = default;

    void Render(float offsetX = 0, float offsetY = 0) {
        for (auto* layer : m_MapLayers) {
            layer->Render(offsetX, offsetY);
        }
    }

    void Update() {
        for (auto* layer : m_MapLayers) {
            layer->Update();
        }
    }

    std::vector<Layer*> GetLayers() const {
        return m_MapLayers;
    }

    int GetWidth() const { return m_Width; }
    int GetHeight() const { return m_Height; }

    void SetSize(int width, int height) {
        m_Width = width;
        m_Height = height;
    }

private:
    friend class MapParser;
    std::vector<Layer*> m_MapLayers;
    int m_Width = 0;
    int m_Height = 0;
};

#endif

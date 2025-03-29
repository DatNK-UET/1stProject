#ifndef GAMEMAP_H
#define GAMEMAP_H

#include <vector>
#include "Layer.h"

class GameMap {
public:
    GameMap() = default;

    void Render() {
        for (auto* layer : m_MapLayers) {
            layer->Render();
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

private:
    friend class MapParser;
    std::vector<Layer*> m_MapLayers;
};

#endif // GAMEMAP_H

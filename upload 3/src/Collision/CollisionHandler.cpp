#include "CollisionHandler.h"
#include "Engine.h"
#include "MapParser.h"

CollisionHandler* CollisionHandler::s_Instance = nullptr;

CollisionHandler::CollisionHandler() {
    m_CollisionLayer = (TileLayer*)MapParser::GetInstance()->GetMap("MAP")->GetLayers().front();
    m_CollisionTilemap = m_CollisionLayer->GetTilemap();
}

bool CollisionHandler::CheckCollision(SDL_Rect a, SDL_Rect b) {
    bool x_overlaps = (a.x + a.w > b.x) && (a.x < b.x + b.w);
    bool y_overlaps = (a.y + a.h > b.y) && (a.y < b.y + b.h);
    return (x_overlaps && y_overlaps);
}

bool CollisionHandler::MapCollision(SDL_Rect a) {
    const int tileSize = 32;
    const int rowCount = 20;
    const int colCount = 60;

    int left_tile = a.x / tileSize;
    int right_tile = (a.x + a.w) / tileSize;
    int top_tile = a.y / tileSize;
    int bottom_tile = (a.y + a.h) / tileSize;

    left_tile = std::max(0, left_tile);
    right_tile = std::min(colCount, right_tile);
    top_tile = std::max(0, top_tile);
    bottom_tile = std::min(rowCount, bottom_tile);

    for (int i = left_tile; i <= right_tile; ++i) {
        for (int j = top_tile; j <= bottom_tile; ++j) {
            if (m_CollisionTilemap[j][i] > 0) {
                return true;
            }
        }
    }




    return false;
}

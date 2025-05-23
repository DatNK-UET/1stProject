#include "TileLayer.h"
#include "TextureManager.h"
#include "Camera.h"
#include <iostream>

TileLayer::TileLayer(int tilesize, int rowcount, int colcount, TileMap tilemap, TilesetList tilesets)
    : m_TileSize(tilesize), m_RowCount(rowcount), m_ColCount(colcount), m_Tilemap(tilemap), m_Tilesets(tilesets) {
    for (unsigned int i = 0; i < m_Tilesets.size(); i++) {
        if (!TextureManager::GetInstance()->Load(m_Tilesets[i].Name, "assets/maps/" + m_Tilesets[i].Source)) {
            std::cout << "Failed to load tileset: " << m_Tilesets[i].Name << " (" << "assets/maps/" + m_Tilesets[i].Source << ")" << std::endl;
            // Có thể thêm xử lý lỗi ở đây, ví dụ: thoát chương trình hoặc bỏ qua tileset
        }
    }
}

void TileLayer::Render() {
    for (unsigned int i = 0; i < m_RowCount; i++) {
        for (unsigned int j = 0; j < m_ColCount; j++) {
            int tileID = m_Tilemap[i][j];
            int index = 0;
            if (tileID == 0) continue;
            if (m_Tilesets.size() > 1) {
                for (unsigned int k = 1; k < m_Tilesets.size(); k++) {
                    if (tileID >= m_Tilesets[k].FirstID && tileID <= m_Tilesets[k].LastID) {
                        tileID = tileID + m_Tilesets[k].FirstID - 1;
                        index = k;
                        break;
                    }
                }
            }

            int row = (tileID - m_Tilesets[index].FirstID) / m_Tilesets[index].ColCount;
            int frame = (tileID - m_Tilesets[index].FirstID) % m_Tilesets[index].ColCount;
            TextureManager::GetInstance()->DrawTile(m_Tilesets[index].Name, m_Tilesets[index].TileSize, j * m_TileSize, i * m_TileSize, row, frame, SDL_FLIP_NONE);        }
    }
}

void TileLayer::Update() {
}

#include "MapParser.h"
#include <iostream>
#include <sstream>

using namespace tinyxml2; // Chỉ dùng trong file .cpp

MapParser* MapParser::s_Instance = nullptr;

bool MapParser::Load() {
    if (!Parse("MAP", "assets/maps/map.tmx"))
        return false;
    return true;
}

void MapParser::Clean() {
    std::map<std::string, GameMap*> ::iterator it;
    for (it = m_Mapdicts.begin(); it != m_Mapdicts.end(); it++) {
        it->second = nullptr;
    }
    m_Mapdicts.clear();
}

bool MapParser::Parse(std::string id, std::string source) {
    XMLDocument xml;
    if (xml.LoadFile(source.c_str()) != XML_SUCCESS) {
        std::cerr << "Failed to load: " << source << std::endl;
        return false;
    }

    XMLElement* root = xml.RootElement();
    int rowcount, colcount, tilesize = 0;

    root->QueryIntAttribute("width", &colcount);
    root->QueryIntAttribute("height", &rowcount);
    root->QueryIntAttribute("tilewidth", &tilesize);

    TilesetList tilesets;
    for (XMLElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
        if (std::strcmp(e->Name(), "tileset") == 0) {
            tilesets.push_back(ParseTileset(e));
        }
    }

    GameMap* gamemap = new GameMap();
    for (XMLElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
        if (std::strcmp(e->Name(), "layer") == 0) {
            TileLayer* tilelayer = ParseTileLayer(e, tilesets, tilesize, rowcount, colcount);
            if (tilelayer == nullptr) {
                std::cerr << "Failed to parse tile layer" << std::endl;
                delete gamemap;
                return false;
            }
            gamemap->m_MapLayers.push_back(tilelayer);
        }
    }

    m_Mapdicts[id] = gamemap;
    return true;
}

Tileset MapParser::ParseTileset(XMLElement* xmlTileset) {
    Tileset tileset;
    tileset.Name = xmlTileset->Attribute("name");
    xmlTileset->QueryIntAttribute("firstgid", &tileset.FirstID);

    xmlTileset->QueryIntAttribute("tilecount", &tileset.TileCount);
    tileset.LastID = (tileset.FirstID + tileset.TileCount) - 1;

    xmlTileset->QueryIntAttribute("columns", &tileset.ColCount);
    tileset.RowCount = tileset.TileCount / tileset.ColCount;
    xmlTileset->QueryIntAttribute("tilewidth", &tileset.TileSize);

    XMLElement* image = xmlTileset->FirstChildElement();
    tileset.Source = image->Attribute("source");
    return tileset;
}

TileLayer* MapParser::ParseTileLayer(XMLElement* xmlLayer, TilesetList tilesets, int tilesize, int rowcount, int colcount) {
    XMLElement* data = nullptr;
    for (XMLElement* e = xmlLayer->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
        if (std::strcmp(e->Name(), "data") == 0) {
            data = e;
            break;
        }
    }

    if (data == nullptr) {
        std::cerr << "Error: No <data> element found in layer" << std::endl;
        return nullptr;
    }

    const char* text = data->GetText();
    if (text == nullptr) {
        std::cerr << "Error: No text data found in <data> element" << std::endl;
        return nullptr;
    }

    std::string matrix(text);
    std::istringstream iss(matrix);
    std::string id;

    TileMap tilemap(rowcount, std::vector<int>(colcount, 0));
    int totalTiles = rowcount * colcount;
    int tileCount = 0;

    while (std::getline(iss, id, ',')) {
        // Bỏ khoảng trắng và ký tự xuống dòng
        id.erase(std::remove_if(id.begin(), id.end(), isspace), id.end());

        if (id.empty()) continue; // Bỏ qua nếu giá trị rỗng

        int row = tileCount / colcount;
        int col = tileCount % colcount;

        if (row >= rowcount || col >= colcount) {
            std::cerr << "Error: Too many tiles in layer data. Expected " << totalTiles << " tiles, but found more." << std::endl;
            return nullptr;
        }

        std::stringstream convertor(id);
        int value;
        if (!(convertor >> value)) {
            std::cerr << "Error: Invalid tile value at position (" << row << ", " << col << "): " << id << std::endl;
            return nullptr;
        }

        tilemap[row][col] = value;
        tileCount++;
    }

    if (tileCount != totalTiles) {
        std::cerr << "Error: Not enough tiles in layer data. Expected " << totalTiles << " tiles, but found " << tileCount << "." << std::endl;
        return nullptr;
    }

    return new TileLayer(tilesize, rowcount, colcount, tilemap, tilesets);
}
MapParser::MapParser() {
}

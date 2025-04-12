#ifndef MAPPARSER_H
#define MAPPARSER_H

#include <map>
#include <string>
#include "GameMap.h"
#include "TileLayer.h"
#include "../Vendor/tinyxml2/tinyxml2.h"

class MapParser {
public:
    bool Load();
    void Clean();
    inline GameMap* GetMap(const std::string& id) { return m_Mapdicts[id]; }
    MapParser();
    inline static MapParser* GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new MapParser(); }

private:
    bool Parse(std::string id, std::string source);
    Tileset ParseTileset(tinyxml2::XMLElement* xmlTileset);
    TileLayer* ParseTileLayer(tinyxml2::XMLElement* xmlLayer, TilesetList tilesets, int tilesize, int rowcount, int colcount);

private:
    static MapParser* s_Instance;
    std::map<std::string, GameMap*> m_Mapdicts;
};

#endif // MAPPARSER_H

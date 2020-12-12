#ifndef MAPRENDER_H_INCLUDED
#define MAPRENDER_H_INCLUDED
#include "LevelRender.h"
#include <Sakura/Map.h>

class MapRender
{
public:
    MapRender(Sakura::Map* map);
    MapRender();
    ~MapRender();

    void AddLevelRender(Sakura::Room* newRoom);
    void RemoveLevelRender(Sakura::Room* eraseRoom);
    void Render(std::map<char,Tileset>& fgTiles, std::map<char,Tileset>& bgTiles, std::map<std::string,Sprite>& sprites, sf::RenderWindow& window, std::map<std::string, std::vector<EntityRenderDef>>& renderDefs);

    std::vector<uint8_t> hasChanged;
private:

    std::vector<LevelRender*> levels;
};


#endif // MAPRENDER_H_INCLUDED

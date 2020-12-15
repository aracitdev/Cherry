#include "MapRender.h"
#include <iostream>

MapRender::MapRender()
{
    //
}

MapRender::MapRender(Sakura::Map* mp)
{
    for(uint32_t i=0; i < mp->rooms.size(); i++)
        AddLevelRender(mp->rooms[i]);
}

MapRender::~MapRender()
{
    for(uint32_t i=0; i < levels.size(); i++)
        delete levels[i];
    levels.clear();
}

void MapRender::AddLevelRender(Sakura::Room* newRoom)
{
    levels.push_back(new LevelRender(newRoom));
    hasChanged.push_back(1);
}

void MapRender::RemoveLevelRender(Sakura::Room* eraseRoom)
{
    uint32_t i;
    for(i=0; i < levels.size(); i++)
        if(levels[i]->renderRoom == eraseRoom)
        break;
    if(i == levels.size())
        return;
    delete levels[i];
    levels.erase(levels.begin() + i);
    hasChanged.erase(hasChanged.begin()+i);
}

void MapRender::Render(std::map<char,Tileset>& fgTiles, std::map<char,Tileset>& bgTiles, std::map<std::string,Sprite>& sprites, sf::RenderWindow& window, std::map<std::string, std::vector<EntityRenderDef>>& renderDefs)
{
    for(uint32_t i=0; i < levels.size(); i++)
    {
        if(hasChanged[i])
        {
            levels[i]->UpdateRender(fgTiles,bgTiles,sprites, renderDefs);
            hasChanged[i]=0;
        }
        sf::Sprite& sprt = levels[i]->prerenderSprite;
        sprt.setPosition(levels[i]->renderRoom->x, levels[i]->renderRoom->y);
        window.draw(sprt);
    }
}

LevelRender* MapRender::GetRoom(size_t i)
{
    return levels[i];
}


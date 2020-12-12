#ifndef LEVELRENDER_H_INCLUDED
#define LEVELRENDER_H_INCLUDED
#include <Sakura/Room.h>
#include <SFML/Graphics.hpp>

#include "../Utility/Tileset.h"
#include "../Utility/SpriteExtraction.h"
#include "EntityRenderDef.h"

class LevelRender
{
public:

    LevelRender();
    LevelRender(Sakura::Room* room);

    void SetRoom(Sakura::Room* room);
    void UpdateRender(std::map<char,Tileset>& fgTiles, std::map<char,Tileset>& bgTiles, std::map<std::string,Sprite>& sprites, std::map<std::string, std::vector<EntityRenderDef>>& renderDefs);
    void RenderTilemap(Sakura::Tiles& tiles, std::map<char,Tileset>& tileDefs);
    void RenderDecals(std::vector<Sakura::Decal>& decals, std::map<std::string,Sprite>& atlas);
    void RenderEntitites(std::vector<Sakura::Entity>& entities, std::map<std::string, std::vector<EntityRenderDef>>& entityRenderDefs);
    sf::RenderTexture texture;
    sf::Sprite prerenderSprite;

    Sakura::Room* renderRoom;
};

#endif // LEVELRENDER_H_INCLUDED

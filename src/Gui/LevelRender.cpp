#include "LevelRender.h"
#include <random>
#include <iostream>

LevelRender::LevelRender()
{
    //
}

LevelRender::LevelRender(Sakura::Room* rm)
{
    SetRoom(rm);
}

void LevelRender::SetRoom(Sakura::Room* rm)
{
    renderRoom = rm;
    texture.create(renderRoom->width, renderRoom->height);
    prerenderSprite.setTexture(texture.getTexture());
}

void LevelRender::RenderTilemap(Sakura::Tiles& tiles, std::map<char,Tileset>& tileDefs)
{
    for(uint32_t x=0; x < tiles.GetSize().x; x++)
        for(uint32_t y=0; y < tiles.GetSize().y; y++)
    {
        srand(x * tiles.GetSize().y + y);   //do this to prevent wiggle
        char bgTile = tiles.GetTile(x,y);
        if(bgTile != '0')
        {
            Tileset& curr = tileDefs[bgTile];
            uint8_t v=0;
            for(uint32_t i=0; i < 9; i++)
                if(i != 4)
                {
                    int32_t posX = x + i % 3 - 1;
                    int32_t posY = y + i / 3 - 1;
                    if(posX < tiles.GetSize().x && posY < tiles.GetSize().y
                        && posX > 0 && posY > 0 &&
                        tiles.GetTile(posX, posY) != '0')
                            v++;
                    if(i != 8)
                        v = v<<1;
                }
            sf::Sprite* sprt = curr.Get(v);
            sprt->setPosition(x * 8, y* 8);
            texture.draw(*sprt);
        }
    }
}


void LevelRender::UpdateRender(std::map<char,Tileset>& fgTiles, std::map<char,Tileset>& bgTiles, std::map<std::string,Sprite>& sprites, std::map<std::string, std::vector<EntityRenderDef>>& renderDefs)
{
    texture.clear(sf::Color(0x50,0x50,0x50));
    RenderTilemap(renderRoom->bgTiles, bgTiles);
    RenderDecals(renderRoom->bgdecals, sprites);
    RenderTilemap(renderRoom->fgTiles, fgTiles);
    RenderDecals(renderRoom->fgdecals, sprites);
    RenderEntitites(renderRoom->entities, renderDefs);
    texture.display();
}

void LevelRender::RenderDecals(std::vector<Sakura::Decal>& decals, std::map<std::string,Sprite>& atlas)
{
    for(uint32_t i=0; i < decals.size(); i++)
    {
        Sprite& atlasSprt = atlas[decals[i].texture];
        sf::Sprite& sprt = atlasSprt.sprt;

        sprt.setScale(decals[i].scaleX, decals[i].scaleY);
        sprt.setOrigin(sprt.getLocalBounds().width/2 + atlasSprt.offsetX
                       ,sprt.getLocalBounds().height/2 + atlasSprt.offsetY);
        sprt.setPosition(decals[i].x, decals[i].y);
        texture.draw(sprt);
    }
}

void LevelRender::RenderEntitites(std::vector<Sakura::Entity>& entities, std::map<std::string, std::vector<EntityRenderDef>>& entityRenderDefs)
{
    for(uint32_t i=0; i < entities.size(); i++)
    {
        auto pos = entityRenderDefs.find(entities[i].name);
        if(pos != entityRenderDefs.end() && pos->second.size() && pos->second[0].sprites.size())
        {
            EntityRenderDef* def = &(pos->second[0]);
            Sprite* sprt = def->sprites[0].second;
            sf::Sprite* display = &(sprt->sprt);

            float w = entities[i].width.value_or(display->getLocalBounds().width);
            float h = entities[i].height.value_or(display->getLocalBounds().width);
            display->setScale(w / display->getLocalBounds().width, h / display->getLocalBounds().height);
            display->setPosition(entities[i].x, entities[i].y);
            display->setOrigin(entities[i].originX.value_or(0), entities[i].originY.value_or(0));
            texture.draw(*display);
        }
        else
        {
            int32_t w = entities[i].width.value_or(8);
            int32_t h = entities[i].height.value_or(8);
            sf::RectangleShape shape(sf::Vector2f(w,h));
            shape.setOrigin(entities[i].originX.value_or(0)
                            ,entities[i].originY.value_or(0));

            shape.setFillColor(sf::Color(0xff,0,0,0x70));
            shape.setPosition(entities[i].x, entities[i].y);
            texture.draw(shape);
        }
    }
}

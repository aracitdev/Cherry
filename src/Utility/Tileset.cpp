#include "Tileset.h"
#include <Sakura/StringFuncs.h>
#include <iostream>
#include <bitset>

Tileset::Tileset()
{
}

Tileset::Tileset(sf::Sprite& tilesetTexture, uint16_t w, uint16_t h)
{
    SetTileset(tilesetTexture,w,h);
}


void Tileset::SetTileset(sf::Sprite& tilesetTexture, uint16_t w, uint16_t h)
{
    sf::IntRect textureRect = tilesetTexture.getTextureRect();
    Resize(textureRect.width/w, textureRect.height/h);

    for(uint32_t countery=0; countery < tileSprites.size(); countery++)
        for(uint32_t counterx=0; counterx < tileSprites[countery].size(); counterx++)
        {
            tileSprites[countery][counterx].setTexture(*tilesetTexture.getTexture());
            tileSprites[countery][counterx].setTextureRect(sf::IntRect(textureRect.left + counterx * w, textureRect.top + countery * h, w,h));
        }
}

void Tileset::Resize(uint16_t w, uint16_t h)
{
    tileSprites.resize(h);
    for(uint32_t i=0; i < tileSprites.size(); i++)
    {
        tileSprites[i].resize(w);
        for(uint32_t x=0; x < tileSprites[i].size(); x++)
            tileSprites[i][x]=sf::Sprite();
    }
}

void Tileset::LoadMask(const std::string& tiles, const std::string& mask)
{
    std::vector<std::string> posTokens = Sakura::SplitString(tiles, ';');
    std::vector<Sakura::Vector2<uint8_t>> tilepos(posTokens.size());
    for(uint32_t i=0; i < posTokens.size(); i++)
    {
        std::vector<std::string> numTokens = Sakura::SplitString(posTokens[i],',');
        tilepos[i] = Sakura::Vector2<uint8_t>(std::stoi(numTokens[0]), std::stoi(numTokens[1]));
    }
    tilePos.push_back({Tilemask(mask),tilepos});
}

sf::Sprite* Tileset::Get(uint8_t x, uint8_t y)
{
    if(tileSprites.size() < y || tileSprites[0].size() < x)
        throw std::runtime_error("Attempted to access tileset out of texture bounds.\nTile was " + std::to_string(x) + " " + std::to_string(y) + " size was " + std::to_string(tileSprites.size()));
    return &(tileSprites[y][x]);
}

sf::Sprite* Tileset::Get(uint8_t mask)
{
    for(uint32_t i=0; i < tilePos.size(); i++)
    {
        if(tilePos[i].first.FitsMask(mask))
        {
            std::vector<Sakura::Vector2<uint8_t>>& sprtList = tilePos[i].second;
            Sakura::Vector2<uint8_t>& pos =  sprtList[(rand() % sprtList.size())];
            return Get(pos.x,pos.y);
        }
    }
    return nullptr;
}



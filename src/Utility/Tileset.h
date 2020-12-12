#ifndef TILESET_H_INCLUDED
#define TILESET_H_INCLUDED
#include <SFML/Graphics.hpp>
#include "Sakura/Vector2.h"
#include "Tilemask.h"

class Tileset
{
public:

    Tileset();
    Tileset(sf::Sprite& tilesetTexture, uint16_t w, uint16_t h);

    void SetTileset(sf::Sprite& tilesetTexture, uint16_t w, uint16_t h);
    void Resize(uint16_t w, uint16_t h);

    sf::Sprite* Get(uint8_t x, uint8_t h);
    sf::Sprite* Get(uint8_t mask);


    std::string ignores;
    void LoadMask(const std::string& tiles, const std::string& mask);

    std::vector<std::vector<sf::Sprite>> tileSprites;
    std::vector<std::pair<Tilemask, std::vector<Sakura::Vector2<uint8_t>>>> tilePos;
private:

};


#endif // TILESET_H_INCLUDED

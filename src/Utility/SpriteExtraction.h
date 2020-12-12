#ifndef SPRITEEXTRACTION_H_INCLUDED
#define SPRITEEXTRACTION_H_INCLUDED
#include <SFML/Graphics.hpp>

class Sprite
{
public:

    void ReadFromStream(std::istream& in);
    void UpdateTexture(sf::Texture& tex);
    sf::Sprite sprt;
    int offsetX;
    int offsetY;
    int realWidth;
    int realHeight;
    int width;
    int height;
    int x;
    int y;

private:

};

void ExtractSpriteImage(std::istream& fileStream, sf::Image& out);
void ExtractSpriteMeta(std::istream& fileStream, sf::Texture& atlasTexture, std::map<std::string,Sprite>& );

bool ExtractSpriteImage(std::string fileIn, std::string fileOut);
bool ExtractSpriteMeta(std::string fileIn, sf::Texture& atlasTexture, std::map<std::string,Sprite>&);

bool LoadAtlas(std::string sprite, std::string spriteImage,std::string meta,std::map<std::string, Sprite>& sprites, sf::Texture& outTexture);
bool DumpAtlasImages(std::string sprite, std::string spriteImage, std::string meta, std::string outPath);

#endif // SPRITEEXTRACTION_H_INCLUDED

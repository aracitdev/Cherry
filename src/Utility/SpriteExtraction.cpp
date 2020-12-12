#include "SpriteExtraction.h"
#include "Sakura/FileFunctions.h"

void Sprite::ReadFromStream(std::istream& in)
{
    x=Sakura::Read<int16_t>(in);
    y=Sakura::Read<int16_t>(in);
    width = Sakura::Read<int16_t>(in);
    height = Sakura::Read<int16_t>(in);
    offsetX = Sakura::Read<int16_t>(in);
    offsetY = Sakura::Read<int16_t>(in);
    realWidth = Sakura::Read<int16_t>(in);
    realHeight = Sakura::Read<int16_t>(in);
}

void Sprite::UpdateTexture(sf::Texture& tex)
{
    sprt.setTexture(tex);
    sprt.setTextureRect(sf::IntRect(x,y,width,height));
}


bool ExtractSpriteImage(std::string spriteFile, std::string textureFile)
{
    std::ifstream spriteStream(spriteFile.c_str(),std::ifstream::binary);
    if(!spriteStream.is_open())
        return false;
    sf::Image outImage;
    ExtractSpriteImage(spriteStream, outImage);
    outImage.saveToFile(textureFile);
    return true;
}

bool ExtractSpriteMeta(std::string fileIn, sf::Texture& atlasTexture, std::map<std::string,Sprite>& returnV)
{
    std::ifstream metaFile(fileIn.c_str(), std::ifstream::binary);
    if(!metaFile.is_open())
        return false;
    ExtractSpriteMeta(metaFile, atlasTexture, returnV);
    return true;
}

void ExtractSpriteImage(std::istream& fileStream, sf::Image& out)
{
    size_t w = (size_t)Sakura::Read<int32_t>(fileStream);
    size_t h = (size_t)Sakura::Read<int32_t>(fileStream);
    bool hasAlpha = Sakura::Read<uint8_t>(fileStream);
    out.create(w,h);
    uint8_t repeat=0;
    for(size_t i=0; i < w * h; i+=repeat)
    {
        sf::Color currentColor;
        repeat = Sakura::Read<uint8_t>(fileStream);
        if(hasAlpha)
        {
            uint8_t alpha=Sakura::Read<uint8_t>(fileStream);
            if(alpha > 0)
                currentColor=sf::Color(Sakura::Read<uint8_t>(fileStream), Sakura::Read<uint8_t>(fileStream), Sakura::Read<uint8_t>(fileStream), alpha);
            else
                currentColor=sf::Color(0,0,0,0);
        }
        else
            currentColor=sf::Color(Sakura::Read<uint8_t>(fileStream), Sakura::Read<uint8_t>(fileStream), Sakura::Read<uint8_t>(fileStream));

        for(size_t j=0; j < repeat; j++)
            out.setPixel((i+ j) % h, (i+j)/h, currentColor);
    }
}


void ExtractSpriteMeta(std::istream& fileStream, sf::Texture& atlasTexture, std::map<std::string,Sprite>& returnV)
{
    Sakura::Read<int32_t>(fileStream);
    Sakura::ReadString(fileStream);
    Sakura::Read<int32_t>(fileStream);

    size_t count = Sakura::Read<int16_t>(fileStream);
    for(size_t i=0; i < count; i++)
    {
        std::string dataFile = Sakura::ReadString(fileStream);
        size_t sprites = Sakura::Read<int16_t>(fileStream);
        for(size_t j=0; j < sprites; j++)
        {
            std::string path = Sakura::ReadString(fileStream);
            for(uint32_t counter=0; counter < path.size(); counter++)
                if(path[counter] == '\\')
                path[counter]='/';

            Sprite& sprt = returnV[path];
            sprt.ReadFromStream(fileStream);
            sprt.UpdateTexture(atlasTexture);
        }
    }
}

bool LoadAtlas(std::string sprite, std::string spriteImage,std::string meta,std::map<std::string, Sprite>& sprites, sf::Texture& outTexture)
{
    if(!Sakura::FileExists(spriteImage))
        ExtractSpriteImage(sprite, spriteImage);
    if(!outTexture.loadFromFile(spriteImage))
        return false;
    ExtractSpriteMeta(meta, outTexture, sprites);
    return true;
}

bool DumpAtlasImages(std::string sprite, std::string spriteImage, std::string meta, std::string outPath)
{
    if(!Sakura::FileExists(sprite))
        ExtractSpriteImage(sprite, spriteImage);
    sf::Image im;
    if(!im.loadFromFile(spriteImage))
        return false;

    std::map<std::string, Sprite> sprites;
    sf::Texture tex;
    ExtractSpriteMeta(meta, tex, sprites);
    for(auto it=sprites.begin(); it != sprites.end(); it++)
    {
        std::string filename = it->first;
        std::string path = filename.substr(0, filename.find_last_of('/'));
        filename = filename.substr(filename.find_last_of('/') + 1);
        filename =outPath + path + "/"+ filename + std::string(".png");
        if(!Sakura::FileExists(filename))
        {
            Sakura::CreatePath(outPath + path);
            sf::Image out;
            out.create(it->second.width, it->second.height);
            out.copy(im, 0,0, sf::IntRect(it->second.x, it->second.y, it->second.width, it->second.height));
            out.saveToFile(filename);
        }
    }
    return true;
}


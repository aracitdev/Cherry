#include "Tiler.h"
#include <Sakura/XMLFile.h>

bool LoadTileXML(const std::string& filename, std::map<char, Tileset>& tilesets, std::map<std::string, Sprite>& sprites)
{
    Sakura::Element* e = Sakura::LoadXML(filename, "Data");
    if(e == nullptr)
        return false;

    for(uint32_t i=0; i < e->children.size(); i++)
    {
        Sakura::Element* currentChild = e->children[i];
        std::string path = "tilesets/" + currentChild->Attr("path");
        char id = '\0';
        if(currentChild->IsAttr<std::string>("id"))
            id=currentChild->Attr("id")[0];
        else
            id = '0' + currentChild->AttrInt("id");

        Tileset& tile = tilesets[id];
        if(currentChild->HasAttr("copy"))
        {
            char copyid = '\0';
            if(currentChild->IsAttr<std::string>("copy"))
                copyid=currentChild->Attr("copy")[0];
            else
                copyid = '0' + currentChild->AttrInt("copy");
            if(tilesets.count(copyid))
                tile = tilesets[copyid];
        }
        if(sprites.count(path))
            tile.SetTileset(sprites[path].sprt, 8,8);
        for(uint32_t j=0; j < currentChild->children.size(); j++)
        {
            Sakura::Element* maskElement = currentChild->children[j];
            if(maskElement->Attr("mask") == "center")
                tile.LoadMask(maskElement->Attr("tiles"), "111-111-111");
            else
            if(maskElement->Attr("mask") != "padding")
                tile.LoadMask(maskElement->Attr("tiles"), maskElement->Attr("mask"));
        }
    }

    delete e;
    return true;
}

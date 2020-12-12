#ifndef TILER_H_INCLUDED
#define TILER_H_INCLUDED
#include "SpriteExtraction.h"
#include "Tileset.h"


bool LoadTileXML(const std::string& filename, std::map<char, Tileset>& tilesets, std::map<std::string, Sprite>& sprites);

#endif // TILER_H_INCLUDED

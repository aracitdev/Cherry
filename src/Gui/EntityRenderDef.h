#ifndef ENTITYRENDERDEF_H_INCLUDED
#define ENTITYRENDERDEF_H_INCLUDED
#include "../Utility/SpriteExtraction.h"
#include <Sakura/Element.h>
#include <Sakura/Vector2.h>

class EntityRenderDef
{
public:


    void LoadFromElement(Sakura::Element* e, std::map<std::string,Sprite>& atlas);

    //values that must be equal to display this sprite
    std::vector<std::pair<std::string,std::variant<int32_t,bool,float,std::string>>> values;

    //if not specified it will default to a rectangle
    std::vector<std::pair<Sakura::Vector2<int32_t>,Sprite*>> sprites;    //stored as offset/sprite
private:

};

bool LoadEntityRenderDefs(const std::string& filename, std::map<std::string,Sprite>& atlas, std::map<std::string,std::vector<EntityRenderDef>>& renderingAtlas);


#endif // ENTITYRENDERDEF_H_INCLUDED

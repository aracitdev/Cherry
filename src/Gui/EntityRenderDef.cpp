#include "EntityRenderDef.h"
#include <Sakura/XMLFile.h>

#include <iostream>

void EntityRenderDef::LoadFromElement(Sakura::Element* e, std::map<std::string,Sprite>& atlas)
{
    size_t index=0;
    values.resize(e->attributes.size());
    for(auto it=e->attributes.begin(); it != e->attributes.end(); it++)
    {
        values[index]={it->first,it->second};
        index++;
    }

    sprites.resize(e->children.size());
    for(uint32_t i=0; i < e->children.size(); i++)
    {
        Sakura::Element* current = e->children[i];
        Sakura::Vector2<int32_t> pos;
        if(current->HasAttr("x"))
            pos.x=current->AttrInt("x");
        if(current->HasAttr("y"))
            pos.y=current->AttrInt("y");
        auto it = atlas.find(current->Attr("texture"));
        Sprite* sprt = nullptr;
        if(it != atlas.end())
            sprt = &(it->second);
        else
            std::cout <<"Failed to find sprite " <<current->Attr("texture")<<"\n";
        sprites[i]={pos,sprt};
    }
}


bool LoadEntityRenderDefs(const std::string& filename, std::map<std::string,Sprite>& atlas, std::map<std::string,std::vector<EntityRenderDef>>& renderingAtlas)
{
    Sakura::Element* element = Sakura::LoadXML(filename, "Render");
    if(element == nullptr)
        return false;
    for(uint32_t i=0; i < element->children.size(); i++)
    {
        Sakura::Element* currentEntity = element->children[i];
        std::vector<EntityRenderDef>& renderDefs = renderingAtlas[currentEntity->name];
        renderDefs.resize(currentEntity->children.size());
        for(uint32_t j=0; j < currentEntity->children.size(); j++)
            renderDefs[j].LoadFromElement(currentEntity->children[j], atlas);
    }

    delete element;
    return true;
}


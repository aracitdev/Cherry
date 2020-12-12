#include "EntityTool.h"
#include <imgui.h>
#include <iostream>

EntityTool::EntityTool(const std::string& toolName) : toolHeader(toolName)
{
    selectedItem=0;
    searchBuffer = new char[searchBufferSize];
    memset(searchBuffer,0,searchBufferSize);
}

EntityTool::EntityTool(const std::map<std::string,Sakura::Entity>& entityList, const std::string& toolName) : EntityTool(toolName)
{
    LoadEntities(entityList);
}

void EntityTool::LoadEntities(const std::map<std::string,Sakura::Entity>& entityList)
{
    uint32_t i=0;
    entityNames.resize(entityList.size());
    entityDefs.resize(entityList.size());
    for(auto it=entityList.begin(); it != entityList.end(); it++)
    {
        entityNames[i] =it->first;
        entityDefs[i] = it->second;
        i++;
    }
}

EntityTool::~EntityTool()
{
    if(searchBuffer != nullptr)
        delete[] searchBuffer;
}

std::string EntityTool::GetName(void)
{
    return toolHeader;
}

void EntityTool::Render(void)
{
    ImVec2 size = ImGui::GetContentRegionMax();
    ImGui::PushItemWidth(-size.x/4.0);
    ImGui::InputText("Search",searchBuffer, searchBufferSize);
    std::string searchText=std::string(searchBuffer);
    if(ImGui::ListBoxHeader(toolHeader.c_str(),{size.x,size.y}))
    {
        for(uint32_t i=0; i < entityDefs.size(); i++)
        {
            if( (searchText.empty() || entityNames[i].find(searchText) != std::string::npos)
                && ImGui::Selectable(entityNames[i].c_str(), selectedItem == i))
                selectedItem=i;
        }
        ImGui::ListBoxFooter();
    }
}

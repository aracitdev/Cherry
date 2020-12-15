#include "ToolSelection.h"
#include <imgui.h>
#include <iostream>

ToolSelection::ToolSelection()
{
    currentTool=0;
}


void ToolSelection::Render(void)
{
    ImGui::SetCursorPos({0,0});
    ImVec2 size = ImGui::GetContentRegionMax();


    ImGui::BeginChild("Tools", {size.x/4,size.y});
    ImGui::PushItemWidth(size.x/2);
    if(ImGui::ListBoxHeader("Tool List", {size.x/4,size.y} ))
    {
        for(uint32_t i=0; i < tools.size(); i++)
            if(ImGui::Selectable(tools[i]->GetName().c_str(), i == currentTool))
            {
                currentTool=i;
            }
        ImGui::ListBoxFooter();
    }
    ImGui::EndChild();
    if(!tools.empty() && currentTool < tools.size())
    {
        ImGui::SetCursorPos({size.x/4, 0});
        ImGui::BeginChild("Tool", {size.x * 3/4,size.y}, false, ImGuiWindowFlags_NoDecoration);
        tools[currentTool]->Render();
        ImGui::EndChild();
    }
}


bool ToolSelection::HandleEvent(sf::Event& ev,sf::Vector2f mouseWorld, LevelRender& currentRender, Sakura::Room* currentRoom)
{
    return tools[currentTool]->HandleEvent(ev,mouseWorld,currentRender,currentRoom);
}

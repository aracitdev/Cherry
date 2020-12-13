#include "RoomController.h"


RoomController::RoomController(Sakura::Map* mp)
{
    SetMap(mp);
}

void RoomController::Render(ViewController& view)
{
    ImVec2 size = ImGui::GetContentRegionMax();
    if(ImGui::ListBoxHeader("Rooms",{size.x,size.y}))
    {
        for(uint32_t i=0; i < currentMap->rooms.size(); i++)
        {
            if(ImGui::Selectable(currentMap->rooms[i]->name.c_str(), selectedItem == i))
            {
                view.SetPos(currentMap->rooms[i]->x, currentMap->rooms[i]->y);
                selectedItem=i;
            }
        }
        ImGui::ListBoxFooter();
    }
}

void RoomController::SetMap(Sakura::Map* mp)
{
    currentMap=mp;
    selectedItem=0;
}

Sakura::Room* RoomController::GetCurrentRoom(void)
{
    if(selectedItem >= currentMap->rooms.size() && !currentMap->rooms.empty())
        selectedItem = currentMap->rooms.size()-1;
    return currentMap->rooms[selectedItem];
}

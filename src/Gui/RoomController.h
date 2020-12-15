#ifndef ROOMCONTROLLER_H_INCLUDED
#define ROOMCONTROLLER_H_INCLUDED
#include <Sakura/Map.h>
#include <imgui.h>
#include "ViewController.h"

class RoomController
{
public:
    RoomController(Sakura::Map* mp=nullptr);
    void Render(ViewController& view);
    void SetMap(Sakura::Map* mp);
    Sakura::Room* GetCurrentRoom(void);
    size_t GetCurrentRoomIndex(void);

private:
    Sakura::Map* currentMap;
    uint32_t selectedItem;
};

#endif // ROOMCONTROLLER_H_INCLUDED

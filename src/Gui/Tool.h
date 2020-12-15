#ifndef TOOL_H_INCLUDED
#define TOOL_H_INCLUDED

#include <Sakura/Map.h>
#include "ViewController.h"
#include "LevelRender.h"
#include <imgui.h>

class ITool
{
public:
    virtual ~ITool();

    virtual std::string GetName(void)=0;
    virtual void Render(void)=0;
    virtual bool HandleEvent(sf::Event& ev,sf::Vector2f mouseWorld, LevelRender& currentRender, Sakura::Room* currentRoom)=0;
private:

};

#endif // TOOL_H_INCLUDED

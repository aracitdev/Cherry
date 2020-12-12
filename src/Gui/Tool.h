#ifndef TOOL_H_INCLUDED
#define TOOL_H_INCLUDED

#include <Sakura/Map.h>
#include <imgui.h>

class ITool
{
public:
    virtual ~ITool();

    virtual std::string GetName(void)=0;
    virtual void Render(void)=0;


    Sakura::Map* mapPtr;
private:

};

#endif // TOOL_H_INCLUDED

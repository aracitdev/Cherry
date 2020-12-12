#ifndef TOOLSELECTION_H_INCLUDED
#define TOOLSELECTION_H_INCLUDED
#include <imgui.h>
#include "Tool.h"

class ToolSelection
{
public:

    ToolSelection();

    void Render(void);
    std::vector<ITool*> tools;
    size_t currentTool;
};


#endif // TOOLSELECTION_H_INCLUDED

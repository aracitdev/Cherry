#include "MainMenuBar.h"
#include <imgui.h>

void MainMenuBar::Render(void)
{
    if(ImGui::BeginMainMenuBar())
    {
        if(ImGui::BeginMenu("File"))
        {
            isOpen=true;
            if(ImGui::MenuItem("save"))
            {
                //
            }
            if(ImGui::MenuItem("open"))
            {
                //
            }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}

#include "MainWindow.hpp"

void MainWindow::onDraw()
{
    static bool showDemo = false;
    ImGui::Checkbox("Show IMGUI Demo" , &showDemo);
    if(showDemo)
    {
        ImGui::ShowDemoWindow();
    }
}

#include "SettingsWindow.hpp"

SettingsWindow::SettingsWindow()
{
    setTitle("Settings");
}

void SettingsWindow::onDraw()
{
    static std::string path = "";
    ImGui::InputText("GPU device path", path);
}

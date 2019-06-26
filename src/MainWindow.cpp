#include "MainWindow.hpp"

MainWindow::MainWindow() {
  gpu.connect();
  setFlag(ImGuiWindowFlags_MenuBar);
  mw->setVisible(showMonitor);
}

void MainWindow::onDraw() {
  // Menu Bar
  {
    if(ImGui::BeginMenuBar()) {
      if(ImGui::BeginMenu("Window")) {
        if(ImGui::MenuItem("Show Monitor Window", NULL, &showMonitor)) {
          mw->setVisible(showMonitor);
        }
        ImGui::EndMenu();
      }
      ImGui::EndMenuBar();
    }
  }
  GPUClock(&settings);
  GPUPower(&settings);
  GPUMemClock(&settings);
  if(ImGui::Button("Apply")) {
    gpu.applySettings(settings);
  }
  ImGui::Separator();
  {
    static int fanSpeed = 20;
    ImGui::Text("Fan Speed");
    if(ImGui::Checkbox("Manual Mode", &fanManualMode))
      gpu.setFanManual(fanManualMode);
    if(fanManualMode) {
      if(ImGui::SliderInt("Fan Speed", &fanSpeed, 0, 255))
        gpu.setFanSpeed(fanSpeed);
    }
  }
}

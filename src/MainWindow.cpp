#include "MainWindow.hpp"

MainWindow::MainWindow() {
  gpu.canConnect();
}

void MainWindow::onDraw() {
  // Menu Bat
  {
    if(ImGui::BeginMenuBar()) {
      if(ImGui::BeginMenu("Window")) {
        if(ImGui::MenuItem("Show Monitor Window", NULL, &showMonitor)) {
          mw->setVisible(showMonitor);
        }
        if(ImGui::MenuItem("Show Settings Window", NULL, &showSettings)) {
          sw->setVisible(showSettings);
        }

        if(ImGui::MenuItem("Show Demo Window", NULL, &showDemo)) {
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

  if(showDemo) {
    ImGui::ShowDemoWindow();
  }

  if(firstDraw) {
    firstDraw          = false;
    char *const args[] = {"sh", NULL};
    cr.runCommand(args);
  }
}

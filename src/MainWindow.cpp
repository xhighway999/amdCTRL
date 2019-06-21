#include "MainWindow.hpp"

MainWindow::MainWindow() {
  gpu.canConnect();
}

void MainWindow::onDraw() {
  static bool showDemo = false;
  static GpuSettings settings;

  GPUClock(&settings);
  GPUPower(&settings);
  GPUMemClock(&settings);
  if(ImGui::Button("Apply")) {
    gpu.applySettings(settings);
  }

  ImGui::Checkbox("Show IMGUI Demo", &showDemo);
  if(showDemo) {
    ImGui::ShowDemoWindow();
  }
  static bool showMonitor = true;
  ImGui::Checkbox("Show Monitor", &showMonitor);
  mw->setVisible(showMonitor);

  if(firstDraw) {
    firstDraw          = false;
    char *const args[] = {"sh", NULL};
    cr.runCommand(args);
  }

  // gpu.updateStats();
  /*ImGui::BeginChild("CrappyTerm");
  {
    static std::string buffer;
    buffer += cr.readAvail();
    ImGui::TextWrapped("%s", buffer.c_str());
    static std::string input = "";
    if(ImGui::InputText("##CMD", input,ImGuiInputTextFlags_EnterReturnsTrue)) {
      cr.write(input);
      cr.write("\n");
    }
  }
  ImGui::EndChild();*/
}

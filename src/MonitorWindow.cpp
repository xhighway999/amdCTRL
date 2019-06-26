#include "MonitorWindow.hpp"

MonitorWindow::MonitorWindow(const GPU &ngpu) : gpu(ngpu) {
  setTitle("Monitor Window");
}

void MonitorWindow::onDraw() {
  {
    const static size_t value_count  = 900;
    static float values[value_count] = {0};
    float newVal                     = gpu.getTemp() / 1000;
    ImGui::AutoPlot("Temperature",
                    &newVal,
                    values,
                    value_count,
                    NULL,
                    -20,
                    150,
                    ImVec2(0, 100));
  }

  {
    const static size_t value_count  = 900;
    static float values[value_count] = {0};
    float newVal                     = gpu.getClock() / 1000000;
    ImGui::AutoPlot(
        "SCLK", &newVal, values, value_count, NULL, 700, 2500, ImVec2(0, 100));
  }

  {
    const static size_t value_count  = 900;
    static float values[value_count] = {0};
    float newVal                     = gpu.getMemClock() / 1000000;
    ImGui::AutoPlot(
        "MCLK", &newVal, values, value_count, NULL, 300, 1500, ImVec2(0, 100));
  }

  {
    const static size_t value_count  = 900;
    static float values[value_count] = {0};
    float newVal                     = gpu.getFanSpeed();
    ImGui::AutoPlot(
        "FAN", &newVal, values, value_count, NULL, 0, 4000, ImVec2(0, 100));
  }
}

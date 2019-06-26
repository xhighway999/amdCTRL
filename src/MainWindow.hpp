#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "GPU.hpp"
#include "GPUWidgets.hpp"
#include "MonitorWindow.hpp"
#include "Shell.hpp"
#include "xhfr.hpp"

class MainWindow : public xhfr::Window {
public:
  MainWindow();
  virtual void onDraw() override;

private:
  GPU gpu;
  Shell cr;
  MonitorWindow *mw  = new MonitorWindow(gpu);
  bool showMonitor   = true;
  bool fanManualMode = false;
  GpuSettings settings;
};

#endif // MAINWINDOW_H

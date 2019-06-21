#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "GPU.hpp"
#include "GPUWidgets.hpp"
#include "MonitorWindow.hpp"
#include "SettingsWindow.hpp"
#include "Shell.hpp"
#include "core.hpp"

class MainWindow : public core::Window {
public:
  MainWindow();
  virtual void onDraw() override;

private:
  bool firstDraw = true;
  GPU gpu;
  Shell cr;
  SettingsWindow *sw = new SettingsWindow();
  MonitorWindow *mw  = new MonitorWindow(gpu);
};

#endif // MAINWINDOW_H

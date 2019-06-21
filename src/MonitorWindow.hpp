#ifndef MONITORWINDOW_H
#define MONITORWINDOW_H

#include "GPU.hpp"
#include "GPUWidgets.hpp"
#include "core.hpp"
class MonitorWindow : public core::Window {
public:
  /**
   * Default constructor
   */
  MonitorWindow(const GPU &ngpu);
  void onDraw() override;
  const GPU &gpu;

private:
  double refresh_time = 60.0;
};

#endif // MONITORWINDOW_H

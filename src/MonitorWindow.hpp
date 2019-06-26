#ifndef MONITORWINDOW_H
#define MONITORWINDOW_H

#include "GPU.hpp"
#include "GPUWidgets.hpp"
#include "xhfr.hpp"
class MonitorWindow : public xhfr::Window {
public:
  /**
   * Default constructor
   */
  MonitorWindow(const GPU &ngpu);
  void onDraw() override;

private:
  const GPU &gpu;
  double refresh_time = 60.0;
};

#endif // MONITORWINDOW_H

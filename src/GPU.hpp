#ifndef GPU_H
#define GPU_H
#include "GPUSettings.hpp"
#include "Shell.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <string_view>

class GPU {
public:
  void connect();
  void updateStats();
  void applySettings(const GpuSettings &settings);
  void setFanManual(bool manual = true);
  void setFanSpeed(unsigned char);
  int getTemp() const;
  int getClock() const;
  int getMemClock() const;
  int getFanSpeed() const;

private:
  std::string devicepath = "/sys/class/drm/card0/device";
  std::string pppath     = devicepath + "/pp_od_clk_voltage";
  std::string perfpath   = devicepath + "/power_dpm_force_performance_level";
  std::string hwmonpath  = devicepath + "/hwmon/hwmon1";

  Shell shell;
};

#endif // GPU_H

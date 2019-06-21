#ifndef GPUSETTINGS_H
#define GPUSETTINGS_H

#include <cstdint>

struct GpuSettings {
  std::size_t coreClockMax = 2000, coreClockMin = 800, memClockMin = 1000,
              memClockMax = 1200, powerLimitMin = 270000000,
              powerLimitMax = 330000000, powerLimit = 300000000,
              memClock = 1150, voltageMin = 700, voltageMax = 1218,
              dispClockMin = 800, dispClockMax = 3000, graphPoints = 3;
  struct GraphPoint {
    std::size_t clock, voltage;
  };
  GraphPoint graphData[3]{{coreClockMin, 750},
                          {1428, 892},
                          {coreClockMax, 1133}};
};

#endif // GPUSETTINGS_H

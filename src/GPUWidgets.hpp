#ifndef GPUWIDGETS_H
#define GPUWIDGETS_H

#include "GPUSettings.hpp"
#include "imgui.h"

#include <algorithm>
#include <iostream>
#include <string>

void GPUClock(GpuSettings *settings);
void GPUMemClock(GpuSettings *settings);
void GPUPower(GpuSettings *settings);
void AutoPlot(const char *label,
              float *newValue,
              float *values,
              int values_count,
              const char *overlay_text = NULL,
              float scale_min          = FLT_MAX,
              float scale_max          = FLT_MAX,
              ImVec2 graph_size        = ImVec2(0, 0),
              int stride               = sizeof(float));
#endif // GPUWIDGETS_H

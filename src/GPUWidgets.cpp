#include "GPUWidgets.hpp"

inline ImU32 getColor(ImGuiCol col) {
  return ImGui::GetColorU32(col);
}

float remap(float low1, float high1, float low2, float high2, float value) {
  return low2 + (value - low1) * (high2 - low2) / (high1 - low1);
}

bool handleLimiter(const char *name,
                   size_t *val,
                   GpuSettings *settings,
                   ImDrawList *list,
                   ImVec2 pos,
                   ImVec2 size,
                   bool drawOnly) {
  int boxWidth = 8;

  ImVec2 canvasSize = ImGui::GetContentRegionAvail();
  // ImVec2 mouse_pos_in_canvas = ImVec2(ImGui::GetIO().MousePos.x - pos.x,
  // ImGui::GetIO().MousePos.y - pos.y);

  auto boxPos      = remap(settings->dispClockMin,
                      settings->dispClockMax,
                      pos.x,
                      canvasSize.x + pos.x,
                      *val);
  ImVec2 rectStart = ImVec2(boxPos - boxWidth / 2, pos.y);
  ImVec2 rectEnd   = ImVec2(rectStart.x + boxWidth, rectStart.y + size.y);
  auto *storarge   = ImGui::GetStateStorage();

  bool &moveMode = *storarge->GetBoolRef(ImGui::GetID(name), false);
  if(ImGui::IsMouseClicked(0) &&
     ImGui::IsMouseHoveringRect(rectStart, rectEnd) && !drawOnly) {
    moveMode = true;
  } else if(ImGui::IsMouseDown(0) && moveMode) {
    auto frequencyAtMouse = remap(pos.x,
                                  canvasSize.x + pos.x,
                                  settings->dispClockMin,
                                  settings->dispClockMax,
                                  ImGui::GetIO().MousePos.x);
    frequencyAtMouse      = std::clamp<size_t>(
        frequencyAtMouse, settings->dispClockMin, settings->dispClockMax);
    *val = frequencyAtMouse;

  } else if(ImGui::IsMouseReleased(0)) {
    moveMode = false;
  }

  list->AddText(ImGui::GetFont(),
                ImGui::GetFontSize(),
                rectEnd,
                getColor(ImGuiCol_Text),
                std::to_string(*val).c_str());
  list->AddRect(rectStart, rectEnd, ImColor(255, 0, 0));
  return moveMode;
}

bool handleGraphPoint(const char *name,
                      GpuSettings::GraphPoint *p,
                      GpuSettings *settings,
                      ImDrawList *list,
                      ImVec2 pos,
                      ImVec2 size) {
  int pointSize = 20;

  ImVec2 canvasSize = ImGui::GetContentRegionAvail();
  // ImVec2 mouse_pos_in_canvas = ImVec2(ImGui::GetIO().MousePos.x - pos.x,
  // ImGui::GetIO().MousePos.y - pos.y);

  auto boxPosX     = remap(settings->dispClockMin,
                       settings->dispClockMax,
                       pos.x,
                       canvasSize.x + pos.x,
                       p->clock);
  auto boxPosY     = remap(settings->voltageMin,
                       settings->voltageMax,
                       canvasSize.y + pos.y,
                       pos.y,
                       p->voltage);
  ImVec2 rectStart = ImVec2(boxPosX - pointSize / 2, boxPosY - pointSize / 2);
  ImVec2 rectEnd   = ImVec2(rectStart.x + pointSize, rectStart.y + pointSize);
  auto *storarge   = ImGui::GetStateStorage();

  bool &moveMode = *storarge->GetBoolRef(ImGui::GetID(name), false);
  if(ImGui::IsMouseClicked(0) &&
     ImGui::IsMouseHoveringRect(rectStart, rectEnd)) {
    moveMode = true;
  } else if(ImGui::IsMouseDown(0) && moveMode) {
    auto frequencyAtMouse = remap(pos.x,
                                  canvasSize.x + pos.x,
                                  settings->dispClockMin,
                                  settings->dispClockMax,
                                  ImGui::GetIO().MousePos.x);
    auto voltageAtMouse   = remap(canvasSize.y + pos.y,
                                pos.y,
                                settings->voltageMin,
                                settings->voltageMax,
                                ImGui::GetIO().MousePos.y);
    frequencyAtMouse      = std::clamp<size_t>(
        frequencyAtMouse, settings->dispClockMin, settings->dispClockMax);
    voltageAtMouse = std::clamp<size_t>(
        voltageAtMouse, settings->voltageMin, settings->voltageMax);
    p->clock   = frequencyAtMouse;
    p->voltage = voltageAtMouse;

  } else if(ImGui::IsMouseReleased(0)) {
    moveMode = false;
  }
  std::string text =
      std::to_string(p->clock) + "mHz " + std::to_string(p->voltage) + "mV";
  list->AddText(ImGui::GetFont(),
                ImGui::GetFontSize(),
                rectEnd,
                getColor(ImGuiCol_Text),
                text.c_str());
  list->AddRect(rectStart, rectEnd, ImColor(255, 0, 0));
  return moveMode;
}

void GPUClock(GpuSettings *settings) {
  ImGui::BeginChild("GpuClock", ImVec2(0, 450), false);
  {
    ImGui::BeginChild("GpuClockInner",
                      ImVec2(0, 400),
                      true,
                      ImGuiWindowFlags_AlwaysAutoResize);
    ImVec2 canvasPos      = ImGui::GetCursorScreenPos();
    ImVec2 canvasSize     = ImGui::GetContentRegionAvail();
    ImDrawList *draw_list = ImGui::GetWindowDrawList();

    bool focus = false;

    for(int i = 0; i < settings->graphPoints; i++) {
      focus |= handleGraphPoint(("GP" + std::to_string(i)).c_str(),
                                &settings->graphData[i],
                                settings,
                                draw_list,
                                canvasPos,
                                canvasSize);
      // first
      if(i == 0) {
        settings->graphData[i].clock = settings->coreClockMin;
      }
      // last
      if(i == settings->graphPoints - 1) {
        settings->graphData[i].clock = settings->coreClockMax;
      }
      // every point else
    }
    handleLimiter("leftLimiter",
                  &settings->coreClockMin,
                  settings,
                  draw_list,
                  canvasPos,
                  canvasSize,
                  focus);
    handleLimiter("rightLimiter",
                  &settings->coreClockMax,
                  settings,
                  draw_list,
                  canvasPos,
                  canvasSize,
                  focus);
    // draw lines
    auto toScreenSpace = [=](const GpuSettings::GraphPoint &p) {
      auto posX = remap(settings->dispClockMin,
                        settings->dispClockMax,
                        canvasPos.x,
                        canvasSize.x + canvasPos.x,
                        p.clock);
      auto posY = remap(settings->voltageMin,
                        settings->voltageMax,
                        canvasSize.y + canvasPos.y,
                        canvasPos.y,
                        p.voltage);

      return ImVec2(posX, posY);
    };
    ImVec2 prev = toScreenSpace(
        settings->graphData
            [0]); //, last =
                  // toScreenSpace(settings->graphData[settings->graphPoints-1]);
    for(int i = 1; i < settings->graphPoints; i++) {
      auto p = toScreenSpace(settings->graphData[i]);
      draw_list->AddLine(p, prev, ImColor(0, 0, 255), 2);
      prev = p;
    }
    ImGui::EndChild();
    ImGui::Text("Frequency (MHz)");
  }
  ImGui::EndChild();
}

void GPUMemClock(GpuSettings *settings) {
  int memClock = settings->memClock;
  ImGui::SliderInt("Memory clock (mHz)",
                   &memClock,
                   settings->memClockMin,
                   settings->memClockMax);
  settings->memClock = memClock;
}

void GPUPower(GpuSettings *settings) {
  int power = settings->powerLimit;
  ImGui::SliderInt("Power Limit mW",
                   &power,
                   settings->powerLimitMin,
                   settings->powerLimitMax);
  settings->powerLimit = power;
}

void AutoPlot(const char *label,
              float *newValue,
              float *values,
              int values_count,
              const char *overlay_text,
              float scale_min,
              float scale_max,
              ImVec2 graph_size,
              int stride) {
  char cat[512];
  if(strlen(label) + 32 > 512)
    abort();
  strcpy(cat, label);
  strcat(cat, "refresh_time");
  float &refresh_time =
      *ImGui::GetStateStorage()->GetFloatRef(ImGui::GetID(cat), 0);
  strcpy(cat, label);
  strcat(cat, "values_offset");
  int &values_offset =
      *ImGui::GetStateStorage()->GetIntRef(ImGui::GetID(cat), 0);
  if(refresh_time == 0.0)
    refresh_time = ImGui::GetTime();
  while(refresh_time < ImGui::GetTime()) {
    static float phase    = 0.0f;
    values[values_offset] = *newValue;
    values_offset         = (values_offset + 1) % values_count;
    phase += 0.10f * values_offset;
    refresh_time += 1.0f / 60.0f;
  }
  ImGui::PlotLines(label,
                   values,
                   values_count,
                   values_offset,
                   overlay_text,
                   scale_min,
                   scale_max,
                   graph_size,
                   stride);
  ImGui::SameLine();
  ImGui::Text("%s", std::to_string((int)values[values_offset - 1]).c_str());
}

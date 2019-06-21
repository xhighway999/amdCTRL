#include "GPU.hpp"

bool GPU::canConnect() {
  // Open a new shell with root access
  char *const args[] = {"pkexec", "su", NULL};
  shell.runCommand(args);
  shell.setBlocking(true);
}

void GPU::updateStats() {
  shell.write("cat " + perfpath + "\n");
  auto result = shell.readAvail();
  std::cout << result;
}

void GPU::applySettings(const GpuSettings &settings) {
  // Manual OC mode
  shell.write("echo \"manual\" >" + perfpath + "\n");
  // write voltage curve
  for(size_t i = 0; i < settings.graphPoints; i++) {
    const auto &p       = settings.graphData[i];
    std::string command = "vc " + std::to_string(i) + " " +
                          std::to_string(p.clock) + " " +
                          std::to_string(p.voltage) + "\n";
    shell.write("echo \"" + command + "\" > " + pppath + "\n");
  }
  // Commit
  shell.write("echo \"c\" > " + pppath + "\n");
  // set clock limits
  shell.write("echo \"s 0 " + std::to_string(settings.coreClockMin) + "\" > " +
              pppath + "\n");
  shell.write("echo \"s 1 " + std::to_string(settings.coreClockMax) + "\" > " +
              pppath + "\n");
  shell.write("echo \"c\" > " + pppath + "\n");

  updateStats();
}

std::string readFile(const std::string_view path) {
  std::ifstream infile;
  infile.open(path.data());
  std::string returnData;
  infile >> returnData;
  return returnData;
};

int GPU::getTemp() const {
  auto ret = readFile(devicepath + "/hwmon/hwmon1/temp1_input");
  return std::stoi(ret);
}

int GPU::getClock() const {
  auto ret = readFile(devicepath + "/hwmon/hwmon1/freq1_input");
  return std::stoi(ret);
}

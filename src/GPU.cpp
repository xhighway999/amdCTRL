#include "GPU.hpp"

void GPU::connect() {
  // Open a new shell with root access
  char *const args[] = {"pkexec", "bash", "-x", nullptr};
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

void GPU::setFanManual(bool manual) {
  int value = manual ? 1 : 2;
  shell.write("echo " + std::to_string(value) + " > " + hwmonpath +
              "/pwm1_enable\n");
}

void GPU::setFanSpeed(unsigned char target) {
  shell.write("echo " + std::to_string(target) + " > " + hwmonpath + "/pwm1\n");
}

std::string readFile(const std::string_view path) {
  std::ifstream infile;
  infile.open(path.data());
  std::string returnData;
  infile >> returnData;
  return returnData;
};

int GPU::getTemp() const {
  auto ret = readFile(hwmonpath + "/temp1_input");
  return std::stoi(ret);
}

int GPU::getClock() const {
  auto ret = readFile(hwmonpath + "/freq1_input");
  return std::stoi(ret);
}

int GPU::getMemClock() const {
  auto ret = readFile(hwmonpath + "/freq2_input");
  return std::stoi(ret);
}

int GPU::getFanSpeed() const {
  auto ret = readFile(hwmonpath + "/fan1_input");
  return std::stoi(ret);
}

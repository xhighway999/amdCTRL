#include "core.hpp"

#include "src/MainWindow.hpp"

int main() {
    core::init();
    auto window = new MainWindow();
    window->setTitle("Control Panel");
    window->setVisible(true);
    core::main();
}

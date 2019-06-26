#include "xhfr.hpp"

#include "src/MainWindow.hpp"

int main() {
    xhfr::init("AmdCTRL");
    auto window = new MainWindow();
    window->setTitle("Control Panel");
    window->setVisible(true);
    return xhfr::main();
}

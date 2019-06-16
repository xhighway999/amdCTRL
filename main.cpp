#include "core.hpp"

#include "src/MainWindow.hpp"
#include "LuaTerm.hpp"

int main() {
    core::init();
    auto window = new MainWindow();
    //auto luaTerm = new LuaTerm();
    window->setTitle("Control Panel");
    window->setVisible(true);
    core::main();
}

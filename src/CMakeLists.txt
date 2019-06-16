project(src)


add_library(src MainWindow.hpp
                MainWindow.cpp
                SettingsWindow.hpp
                SettingsWindow.cpp)
target_link_libraries(src core)

project(src)

set (CMAKE_CXX_STANDARD 17)

add_library(src commandrunner.hpp
                commandrunner.cpp
                GPU.hpp
                GPU.cpp
                GPUSettings.hpp
                GPUWidgets.hpp
                GPUWidgets.cpp
                MainWindow.hpp
                MainWindow.cpp
                MonitorWindow.hpp
                MonitorWindow.cpp
                SettingsWindow.hpp
                SettingsWindow.cpp
                Shell.hpp
                Shell.cpp)
target_link_libraries(src xhfr)

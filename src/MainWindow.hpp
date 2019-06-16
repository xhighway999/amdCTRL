#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "core.hpp"

#include "SettingsWindow.hpp"

class MainWindow : public core::Window
{
public:
    virtual void onDraw() override;
private:
    SettingsWindow* sw = new SettingsWindow();

};

#endif // MAINWINDOW_H

#include "settingswindow.h"
#include "ui_settingswindow.h"

SettingsWindow::SettingsWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsWindow)
{
    ui->setupUi(this);
    setWindowTitle("Settings");
    setWindowIcon(QIcon::fromTheme("applications-system"));
}

SettingsWindow::~SettingsWindow()
{        
    delete ui;
}

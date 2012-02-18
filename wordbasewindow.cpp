#include "wordbasewindow.h"
#include "ui_wordbasewindow.h"

WordBaseWindow::WordBaseWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WordBaseWindow)
{
    ui->setupUi(this);
    setWindowTitle("Word Base");
    setWindowIcon(QIcon::fromTheme("applications-office"));
}

WordBaseWindow::~WordBaseWindow()
{
    delete ui;
}

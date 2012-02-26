#include "newmediawindow.h"
#include "ui_newmediawindow.h"

NewMediaWindow::NewMediaWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewMediaWindow)
{
    ui->setupUi(this);
    setWindowTitle("New");
    setWindowIcon(QIcon::fromTheme("list-add"));
}

NewMediaWindow::~NewMediaWindow()
{
    delete ui;
}

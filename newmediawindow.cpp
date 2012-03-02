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

QString NewMediaWindow::getName(){
    return "The Muppet SHow";//ui->nameEdit->text();
}

QString NewMediaWindow::getMedia(){
    return "../../film.avi";//ui->mediaButton->text();
}

QString NewMediaWindow::getSub(){
    return "../../film.srt";//ui->subButton->text();
}

QString NewMediaWindow::getTrSub(){
    return "";//ui->trSubButton->text();
}

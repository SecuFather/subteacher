#include "newmoviewindow.h"
#include "ui_newmoviewindow.h"

NewMovieWindow::NewMovieWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewMovieWindow)
{
    ui->setupUi(this);    
    setWindowIcon(QIcon::fromTheme("list-add"));
}

NewMovieWindow::~NewMovieWindow()
{
    delete ui;
}

void NewMovieWindow::show(bool edit){
    if(edit){
        setWindowTitle("Edit movie");
    }else{
        setWindowTitle("New Movie");
    }
    QDialog::show();
}

#include "loadmediawindow.h"
#include "ui_loadmediawindow.h"

#include <QStringList>

LoadMediaWindow::LoadMediaWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoadMediaWindow)
{
    ui->setupUi(this);
    setWindowTitle("Load");
    setWindowIcon(QIcon::fromTheme("document-open"));
}

LoadMediaWindow::~LoadMediaWindow()
{
    delete ui;
}

void LoadMediaWindow::show(QStringList *mediaList){    
    ui->mediaList->clear();
    for(int i=0; i<mediaList->count(); ++i){
        QListWidgetItem *item = new QListWidgetItem(mediaList->at(i), ui->mediaList);
    }
    QWidget::show();
}

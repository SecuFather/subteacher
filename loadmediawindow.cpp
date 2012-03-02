#include "loadmediawindow.h"
#include "ui_loadmediawindow.h"

#include <QStringList>
#include <QPushButton>

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
;

    ui->mediaList->clear();
    for(int i=0; i<mediaList->count(); ++i){
        QListWidgetItem *item = new QListWidgetItem(mediaList->at(i), ui->mediaList);
        item->setData(Qt::UserRole, i);
    }
    if(mediaList->isEmpty()){
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    }else{
        ui->mediaList->item(0)->setSelected(true);
    }
    QWidget::show();
}

QString LoadMediaWindow::getMedia(){
    return ui->mediaList->currentItem()->text();
}

int LoadMediaWindow::getIndex(){
    return ui->mediaList->currentIndex().row();
}

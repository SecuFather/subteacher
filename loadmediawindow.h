#ifndef LOADMEDIAWINDOW_H
#define LOADMEDIAWINDOW_H

#include <QDialog>

namespace Ui {
class LoadMediaWindow;
}

class LoadMediaWindow : public QDialog
{
    Q_OBJECT
    
public:
    explicit LoadMediaWindow(QWidget *parent = 0);
    ~LoadMediaWindow();

    void show(QStringList *mediaList);
    QString getMedia();
    int getIndex();    
    
private:
    Ui::LoadMediaWindow *ui;        
};

#endif // LOADMEDIAWINDOW_H

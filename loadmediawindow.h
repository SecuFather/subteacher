#ifndef LOADMEDIAWINDOW_H
#define LOADMEDIAWINDOW_H

#include <QDialog>

class QStringList;

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
    
private:
    Ui::LoadMediaWindow *ui;        
};

#endif // LOADMEDIAWINDOW_H

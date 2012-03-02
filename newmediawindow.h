#ifndef NEWMEDIAWINDOW_H
#define NEWMEDIAWINDOW_H

#include <QDialog>

namespace Ui {
class NewMediaWindow;
}

class NewMediaWindow : public QDialog
{
    Q_OBJECT
    
public:
    explicit NewMediaWindow(QWidget *parent = 0);
    ~NewMediaWindow();

    QString getName();
    QString getMedia();
    QString getSub();
    QString getTrSub();
    
private:
    Ui::NewMediaWindow *ui;
};

#endif // NEWMEDIAWINDOW_H

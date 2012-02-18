#ifndef NEWMOVIEWINDOW_H
#define NEWMOVIEWINDOW_H

#include <QDialog>

namespace Ui {
class NewMovieWindow;
}

class NewMovieWindow : public QDialog
{
    Q_OBJECT
    
public:
    explicit NewMovieWindow(QWidget *parent = 0);
    ~NewMovieWindow();

    void show(bool edit=false);
    
private:
    Ui::NewMovieWindow *ui;
};

#endif // NEWMOVIEWINDOW_H

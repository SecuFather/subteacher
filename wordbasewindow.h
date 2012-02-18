#ifndef WORDBASEWINDOW_H
#define WORDBASEWINDOW_H

#include <QDialog>

namespace Ui {
class WordBaseWindow;
}

class WordBaseWindow : public QDialog
{
    Q_OBJECT
    
public:
    explicit WordBaseWindow(QWidget *parent = 0);
    ~WordBaseWindow();
    
private:
    Ui::WordBaseWindow *ui;
};

#endif // WORDBASEWINDOW_H

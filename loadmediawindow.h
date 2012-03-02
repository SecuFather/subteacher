#ifndef LOADMEDIAWINDOW_H
#define LOADMEDIAWINDOW_H

#include <QDialog>

class MediaRow : public QString{
public:
    QString name, media, sub, trSub;
    int at;
    MediaRow(QString name, QString media, QString sub, QString trSub, int at) :
        QString(name), name(name), media(media), sub(sub), trSub(trSub), at(at){}
};

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

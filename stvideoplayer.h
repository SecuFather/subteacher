#ifndef STVIDEOPLAYER_H
#define STVIDEOPLAYER_H

#include <Phonon>
#include <phonon/VideoPlayer>
#include <QThread>
#include <QFrame>
#include "mainwindow.h"


using namespace Phonon;

class STVideoPlayer : public VideoPlayer{
    Q_OBJECT
private:
    MainWindow *parent;    
public:
    STVideoPlayer(QString fileName, MainWindow *parent);
    ~STVideoPlayer();
public slots:
    void playPauseVideo();
    void stopVideo();
};

#endif // STVIDEOPLAYER_H

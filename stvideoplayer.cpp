#include "stvideoplayer.h"
#include <QPushButton>

STVideoPlayer::STVideoPlayer(QString fileName, MainWindow *parent):
    VideoPlayer(VideoCategory, parent->getVideoFrame()), parent(parent){

    setFixedSize(800, 400);
    load(MediaSource(fileName));

    QObject::connect(parent->getPlayPauseButton(), SIGNAL(clicked()),
                     this, SLOT(playPauseVideo()));
    QObject::connect(parent->getStopButton(), SIGNAL(clicked()),
                     this, SLOT(stopVideo()));
}
void STVideoPlayer::playPauseVideo(){
    if(isPlaying()){
        pause();
        parent->getPlayPauseButton()->setText("Play");
    }else{
        play();
        parent->getPlayPauseButton()->setText("Pause");
    }
}
void STVideoPlayer::stopVideo(){
    stop();
    parent->getPlayPauseButton()->setText("Play");
}
STVideoPlayer::~STVideoPlayer(){
    qDebug("vDestruct");
}

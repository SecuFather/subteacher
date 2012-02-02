#ifndef SUBMANAGER_H
#define SUBMANAGER_H

#include "stvideoplayer.h"
#include <QThread>
#include <QTextStream>
#include <QFile>
#include <QTime>



class SubManager : public QThread{
    Q_OBJECT
private:
    QTextStream *lyricStream;    
    QTextStream *trLyricStream;
    QString sub, answer, hint, fileName, trFileName, srtLine;
    MainWindow *parent;
    STVideoPlayer* vp;
    QFile *file;    
    QFile *trFile;
    bool saving;
    qint64 trSubDelay;
public:
    SubManager(QString fileName, QString trFileName, MainWindow *parent, STVideoPlayer* vp);

    void loadLyrics();
    void run();
    qint64 srtToInt(QString line);
    bool srtToInt(QTextStream *txtStream, qint64 &subStart, qint64 &subEnd);
    QString getSub(QTextStream *txtStream);
    QString generateHint();
    bool isLetterOrNumber(QChar c);    
    int skipSignes(QString str, int i, bool start=false);
    int subRand(int n);

    ~SubManager();
signals:
    void subEndSignal();
    void repeatSub(qint64 subStart);
    void hintEditChanged(QString str);
    void trEditChanged(QString str);
    void enablePlayPause(bool state);

public slots:
    void checkSub();
    void help();
    void skip();
    void save();
    void incSubDelay();
    void decSubDelay();
    void incTrSubDelay();
    void decTrSubDelay();
};

#endif // SUBMANAGER_H

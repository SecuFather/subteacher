#ifndef SUBTEACHERTHREAD_H
#define SUBTEACHERTHREAD_H

#include <Phonon>
#include <phonon/VideoPlayer>
#include <QThread>
class SubManager;

using namespace Phonon;

class SubTeacherThread : public QThread
{
    Q_OBJECT
public:
    explicit SubTeacherThread(VideoPlayer *vp, SubManager *sm);
    ~SubTeacherThread();
        
    void run();
    void run(bool correct);

    void loadMediaList();
    void saveMediaList();
    bool addMedia(QString name, QString media, QString sub, QString trSub, int at);

    QStringList *getNameList();
    QString getMedia(int i);
    QString getSub(int i);
    QString getTrSub(int i);
    int getAt(int i);

    void setSubManager(SubManager *sm);
private:
    VideoPlayer *vp;
    SubManager *sm;
    bool correct, step, first;
    QStringList *nameList, *mediaList, *subList, *trSubList;
    QList<int> *atList;

    const QString mediaListFileName;
signals:
    void mediaPlay(bool);
    void mediaRestart();
    void showSubs(bool);

};

#endif // SUBTEACHERTHREAD_H

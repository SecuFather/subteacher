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
        
    void run();
    void run(bool correct);
private:
    VideoPlayer *vp;
    SubManager *sm;
    bool correct, step, first;
signals:
    void mediaPlay(bool);
    void mediaRestart();
    void showSubs(bool);

};

#endif // SUBTEACHERTHREAD_H

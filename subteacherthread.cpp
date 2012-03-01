#include "subteacherthread.h"
#include "submanager.h"

SubTeacherThread::SubTeacherThread(VideoPlayer *vp, SubManager *sm) :
    QThread(0), vp(vp), sm(sm), correct(false), step(true), first(true)
{    
    start();
}

void SubTeacherThread::run(){    
    bool b=false;

    while(true){
        while(!step);

        if(!first || (first=false)){
            int s = sm->currentSubStart() - sm->getSubMargin();
            if(s<0){
                s=0;
            }
            vp->seek(s);
            while(sm->finishSubFrame(vp->currentTime()));
            if(correct){
                b = false;
                if(!sm->next()){
                    emit mediaRestart();
                }
            }else{
                b = true;
            }
        }

        emit mediaPlay(true);        

        while(sm->startSubFrame(vp->currentTime()));
        emit showSubs(b);

        while(!sm->finishSubFrame(vp->currentTime()));

        emit mediaPlay(false);        

        step = false;        
    }
}

void SubTeacherThread::run(bool correct){
    this->correct = correct;
    step = true;
}


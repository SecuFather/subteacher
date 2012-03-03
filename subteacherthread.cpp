#include "subteacherthread.h"
#include "submanager.h"

#include <QFile>

SubTeacherThread::SubTeacherThread(VideoPlayer *vp, SubManager *sm) :
    QThread(0), vp(vp), sm(sm), correct(false), step(false), first(true),
    nameList(new QStringList()), mediaList(new QStringList()), subList(new QStringList()),
    trSubList(new QStringList()),atList(new QList<int>()),
    mediaListFileName("medialist.dat")
{    
    start();
    loadMediaList();
}

SubTeacherThread::~SubTeacherThread(){
    saveMediaList();
}

void SubTeacherThread::run(){    
    bool b=false;

    while(true){
        while(!step);

        if(!first || (first=false) || sm->currentAt()){
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

void SubTeacherThread::loadMediaList(){
    QFile file(mediaListFileName);

    if(file.open(QFile::ReadOnly)){
        QTextStream ts(&file);

        while(!ts.readLine().isEmpty()){
            nameList->push_back(ts.readLine());
            mediaList->push_back(ts.readLine());
            subList->push_back(ts.readLine());
            trSubList->push_back(ts.readLine());
            atList->push_back(ts.readLine().toInt());
        }
        file.close();
    }
}

void SubTeacherThread::saveMediaList(){
    QFile file(mediaListFileName);

    if(file.open(QIODevice::Text | QIODevice::WriteOnly)){
        QTextStream ts(&file);
        for(int i=0; i<nameList->count(); ++i){
            ts << "#\n";
            ts << nameList->at(i) << "\n";
            ts << mediaList->at(i) << "\n";
            ts << subList->at(i) << "\n";
            ts << trSubList->at(i) << "\n";
            ts << atList->at(i) << "\n";
        }
        file.close();
    }
}

bool SubTeacherThread::addMedia(QString name, QString media, QString sub, QString trSub, int at){
    if(qFind(nameList->begin(), nameList->end(), name) != nameList->end()){
        return false;
    }
    nameList->push_front(name);
    mediaList->push_front(media);
    subList->push_front(sub);
    trSubList->push_front(trSub);
    atList->push_front(at);

    return true;
}

QStringList *SubTeacherThread::getNameList(){
    return nameList;
}

QString SubTeacherThread::getMedia(int i){
    return mediaList->at(i);
}

QString SubTeacherThread::getSub(int i){
    return subList->at(i);
}

QString SubTeacherThread::getTrSub(int i){
    return trSubList->at(i);
}

int SubTeacherThread::getAt(int i){
    return atList->at(i);
}

void SubTeacherThread::setAt(int i){
    atList->replace(i, sm->currentAt());
}

void SubTeacherThread::setSubManager(SubManager *sm){
    this->sm = sm;
    first = true;
    step = true;
}

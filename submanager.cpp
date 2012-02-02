#include "submanager.h"
#include <QFile>

SubManager::SubManager(QString fileName, QString trFileName, MainWindow *parent, STVideoPlayer* vp)
    : parent(parent), vp(vp), file(0), trFile(0), fileName(fileName), trFileName(trFileName),
      saving(false), trSubDelay(63000){

    loadLyrics();

    QObject::connect(this, SIGNAL(hintEditChanged(QString)),
                     parent, SLOT(setHintEdit(QString)));
    QObject::connect(this, SIGNAL(trEditChanged(QString)),
                     parent, SLOT(setTrEdit(QString)));
    QObject::connect(parent->getCheckButton(), SIGNAL(clicked()),
                     this, SLOT(checkSub()));
    QObject::connect(parent->getHintButton(), SIGNAL(clicked()),
                     this, SLOT(help()));
    QObject::connect(parent->getSkipButton(), SIGNAL(clicked()),
                     this, SLOT(skip()));    
    QObject::connect(this, SIGNAL(enablePlayPause(bool)),
                     parent, SLOT(enablePlayPause(bool)));
    QObject::connect(parent->getIncSubDelayAction(), SIGNAL(triggered()),
                     this, SLOT(incSubDelay()));
    QObject::connect(parent->getDecSubDelayAction(), SIGNAL(triggered()),
                     this, SLOT(decSubDelay()));
    QObject::connect(parent->getIncTrSubDelayAction(), SIGNAL(triggered()),
                     this, SLOT(incTrSubDelay()));
    QObject::connect(parent->getDecTrSubDelayAction(), SIGNAL(triggered()),
                     this, SLOT(decTrSubDelay()));


    qsrand(QTime::currentTime().msec());    

    start();
}

void SubManager::loadLyrics(){
    if(!fileName.isEmpty()){
        file = new QFile("../subteacher/temp.srt");
        if(!file->open(QFile::ReadOnly)){
            delete file;
            file = new QFile(fileName);
            file->open(QFile::ReadOnly);
        }
        lyricStream = new QTextStream(file);
    }

    if(!trFileName.isEmpty()){
        trFile = new QFile(trFileName);
        trFile->open(QFile::ReadOnly);
        trLyricStream = new QTextStream(trFile);
    }

}
void SubManager::run(){
    qint64 subStart=0, subEnd=0;
    qint64 trSubStart, trSubEnd;    
    bool start = true;


    srtToInt(trLyricStream, trSubStart, trSubEnd);
    while(srtToInt(lyricStream, subStart, subEnd)){                
        sub = getSub(lyricStream);

        if(start){
            vp->play();
            sleep(1);
            vp->seek(subStart - 5000 < 0 ? 0 : subStart - 5000);
            start = false;
        }

        do{
            hint = generateHint();
            emit enablePlayPause(true);
            while(vp->currentTime() < subStart);            
            emit hintEditChanged(hint);
            while(vp->currentTime() < subEnd);
            emit enablePlayPause(false);

            if(hint != sub){
                vp->pause();
                vp->seek(subStart-1000);                
            }else{
                break;
            }
            while(answer.isEmpty()){
                sleep(1);
            }
            vp->play();
        }while(true);

        while(trSubEnd <= subStart-trSubDelay){
            emit trEditChanged(getSub(trLyricStream));
            srtToInt(trLyricStream, trSubStart, trSubEnd);
        }
        while(saving){
            sleep(1);
        }
    }
}
qint64 SubManager::srtToInt(QString line){
    QStringList strList = line.split(',');
    qint64 converted = strList.at(1).toInt();
    strList = strList.at(0).split(':');
    converted += strList.at(2).toInt()*1000;
    converted += strList.at(1).toInt()*60000;
    converted += strList.at(0).toInt()*3600000;

    return converted;
}
bool SubManager::srtToInt(QTextStream *txtStream, qint64 &subStart, qint64 &subEnd){
    srtLine.clear();
    QString line = txtStream->readLine();    
    srtLine.append(line);
    if(line.isEmpty()){
        return false;
    }
    line = txtStream->readLine();
    srtLine.append("\n" + line);
    QStringList strList = line.split(" --> ");
    subStart = srtToInt(strList.at(0));
    subEnd = srtToInt(strList.at(1));

    return true;
}
QString SubManager::getSub(QTextStream *txtStream){
    QString temp, sub;

    while(!(temp = txtStream->readLine()).isEmpty()){
        if(sub.isEmpty()){
            sub.append(temp);
        }else{
            sub.append("\n"+temp);
        }
    }
    srtLine.append("\n" + sub);
    srtLine.append("\n\n");
    return sub;
}

QString SubManager::generateHint(){
    QString hint = sub;
    QChar cSub, cAns;
    bool forceInsert = false;

    int j0 = skipSignes(answer, 0, true) + 1;
    for(int i=0, j=j0; i<sub.size(); ++i, ++j){
        cSub = sub[i];
        if(j >= answer.size()){
            forceInsert = true;
        }else{
            cAns = answer[j];
        }
        if(isLetterOrNumber(cSub)){
            if(isLetterOrNumber(cAns)){
                if(forceInsert || cSub.toLower() != cAns.toLower()){
                    hint[i] = '#';
                }
            }else{
                --j;
                hint[i] = '#';
            }
        }else{
            i = skipSignes(sub, i);
            j = skipSignes(answer, j);
        }
    }
    answer.clear();
    return hint;
}

bool SubManager::isLetterOrNumber(QChar c){
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9');
}


int SubManager::skipSignes(QString str, int index, bool start){
    if(!start && isLetterOrNumber(str[index])){
        start = false;
    }
    for(int i=index; i<str.size(); ++i){
        if(isLetterOrNumber(str[i])){
            if(start){
                return i-1;
            }
        }else{
            start = true;
        }
    }
    return str.size();
}

int SubManager::subRand(int n){
    return qrand()%n;
}

void SubManager::checkSub(){
    if(!parent->getCheckButton()->isEnabled()){
        return;
    }
    answer = parent->getAnswerEdit()->toPlainText();
    if(answer.isEmpty()){
        answer = " ";
    }
}

void SubManager::help(){    
    for(int i=0; i<hint.size(); ++i){
        if(hint[i] == '#'){
            hint[i]=sub[i];
            emit hintEditChanged(hint);
            return;
        }
    }
}

void SubManager::skip(){
    hint = answer = sub;
}

void SubManager::save(){
    saving = true;
    QFile saveFile("../subteacher/temp.srt");
    saveFile.open(QFile::WriteOnly);
    QTextStream tempStream(&saveFile);
    tempStream<<srtLine;
    tempStream<<lyricStream->readAll();
    saving = false;
}

void SubManager::incSubDelay(){

}

void SubManager::decSubDelay(){

}

void SubManager::incTrSubDelay(){
    trSubDelay += 500;
    qDebug(QString::number(trSubDelay).toAscii());
}

void SubManager::decTrSubDelay(){
    trSubDelay -=500;

    qDebug(QString::number(trSubDelay).toAscii());
}


SubManager::~SubManager(){    
    save();
    if(file){
        file->close();
        delete file;
            delete lyricStream;
    }

    if(trFile){
        trFile->close();
        delete trFile;
        delete trLyricStream;
    }
    qDebug("SubDestruct");
}


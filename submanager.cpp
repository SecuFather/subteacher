#include "submanager.h"

#include <QString>
#include <QFile>
#include <QTextStream>
#include <QStack>
#include <QStringList>

SubManager::SubManager(QString filePath) :  at(0), init(false){
    QFile file(filePath);
    QString line;
    QStack<int> subStartStack;
    QStack<int> subEndStack;
    QStack<QString*> subStack;

    if(file.open(QFile::ReadOnly)){
        QTextStream ts(&file);

        for(n=0; !ts.readLine().isEmpty(); ++n){
            line = ts.readLine();
            subStartStack.push_front(getSubStart(line));
            subEndStack.push_front(getSubEnd(line));

            subStack.push_front(new QString());
            while(!(line = ts.readLine()).isEmpty()){
                subStack.front()->append(line);
            }
        }
        if(n > 0){
            init = true;
            subStart = new int[n];
            subEnd = new int[n];
            sub = new QString*[n];

            for(int i=0; i<n; ++i){
                subStart[i] = subStartStack.top();
                subStartStack.pop_back();
                subEnd[i] = subEndStack.top();
                subEndStack.pop_back();
                sub[i] = subStack.top();
                subStack.pop_back();
            }
        }
        file.close();
    }
}

SubManager::~SubManager(){
    if(init){
        for(int i=0; i<n; ++i){
            delete sub[i];
        }
        delete[] sub;
        delete[] subEnd;
        delete[] subStart;
    }
}

int SubManager::getSubStart(const QString &time){
    return timeToInt(time.split(" --> ").at(0));
}

int SubManager::getSubEnd(const QString &time){
    return timeToInt(time.split(" --> ").at(1));
}

int SubManager::timeToInt(const QString &time){
    QString ms = time.split(",").at(1);
    QStringList tmp = time.split(",").at(0).split(":");

    return ms.toInt() + tmp.at(2).toInt()*1000 + tmp.at(1).toInt()*60000 + tmp.at(0).toInt()*3600000;
}

QString SubManager::getSub(int i){
    return *sub[i];
}

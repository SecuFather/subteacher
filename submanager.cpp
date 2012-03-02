#include "submanager.h"

#include <QString>
#include <QFile>
#include <QTextStream>
#include <QStack>
#include <QStringList>

SubManager::SubManager(QString filePath, int subMargin) :  at(0), subMargin(subMargin), init(false){
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
                subStack.front()->append(line + "\n");
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
                sub[i]->replace('#', ' ');
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

bool SubManager::next(){
    if(n == ++at){
        return false;
    }
    return true;
}

QString SubManager::currentHint(QString ans){
    int e;
    return currentHint(ans, e);
}


QString SubManager::currentHint(QString ans, int &e){
    QString result = *sub[at];
    int ansLength = ans.length();
    int resLength = result.length();
    e=0;

    for(int i=0,j=0; i<resLength;){
        while(i<resLength && !result[i].isLetterOrNumber()){
            ++i;
        }
        while(j<ansLength && !ans[j].isLetterOrNumber()){
            ++j;
        }
        while(i<resLength && result[i].isLetterOrNumber()){
            if(j<ansLength && ans[j].isLetterOrNumber()){
                if(ans[j].toLower() != result[i].toLower()){
                    result[i]='#';
                    ++e;
                }
                ++j;
            }else{
                result[i]='#';
                ++e;
            }
            ++i;
        }
        while(j<ansLength && ans[j].isLetterOrNumber()){
            ++j;
        }
    }    
    return result;
}

QString SubManager::currentSub(){
    return *sub[at];
}

int SubManager::currentSubStart(){
    return subStart[at];
}

QString SubManager::help(QString hint){
    for(int i=0; i<hint.length(); ++i){
        if(!hint[i].isLetterOrNumber() && sub[at]->at(i).isLetterOrNumber()){
            hint[i] = sub[at]->at(i);
            return hint;
        }
    }
    return hint;
}

int SubManager::getSubMargin(){
    return subMargin;
}

bool SubManager::startSubFrame(int current){
    return (current <  subStart[at]-subMargin);
}

bool SubManager::finishSubFrame(int current){
    return (current > subEnd[at]+subMargin);
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


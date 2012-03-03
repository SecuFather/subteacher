#ifndef SUBMANAGER_H
#define SUBMANAGER_H

class QString;

class SubManager
{
private:
    int at, n, *subStart, *subEnd, subMargin;
    QString **sub;
    bool init;

    int getSubStart(const QString &time);
    int getSubEnd(const QString &time);
    int timeToInt(const QString &time);
public:
    SubManager(QString filePath, int at, int subMargin=0);
    ~SubManager();

    bool next();

    QString currentHint(QString ans);
    QString currentHint(QString ans, int &e);
    QString currentSub();    
    int currentSubStart();
    int currentAt();
    QString help(QString hint);

    int getSubMargin();

    bool startSubFrame(int current);
    bool finishSubFrame(int current);    
};

#endif // SUBMANAGER_H

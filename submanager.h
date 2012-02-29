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
    SubManager(QString filePath, int subMargin=0);
    ~SubManager();

    bool next();
    QString currentSub();
    int currentSubStart();
    int getSubMargin();

    bool startSubFrame(int current);
    bool finishSubFrame(int current);
};

#endif // SUBMANAGER_H

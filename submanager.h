#ifndef SUBMANAGER_H
#define SUBMANAGER_H

class QString;

class SubManager
{
private:
    int at, n, *subStart, *subEnd;
    QString **sub;
    bool init;

public:
    SubManager(QString filePath);
    ~SubManager();

    int getSubStart(const QString &time);
    int getSubEnd(const QString &time);
    int timeToInt(const QString &time);
    QString getSub(int i);
};

#endif // SUBMANAGER_H

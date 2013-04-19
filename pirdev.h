#ifndef PIRDEV_H
#define PIRDEV_H

#include <QObject>

class pirdev : public QObject
{
    Q_OBJECT
public:
    explicit pirdev(QObject *parent = 0);
    Q_INVOKABLE void start(const QString proxy,const QString port);
//    Q_INVOKABLE QString check(void) ;
    Q_INVOKABLE void del(void);
    Q_INVOKABLE QString get(void);
    
};

#endif // PIRDEV_H

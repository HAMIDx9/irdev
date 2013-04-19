#include "pirdev.h"
#include <QDebug>
#include <QFile>
#include <QProcess>
#include <QRegExp>

pirdev::pirdev(QObject *parent) :
    QObject(parent)
{
}

void pirdev::start(const QString proxy,const QString port){

    if ( proxy != ""  && port != "" ) {
    QString pip,pport;

    pip = proxy;
    pport = port;
    qDebug() << pip + ":" + pport ;
    QString http = "Acquire::http::Proxy \"http://" + pip + ":" + pport + "/\";";
    QString https = "Acquire::https::Proxy \"https://" + pip + ":" + pport + "/\";";

    qDebug() << http << "\n" << https;

    QFile f("/tmp/ir-dev.sh");
    if (!f.open(QFile::WriteOnly|QFile::Truncate)) {
        qDebug() << "[0]Error: File cannot be created" << "";
        exit(1);
    }

    QTextStream ts(&f) ;
    ts << "#!/bin/sh\n" << "cp -Rf /tmp/01proxy /etc/apt/apt.conf.d/";
    f.close();
      /////

    QFile f1("/tmp/01proxy");
    if (!f1.open(QFile::WriteOnly|QFile::Truncate)) {
        qDebug() << "[1]Error: File cannot be created" << "";
        exit(1);
    }
    QTextStream ts1(&f1);
    ts1 << http + "\n" + https;
    f1.close();

    ////
    QStringList args;

    QFile f2("/tmp/ir-dev2.sh");
    if (!f2.open(QFile::WriteOnly|QFile::Truncate)){
        qDebug() << "[2]Error: File cannot be created" << "";
        exit(1);
    }
    QTextStream ts2(&f2);
    ts2 << "#!/bin/sh\n\n" <<  "export _SBOX_DIR=xxx\n\n" << "/usr/lib/package-manager/pm-notification-tool.sh perl -e \'$<=0;$>=0;exec(\"sh\",\"/tmp/ir-dev.sh\")\' ";

    f2.close();
    args << "/tmp/ir-dev2.sh";
    QProcess::startDetached("/bin/sh",args);
    }
    else
    {
        qDebug() << "Error";
        //exit(1);
    }
}

//QString pirdev::check(void) {

//    QFile f("/etc/apt/apt.conf.d/01proxy");

//    if (f.exists()) {
//        qDebug() << "01proxy exists...";
//        return 0;
//    } else {
//        qDebug() << "01proxy does not exist...";
//        return 1;
//    }
//}

QString pirdev::get(void){

    QFile myfile("/etc/apt/apt.conf.d/01proxy");
    QString Line;
    if (!myfile.open(QFile::ReadOnly)) {
        qDebug() << "There is a problem in reading /etc/apt/apt.conf.d/01proxy...";
        return "Disabled!";
    }

    QRegExp rx("(\\d{1,3}.\\d{1,3}.\\d{1,3}.\\d{1,3}:\\d{3,5})");
    QTextStream stream(&myfile);
    Line = stream.readLine();
//    qDebug() << Line ;
    int pos = 0;

    while ((pos = rx.indexIn(Line, pos)) != -1)
    {
        if (rx.cap(1) != "") {
        qDebug() << "Extracted IP & PORT Address: " << rx.cap(1);
        break;
        }
        pos += rx.matchedLength();
    }
    return rx.cap(1);

}

void pirdev::del(void){

    QFile f3("/tmp/del-ir-dev.sh");
    if (!f3.open(QFile::WriteOnly|QFile::Truncate)){
        qDebug() << "[3]Error: File cannot be created" << "";
        exit(1);
    }
    QTextStream ts3(&f3);
    ts3 << "#!/bin/sh\n\n" <<  "export _SBOX_DIR=xxx\n\n" << "/usr/lib/package-manager/pm-notification-tool.sh perl -e \'$<=0;$>=0;exec(\"rm\",\"-f\",\"/etc/apt/apt.conf.d/01proxy\")\' ";

    f3.close();

    QStringList args;
    args << "/tmp/del-ir-dev.sh";
    QProcess::startDetached("/bin/sh",args);
}




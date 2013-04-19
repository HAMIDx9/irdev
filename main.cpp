#include <QtGui/QApplication>
#include "qmlapplicationviewer.h"
#include <QtDeclarative>
#include "pirdev.h"
#include <QObject>

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QScopedPointer<QApplication> app(createApplication(argc, argv));

    QDeclarativeView *viewer = new QDeclarativeView();
    pirdev *p1 = new pirdev();

    viewer->rootContext()->setContextProperty("pirdev",p1);

    QObject::connect(viewer->engine(), SIGNAL(quit()), QCoreApplication::instance(), SLOT(quit()));
    viewer->setWindowTitle("IR Dev-Mode Enabler");
    viewer->setSource(QUrl("qrc:/qml/main.qml"));
    viewer->showFullScreen();

    return app->exec();
}

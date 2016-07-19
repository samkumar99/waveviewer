#include <QGuiApplication>
#include <QQmlApplicationEngine>

#ifdef Q_OS_ANDROID
#include <QAndroidJniObject>
#include <QtAndroid>
#endif
#include "waveviewer.h"

#include <libbw.h>
#include <libmrplotter.h>

int main(int argc, char *argv[])
{
    qDebug() << "init guiapp";
    QGuiApplication app(argc, argv);
    qDebug() << "finished init guiapp";
    initLibBW();
    initLibMrPlotter();

    WaveViewer *wv = WaveViewer::instance();
    Q_UNUSED(wv)
    return app.exec();
}

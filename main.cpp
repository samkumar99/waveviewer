#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "waveviewer.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    WaveViewer *wv = WaveViewer::instance();
    Q_UNUSED(wv)

    return app.exec();
}
#ifndef QRSNOOPER_H
#define QRSNOOPER_H

#include <QObject>
#include <QVideoFrame>
#include <QVideoProbe>

#include <QZXing.h>

class QRSnooper : public QObject
{
    Q_OBJECT

public:
    QRSnooper(QObject* parent = nullptr);

    Q_INVOKABLE void setInputQMLCamera(const QVariant& cameraVar);

signals:
    void decodedQRCode(QString decoded);

private slots:
    void handleVideoFrame(const QVideoFrame& probed);

private:

    const QVideoFrame* lastFrame;
    QVideoProbe* probe;

    QZXing* decoder;
};

#endif // QRSNOOPER_H

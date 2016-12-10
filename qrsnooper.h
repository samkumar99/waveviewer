#ifndef QRSNOOPER_H
#define QRSNOOPER_H

#include <QAbstractVideoSurface>
#include <QVideoFrame>
#include <QZXing.h>

class QRSearcher : public QAbstractVideoSurface
{
    Q_OBJECT
    Q_PROPERTY(QAbstractVideoSurface videoSurface MEMBER videoSurface)
public:
    QRSearcher(QObject* parent = nullptr);

    virtual bool present(const QVideoFrame& frame);

signals:
    void decodedQRCode(QString decoded);

private:

    QAbstractVideoSurface* output;
    const QVideoFrame* lastFrame;

    QZXing decoder;
};

#endif // QRSNOOPER_H

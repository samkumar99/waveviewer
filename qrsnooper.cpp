#include "qrsnooper.h"

#include <QAbstractVideoSurface>
#include <QCamera>
#include <QCameraViewfinderSettings>
#include <QImage>
#include <QString>
#include <QVideoFrame>

#include <QZXing.h>

QRSnooper::QRSnooper(QObject* parent) : QObject(parent)
{
    this->decoder = new QZXing(this);
    this->decoder->setDecoder(QZXing::DecoderFormat::DecoderFormat_QR_CODE);
    this->probe = new QVideoProbe(this);
}

void QRSnooper::setInputQMLCamera(const QVariant& cameraVar)
{
    QObject* cameraObj = cameraVar.value<QObject*>();
    QCamera* camera = cameraObj->property("mediaObject").value<QCamera*>();

    if (camera != nullptr)
    {
        if (probe->setSource(camera))
        {
            qDebug("Connecting the signal to the slot");
            QObject::connect(this->probe, SIGNAL(videoFrameProbed(const QVideoFrame&)),
                             this, SLOT(handleVideoFrame(const QVideoFrame&)));
        }
    }
}

void QRSnooper::handleVideoFrame(const QVideoFrame& probed)
{
    QImage img;
    QVideoFrame copy(probed);
    copy.map(QAbstractVideoBuffer::MapMode::ReadOnly);
    QImage::Format imgFormat = QVideoFrame::imageFormatFromPixelFormat(copy.pixelFormat());
    qDebug("imgFormat: %d, pixelFormat: %d", imgFormat, copy.pixelFormat());
    if (imgFormat != QImage::Format_Invalid)
    {
        img = QImage(copy.bits(), copy.width(), copy.height(), copy.bytesPerLine(), imgFormat);
    }
    else
    {
        img = QImage::fromData(copy.bits(), copy.mappedBytes());
        qDebug("Null? %d", img.isNull());
    }
    QString decoded = this->decoder->decodeImage(img);
    copy.unmap();

    if (!decoded.isEmpty())
    {
        qDebug("Finished decoding: %s", qPrintable(decoded));
        emit this->decodedQRCode(decoded);
    }
}

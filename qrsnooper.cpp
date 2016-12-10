#include "qrsnooper.h"

#include <QAbstractVideoSurface>
#include <QVideoFrame>

QRSnooper::QRSnooper(QObject* parent) : QAbstractVideoSurface(parent)
{
    this->output = nullptr;
    this->lastFrame = nullptr;
}

virtual bool QRSnooper::present(const QVideoFrame& frame) {
    if (frame.isValid()) {
        this->lastFrame = &frame;
    }

    /* Pass it on to the target... */
    if (this->output != nullptr) {
        this->output->present(frame);
    }
}

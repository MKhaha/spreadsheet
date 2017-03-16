#include <QDateTime>
#include "qrencodepublic.h"
#include "qrencode.h"

#define INCHES_PER_METER (100.0/2.54)

QrencodePublic::QrencodePublic()
{
    d_ptr = new QrencodePri();
}

QrencodePublic::~QrencodePublic()
{
    delete d_ptr;
}

void QrencodePublic::setLevel(QrencodePublic::ErrorCorrectionLevel value)
{

    switch (value) {
    case LOW:
        d_ptr->m_level = QR_ECLEVEL_L;
        break;
    case MEDIUM:
        d_ptr->m_level = QR_ECLEVEL_M;
        break;
    case QUARTILE:
        d_ptr->m_level = QR_ECLEVEL_Q;
        break;
    case HIGH:
        d_ptr->m_level = QR_ECLEVEL_H;
        break;
    }
}

QrencodePublic::ErrorCorrectionLevel QrencodePublic::getLevel() const
{
    switch (d_ptr->m_level) {
    case QR_ECLEVEL_L:
        return LOW;
    case QR_ECLEVEL_M:
        return MEDIUM;
    case QR_ECLEVEL_Q:
        return QUARTILE;
    case QR_ECLEVEL_H:
        return HIGH;
    }
    return LOW;
}

void QrencodePublic::setVersion(int version)
{

    // 1 - 40
    if (version > 0 && version <= 40)
        d_ptr->m_version = version;
}

int QrencodePublic::version() const
{
    return d_ptr->m_version;
}

void QrencodePublic::setMargin(int value)
{

    if (value > -1)
        d_ptr->m_margin = value;
}

int QrencodePublic::margin() const
{
    return d_ptr->m_margin;
}

void QrencodePublic::setMicro(bool value)
{

    d_ptr->m_micro = (value) ? 1 : 0;
}

bool QrencodePublic::isMicro() const
{
    return (d_ptr->m_micro == 1) ? true : false;
}

void QrencodePublic::setBackground(QColor color)
{

    d_ptr->m_bg.setColor(color);
}

void QrencodePublic::setForeground(QColor color)
{

    d_ptr->m_fg.setColor(color);
    d_ptr->m_pen.setColor(color);
}

bool QrencodePublic::encode(QByteArray input)
{

    QRcode *c = NULL;
    if (input.isEmpty()) return false;
    if (d_ptr->m_micro) {
        c = QRcode_encodeDataMQR(input.size(), (const unsigned char*)input.constData(),
                                   d_ptr->m_version, d_ptr->m_level);
    } else {
        c = QRcode_encodeData(input.size(), (const unsigned char*)input.constData(),
                              d_ptr->m_version, d_ptr->m_level);
    }
    if (c == NULL) {
        return false;
    }
    if (d_ptr->m_code) QRcode_free(d_ptr->m_code);
    d_ptr->m_code = c;
    return true;
}

bool QrencodePublic::encode(QString input, bool caseSensitive)
{

    if (input.isEmpty()) return false;
    QRcode *c = NULL;
    if (d_ptr->m_micro) {
        c = QRcode_encodeStringMQR(input.toStdString().c_str(),
                                   d_ptr->m_version,
                                   d_ptr->m_level,
                                   QR_MODE_8,
                                   (caseSensitive) ? 1 : 0);
    } else {
        c = QRcode_encodeString(input.toStdString().c_str(),
                                d_ptr->m_version,
                                d_ptr->m_level,
                                QR_MODE_8,
                                (caseSensitive) ? 1 : 0);
    }
    if (c == NULL) {
        return false;
    }
    if (d_ptr->m_code) QRcode_free(d_ptr->m_code);
    d_ptr->m_code = c;
    return true;
}

bool QrencodePublic::encodeKanji(QByteArray input, bool caseSensitive)
{

    if (input.isEmpty()) return false;
    QRcode *c = NULL;
    if (d_ptr->m_micro) {
        c = QRcode_encodeStringMQR(input.constData(),
                                   d_ptr->m_version,
                                   d_ptr->m_level,
                                   QR_MODE_KANJI,
                                   (caseSensitive) ? 1 : 0);
    } else {
        c = QRcode_encodeString(input.constData(),
                                d_ptr->m_version,
                                d_ptr->m_level,
                                QR_MODE_KANJI,
                                (caseSensitive) ? 1 : 0);
    }
    if (c == NULL) {
        return false;
    }
    if (d_ptr->m_code) QRcode_free(d_ptr->m_code);
    d_ptr->m_code = c;
    return true;
}

//bool QrencodePublic::toSVG(QString output, int size)
//{

//    if (output.isEmpty() || d_ptr->m_code == NULL) {
//        return false;
//    }
//    QSvgGenerator generator;
//    generator.setFileName(output);
//    generator.setSize(QSize(size, size));
//    int symwidth = d_ptr->m_code->width + d_ptr->m_margin * 2;
//    generator.setViewBox(QRect(0, 0, symwidth, symwidth));

//    QPainter painter;
//    painter.begin(&generator);
//    d_ptr->paint(painter);
//    painter.end();

//    return true;
//}

QImage QrencodePublic::toQImage(int size)
{

    if (size < 0) throw std::invalid_argument("Invalid size");

    if (d_ptr->m_code == NULL) {
        std::logic_error("No qr code to convert");
    }

    int symwidth = d_ptr->m_code->width + d_ptr->m_margin * 2;
    QImage result(QSize(symwidth, symwidth), QImage::Format_Mono);
    result.fill(Qt::white);

    QPainter painter;
    painter.begin(&result);
    d_ptr->paint(painter);
    painter.end();

    if (size > 0)
        return result.scaled(size, size);
    return result;
}

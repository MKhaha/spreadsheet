#ifndef QRENCODEPUBLIC_H
#define QRENCODEPUBLIC_H

#include <QImage>
#include "qrencodepri.h"
class QrencodePublic
{
public:
    enum ErrorCorrectionLevel {
        LOW,
        MEDIUM,
        QUARTILE,
        HIGH
    };
    QrencodePublic();
    ~QrencodePublic();

    void setLevel(ErrorCorrectionLevel value);
    ErrorCorrectionLevel getLevel() const;
    void setVersion(int version);
    int version() const;
    void setMargin(int value);
    int margin() const;
    void setMicro(bool value);
    bool isMicro() const;
    void setBackground(QColor color);
    void setForeground(QColor color);

    bool encode(QByteArray input);
    bool encode(QString input, bool caseSensitive=true);
    bool encodeKanji(QByteArray input, bool caseSensitive=true);

    QImage toQImage(int size=0);

private:
    QrencodePri *d_ptr;
};

#endif // QRENCODEPUBLIC_H

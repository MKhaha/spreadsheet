#ifndef QRENCODEPRI_H
#define QRENCODEPRI_H

#include <QPen>
#include <QBrush>
#include <QPainter>
#include "qrencode.h"

class QrencodePri
{
public:
    QrencodePri()
        : m_code(NULL), m_level(QR_ECLEVEL_H),m_version(1), m_margin(4), m_micro(0),
          m_pen(Qt::black, 0.1, Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin), m_bg(Qt::white),
          m_fg(Qt::black)
    {
    }

    ~QrencodePri();

    void paint(QPainter &painter);

    QRcode *m_code;
    QRecLevel m_level;
    int m_version;
    int m_margin;
    int m_micro;
    QPen m_pen;
    QBrush m_bg;
    QBrush m_fg;
};

#endif // QRENCODEPRI_H

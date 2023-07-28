#ifndef SWAYDISPLAY_HPP
#define SWAYDISPLAY_HPP

#include <QRectF>

class SwayDisplay {
public:
    SwayDisplay(double x, double y, double width, double height, QString name);
    QRectF getRect();
    double getDivisor();

    double x;
    double y;
    double width;
    double height;

    QString name;
};

#endif // SWAYDISPLAY_HPP

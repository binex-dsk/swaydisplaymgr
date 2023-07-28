#include "swaydisplay.hpp"

SwayDisplay::SwayDisplay(double x, double y, double width, double height, QString name) :
    x(x),
    y(y),
    width(width),
    height(height),
    name(name)
{}

QRectF SwayDisplay::getRect() {
    qsizetype divisor = qMax(width, height) / 250.; // TODO: dynamically scale based upon display size?

    return QRectF(x / divisor, y / divisor, width / divisor, height / divisor);
}

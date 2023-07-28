#include "swaydisplay.hpp"

SwayDisplay::SwayDisplay(double x, double y, double width, double height, QString name) :
    x(x),
    y(y),
    width(width),
    height(height),
    name(name)
{}

QRectF SwayDisplay::getRect() {
    double divisor = getDivisor();
    return QRectF(x / divisor, y / divisor, width / divisor, height / divisor);
}

double SwayDisplay::getDivisor() {
    return qMax(width, height) / 250.; // TODO: dynamically scale based upon display size?
}

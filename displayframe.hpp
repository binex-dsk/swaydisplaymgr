#ifndef DISPLAYFRAME_HPP
#define DISPLAYFRAME_HPP

#include <QWidget>

#include "swaydisplay.hpp"

const std::vector<Qt::GlobalColor> colors = {
    Qt::blue,
    Qt::red,
    Qt::yellow,
    Qt::green,
};

class DisplayFrame : public QWidget
{
private:
    QList<SwayDisplay *> m_displays;

public:
    DisplayFrame(QWidget *parent = nullptr);

    void setDisplays(QList<SwayDisplay *> &displays);

    void paintEvent(QPaintEvent *paintEvent);
};

#endif // DISPLAYFRAME_HPP

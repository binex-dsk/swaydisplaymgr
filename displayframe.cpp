#include <QPainter>

#include "displayframe.hpp"

DisplayFrame::DisplayFrame(QWidget *parent)
    : QWidget(parent)
{}

void DisplayFrame::setDisplays(QList<SwayDisplay *> &displays) {
    m_displays = displays;
}

void DisplayFrame::paintEvent(QPaintEvent *) {
    qDebug() << "hi";
    for (int i = 0; i < m_displays.size(); ++i) {
        // make displays
        SwayDisplay *d = m_displays[i];

        QRectF rect = d->getRect();

        QPainter painter(this);
        painter.setPen(Qt::white);
        painter.drawRect(rect);
        painter.fillRect(rect, colors[i]);

        painter.setFont(QFont("Arial", 20));
        painter.setPen(Qt::black);
        painter.drawText(rect, Qt::AlignCenter | Qt::AlignHCenter, d->name);
    }
}

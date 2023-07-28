#include "mainwindow.hpp"

#include <QProcess>
#include <QPainter>
#include <QMouseEvent>
#include <QApplication>

void updateSelectedDisplay(SwayDisplay *selectedDisplay) {
    QString program = "swaymsg";
    QStringList args;

    args << "output" << selectedDisplay->name << "mode"
         << QString::number(selectedDisplay->width) + "x" + QString::number(selectedDisplay->height)
         << "pos"
         << QString::number(selectedDisplay->x) << QString::number(selectedDisplay->y);

    QProcess *process = new QProcess;

    QProcess::connect(process, &QProcess::finished, [process](int code, QProcess::ExitStatus) {
        if (code != 0) {
            qWarning() << process->readAllStandardError();
        }
    });
    process->start(program, args);
}

void MainWindow::refreshTextBoxes() {
    m_x->setEditText(QString::number(m_selectedDisplay->x));
    m_y->setEditText(QString::number(m_selectedDisplay->y));
    m_width->setEditText(QString::number(m_selectedDisplay->width));
    m_height->setEditText(QString::number(m_selectedDisplay->height));
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),

    m_widget(new QWidget(this)),

    m_apply(new QPushButton("Apply", this)),
    m_refresh(new QPushButton("Refresh", this)),

    m_x(new LabeledEdit("X", "0")),
    m_y(new LabeledEdit("Y", "0")),
    m_width(new LabeledEdit("Width", "0")),
    m_height(new LabeledEdit("Height", "0")),
    m_coordinatesLayout(new QHBoxLayout),

    m_layout(new QGridLayout(m_widget))
{
    m_coordinatesLayout->addWidget(m_x);
    m_coordinatesLayout->addWidget(m_y);
    m_coordinatesLayout->addWidget(m_width);
    m_coordinatesLayout->addWidget(m_height);

    connect(m_apply, &QPushButton::clicked, [this] {
        m_selectedDisplay->x = m_x->editText().toDouble();
        m_selectedDisplay->y = m_y->editText().toDouble();
        m_selectedDisplay->width = m_width->editText().toDouble();
        m_selectedDisplay->height = m_height->editText().toDouble();

        repaint();

        updateSelectedDisplay(m_selectedDisplay);
        refreshDisplays();
    });

    connect(m_refresh, &QPushButton::clicked, [this] {
        refreshDisplays();
    });

    m_layout->addLayout(m_coordinatesLayout, 1, 0, 1, 4);

    m_layout->addWidget(m_apply, 2, 0);
    m_layout->addWidget(m_refresh, 2, 1);

    setCentralWidget(m_widget);
}

void MainWindow::refreshDisplays() {
    QString program = "/home/swurl/displays.sh"; // tmp
    QStringList outputArgs;
    outputArgs << "-t" << "get_outputs";

    QStringList args;

    m_displays.clear();
    QProcess *process = new QProcess(this);

    connect(process, &QProcess::finished, this, [this, process](int code, QProcess::ExitStatus status) {
        QByteArray stdout = process->readAllStandardOutput();
        // each display is described by a string ending in a newline
        QList<QByteArray> displays = stdout.split('\n');

        // but there will be an empty string at the end :(
        displays.pop_back();

        for (int i = 0; i < displays.size(); ++i) {
            // x y width height name
            QList<QByteArray> data = displays[i].split(' ');

            qsizetype x = data[0].toInt();
            qsizetype y = data[1].toInt();

            qsizetype width = data[2].toInt();
            qsizetype height = data[3].toInt();

            QString name = data[4];

            SwayDisplay *d = new SwayDisplay(x, y, width, height, name);
            m_displays.push_back(d);

            // TODO: more settings in general.
            // TODO: input settings
            repaint();
        }
    });

    process->start(program, args);
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    for (int i = 0; i < m_displays.size(); ++i) {
        SwayDisplay *d = m_displays[i];
        if (d->getRect().contains(event->position())) {
            m_selectedDisplay = d;
            refreshTextBoxes();

            m_dragStart = event->position();
            m_dragReady = true;
            m_dragDiff = event->position() - QPointF(d->x / d->getDivisor(), d->y / d->getDivisor());
        }
    }

    repaint();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
    if (!(event->buttons() & Qt::LeftButton)
        ||
        (event->pos() - m_dragStart).manhattanLength() < QApplication::startDragDistance()
        ||
        !m_dragReady) {
        return;
    }

    double mult = m_selectedDisplay->getDivisor();
    m_selectedDisplay->x = qRound(event->position().x() * mult - m_dragDiff.x());
    m_selectedDisplay->y = qRound(event->position().y() * mult - m_dragDiff.y());
    refreshTextBoxes();
    repaint();
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event) {
    refreshTextBoxes();
    m_dragReady = false;
}

void MainWindow::paintEvent(QPaintEvent *paintEvent) {
    for (int i = 0; i < m_displays.size(); ++i) {
        // make displays
        SwayDisplay *d = m_displays[i];

        QRectF rect = d->getRect(); // TODO: center this

        QPainter painter(this);
        painter.setPen(QPen(QBrush(Qt::white), 5));
        painter.drawRect(rect);
        painter.fillRect(rect, colors[i]);

        painter.setFont(QFont("Arial", 20));
        painter.setPen(Qt::black);
        painter.drawText(rect, Qt::AlignCenter | Qt::AlignHCenter, d->name);
    }
}

MainWindow::~MainWindow()
{
}


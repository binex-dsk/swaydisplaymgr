#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QList>
#include <QPushButton>

#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>

#include "swaydisplay.hpp"
#include "displayframe.hpp"

class LabeledEdit : public QWidget {
    Q_OBJECT
private:
    QLabel *m_label;
    QLineEdit *m_edit;

    QHBoxLayout *m_layout;

public:
    LabeledEdit(QString label, QString editText) {
        m_label = new QLabel(label, this);
        m_edit = new QLineEdit(editText, this);

        m_layout = new QHBoxLayout(this);

        m_layout->addWidget(m_label);
        m_layout->addWidget(m_edit);

        this->setLayout(m_layout);
    }

    inline void setLabel(QString label) {
        m_label->setText(label);
    }

    inline void setEditText(QString editText) {
        m_edit->setText(editText);
    }

    inline QString label() {
        return m_label->text();
    }

    inline QString editText() {
        return m_edit->text();
    }
};

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    void refreshTextBoxes();

    QList<SwayDisplay *> m_displays;

    SwayDisplay *m_selectedDisplay;

    QWidget *m_widget;

    LabeledEdit *m_x;
    LabeledEdit *m_y;
    LabeledEdit *m_width;
    LabeledEdit *m_height;

    QPushButton *m_apply;
    QPushButton *m_refresh;

    QGridLayout *m_layout;
    QHBoxLayout *m_coordinatesLayout;

    QPointF m_dragStart{};
    bool m_dragReady = false;
    QPointF m_dragDiff{};

public:
    MainWindow(QWidget *parent = nullptr);
    void refreshDisplays();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *paintEvent);

    ~MainWindow();
};
#endif // MAINWINDOW_HPP

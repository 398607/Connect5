#ifndef MOBS_H
#define MOBS_H

#include <QObject>
#include <QWidget>
#include <QMouseEvent>

class MouseObserver : public QWidget {
    Q_OBJECT

public:
    MouseObserver(QWidget* parent, int _size, const QRect& rect) {
        this->setParent(parent);
        cell_size = _size;
        this->setGeometry(rect);
    }
protected:
    void mousePressEvent(QMouseEvent* e) {
        int x = e->y() / cell_size;
        int y = e->x() / cell_size;
        emit click(x, y);
    }
signals:
    void click(int x, int y) ;
private:
    int cell_size;
};

#endif
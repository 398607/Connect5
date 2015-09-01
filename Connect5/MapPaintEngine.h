#ifndef MAPPE_H
#define MAPPE_H

#include <QRect>
#include <QPainter>

#include "Map.h"

class MapPaintEngine {
public:
    MapPaintEngine() {

    }
    void paint(QWidget* stage, const CellMatrix& m, const QRect& rect) {
        QPainter painter(stage);
        
        painter.setPen(QPen(QBrush(QColor(0, 0, 0)), 3));
        painter.setBrush(QColor(100, 100, 100));
        painter.drawRect(rect);

        painter.translate(40, 40);

        int cell_size = rect.width() / m.len();
        int cover = cell_size / 2;
        for (int h = 0; h < m.len(); h++) {
            painter.setPen(QPen(QColor(0, 0, 0), 3));
            // h
            painter.drawLine(cover                            , cover + h * cell_size,
                             cover + (m.len() - 1) * cell_size, cover + h * cell_size);
            // v
            painter.drawLine(cover + h * cell_size, cover,
                             cover + h * cell_size, cover + (m.len() - 1) * cell_size);
        }

        for (int i = 0; i < m.len(); i++)
            for (int j = 0; j < m.len(); j++) {
                if (m()[i][j] == Cell::Black) {
                    painter.setPen(Qt::NoPen);
                    painter.setBrush(QColor(0, 0, 0, 200));
                    if (Pos(i, j) == m.last())
                        painter.setBrush(QColor(0, 0, 0, 255));
                        
                }
                else if (m()[i][j] == Cell::White){
                    painter.setPen(Qt::NoPen);
                    painter.setBrush(QColor(255, 255, 255, 200));
                    if (Pos(i, j) == m.last())
                        painter.setBrush(QColor(255, 255, 255, 255));
                }
                else { // Cell::Empty
                    continue;
                }
                // black / white
                painter.drawEllipse((j + 0.1) * cell_size, (i + 0.1) * cell_size, cell_size * 0.8, cell_size * 0.8);
            }
    }
};


#endif
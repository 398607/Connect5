#ifndef MAP_H
#define MAP_H
#include <vector>


#include <QObject>
#include <QDebug>

enum class Cell : int {
    Empty = 0, Black, White
};

enum class Player : int {
    None = 0, Black, White
};

class Pos {
public:
    Pos(int x = 0, int y = 0): _x(x), _y(y) {
        
    }
    Pos(const Pos& p): _x(p._x), _y(p._y) {

    }
    bool operator==(const Pos& p) const {
        return _x == p._x && _y == p._y;
    }
    Pos& operator=(const Pos& p) {
        _x = p._x;
        _y = p._y;
        return *this;
    }
    int x() const {
        return _x;
    }
    int y() const {
        return _y;
    }
private:
    int _x, _y;
};

class CellMatrix : public QObject {
    Q_OBJECT

    typedef std::vector<std::vector<Cell>> map2D;
public:
    CellMatrix(unsigned _n = 0) {
        n = _n;
        for (unsigned i = 0; i < _n; i++)
            matrix.push_back(std::vector<Cell>(_n));
    }

    static Player nextPlayer(const Player& p) {
        if (p == Player::White)
            return Player::Black;
        if (p == Player::Black)
            return Player::White;
        return Player::None;
    }

    int len() const {
        return n;
    }
    const map2D& operator()(void) const {
        return matrix;
    }
    const Cell& cellAt(const Pos& p) const {
        return matrix[p.x()][p.y()];
    }
    bool move(const Player& player, const Pos& p)  {
        if (cellAt(p) == Cell::Empty) {
            cellAt(p) = Cell(player);
            lastPos = p;
            if (checkWin())
                emit endGame(Player(cellAt(lastPos)));
            return true;
        }
        return false;
    }
    const Pos last() const {
        return lastPos;
    }
    bool checkWin() {
        int dx[] = {1,  1,  0, -1, -1, -1,  0,  1};
        int dy[] = {0,  1,  1,  1,  0, -1, -1, -1};
        for (int d = 0; d < 4; d++) {
            int rd = d + 4;
            int num = -1; // to make it balanced

            int nowx = lastPos.x(), nowy = lastPos.y();
            const Cell color = cellAt(lastPos);

            while(nowx >= 0 && nowx < len() && nowy >= 0 && nowy < len()) {

                if (cellAt(Pos(nowx, nowy)) == color) {
                    num++;
                }
                else {
                    break;
                }
                nowx += dx[d];
                nowy += dy[d];
            }

            // if (num >= 5)
            //     return true;

            nowx = lastPos.x(), nowy = lastPos.y();

            while(nowx >= 0 && nowx < len() && nowy >= 0 && nowy < len()) {

                if (cellAt(Pos(nowx, nowy)) == color) {
                    num++;
                }
                else {
                    break;
                }
                nowx += dx[rd];
                nowy += dy[rd];
            }

            qDebug() << num;

            if (num >= 5)
                return true;

        }
        return false;
    }
signals:
    void endGame(const Player& p);
protected:
    // non-const Cell find
    Cell& cellAt(const Pos& p) {
        return matrix[p.x()][p.y()];
    }
    map2D& operator()(void) {
        return matrix;
    }
    bool clear(const Pos& p) {
        if (cellAt(p) == Cell::Empty) {
            return false;
        }
        cellAt(p) = Cell::Empty;
        return true;
    }
private:
    map2D matrix;
    int n;

    Pos lastPos;

    // ban
    CellMatrix(const CellMatrix& c);
    CellMatrix& operator=(const CellMatrix& c);
};

#endif
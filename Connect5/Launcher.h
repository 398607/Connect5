#ifndef LAUNCHE_H
#define LAUNCHE_H

#include <QDialog>
#include <QPushButton>
#include <QApplication>
#include <QDebug>

#include "game.h"

class Launcher : public QDialog {
    Q_OBJECT

public:
    Launcher() {
        this->setFixedSize(400, 800);

        btn_LM = new QPushButton(this);
        btn_LM->setGeometry(80, 50, 240, 60);
        btn_LM->setText("Local Multi");
        connect(btn_LM, &QPushButton::clicked, this, &Launcher::newLMGame);

        btn_NB = new QPushButton(this);
        btn_NB->setGeometry(80, 330, 240, 60);
        btn_NB->setText("Net Battle");
        connect(btn_NB, &QPushButton::clicked, this, &Launcher::newNBGame);


        btn_exit = new QPushButton(this);
        btn_exit->setGeometry(80, 610, 240, 60);
        btn_exit->setText("Quit App");
        connect(btn_exit, &QPushButton::clicked, qApp, &QApplication::quit);
    }
    ~Launcher() {
        delete btn_exit;
        delete btn_LM;
        delete btn_NB;
    }
public slots:
    void newLMGame() {
        Game* game = new Game(Game::GameMode::LOCALMULTI);
        game->show();
    }
    void newNBGame() {
        Game* game = new Game(Game::GameMode::NETBATTLE);
        game->show();
    }
private:
    QPushButton* btn_LM;
    QPushButton* btn_NB;
    QPushButton* btn_exit;
};

#endif
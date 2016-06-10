#ifndef OKNO_H
#define OKNO_H

#include <QMainWindow>
#include <QPushButton>
#include "logika.h"
#include <QEventLoop>
#include <QLabel>

namespace Ui {
class okno;
}

class okno : public QMainWindow
{
    Q_OBJECT

public:
    explicit okno(QWidget *parent = 0);
    ~okno();
    bool ended;//byly smazány dynamicky alokované proměnné?
    int velikostPole;// velikost hrany pexesa
    double difficulty;//Jednoduchost počítače, při hře jednoho hráče
    int hraci;// pocet hracu
    bool second;//druhé otočení kartičky?
    int previous;//Předchozí hodnota
    int prevIndex;
    int player;//č. hráče, který je na řadě.
    int guessed;//spravne uhadnutych karet
    human *hrac;
    QPushButton *Prev;//Pointer na předchozí zmáčknutý pointer
    PChrac *oponent;// trida Umele Inteligence
    gameData *hra; // data hry
    QPushButton *pexeso;// zde je následně převedena hra na PushButtons
    QStatusBar *turn;//kdo je na tahu
    QEventLoop loop;


private slots:
    void on_actionHow_to_play_triggered();
    void on_actionAbout_triggered();
    void on_actionQuit_triggered();
    void on_actionNew_Game_2_triggered();
    void click();
    void pcClick();
    void RpcClick();
    void konec();

private:
    Ui::okno *ui;
};

#endif // OKNO_H

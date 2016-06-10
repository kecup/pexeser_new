#ifndef CONFIG_H
#define CONFIG_H

#include <QDialog>

namespace Ui {
class config;
}

class config : public QDialog
{
    Q_OBJECT


public:
    int getVelikost();
    double getDifficulty();
    int getPlayers();
    explicit config(QWidget *parent = 0);
    ~config();
private slots:
    void on_velikost_valueChanged(int arg1);

private:
    Ui::config *ui;
};

#endif // CONFIG_H

#include "config.h"
#include "ui_config.h"
#include <QDialog>

config::config(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::config)
{
    ui->setupUi(this);
}

config::~config()
{
    delete ui;
}


int config::getVelikost()
{
    return ui->velikost->value();
}

double config::getDifficulty()
{
    return ui->obtiznost->value();
}

int config::getPlayers()
{
    return ui->pHracu->value();
}

void config::on_velikost_valueChanged(int arg1)
{
    if(arg1%2==1)
    {
        ui->velikost->setValue(arg1-1);
    }
    else if(arg1>10)
    {
        ui->velikost->setValue(10);
    }
    else if(arg1<2)
    {
        ui->velikost->setValue(2);
    }
}

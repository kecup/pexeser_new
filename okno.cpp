#include "okno.h"
#include "ui_okno.h"
#include "config.h"
#include <QMessageBox>
#include <QThread>
#include <QFileInfo>

okno::okno(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::okno)
{
    ui->setupUi(this);
    ended=true;
    Prev=NULL;
}

okno::~okno()
{
    if(ended==false)
        konec();
    delete ui;
}

void okno::konec()
{
    if(hraci==1)
    delete oponent;

    delete [] hrac;
    delete hra;
    delete turn;
    delete [] pexeso;
    ended=true;
}

void okno::on_actionHow_to_play_triggered()
{
    QMessageBox::information(this,tr("Jak hrát"),tr("Pexeso se hraje úplně normálně jako to stolní.\n V nastavení můžete změnit obtížnost: Nastavujete zapomnětlivost stroje (momentálně vašeho protihráče). 0 je nejtěžší, stroj nic nezapomene a bude vyhledávat ideální kombinace. Nastavit hodnotu na 1 nedoporučuji, po každém tahu počítač zapomene jaké karty byly otočeny a bude hrát velmi náhodně."));
}

void okno::on_actionAbout_triggered()
{
    QMessageBox::information(this,tr("O programu Pexeser"),tr("Zatím jen velmi jednoduché pexeso. V případě, že by autor/autoři měli móře času, mohli byste se dočkat i LAN verze.\n\n Jan Půček \n FJFI ČVUT"));

}

void okno::on_actionQuit_triggered()
{
    close();
}


void okno::on_actionNew_Game_2_triggered()
{
    config dialog;
    if(dialog.exec()==QDialog::Accepted)
    {
        if(ended==false)
            konec();

        velikostPole=dialog.getVelikost();
        difficulty=dialog.getDifficulty();
        hraci=dialog.getPlayers();
        guessed=0;
        player=0;
        if(hraci>1)
        {
            hrac = new human [hraci];
        }
        else
        {
            hrac = new human [2];
            oponent= new PChrac(velikostPole, difficulty);
        }
        hra= new gameData(velikostPole);
        pexeso = new QPushButton [velikostPole*velikostPole];
        //turn = new QLabel("Hraje hráč č. "+QString::number(player));
        turn= new QStatusBar();
        this->setStatusBar(turn);
        second=false;
        ended=false;

        int chybejiciObraz=0;
        for(int i=0; i<velikostPole*velikostPole/2; i++)
        {
            QFileInfo f("obrazky/"+QString::number(i)+".png");
            if(!f.isFile())
            {
               QMessageBox::information(this,tr("Ve složce /obrazky chybí soubor"),"Můžete pokračovat, ale doporučujeme tuto chybu opravit opětovnou instalací programu, případně nahrajte do složky /obrazky chybějící .png soubor.");
                chybejiciObraz++;
            }
            if(chybejiciObraz>1)
            {
                QMessageBox::information(this,tr("Ve složce /obrazky chybí více souborů"),"V tomto případě hra nelze hrát a tudíž nebude nová hra spuštěna.");
                konec();
                return;
            }
        }

        for(int a=0;a<velikostPole;a++)
        {
            for(int b=0; b<velikostPole;b++)
            {
            pexeso[a*velikostPole+b].setCheckable(true);
            pexeso[a*velikostPole+b].setMaximumHeight(100);
            pexeso[a*velikostPole+b].setMaximumWidth(100);
                if(hraci>1)
                connect(&pexeso[a*velikostPole+b],SIGNAL(clicked(bool)),this,SLOT(click()));
                else
                connect(&pexeso[a*velikostPole+b],SIGNAL(clicked(bool)),this,SLOT(pcClick()));
            ui->Grid->addWidget(&pexeso[a*velikostPole+b],a,b);
            }
        }
        //ui->Outside->addWidget(turn,2);

        setLayout(ui->Grid);
    }
}

void okno::click()
{
    ui->centralWidget->setAttribute(Qt::WA_TransparentForMouseEvents);//zamezení zběsilého klikání, které vytvářelo chybu hry.
    int index=0;
    QPushButton* button = (QPushButton*)sender();
    if(button!=Prev)
    {
        while(button!=&pexeso[index])
        {
            index++;
        }
        //button->setText(QString::number(hra->getValue(index)));
        button->setIcon(QIcon("obrazky/"+QString::number(hra->getValue(index))+".png"));
        button->setIconSize(button->size());
        button->setChecked(true);
        loop.processEvents(QEventLoop::AllEvents,1000);
        if(second)
        {
            second=false;
            if(previous==hra->getValue(index))
            {

                QThread::sleep(1);
                Prev->setVisible(false);
                button->setVisible(false);
                hrac[player].body++;
                guessed++;
                ui->centralWidget->setAttribute(Qt::WA_TransparentForMouseEvents,false);
                if(2*guessed==velikostPole*velikostPole)
                {
                 int vyhral=0;
                 index=0;
                 for(int h=0; h<hraci;h++)
                 {
                     if(hrac[h].body>vyhral)
                     {
                         vyhral=hrac[h].body;
                         index=h;
                     }
                 }
                 QMessageBox::information(this,tr("Gratulujeme"),"Vyhrál hráč č. "+QString::number(index)+" s "+QString::number(vyhral)+" body.");
                 konec();
                }
            }
            else
            {
                if(player>=hraci-1)
                    player=0;
                else
                {
                    player++;
                }
                QThread::sleep(1);

                Prev->setChecked(false);
                Prev->setText("");
                Prev->setIcon(QIcon());
                button->setChecked(false);
                button->setText("");
                button->setIcon(QIcon());
                Prev=NULL;
                turn->showMessage("Hraje hráč č. "+QString::number(player));
                //ui->centralWidget->setAttribute(Qt::WA_TransparentForMouseEvents,false);
            }
        }
        else
        {
           previous= hra->getValue(index);
           Prev = button;
           second=true;
        }
    }
    ui->centralWidget->setAttribute(Qt::WA_TransparentForMouseEvents,false);

}

void okno::pcClick()
{
    ui->centralWidget->setAttribute(Qt::WA_TransparentForMouseEvents);
    int index=0;
    QPushButton* button = (QPushButton*)sender();
    if(button!=Prev)
    {
        while(button!=&pexeso[index])
        {
            index++;
        }
        //button->setText(QString::number(hra->getValue(index)));
        button->setIcon(QIcon("obrazky/"+QString::number(hra->getValue(index))+".png"));
        button->setIconSize(button->size());
        button->setChecked(true);
        oponent->otocenaKarta(index,hra->getValue(index));

        loop.processEvents(QEventLoop::AllEvents,1000);
        if(second)
        {
            second=false;
            if(previous==hra->getValue(index))
            {
                oponent->vyhrano(index,prevIndex);
                QThread::sleep(1);
                Prev->setVisible(false);
                button->setVisible(false);
                hrac[player].body++;
                guessed++;
                ui->centralWidget->setAttribute(Qt::WA_TransparentForMouseEvents,false);
                if(2*guessed==velikostPole*velikostPole)
                {
                 int vyhral=0;
                 index=0;
                 for(unsigned int h=0; h<2;h++)// aby hrál počítač, tak musí být pouze jeden reálný hráč...
                 {
                     if(hrac[h].body>vyhral)
                     {
                         vyhral=hrac[h].body;
                         index=h;
                     }
                 }
                 if(index==1)
                    QMessageBox::information(this,tr("Smůla"),"Vyhrál počítač s "+QString::number(vyhral)+" body.");
                 else
                    QMessageBox::information(this,tr("Gratulujeme"),"Vyhrál hráč č. "+QString::number(index)+" s "+QString::number(vyhral)+" body.");
                 player=0;
                 konec();
                }
                else if(player==1)
                {
                 RpcClick();
                }
            }
            else
            {
                if(player>=1)
                    player=0;
                else
                {
                    player++;
                }
                QThread::sleep(1);
                Prev->setChecked(false);
                //Prev->setText("");
                Prev->setIcon(QIcon());
                button->setChecked(false);
                //button->setText("");
                button->setIcon(QIcon());
                Prev=NULL;
                turn->showMessage("Hraje hráč č. "+QString::number(player));
                ui->centralWidget->setAttribute(Qt::WA_TransparentForMouseEvents,false);
                if(player==1)
                {
                    ui->centralWidget->setAttribute(Qt::WA_TransparentForMouseEvents);
                    turn->showMessage("Hraje počítač");
                    QThread::sleep(1);
                    RpcClick();
                }
            }
        }
        else
        {
           previous= hra->getValue(index);
           Prev = button;
           prevIndex=index;
           second=true;
           ui->centralWidget->setAttribute(Qt::WA_TransparentForMouseEvents,false);
           if(player==1)
           {
               ui->centralWidget->setAttribute(Qt::WA_TransparentForMouseEvents);
               oponent->lastIndex=index;
               oponent->lastValue=hra->getValue(index);
               RpcClick();
           }
        }
    }
}

void okno::RpcClick()
{

    if(oponent->getPrvni())
    {
        pexeso[oponent->prvniTah()].click();
    }
    else
    {
        pexeso[oponent->druhyTah()].click();
    }
}

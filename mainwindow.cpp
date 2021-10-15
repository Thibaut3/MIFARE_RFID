#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btndecr_clicked()
{
    int decr = ui->decrement->text().toInt();
    if(decr>ui->nbUnit->text().toInt()){
        QMessageBox msgBox;
        msgBox.setText("Nombre d'unités trop basse.");
        msgBox.exec();
    }else{
        int value = ui->nbUnit->text().toInt() - decr;
        ui->nbUnit->setText(QString::number(value));

        //MODIFIER NB UNIT SUR LA CARTE
    }
    ui->decrement->setValue(0);
}

void MainWindow::on_btnincr_clicked()
{
    int incr = ui->increment->text().toInt();
    int value = ui->nbUnit->text().toInt() + incr;
    ui->nbUnit->setText(QString::number(value));
    ui->increment->setValue(0);

    //MODIFIER NB UNIT SUR LA CARTE
}

void MainWindow::on_btnmaj_clicked()
{
    QMessageBox msgBox;
    msgBox.setText("L'identité a été modifiée.");
    msgBox.exec();

    //ENVOYER NOM PRENOM à LA CARTE
}

void MainWindow::on_btnconnect_clicked()
{
    //CONNECTER
    ui->btndisco->setEnabled(true);
    ui->btnselec->setEnabled(true);
    ui->btnconnect->setEnabled(false);
}

void MainWindow::on_btndisco_clicked()
{
    //DISCONNECT
    ui->btndisco->setEnabled(false);
    ui->btnselec->setEnabled(false);
    ui->btnconnect->setEnabled(true);
}

void MainWindow::on_btnselec_clicked()
{
    //CONFIGURATION DE BASE

    ui->nbUnit->setText("50");
    ui->prenom->setText("Thibaut");
    ui->nom->setText("JUILLARD");
}

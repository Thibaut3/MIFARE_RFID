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
        uint32_t decrValue = ui->decrement->text().toInt();
        reader->WriteDECR(decrValue);
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

    uint32_t incrValue = incr;
    reader->WriteINCR(incrValue);
    //MODIFIER NB UNIT SUR LA CARTE
}

void MainWindow::on_btnmaj_clicked()
{
    //ENVOYER NOM PRENOM à LA CARTE
    char DataIn[16];
    sprintf(DataIn, ui->prenom->text().toUtf8().data(), 16);
    reader->setNewPrenom(DataIn);
    char DataIn2[16];
    sprintf(DataIn2, ui->nom->text().toUtf8().data(),16);
    reader->setNewNom(DataIn2);
    reader->WriteID();
    QMessageBox msgBox;
    msgBox.setText("L'identité a été modifiée.");
    msgBox.exec();
}

void MainWindow::on_btnconnect_clicked()
{
    //CONNECTER
    reader->PriseContact();
    ui->btndisco->setEnabled(true);
    ui->btnselec->setEnabled(true);
    ui->btnconnect->setEnabled(false);
}

void MainWindow::on_btndisco_clicked()
{
    //DISCONNECT
    reader->Close();
    ui->btndisco->setEnabled(false);
    ui->btnselec->setEnabled(false);
    ui->btnconnect->setEnabled(true);
    ui->nom->setText("");
    ui->prenom->setText("");
    ui->nbUnit->setText("");
}

void MainWindow::on_btnselec_clicked()
{
    //CONFIGURATION DE BASE
    ui->prenom->setText(reader->getPrenom());
    ui->nom->setText(reader->getNom());
    ui->nbUnit->setText(QString::number(reader->getUnite()));
}

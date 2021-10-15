#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QDebug>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btndecr_clicked();

    void on_btnincr_clicked();

    void on_btnmaj_clicked();

    void on_btnconnect_clicked();

    void on_btndisco_clicked();

    void on_btnselec_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

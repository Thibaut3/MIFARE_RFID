#include "mainwindow.h"

#include "readermanager.h"

#include <QApplication>

int main(int argc, char *argv[])
{


    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    ReaderManager reader =  ReaderManager();
    reader.PriseContact();
    reader.LectureBlock2();
    reader.LectureBlock3();
    return a.exec();
}

//*****************************************************************************
//
// Main Program Projet IN55
//
//*****************************************************************************
#include <QApplication>
#include "AnimationPersonnage.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AnimationPersonnage win;
    win.show();
    return a.exec();
}


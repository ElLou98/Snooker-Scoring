#include <QApplication>
#include <QtWidgets>
#include "snookerscoring.h"
#include "snookeraccueil.h"
#include "snookersettings.h"
#include "Joueur.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);


    SnookerAccueil fenetre2;
    fenetre2.show();
   // SnookerSettings fenetre3;
    //fenetre3.show();
    //SnookerScoring fenetre;
    //fenetre.show();

    return app.exec();
}

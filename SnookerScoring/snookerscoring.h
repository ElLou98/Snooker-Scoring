#ifndef SNOOKERSCORING_H
#define SNOOKERSCORING_H

#include "qtmaterialraisedbutton.h"
#include "qtmaterialiconbutton.h"
#include "Joueur.h"
#include "timerclass.h"
#include <QWidget>
#include <QGraphicsDropShadowEffect>
#include <QVBoxLayout>
#include <QColor>
#include <QPixmap>
#include <QIcon>
#include <QAction>
#include <QMessageBox>
#include <QShortcut>


namespace Ui {
class SnookerScoring;
}

class SnookerScoring : public QWidget
{
    Q_OBJECT

//private slots:
  //  void secondeCustomSlot(int);
    //void minuteCustomSlot(int);

public slots:
    void retourAccueil();
    void ajoutScoreRouge();
    void ajoutScoreJaune();
    void ajoutScoreVert();
    void ajoutScoreMarron();
    void ajoutScoreBleu();
    void ajoutScoreRose();
    void ajoutScoreNoir();
    void passerBreak();
    void afficherMemory();
    void afficherCount();
    void annoncerGagnant();
    void reinitialiserFramesJoueur1();
    void reinitialiserFramesJoueur2();
    void ajouterFramesJoueur1();
    void ajouterFramesJoueur2();
    void changerFaute();
    void secondeCustomSlot(int);
    void minuteCustomSlot(int);

public:
    explicit SnookerScoring(Joueur *player1,Joueur *player2,QString nbrFrames,QWidget *parent = nullptr);
    void Card(QString color, QWidget *wd);
    int getBilleRestantes(int indiceG);
    void setBilleRestantes(int valeur,int indiceS);
    int premiereBilleRestantes();
    void fauteFreeBallJoueur1(int idBille);
    void fauteFreeBallJoueur2(int idBille);
    ~SnookerScoring();

private:
    Ui::SnookerScoring *ui;
    QtMaterialRaisedButton *boutonFinPartie;
    QtMaterialIconButton *boutonReset1;
    QtMaterialIconButton *boutonReset2;
    QtMaterialIconButton *boutonAjout1;
    QtMaterialIconButton *boutonAjout2;
    QtMaterialRaisedButton *boutonMemory;
    QtMaterialRaisedButton *boutonCount;
    QtMaterialIconButton *boutonRouge;
    QtMaterialIconButton *boutonJaune;
    QtMaterialIconButton *boutonVert;
    QtMaterialIconButton *boutonMarron;
    QtMaterialIconButton *boutonBleu;
    QtMaterialIconButton *boutonRose;
    QtMaterialIconButton *boutonNoir;
    Joueur *player1;
    Joueur *player2;
    QShortcut *shortcutFinPartie;
    QShortcut *shortcutReset1;
    QShortcut *shortcutReset2;
    QShortcut *shortcutAjout1;
    QShortcut *shortcutAjout2;
    QShortcut *shortcutMemory;
    QShortcut *shortcutCount;
    QShortcut *shortcutRouge;
    QShortcut *shortcutJaune;
    QShortcut *shortcutVert;
    QShortcut *shortcutMarron;
    QShortcut *shortcutBleu;
    QShortcut *shortcutRose;
    QShortcut *shortcutNoir;
    QShortcut *shortcutBreak;
    QShortcut *shortcutWinner;
    QShortcut *shortcutFault;
    QVector<int> billeRestantes;
    QLabel *nbrRouge;
    QLabel *nbrJaune;
    QLabel *nbrVert;
    QLabel *nbrMarron;
    QLabel *nbrBleu;
    QLabel *nbrRose;
    QLabel *nbrNoir;
    QString nbrFrames;
    QPixmap pixmapBilleRouge;
    QIcon iconeBilleRouge;
    TimerClass *secondeObj;
    TimerClass *minuteObj;
};

#endif // SNOOKERSCORING_H

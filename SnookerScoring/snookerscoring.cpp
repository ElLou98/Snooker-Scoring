#include "snookerscoring.h"
#include "ui_snookerscoring.h"
#include "snookeraccueil.h"
#include "Joueur.h"
#include <QDebug>

SnookerScoring::SnookerScoring(Joueur *player1, Joueur *player2,QString nbrFrames, QWidget *parent) :
    QWidget(parent)
    ,boutonFinPartie (new QtMaterialRaisedButton("End Game"))
    ,boutonMemory (new QtMaterialRaisedButton("Memory"))
    ,boutonCount (new QtMaterialRaisedButton("Count"))
    ,ui(new Ui::SnookerScoring)
{
    ui->setupUi(this);
    this->showFullScreen();
    QColor couleurBouton("#9c2b60"); //couleur des boutons

    //initialisation du timer
    secondeObj = new TimerClass;
    minuteObj = new TimerClass;

    //initilaisation du tableau contenant le nombre de bille restantes
    billeRestantes.append(0);
    billeRestantes.append(15);
    billeRestantes.append(1);
    billeRestantes.append(1);
    billeRestantes.append(1);
    billeRestantes.append(1);
    billeRestantes.append(1);
    billeRestantes.append(1);

    //Cacher la fleche à droite en début de partie
    ui->labelFlechePlayer2->setVisible(false);

    //intitialisation des objets player
    this->player1=player1;
    this->player2=player2;

    //initialisation des nombres de frames maximale
    this->nbrFrames=nbrFrames;

    //creation des boutons ajouts des Frames
    QPixmap imagePlus(":/main/pics/plus.png");
    QIcon iconePlus(imagePlus);
    boutonAjout1=new QtMaterialIconButton(iconePlus);
    boutonAjout2=new QtMaterialIconButton(iconePlus);
    ui->layoutRes1->addWidget(boutonAjout1,0,Qt::AlignRight);
    ui->layoutRes2->addWidget(boutonAjout2,0,Qt::AlignLeft);

    //creation des boutons de reset des Frames
    QPixmap imageReset(":/main/pics/reset.png");
    QIcon iconeReset(imageReset);
    boutonReset1=new QtMaterialIconButton(iconeReset);
    boutonReset2=new QtMaterialIconButton(iconeReset);
    ui->layoutRes1->addWidget(boutonReset1,0,Qt::AlignRight);
    ui->layoutRes2->addWidget(boutonReset2,0,Qt::AlignLeft);

    //Creation bouton Memory
    boutonMemory->setBackgroundColor(couleurBouton);
    ui->layoutBoutonMemory->addWidget(boutonMemory,0/*Qt::AlignRight*/);

    //Creation bouton Count
    boutonCount->setBackgroundColor(couleurBouton);
    ui->layoutBoutonCount->addWidget(boutonCount,0/*Qt::AlignLeft*/);

    //Creation bouton Fin Partie
    boutonFinPartie->setBackgroundColor(couleurBouton);
    ui->layoutBoutonFin->addWidget(boutonFinPartie,0,Qt::AlignRight);

    //Assignation des nombre de billes de départ
    nbrRouge=new QLabel(QString::number(billeRestantes[1]));
    nbrJaune=new QLabel(QString::number(billeRestantes[2]));
    nbrVert=new QLabel(QString::number(billeRestantes[3]));
    nbrMarron=new QLabel(QString::number(billeRestantes[4]));
    nbrBleu=new QLabel(QString::number(billeRestantes[5]));
    nbrRose=new QLabel(QString::number(billeRestantes[6]));
    nbrNoir=new QLabel(QString::number(billeRestantes[7]));

    //changement de police des nombres de billes
    QFont police_nbr( "Roboto Black", 16);
    nbrRouge->setFont(police_nbr);
    nbrJaune->setFont(police_nbr);
    nbrVert->setFont(police_nbr);
    nbrMarron->setFont(police_nbr);
    nbrBleu->setFont(police_nbr);
    nbrRose->setFont(police_nbr);
    nbrNoir->setFont(police_nbr);

    //Création des boutons icônes pour les billes.
    QPixmap pixmapBilleRouge(":/main/pics/billeRouge.png");
    QIcon iconeBilleRouge(pixmapBilleRouge);
    QPixmap pixmapBilleBleu(":/main/pics/billeBleu.png");
    QIcon iconeBilleBleu(pixmapBilleBleu);
    QPixmap pixmapBilleJaune(":/main/pics/billeJaune.png");
    QIcon iconeBilleJaune(pixmapBilleJaune);
    QPixmap pixmapBilleMarron(":/main/pics/billeMarron.png");
    QIcon iconeBilleMarron(pixmapBilleMarron);
    QPixmap pixmapBilleNoir(":/main/pics/billeNoir.png");
    QIcon iconeBilleNoir(pixmapBilleNoir);
    QPixmap pixmapBilleVert(":/main/pics/billeVert.png");
    QIcon iconeBilleVert(pixmapBilleVert);
    QPixmap pixmapBilleRose(":/main/pics/billeRose.png");
    QIcon iconeBilleRose(pixmapBilleRose);

    boutonRouge=new QtMaterialIconButton((iconeBilleRouge));
    boutonJaune=new QtMaterialIconButton((iconeBilleJaune));
    boutonVert=new QtMaterialIconButton((iconeBilleVert));
    boutonMarron=new QtMaterialIconButton((iconeBilleMarron));
    boutonBleu=new QtMaterialIconButton((iconeBilleBleu));
    boutonRose=new QtMaterialIconButton((iconeBilleRose));
    boutonNoir=new QtMaterialIconButton((iconeBilleNoir));

    QColor rouge;
    QColor jaune;
    QColor vert;
    QColor marron;
    QColor bleu;
    QColor rose;
    QColor noir;
    rouge.setNamedColor("#BA0E0E");
    jaune.setNamedColor("#F5EA15");
    vert.setNamedColor("#199111");
    marron.setNamedColor("#75421B");
    bleu.setNamedColor("#001FAA");
    rose.setNamedColor("#C734B6");
    noir.setNamedColor("#1B1B1B");
    boutonRouge->setColor(rouge);
    boutonJaune->setColor(jaune);
    boutonVert->setColor(vert);
    boutonMarron->setColor(marron);
    boutonBleu->setColor(bleu);
    boutonRose->setColor(rose);
    boutonNoir->setColor(noir);




    // Ajout des bille et leur nombre dans le layout
    ui->gridLayout->addWidget(nbrRouge,1,1,Qt::AlignRight);
    ui->gridLayout->addWidget(boutonRouge,1,2,Qt::AlignLeft);

    ui->gridLayout->addWidget(nbrJaune,1,3,Qt::AlignRight);
    ui->gridLayout->addWidget(boutonJaune,1,4,Qt::AlignLeft);

    ui->gridLayout->addWidget(nbrVert,1,5,Qt::AlignRight);
    ui->gridLayout->addWidget(boutonVert,1,6,Qt::AlignLeft);

    ui->gridLayout->addWidget(nbrMarron,1,7,Qt::AlignRight);
    ui->gridLayout->addWidget(boutonMarron,1,8,Qt::AlignLeft);

    ui->gridLayout->addWidget(nbrBleu,2,2,Qt::AlignRight);
    ui->gridLayout->addWidget(boutonBleu,2,3,Qt::AlignLeft);

    ui->gridLayout->addWidget(nbrRose,2,4,Qt::AlignRight);
    ui->gridLayout->addWidget(boutonRose,2,5,Qt::AlignLeft);

    ui->gridLayout->addWidget(nbrNoir,2,6,Qt::AlignRight);
    ui->gridLayout->addWidget(boutonNoir,2,7,Qt::AlignLeft);

    //Changer la couleur de l'arriére plan
    Card("#F1F0CC",ui->groupBox);

    //Assigner les nom des joueurs dans le QLabel adéquat
    ui->labelNomJoueur1->setText(player1->getUsername());
    ui->labelNomJoueur2->setText(player2->getUsername());



    //Liaison des boutons des Billes avec les SLOT
    QObject::connect(boutonRouge,SIGNAL(released()),this,SLOT(ajoutScoreRouge()));
    shortcutRouge = new QShortcut(QKeySequence("1"), this);
    QObject::connect(shortcutRouge, SIGNAL(activated()), this, SLOT(ajoutScoreRouge()));

    QObject::connect(boutonJaune,SIGNAL(released()),this,SLOT(ajoutScoreJaune()));
    shortcutJaune = new QShortcut(QKeySequence("2"), this);
    QObject::connect(shortcutJaune, SIGNAL(activated()), this, SLOT(ajoutScoreJaune()));

    QObject::connect(boutonVert,SIGNAL(released()),this,SLOT(ajoutScoreVert()));
    shortcutVert = new QShortcut(QKeySequence("3"), this);
    QObject::connect(shortcutVert, SIGNAL(activated()), this, SLOT(ajoutScoreVert()));

    QObject::connect(boutonMarron,SIGNAL(released()),this,SLOT(ajoutScoreMarron()));
    shortcutMarron = new QShortcut(QKeySequence("4"), this);
    QObject::connect(shortcutMarron, SIGNAL(activated()), this, SLOT(ajoutScoreMarron()));

    QObject::connect(boutonBleu,SIGNAL(released()),this,SLOT(ajoutScoreBleu()));
    shortcutBleu = new QShortcut(QKeySequence("5"), this);
    QObject::connect(shortcutBleu, SIGNAL(activated()), this, SLOT(ajoutScoreBleu()));

    QObject::connect(boutonRose,SIGNAL(released()),this,SLOT(ajoutScoreRose()));
    shortcutRose = new QShortcut(QKeySequence("6"), this);
    QObject::connect(shortcutRose, SIGNAL(activated()), this, SLOT(ajoutScoreRose()));

    QObject::connect(boutonNoir,SIGNAL(released()),this,SLOT(ajoutScoreNoir()));
    shortcutNoir = new QShortcut(QKeySequence("7"), this);
    QObject::connect(shortcutNoir, SIGNAL(activated()), this, SLOT(ajoutScoreNoir()));



    //Liaison entre la touche "0" du pavé numérique et le changement de break
    shortcutBreak = new QShortcut(QKeySequence("b"), this);
    QObject::connect(shortcutBreak, SIGNAL(activated()), this, SLOT(passerBreak()));

    //Liaison entre bouton memory et le slot afficherMemory
    QObject::connect(boutonMemory,SIGNAL(released()),this,SLOT(afficherMemory()));
    shortcutMemory = new QShortcut(QKeySequence("m"), this);
    QObject::connect(shortcutMemory, SIGNAL(activated()), this, SLOT(afficherMemory()));

    //Liaison entre bouton count et le slot afficherCount
    QObject::connect(boutonCount,SIGNAL(released()),this,SLOT(afficherCount()));
    shortcutCount = new QShortcut(QKeySequence("c"), this);
    QObject::connect(shortcutCount, SIGNAL(activated()), this, SLOT(afficherCount()));

    //Liaison entre w et l'annonce du gagnant
    shortcutWinner = new QShortcut(QKeySequence("w"), this);
    QObject::connect(shortcutWinner, SIGNAL(activated()), this, SLOT(annoncerGagnant()));

    //Liaison entre les boutons de réinitialisation et les slot réinitilaiser frame
    QObject::connect(boutonReset1, SIGNAL(released()), this, SLOT(reinitialiserFramesJoueur1()));
    shortcutReset1 = new QShortcut(QKeySequence("r"), this);
    QObject::connect(shortcutReset1, SIGNAL(activated()), this, SLOT(reinitialiserFramesJoueur1()));

    QObject::connect(boutonReset2, SIGNAL(released()), this, SLOT(reinitialiserFramesJoueur2()));
    shortcutReset2 = new QShortcut(QKeySequence("Ctrl+r"), this);
    QObject::connect(shortcutReset2, SIGNAL(activated()), this, SLOT(reinitialiserFramesJoueur2()));

    //Liaison entre les boutons d'ajout et les slot ajouter frame
    QObject::connect(boutonAjout1, SIGNAL(released()), this, SLOT(ajouterFramesJoueur1()));
    shortcutAjout1 = new QShortcut(QKeySequence("a"), this);
    QObject::connect(shortcutAjout1, SIGNAL(activated()), this, SLOT(ajouterFramesJoueur1()));

    QObject::connect(boutonAjout2, SIGNAL(released()), this, SLOT(ajouterFramesJoueur2()));
    shortcutAjout2 = new QShortcut(QKeySequence("Ctrl+a"), this);
    QObject::connect(shortcutAjout2, SIGNAL(activated()), this, SLOT(ajouterFramesJoueur2()));

    //Liaison entre f et l'annonce d'une faute
    shortcutFault = new QShortcut(QKeySequence("f"), this);
    QObject::connect(shortcutFault, SIGNAL(activated()), this, SLOT(changerFaute()));

    //Liaison entre les objets seconde, minutes et les labels
    connect(secondeObj,SIGNAL(secondeCustomSignal(int)),this,SLOT(secondeCustomSlot(int)));
    connect(minuteObj,SIGNAL(minuteCustomSignal(int)),this,SLOT(minuteCustomSlot(int)));

    //Liason entre le bouton et le retour à l'accueil
    QObject::connect(boutonFinPartie,SIGNAL(clicked()),this,SLOT(retourAccueil()));
    shortcutFinPartie = new QShortcut(QKeySequence("e"), this);
    QObject::connect(shortcutFinPartie, SIGNAL(activated()), this, SLOT(retourAccueil()));
}

SnookerScoring::~SnookerScoring()
{
    delete ui;
}

void SnookerScoring::secondeCustomSlot(int value)
{
    if(QString::number(value).size()==1)
    {
        ui->labelSeconde->setText("0"+QString::number(value));
    }
    else
    {
        ui->labelSeconde->setText(QString::number(value));
    }

}

void SnookerScoring::minuteCustomSlot(int value)
{
    if(QString::number(value).size()==1)
    {
        ui->labelMinute->setText("0"+QString::number(value));
    }
    else
    {
        ui->labelMinute->setText(QString::number(value));
    }

}

void SnookerScoring::Card(QString color, QWidget *wd)
{
    QGraphicsDropShadowEffect* effect = new QGraphicsDropShadowEffect();

       QVBoxLayout *widgetlayout = new QVBoxLayout;
        QString style = "QGroupBox { background: " + color +
                        ";  border: 1px solid #d7dfe3;  border-radius: 4px; }";
         wd->setStyleSheet(style);
        effect->setBlurRadius(20);
        effect->setColor(QColor(0, 0, 0, 50));
        effect->setOffset(0,0);
        wd->setGraphicsEffect(effect);
        wd->setLayout(widgetlayout);

}

int SnookerScoring::getBilleRestantes(int indiceG)
{
    return billeRestantes[indiceG];
}
void SnookerScoring::setBilleRestantes(int valeur,int indiceS)
{
    this->billeRestantes[indiceS]=valeur;

}

void SnookerScoring::retourAccueil()
{
    SnookerAccueil *fenetre=new SnookerAccueil;
    this->close();
    fenetre->show();
}

int SnookerScoring::premiereBilleRestantes()
{
    int k=1;
    while((k<billeRestantes.size())&&(billeRestantes[k]==0))
    {
        k++;
    }
    return k;
}

void SnookerScoring::fauteFreeBallJoueur1(int idBille)
{
    if (billeRestantes[1]>0)
    {
        player1->setScoreBreak(player1->getScoreBreak()+1);
        ui->labelScoreBreak->setText(QString::number(player1->getScoreBreak()));
        player1->setScore(player1->getScore()+1);
        ui->labelScorePlayer1->setText(QString::number(player1->getScore()));
        player1->setVisitedToFalse();
        player1->ajouterHistorique("Rouge");
        player1->setFault("None");
        ui->labelFault->setText("None");
        if (idBille==1)
        {
            billeRestantes[1]--;
            nbrRouge->setText(QString::number(billeRestantes[1]));
        }

    }
    else
    {
        if (billeRestantes[1]==0)
        {
            int valDerniereBille=premiereBilleRestantes();
            switch(idBille)
            {
            case 2:
                player1->setScoreBreak(player1->getScoreBreak()+valDerniereBille);
                ui->labelScoreBreak->setText(QString::number(player1->getScoreBreak()));
                player1->setScore(player1->getScore()+valDerniereBille);
                ui->labelScorePlayer1->setText(QString::number(player1->getScore()));
                player1->setVisitedToFalse();
                player1->ajouterHistorique("Jaune");
                player1->setFault("None");
                ui->labelFault->setText("None");
                break;
            case 3:
                player1->setScoreBreak(player1->getScoreBreak()+valDerniereBille);
                ui->labelScoreBreak->setText(QString::number(player1->getScoreBreak()));
                player1->setScore(player1->getScore()+valDerniereBille);
                ui->labelScorePlayer1->setText(QString::number(player1->getScore()));
                player1->setVisitedToFalse();
                player1->ajouterHistorique("Vert");
                player1->setFault("None");
                ui->labelFault->setText("None");
                break;
            case 4:
                player1->setScoreBreak(player1->getScoreBreak()+valDerniereBille);
                ui->labelScoreBreak->setText(QString::number(player1->getScoreBreak()));
                player1->setScore(player1->getScore()+valDerniereBille);
                ui->labelScorePlayer1->setText(QString::number(player1->getScore()));
                player1->setVisitedToFalse();
                player1->ajouterHistorique("Marron");
                player1->setFault("None");
                ui->labelFault->setText("None");
                break;
            case 5:
                player1->setScoreBreak(player1->getScoreBreak()+valDerniereBille);
                ui->labelScoreBreak->setText(QString::number(player1->getScoreBreak()));
                player1->setScore(player1->getScore()+valDerniereBille);
                ui->labelScorePlayer1->setText(QString::number(player1->getScore()));
                player1->setVisitedToFalse();
                player1->ajouterHistorique("Bleu");
                player1->setFault("None");
                ui->labelFault->setText("None");
                break;
            case 6:
                player1->setScoreBreak(player1->getScoreBreak()+valDerniereBille);
                ui->labelScoreBreak->setText(QString::number(player1->getScoreBreak()));
                player1->setScore(player1->getScore()+valDerniereBille);
                ui->labelScorePlayer1->setText(QString::number(player1->getScore()));
                player1->setVisitedToFalse();
                player1->ajouterHistorique("Rose");
                player1->setFault("None");
                ui->labelFault->setText("None");
                break;
            case 7:
                player1->setScoreBreak(player1->getScoreBreak()+valDerniereBille);
                ui->labelScoreBreak->setText(QString::number(player1->getScoreBreak()));
                player1->setScore(player1->getScore()+valDerniereBille);
                ui->labelScorePlayer1->setText(QString::number(player1->getScore()));
                player1->setVisitedToFalse();
                player1->ajouterHistorique("Noir");
                player1->setFault("None");
                ui->labelFault->setText("None");
                break;
            }
        }
    }
}

void SnookerScoring::fauteFreeBallJoueur2(int idBille)
{
    if (billeRestantes[1]>0)
    {
        player2->setScoreBreak(player2->getScoreBreak()+1);
        ui->labelScoreBreak->setText(QString::number(player2->getScoreBreak()));
        player2->setScore(player2->getScore()+1);
        ui->labelScorePlayer2->setText(QString::number(player2->getScore()));
        player2->setVisitedToFalse();
        player2->ajouterHistorique("Rouge");
        player2->setFault("None");
        ui->labelFault->setText("None");
        if (idBille==1)
        {
            billeRestantes[1]--;
            nbrRouge->setText(QString::number(billeRestantes[1]));
        }

    }
    else
    {
        if (billeRestantes[1]==0)
        {
            int valDerniereBille=premiereBilleRestantes();
            switch(idBille)
            {
            case 2:
                player2->setScoreBreak(player2->getScoreBreak()+valDerniereBille);
                ui->labelScoreBreak->setText(QString::number(player2->getScoreBreak()));
                player2->setScore(player2->getScore()+valDerniereBille);
                ui->labelScorePlayer2->setText(QString::number(player2->getScore()));
                player2->setVisitedToFalse();
                player2->ajouterHistorique("Jaune");
                player2->setFault("None");
                ui->labelFault->setText("None");
                break;
            case 3:
                player2->setScoreBreak(player2->getScoreBreak()+valDerniereBille);
                ui->labelScoreBreak->setText(QString::number(player2->getScoreBreak()));
                player2->setScore(player2->getScore()+valDerniereBille);
                ui->labelScorePlayer2->setText(QString::number(player2->getScore()));
                player2->setVisitedToFalse();
                player2->ajouterHistorique("Vert");
                player2->setFault("None");
                ui->labelFault->setText("None");
                break;
            case 4:
                player2->setScoreBreak(player2->getScoreBreak()+valDerniereBille);
                ui->labelScoreBreak->setText(QString::number(player2->getScoreBreak()));
                player2->setScore(player2->getScore()+valDerniereBille);
                ui->labelScorePlayer2->setText(QString::number(player2->getScore()));
                player2->setVisitedToFalse();
                player2->ajouterHistorique("Marron");
                player2->setFault("None");
                ui->labelFault->setText("None");
                break;
            case 5:
                player2->setScoreBreak(player2->getScoreBreak()+valDerniereBille);
                ui->labelScoreBreak->setText(QString::number(player2->getScoreBreak()));
                player2->setScore(player2->getScore()+valDerniereBille);
                ui->labelScorePlayer2->setText(QString::number(player2->getScore()));
                player2->setVisitedToFalse();
                player2->ajouterHistorique("Bleu");
                player2->setFault("None");
                ui->labelFault->setText("None");
                break;
            case 6:
                player2->setScoreBreak(player2->getScoreBreak()+valDerniereBille);
                ui->labelScoreBreak->setText(QString::number(player2->getScoreBreak()));
                player2->setScore(player2->getScore()+valDerniereBille);
                ui->labelScorePlayer2->setText(QString::number(player2->getScore()));
                player2->setVisitedToFalse();
                player2->ajouterHistorique("Rose");
                player2->setFault("None");
                ui->labelFault->setText("None");
                break;
            case 7:
                player2->setScoreBreak(player2->getScoreBreak()+valDerniereBille);
                ui->labelScoreBreak->setText(QString::number(player2->getScoreBreak()));
                player2->setScore(player2->getScore()+valDerniereBille);
                ui->labelScorePlayer2->setText(QString::number(player2->getScore()));
                player2->setVisitedToFalse();
                player2->ajouterHistorique("Noir");
                player2->setFault("None");
                ui->labelFault->setText("None");
                break;
            }
        }
    }
}

void SnookerScoring::ajoutScoreRouge()
{
    if (billeRestantes[1]>0)
    {
        if(this->player1->isEtatBreak())
        {
            if (player1->getFault()=="Foul")
            {
                player2->setScore(player2->getScore()+4);
                ui->labelScorePlayer2->setText(QString::number(player2->getScore()));
                player2->setVisitedToFalse();
                player2->ajouterHistorique("Marron");
                billeRestantes[1]--;
                nbrRouge->setText(QString::number(billeRestantes[1]));
                passerBreak();
            }
            else
            {
                if (player1->getFault()=="Free Ball")
                {
                    fauteFreeBallJoueur1(1);
                }
                else
                {
                    if(player1->getFault()=="None")
                    {
                        player1->setScoreBreak(player1->getScoreBreak()+1);
                        ui->labelScoreBreak->setText(QString::number(player1->getScoreBreak()));
                        player1->setScore(player1->getScore()+1);
                        ui->labelScorePlayer1->setText(QString::number(player1->getScore()));
                        player1->setVisitedToFalse();
                        player1->ajouterHistorique("Rouge");
                        billeRestantes[1]--;
                        nbrRouge->setText(QString::number(billeRestantes[1]));
                        QLabel *labelImage= new QLabel();
                        labelImage->setPixmap(QPixmap(":/main/pics/billeRouge.png"));
                        if (player1->tailleHistorique()<=12)
                        {
                            ui->gridLayoutBillePlayer1->addWidget(labelImage,1,player1->tailleHistorique());
                        }
                        else
                        {
                            if ((player1->tailleHistorique()>12)&&(player1->tailleHistorique()<=24))
                            {
                                ui->gridLayoutBillePlayer1->addWidget(labelImage,2,player1->tailleHistorique()-12);
                            }

                            else if (player1->tailleHistorique()>24)
                            {
                                ui->gridLayoutBillePlayer1->addWidget(labelImage,3,player1->tailleHistorique()-24);
                            }
                        }
                    }
                }
            }
        }

        else if(player2->isEtatBreak())
        {
            if (player2->getFault()=="Foul")
            {
                player1->setScore(player1->getScore()+4);
                ui->labelScorePlayer1->setText(QString::number(player1->getScore()));
                player1->setVisitedToFalse();
                player1->ajouterHistorique("Marron");
                billeRestantes[1]--;
                nbrRouge->setText(QString::number(billeRestantes[1]));
                passerBreak();
            }
            else
            {
                if (player2->getFault()=="Free Ball")
                {
                    fauteFreeBallJoueur2(1);
                }
                else
                {
                    if(player2->getFault()=="None")
                    {
                        player2->setScoreBreak(player2->getScoreBreak()+1);
                        ui->labelScoreBreak->setText(QString::number(player2->getScoreBreak()));
                        player2->setScore(player2->getScore()+1);
                        ui->labelScorePlayer2->setText(QString::number(player2->getScore()));
                        player2->setVisitedToFalse();
                        player2->ajouterHistorique("Rouge");
                        billeRestantes[1]--;
                        nbrRouge->setText(QString::number(billeRestantes[1]));
                        QLabel *labelImage= new QLabel();
                        labelImage->setPixmap(QPixmap(":/main/pics/billeRouge.png"));
                        if (player2->tailleHistorique()<=12)
                        {
                            ui->gridLayoutBillePlayer2->addWidget(labelImage,1,player2->tailleHistorique());
                        }
                        else
                        {
                            if ((player2->tailleHistorique()>12)&&(player2->tailleHistorique()<=24))
                            {
                                ui->gridLayoutBillePlayer2->addWidget(labelImage,2,player2->tailleHistorique()-12);
                            }

                            else if (player2->tailleHistorique()>24)
                            {
                                ui->gridLayoutBillePlayer2->addWidget(labelImage,3,player2->tailleHistorique()-24);
                            }
                        }

                    }
                }
            }
        }
    }

}

void SnookerScoring::ajoutScoreJaune()
{
    if (billeRestantes[2]>0)
    {
        if(player1->isEtatBreak())
        {
            if (player1->getFault()=="Foul")
            {
                player2->setScore(player2->getScore()+4);
                ui->labelScorePlayer2->setText(QString::number(player2->getScore()));
                player2->setVisitedToFalse();
                player2->ajouterHistorique("Marron");
                passerBreak();
            }
            else
            {
                if (player1->getFault()=="Free Ball")
                {
                    fauteFreeBallJoueur1(2);
                }
                else
                {
                    if(player1->getFault()=="None")
                    {
                        player1->setScoreBreak(player1->getScoreBreak()+2);
                        ui->labelScoreBreak->setText(QString::number(player1->getScoreBreak()));
                        player1->setScore(player1->getScore()+2);
                        ui->labelScorePlayer1->setText(QString::number(player1->getScore()));
                        if ((billeRestantes[1]==0)&&(player1->dernierHistorique()!="Rouge"))
                        {
                            billeRestantes[2]--;
                            nbrJaune->setText(QString::number(billeRestantes[2]));
                        }
                        player1->setVisitedToFalse();
                        player1->ajouterHistorique("Jaune");
                        QLabel *labelImage= new QLabel();
                        labelImage->setPixmap(QPixmap(":/main/pics/billeJaune.png"));
                        if (player1->tailleHistorique()<=12)
                        {
                            ui->gridLayoutBillePlayer1->addWidget(labelImage,1,player1->tailleHistorique());
                        }
                        else
                        {
                            if ((player1->tailleHistorique()>12)&&(player1->tailleHistorique()<=24))
                            {
                                ui->gridLayoutBillePlayer1->addWidget(labelImage,2,player1->tailleHistorique()-12);
                            }

                            else if (player1->tailleHistorique()>24)
                            {
                                ui->gridLayoutBillePlayer1->addWidget(labelImage,3,player1->tailleHistorique()-24);
                            }
                        }
                    }
                }
            }
        }

        else if(player2->isEtatBreak())
        {
            if (player2->getFault()=="Foul")
            {
                player1->setScore(player1->getScore()+4);
                ui->labelScorePlayer1->setText(QString::number(player1->getScore()));
                player1->setVisitedToFalse();
                player1->ajouterHistorique("Marron");
                passerBreak();
            }
            else
            {
                if (player2->getFault()=="Free Ball")
                {
                    fauteFreeBallJoueur2(2);
                }
                else
                {
                    if(player2->getFault()=="None")
                    {
                        player2->setScoreBreak(player2->getScoreBreak()+2);
                        ui->labelScoreBreak->setText(QString::number(player2->getScoreBreak()));
                        player2->setScore(player2->getScore()+2);
                        ui->labelScorePlayer2->setText(QString::number(player2->getScore()));
                        if ((billeRestantes[1]==0)&&(player2->dernierHistorique()!="Rouge"))
                        {
                            billeRestantes[2]--;
                            nbrJaune->setText(QString::number(billeRestantes[2]));
                        }
                        player2->setVisitedToFalse();
                        player2->ajouterHistorique("Jaune");
                        QLabel *labelImage= new QLabel();
                        labelImage->setPixmap(QPixmap(":/main/pics/billeJaune.png"));
                        if (player2->tailleHistorique()<=12)
                        {
                            ui->gridLayoutBillePlayer2->addWidget(labelImage,1,player2->tailleHistorique());
                        }
                        else
                        {
                            if ((player2->tailleHistorique()>12)&&(player2->tailleHistorique()<=24))
                            {
                                ui->gridLayoutBillePlayer2->addWidget(labelImage,2,player2->tailleHistorique()-12);
                            }

                            else if (player2->tailleHistorique()>24)
                            {
                                ui->gridLayoutBillePlayer2->addWidget(labelImage,3,player2->tailleHistorique()-24);
                            }
                        }
                    }
                }
            }
        }
    }

}

void SnookerScoring::ajoutScoreVert()
{
    if (billeRestantes[3]>0)
    {
        if(player1->isEtatBreak())
        {
            if (player1->getFault()=="Foul")
            {
                player2->setScore(player2->getScore()+4);
                ui->labelScorePlayer2->setText(QString::number(player2->getScore()));
                player2->setVisitedToFalse();
                player2->ajouterHistorique("Marron");
                passerBreak();
            }
            else
            {
                if (player1->getFault()=="Free Ball")
                {
                    fauteFreeBallJoueur1(3);
                }
                else
                {
                    if(player1->getFault()=="None")
                    {
                        player1->setScoreBreak(player1->getScoreBreak()+3);
                        ui->labelScoreBreak->setText(QString::number(player1->getScoreBreak()));
                        player1->setScore(player1->getScore()+3);
                        ui->labelScorePlayer1->setText(QString::number(player1->getScore()));
                        if ((billeRestantes[1]==0)&&(player1->dernierHistorique()!="Rouge"))
                        {
                            billeRestantes[3]--;
                            nbrVert->setText(QString::number(billeRestantes[3]));
                        }
                        player1->setVisitedToFalse();
                        player1->ajouterHistorique("Vert");
                        QLabel *labelImage= new QLabel();
                        labelImage->setPixmap(QPixmap(":/main/pics/billeVert.png"));
                        if (player1->tailleHistorique()<=12)
                        {
                            ui->gridLayoutBillePlayer1->addWidget(labelImage,1,player1->tailleHistorique());
                        }
                        else
                        {
                            if ((player1->tailleHistorique()>12)&&(player1->tailleHistorique()<=24))
                            {
                                ui->gridLayoutBillePlayer1->addWidget(labelImage,2,player1->tailleHistorique()-12);
                            }

                            else if (player1->tailleHistorique()>24)
                            {
                                ui->gridLayoutBillePlayer1->addWidget(labelImage,3,player1->tailleHistorique()-24);
                            }
                        }
                    }
                }
            }
        }

        else if(player2->isEtatBreak())
        {
            if (player2->getFault()=="Foul")
            {
                player1->setScore(player1->getScore()+4);
                ui->labelScorePlayer1->setText(QString::number(player1->getScore()));
                player1->setVisitedToFalse();
                player1->ajouterHistorique("Marron");
                passerBreak();
            }
            else
            {
                if (player2->getFault()=="Free Ball")
                {
                    fauteFreeBallJoueur2(3);
                }
                else
                {
                    if(player2->getFault()=="None")
                    {
                        player2->setScoreBreak(player2->getScoreBreak()+3);
                        ui->labelScoreBreak->setText(QString::number(player2->getScoreBreak()));
                        player2->setScore(player2->getScore()+3);
                        ui->labelScorePlayer2->setText(QString::number(player2->getScore()));
                        if ((billeRestantes[1]==0)&&(player2->dernierHistorique()!="Rouge"))
                        {
                            billeRestantes[3]--;
                            nbrVert->setText(QString::number(billeRestantes[3]));
                        }
                        player2->setVisitedToFalse();
                        player2->ajouterHistorique("Vert");
                        QLabel *labelImage= new QLabel();
                        labelImage->setPixmap(QPixmap(":/main/pics/billeVert.png"));
                        if (player2->tailleHistorique()<=12)
                        {
                            ui->gridLayoutBillePlayer2->addWidget(labelImage,1,player2->tailleHistorique());
                        }
                        else
                        {
                            if ((player2->tailleHistorique()>12)&&(player2->tailleHistorique()<=24))
                            {
                                ui->gridLayoutBillePlayer2->addWidget(labelImage,2,player2->tailleHistorique()-12);
                            }

                            else if (player2->tailleHistorique()>24)
                            {
                                ui->gridLayoutBillePlayer2->addWidget(labelImage,3,player2->tailleHistorique()-24);
                            }
                        }
                    }
                }
            }
        }
    }

}

void SnookerScoring::ajoutScoreMarron()
{
    if (billeRestantes[4]>0)
    {
        if(player1->isEtatBreak())
        {
            if (player1->getFault()=="Foul")
            {
                player2->setScore(player2->getScore()+4);
                ui->labelScorePlayer2->setText(QString::number(player2->getScore()));
                player2->setVisitedToFalse();
                player2->ajouterHistorique("Marron");
                passerBreak();
            }
            else
            {
                if (player1->getFault()=="Free Ball")
                {
                    fauteFreeBallJoueur1(4);
                }
                else
                {
                    if(player1->getFault()=="None")
                    {
                        player1->setScoreBreak(player1->getScoreBreak()+4);
                        ui->labelScoreBreak->setText(QString::number(player1->getScoreBreak()));
                        player1->setScore(player1->getScore()+4);
                        ui->labelScorePlayer1->setText(QString::number(player1->getScore()));
                        if ((billeRestantes[1]==0)&&(player1->dernierHistorique()!="Rouge"))
                        {
                            billeRestantes[4]--;
                            nbrMarron->setText(QString::number(billeRestantes[4]));
                        }
                        player1->setVisitedToFalse();
                        player1->ajouterHistorique("Marron");
                        QLabel *labelImage= new QLabel();
                        labelImage->setPixmap(QPixmap(":/main/pics/billeMarron.png"));
                        if (player1->tailleHistorique()<=12)
                        {
                            ui->gridLayoutBillePlayer1->addWidget(labelImage,1,player1->tailleHistorique());
                        }
                        else
                        {
                            if ((player1->tailleHistorique()>12)&&(player1->tailleHistorique()<=24))
                            {
                                ui->gridLayoutBillePlayer1->addWidget(labelImage,2,player1->tailleHistorique()-12);
                            }

                            else if (player1->tailleHistorique()>24)
                            {
                                ui->gridLayoutBillePlayer1->addWidget(labelImage,3,player1->tailleHistorique()-24);
                            }
                        }
                    }
                }
            }
        }

        else if(player2->isEtatBreak())
        {
            if (player2->getFault()=="Foul")
            {
                player1->setScore(player1->getScore()+4);
                ui->labelScorePlayer1->setText(QString::number(player1->getScore()));
                player1->setVisitedToFalse();
                player1->ajouterHistorique("Marron");
                passerBreak();
            }
            else
            {
                if (player2->getFault()=="Free Ball")
                {
                    fauteFreeBallJoueur2(4);
                }
                else
                {
                    if(player2->getFault()=="None")
                    {
                        player2->setScoreBreak(player2->getScoreBreak()+4);
                        ui->labelScoreBreak->setText(QString::number(player2->getScoreBreak()));
                        player2->setScore(player2->getScore()+4);
                        ui->labelScorePlayer2->setText(QString::number(player2->getScore()));
                        if ((billeRestantes[1]==0)&&(player2->dernierHistorique()!="Rouge"))
                        {
                            billeRestantes[4]--;
                            nbrMarron->setText(QString::number(billeRestantes[4]));
                        }
                        player2->setVisitedToFalse();
                        player2->ajouterHistorique("Marron");
                        QLabel *labelImage= new QLabel();
                        labelImage->setPixmap(QPixmap(":/main/pics/billeMarron.png"));
                        if (player2->tailleHistorique()<=12)
                        {
                            ui->gridLayoutBillePlayer2->addWidget(labelImage,1,player2->tailleHistorique());
                        }
                        else
                        {
                            if ((player2->tailleHistorique()>12)&&(player2->tailleHistorique()<=24))
                            {
                                ui->gridLayoutBillePlayer2->addWidget(labelImage,2,player2->tailleHistorique()-12);
                            }

                            else if (player2->tailleHistorique()>24)
                            {
                                ui->gridLayoutBillePlayer2->addWidget(labelImage,3,player2->tailleHistorique()-24);
                            }
                        }
                    }
                }
            }
        }
    }

}

void SnookerScoring::ajoutScoreBleu()
{
    if (billeRestantes[5]>0)
    {
        if(player1->isEtatBreak())
        {
            if (player1->getFault()=="Foul")
            {
                player2->setScore(player2->getScore()+5);
                ui->labelScorePlayer2->setText(QString::number(player2->getScore()));
                player2->setVisitedToFalse();
                player2->ajouterHistorique("Bleu");
                passerBreak();
            }
            else
            {
                if (player1->getFault()=="Free Ball")
                {
                    fauteFreeBallJoueur1(5);
                }
                else
                {
                    if(player1->getFault()=="None")
                    {
                        player1->setScoreBreak(player1->getScoreBreak()+5);
                        ui->labelScoreBreak->setText(QString::number(player1->getScoreBreak()));
                        player1->setScore(player1->getScore()+5);
                        ui->labelScorePlayer1->setText(QString::number(player1->getScore()));
                        if ((billeRestantes[1]==0)&&(player1->dernierHistorique()!="Rouge"))
                        {
                            billeRestantes[5]--;
                            nbrBleu->setText(QString::number(billeRestantes[5]));
                        }
                        player1->setVisitedToFalse();
                        player1->ajouterHistorique("Bleu");
                        QLabel *labelImage= new QLabel();
                        labelImage->setPixmap(QPixmap(":/main/pics/billeBleu.png"));
                        if (player1->tailleHistorique()<=12)
                        {
                            ui->gridLayoutBillePlayer1->addWidget(labelImage,1,player1->tailleHistorique());
                        }
                        else
                        {
                            if ((player1->tailleHistorique()>12)&&(player1->tailleHistorique()<=24))
                            {
                                ui->gridLayoutBillePlayer1->addWidget(labelImage,2,player1->tailleHistorique()-12);
                            }

                            else if (player1->tailleHistorique()>24)
                            {
                                ui->gridLayoutBillePlayer1->addWidget(labelImage,3,player1->tailleHistorique()-24);
                            }
                        }
                    }
                }
            }
        }

        else if(player2->isEtatBreak())
        {
            if (player2->getFault()=="Foul")
            {
                player1->setScore(player1->getScore()+5);
                ui->labelScorePlayer1->setText(QString::number(player1->getScore()));
                player1->setVisitedToFalse();
                player1->ajouterHistorique("Bleu");
                passerBreak();
            }
            else
            {
                if (player2->getFault()=="Free Ball")
                {
                    fauteFreeBallJoueur2(5);
                }
                else
                {
                    if(player2->getFault()=="None")
                    {
                        player2->setScoreBreak(player2->getScoreBreak()+5);
                        ui->labelScoreBreak->setText(QString::number(player2->getScoreBreak()));
                        player2->setScore(player2->getScore()+5);
                        ui->labelScorePlayer2->setText(QString::number(player2->getScore()));
                        if ((billeRestantes[1]==0)&&(player2->dernierHistorique()!="Rouge"))
                        {
                            billeRestantes[5]--;
                            nbrBleu->setText(QString::number(billeRestantes[5]));
                        }
                        player2->setVisitedToFalse();
                        player2->ajouterHistorique("Bleu");
                        QLabel *labelImage= new QLabel();
                        labelImage->setPixmap(QPixmap(":/main/pics/billeBleu.png"));
                        if (player2->tailleHistorique()<=12)
                        {
                            ui->gridLayoutBillePlayer2->addWidget(labelImage,1,player2->tailleHistorique());
                        }
                        else
                        {
                            if ((player2->tailleHistorique()>12)&&(player2->tailleHistorique()<=24))
                            {
                                ui->gridLayoutBillePlayer2->addWidget(labelImage,2,player2->tailleHistorique()-12);
                            }

                            else if (player2->tailleHistorique()>24)
                            {
                                ui->gridLayoutBillePlayer2->addWidget(labelImage,3,player2->tailleHistorique()-24);
                            }
                        }
                    }
                }
            }
        }
    }

}

void SnookerScoring::ajoutScoreRose()
{
    if (billeRestantes[6]>0)
    {
        if(player1->isEtatBreak())
        {
            if (player1->getFault()=="Foul")
            {
                player2->setScore(player2->getScore()+6);
                ui->labelScorePlayer2->setText(QString::number(player2->getScore()));
                player2->setVisitedToFalse();
                player2->ajouterHistorique("Rose");
                passerBreak();
            }
            else
            {
                if (player1->getFault()=="Free Ball")
                {
                    fauteFreeBallJoueur1(6);
                }
                else
                {
                    if(player1->getFault()=="None")
                    {
                        player1->setScoreBreak(player1->getScoreBreak()+6);
                        ui->labelScoreBreak->setText(QString::number(player1->getScoreBreak()));
                        player1->setScore(player1->getScore()+6);
                        ui->labelScorePlayer1->setText(QString::number(player1->getScore()));
                        if ((billeRestantes[1]==0)&&(player1->dernierHistorique()!="Rouge"))
                        {
                            billeRestantes[6]--;
                            nbrRose->setText(QString::number(billeRestantes[6]));
                        }
                        player1->setVisitedToFalse();
                        player1->ajouterHistorique("Rose");
                        QLabel *labelImage= new QLabel();
                        labelImage->setPixmap(QPixmap(":/main/pics/billeRose.png"));
                        if (player1->tailleHistorique()<=12)
                        {
                            ui->gridLayoutBillePlayer1->addWidget(labelImage,1,player1->tailleHistorique());
                        }
                        else
                        {
                            if ((player1->tailleHistorique()>12)&&(player1->tailleHistorique()<=24))
                            {
                                ui->gridLayoutBillePlayer1->addWidget(labelImage,2,player1->tailleHistorique()-12);
                            }

                            else if (player1->tailleHistorique()>24)
                            {
                                ui->gridLayoutBillePlayer1->addWidget(labelImage,3,player1->tailleHistorique()-24);
                            }
                        }
                    }
                }
            }
        }

        else if(player2->isEtatBreak())
        {
            if (player2->getFault()=="Foul")
            {
                player1->setScore(player1->getScore()+6);
                ui->labelScorePlayer1->setText(QString::number(player1->getScore()));
                player1->setVisitedToFalse();
                player1->ajouterHistorique("Rose");
                passerBreak();
            }
            else
            {
                if (player2->getFault()=="Free Ball")
                {
                    fauteFreeBallJoueur2(6);
                }
                else
                {
                    if(player2->getFault()=="None")
                    {
                        player2->setScoreBreak(player2->getScoreBreak()+6);
                        ui->labelScoreBreak->setText(QString::number(player2->getScoreBreak()));
                        player2->setScore(player2->getScore()+6);
                        ui->labelScorePlayer2->setText(QString::number(player2->getScore()));
                        if ((billeRestantes[1]==0)&&(player2->dernierHistorique()!="Rouge"))
                        {
                            billeRestantes[6]--;
                            nbrRose->setText(QString::number(billeRestantes[6]));
                        }
                        player2->setVisitedToFalse();
                        player2->ajouterHistorique("Rose");
                        QLabel *labelImage= new QLabel();
                        labelImage->setPixmap(QPixmap(":/main/pics/billeRose.png"));
                        if (player2->tailleHistorique()<=12)
                        {
                            ui->gridLayoutBillePlayer2->addWidget(labelImage,1,player2->tailleHistorique());
                        }
                        else
                        {
                            if ((player2->tailleHistorique()>12)&&(player2->tailleHistorique()<=24))
                            {
                                ui->gridLayoutBillePlayer2->addWidget(labelImage,2,player2->tailleHistorique()-12);
                            }

                            else if (player2->tailleHistorique()>24)
                            {
                                ui->gridLayoutBillePlayer2->addWidget(labelImage,3,player2->tailleHistorique()-24);
                            }
                        }
                    }
                }
            }
        }
    }

}

void SnookerScoring::ajoutScoreNoir()
{
    if (billeRestantes[7]>0)
    {
        if(player1->isEtatBreak())
        {
            if (player1->getFault()=="Foul")
            {
                player2->setScore(player2->getScore()+7);
                ui->labelScorePlayer2->setText(QString::number(player2->getScore()));
                player2->setVisitedToFalse();
                player2->ajouterHistorique("Noir");
                passerBreak();
            }
            else
            {
                if (player1->getFault()=="Free Ball")
                {
                    fauteFreeBallJoueur1(7);
                }
                else
                {
                    if(player1->getFault()=="None")
                    {
                        player1->setScoreBreak(player1->getScoreBreak()+7);
                        ui->labelScoreBreak->setText(QString::number(player1->getScoreBreak()));
                        player1->setScore(player1->getScore()+7);
                        ui->labelScorePlayer1->setText(QString::number(player1->getScore()));
                        if ((billeRestantes[1]==0)&&(player1->dernierHistorique()!="Rouge"))
                        {
                            billeRestantes[7]--;
                            nbrNoir->setText(QString::number(billeRestantes[7]));
                        }
                        player1->setVisitedToFalse();
                        player1->ajouterHistorique("Noir");
                        QLabel *labelImage= new QLabel();
                        labelImage->setPixmap(QPixmap(":/main/pics/billeNoir.png"));
                        if (player1->tailleHistorique()<=12)
                        {
                            ui->gridLayoutBillePlayer1->addWidget(labelImage,1,player1->tailleHistorique());
                        }
                        else
                        {
                            if ((player1->tailleHistorique()>12)&&(player1->tailleHistorique()<=24))
                            {
                                ui->gridLayoutBillePlayer1->addWidget(labelImage,2,player1->tailleHistorique()-12);
                            }

                            else if (player1->tailleHistorique()>24)
                            {
                                ui->gridLayoutBillePlayer1->addWidget(labelImage,3,player1->tailleHistorique()-24);
                            }
                        }
                    }
                }
            }
        }

        else if(player2->isEtatBreak())
        {
            if (player2->getFault()=="Foul")
            {
                player1->setScore(player1->getScore()+7);
                ui->labelScorePlayer1->setText(QString::number(player1->getScore()));
                player1->setVisitedToFalse();
                player1->ajouterHistorique("Noir");
                passerBreak();
            }
            else
            {
                if (player2->getFault()=="Free Ball")
                {
                    fauteFreeBallJoueur2(7);
                }
                else
                {
                    if(player2->getFault()=="None")
                    {
                        player2->setScoreBreak(player2->getScoreBreak()+7);
                        ui->labelScoreBreak->setText(QString::number(player2->getScoreBreak()));
                        player2->setScore(player2->getScore()+7);
                        ui->labelScorePlayer2->setText(QString::number(player2->getScore()));
                        if ((billeRestantes[1]==0)&&(player2->dernierHistorique()!="Rouge"))
                        {
                            billeRestantes[7]--;
                            nbrNoir->setText(QString::number(billeRestantes[7]));
                        }
                        player2->setVisitedToFalse();
                        player2->ajouterHistorique("Noir");
                        QLabel *labelImage= new QLabel();
                        labelImage->setPixmap(QPixmap(":/main/pics/billeNoir.png"));
                        if (player2->tailleHistorique()<=12)
                        {
                            ui->gridLayoutBillePlayer2->addWidget(labelImage,1,player2->tailleHistorique());
                        }
                        else
                        {
                            if ((player2->tailleHistorique()>12)&&(player2->tailleHistorique()<=24))
                            {
                                ui->gridLayoutBillePlayer2->addWidget(labelImage,2,player2->tailleHistorique()-12);
                            }

                            else if (player2->tailleHistorique()>24)
                            {
                                ui->gridLayoutBillePlayer2->addWidget(labelImage,3,player2->tailleHistorique()-24);
                            }
                        }
                    }
                }
            }
        }
    }

}

void SnookerScoring::passerBreak()
{
    if(player1->isEtatBreak())
    {
        player1->setEtatBreak(false);
        ui->labelFlechePlayer1->setVisible(false);
        ui->labelFlechePlayer2->setVisible(true);
        player1->setScoreBreak(0);
        player1->setFault("None");
        ui->labelScoreBreak->setText("00");
        ui->labelScorePlayer1->setText(QString::number(player1->compterScoreTotal()));
        ui->labelFault->setText(""+player2->getFault());
        ui->labelPlayer1->setPixmap(QPixmap(":/main/pics/player1.png"));
        ui->labelPlayer2->setPixmap(QPixmap(":/main/pics/player2Baguette.png"));
        player2->setEtatBreak(true);
    }

    else if(player2->isEtatBreak())
    {
        player2->setEtatBreak(false);
        ui->labelFlechePlayer2->setVisible(false);
        ui->labelFlechePlayer1->setVisible(true);
        player2->setScoreBreak(0);
        player2->setFault("None");
        ui->labelScoreBreak->setText("00");
        ui->labelScorePlayer2->setText(QString::number(player2->compterScoreTotal()));
        ui->labelFault->setText(""+player1->getFault());
        ui->labelPlayer1->setPixmap(QPixmap(":/main/pics/player1Baguette.png"));
        ui->labelPlayer2->setPixmap(QPixmap(":/main/pics/player2.png"));
        player1->setEtatBreak(true);
    }
}

void SnookerScoring::afficherMemory()
{
    QString derniereBilleNonVisite;
    if(player1->isEtatBreak())
    {
        derniereBilleNonVisite=player1->dernierEtatBille();
        if (derniereBilleNonVisite=="Rouge")
        {
            ui->labelScorePlayer1->setText("1");
        }
        else
        {
            if (derniereBilleNonVisite=="Jaune")
            {
                ui->labelScorePlayer1->setText("2");
            }
            else
            {
                if (derniereBilleNonVisite=="Vert")
                {
                    ui->labelScorePlayer1->setText("3");
                }
                else
                {
                    if (derniereBilleNonVisite=="Marron")
                    {
                        ui->labelScorePlayer1->setText("4");
                    }
                    else
                    {
                        if (derniereBilleNonVisite=="Bleu")
                        {
                            ui->labelScorePlayer1->setText("5");
                        }
                        else
                        {
                            if (derniereBilleNonVisite=="Rose")
                            {
                                ui->labelScorePlayer1->setText("6");
                            }
                            else
                            {
                                if (derniereBilleNonVisite=="Noir")
                                {
                                    ui->labelScorePlayer1->setText("7");
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    else if(player2->isEtatBreak())
    {
        derniereBilleNonVisite=player2->dernierEtatBille();
        if (derniereBilleNonVisite=="Rouge")
        {
            ui->labelScorePlayer2->setText("1");
        }
        else
        {
            if (derniereBilleNonVisite=="Jaune")
            {
                ui->labelScorePlayer2->setText("2");
            }
            else
            {
                if (derniereBilleNonVisite=="Vert")
                {
                    ui->labelScorePlayer2->setText("3");
                }
                else
                {
                    if (derniereBilleNonVisite=="Marron")
                    {
                        ui->labelScorePlayer2->setText("4");
                    }
                    else
                    {
                        if (derniereBilleNonVisite=="Bleu")
                        {
                            ui->labelScorePlayer2->setText("5");
                        }
                        else
                        {
                            if (derniereBilleNonVisite=="Rose")
                            {
                                ui->labelScorePlayer2->setText("6");
                            }
                            else
                            {
                                if (derniereBilleNonVisite=="Noir")
                                {
                                    ui->labelScorePlayer2->setText("7");
                                }
                            }
                        }
                    }
                }
            }
        }
    }


}

void SnookerScoring::afficherCount()
{
    if(player1->isEtatBreak())
    {
        ui->labelScorePlayer1->setText(QString::number(player1->compterScoreTotal()));
    }

    else if(player2->isEtatBreak())
    {
        ui->labelScorePlayer2->setText(QString::number(player2->compterScoreTotal()));
    }
}

void SnookerScoring::annoncerGagnant()
{
    bool egalite=false;
    int framesAJoue=nbrFrames.toInt();
    if ((player1->getFrames()+player2->getFrames())<framesAJoue)
    {
        if(player1->getScore()>player2->getScore())
        {
            player1->setFrames(player1->getFrames()+1);
            ui->labelFramesPlayer1->setText(QString::number(player1->getFrames()));
        }
        else
        {
            if(player1->getScore()<player2->getScore())
            {
            player2->setFrames(player2->getFrames()+1);
            ui->labelFramesPlayer2->setText(QString::number(player2->getFrames()));
            }
            else
            {
                egalite=true;
            }
        }
    }
    if (((player1->getFrames()+player2->getFrames())==framesAJoue)||(player1->getFrames()>(float)framesAJoue/2)||(player2->getFrames()>(float)framesAJoue/2))
    {
        if(player1->getFrames()>player2->getFrames())
        {
            ui->labelNomJoueur1->setText("WINNER :"+player1->getUsername());
        }
        else if(player1->getScore()<player2->getScore())
        {
            ui->labelNomJoueur2->setText("WINNER :"+player2->getUsername());
        }

    }

    player1->setFault("None");
    player1->setScore(0);
    player1->setScoreBreak(0);
    player1->viderHistorique();
    player2->setFault("None");
    player2->setScore(0);
    player2->setScoreBreak(0);
    player2->viderHistorique();

    secondeCustomSlot(0);
    minuteCustomSlot(0);
    secondeObj->resetSeconde();
    minuteObj->resetMinute();
    secondeObj->settimeCount(0);
    secondeObj->setminuteCount(0);
    minuteObj->settimeCount(0);
    minuteObj->setminuteCount(0);

    if (ui->gridLayoutBillePlayer1->layout() != NULL )
    {
        QLayoutItem* item;
        while ( ( item = ui->gridLayoutBillePlayer1->layout()->takeAt( 0 ) ) != NULL )
        {
            delete item->widget();
            delete item;
        }
    }

    if (ui->gridLayoutBillePlayer2->layout() != NULL )
    {
        QLayoutItem* item;
        while ( ( item = ui->gridLayoutBillePlayer2->layout()->takeAt( 0 ) ) != NULL )
        {
            delete item->widget();
            delete item;
        }
    }

    ui->labelScoreBreak->setText("00");
    ui->labelFault->setText("None");
    ui->labelScorePlayer1->setText("0");
    ui->labelScorePlayer2->setText("0");

    if(egalite)
    {
        billeRestantes.clear();
        billeRestantes.append(0);
        billeRestantes.append(0);
        billeRestantes.append(0);
        billeRestantes.append(0);
        billeRestantes.append(0);
        billeRestantes.append(0);
        billeRestantes.append(0);
        billeRestantes.append(1);
    }
    else
    {
        billeRestantes.clear();
        billeRestantes.append(0);
        billeRestantes.append(15);
        billeRestantes.append(1);
        billeRestantes.append(1);
        billeRestantes.append(1);
        billeRestantes.append(1);
        billeRestantes.append(1);
        billeRestantes.append(1);
    }
    nbrRouge->setText(QString::number(billeRestantes[1]));
    nbrJaune->setText(QString::number(billeRestantes[2]));
    nbrVert->setText(QString::number(billeRestantes[3]));
    nbrMarron->setText(QString::number(billeRestantes[4]));
    nbrBleu->setText(QString::number(billeRestantes[5]));
    nbrRose->setText(QString::number(billeRestantes[6]));
    nbrNoir->setText(QString::number(billeRestantes[7]));
    ui->labelPlayer1->setPixmap(QPixmap(":/main/pics/player1Baguette.png"));
    ui->labelPlayer2->setPixmap(QPixmap(":/main/pics/player2.png"));

}

void SnookerScoring::ajouterFramesJoueur1()
{
    player1->setFrames(player1->getFrames()+1);
    ui->labelFramesPlayer1->setText(QString::number(player1->getFrames()));
}

void SnookerScoring::ajouterFramesJoueur2()
{
    player2->setFrames(player2->getFrames()+1);
    ui->labelFramesPlayer2->setText(QString::number(player2->getFrames()));
}

void SnookerScoring::reinitialiserFramesJoueur1()
{
    player1->setFault("None");
    player1->setScore(0);
    player1->setFrames(0);
    player1->setScoreBreak(0);
    player1->viderHistorique();
    ui->labelNomJoueur1->setText(player1->getUsername());
    ui->labelFault->setText("None");
    ui->labelScoreBreak->setText("00");
    ui->labelScorePlayer1->setText("0");
    ui->labelFramesPlayer1->setText("0");

    secondeCustomSlot(0);
    minuteCustomSlot(0);
    secondeObj->resetSeconde();
    minuteObj->resetMinute();
    secondeObj->settimeCount(0);
    secondeObj->setminuteCount(0);
    minuteObj->settimeCount(0);
    minuteObj->setminuteCount(0);

    if (ui->gridLayoutBillePlayer1->layout() != NULL )
    {
        QLayoutItem* item;
        while ( ( item = ui->gridLayoutBillePlayer1->layout()->takeAt( 0 ) ) != NULL )
        {
            delete item->widget();
            delete item;
        }
    }


    billeRestantes.clear();
    billeRestantes.append(0);
    billeRestantes.append(15);
    billeRestantes.append(1);
    billeRestantes.append(1);
    billeRestantes.append(1);
    billeRestantes.append(1);
    billeRestantes.append(1);
    billeRestantes.append(1);
    nbrRouge->setText(QString::number(billeRestantes[1]));
    nbrJaune->setText(QString::number(billeRestantes[2]));
    nbrVert->setText(QString::number(billeRestantes[3]));
    nbrMarron->setText(QString::number(billeRestantes[4]));
    nbrBleu->setText(QString::number(billeRestantes[5]));
    nbrRose->setText(QString::number(billeRestantes[6]));
    nbrNoir->setText(QString::number(billeRestantes[7]));
    ui->labelPlayer1->setPixmap(QPixmap(":/main/pics/player1Baguette.png"));
}

void SnookerScoring::reinitialiserFramesJoueur2()
{
    player2->setFault("None");
    player2->setScore(0);
    player2->setFrames(0);
    player2->setScoreBreak(0);
    player2->viderHistorique();
    ui->labelNomJoueur2->setText(player2->getUsername());
    ui->labelFault->setText("None");
    ui->labelScoreBreak->setText("00");
    ui->labelScorePlayer2->setText("0");
    ui->labelFramesPlayer2->setText("0");

    secondeCustomSlot(0);
    minuteCustomSlot(0);
    secondeObj->resetSeconde();
    minuteObj->resetMinute();
    secondeObj->settimeCount(0);
    secondeObj->setminuteCount(0);
    minuteObj->settimeCount(0);
    minuteObj->setminuteCount(0);

    if (ui->gridLayoutBillePlayer2->layout() != NULL )
    {
        QLayoutItem* item;
        while ( ( item = ui->gridLayoutBillePlayer2->layout()->takeAt( 0 ) ) != NULL )
        {
            delete item->widget();
            delete item;
        }
    }

    billeRestantes.clear();
    billeRestantes.append(0);
    billeRestantes.append(15);
    billeRestantes.append(1);
    billeRestantes.append(1);
    billeRestantes.append(1);
    billeRestantes.append(1);
    billeRestantes.append(1);
    billeRestantes.append(1);
    nbrRouge->setText(QString::number(billeRestantes[1]));
    nbrJaune->setText(QString::number(billeRestantes[2]));
    nbrVert->setText(QString::number(billeRestantes[3]));
    nbrMarron->setText(QString::number(billeRestantes[4]));
    nbrBleu->setText(QString::number(billeRestantes[5]));
    nbrRose->setText(QString::number(billeRestantes[6]));
    nbrNoir->setText(QString::number(billeRestantes[7]));
    ui->labelPlayer2->setPixmap(QPixmap(":/main/pics/player2.png"));
}

void SnookerScoring::changerFaute()
{
    if(player1->isEtatBreak())
    {
        if (player1->getFault()=="None")
        {
            player1->setFault("Foul");
            ui->labelFault->setText(""+player1->getFault());
        }
        else
        {
            if (player1->getFault()=="Foul")
            {
                player1->setFault("Free Ball");
                ui->labelFault->setText(""+player1->getFault());
            }
            else
                if (player1->getFault()=="Free Ball")
                {
                    player1->setFault("None");
                    ui->labelFault->setText(player1->getFault());
                }
        }

    }

    else if(player2->isEtatBreak())
    {
        if (player2->getFault()=="None")
        {
            player2->setFault("Foul");
            ui->labelFault->setText(""+player2->getFault());
        }
        else
        {
            if (player2->getFault()=="Foul")
            {
                player2->setFault("Free Ball");
                ui->labelFault->setText(""+player2->getFault());
            }
            else
                if (player2->getFault()=="Free Ball")
                {
                    player2->setFault("None");
                    ui->labelFault->setText(player2->getFault());
                }
        }
    }
}


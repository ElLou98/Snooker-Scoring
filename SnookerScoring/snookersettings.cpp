#include "snookersettings.h"
#include "ui_snookersettings.h"
#include "snookeraccueil.h"
#include "snookerscoring.h"
#include "Joueur.h"

SnookerSettings::SnookerSettings(QWidget *parent) :
    QWidget(parent)
    ,boutonLancerPartie (new QtMaterialRaisedButton("Start Game"))
    ,boutonRetour (new QtMaterialRaisedButton("Back"))
    ,nomJoueur1 (new QtMaterialTextField())
    ,nomJoueur2 (new QtMaterialTextField())
    ,ui(new Ui::SnookerSettings)
{
    ui->setupUi(this);
    this->showFullScreen();

    QColor couleurBouton("#9c2b60");
    QColor couleurTexte("#9c2b60");

    QString labelTexte="Click Here !";


    nomJoueur1->setLabel("Click Here !");
    nomJoueur1->setPlaceholderText("Name / Surname");
    nomJoueur1->setLabelColor(couleurTexte);
    nomJoueur1->setInkColor(couleurTexte);
    nomJoueur1->setLabelFontSize(11);
    ui->layoutTextField1->addWidget(nomJoueur1,0,Qt::AlignTop);

    nomJoueur2->setLabel("Click Here !");
    nomJoueur2->setPlaceholderText("Name / Surname");
    nomJoueur2->setLabelColor(couleurTexte);
    nomJoueur2->setInkColor(couleurTexte);
    nomJoueur2->setLabelFontSize(11);
    ui->layoutTextField2->addWidget(nomJoueur2,0,Qt::AlignTop);



    boutonLancerPartie->setBackgroundColor(couleurBouton);
    ui->layoutBoutonPlay->addWidget(boutonLancerPartie);

    boutonRetour->setBackgroundColor(couleurBouton);
    ui->verticalLayout_7->addWidget(boutonRetour,0,Qt::AlignTop);

    shortcutRetour = new QShortcut(QKeySequence("b"), this);
    QObject::connect(shortcutRetour, SIGNAL(activated()), this, SLOT(retourAccueil()));

    shortcutLancerPartie = new QShortcut(QKeySequence("Ctrl+s"), this);
    QObject::connect(shortcutLancerPartie, SIGNAL(activated()), this, SLOT(allerScoring()));

    QObject::connect(boutonLancerPartie,SIGNAL(clicked()),this,SLOT(allerScoring()));
    QObject::connect(boutonRetour,SIGNAL(clicked()),this,SLOT(retourAccueil()));


    Card("#F1F0CC",ui->groupBox);
}

SnookerSettings::~SnookerSettings()
{
    delete ui;
}

void SnookerSettings::Card(QString color, QWidget *wd)
{
    QGraphicsDropShadowEffect* effect = new QGraphicsDropShadowEffect();

       // QVBoxLayout *widgetlayout = new QVBoxLayout;
        QString style = "QGroupBox { background: " + color +
                        ";  border: 1px solid #d7dfe3;  border-radius: 4px; }";
         wd->setStyleSheet(style);
        effect->setBlurRadius(20);
        effect->setColor(QColor(0, 0, 0, 50));
        effect->setOffset(0,0);
        wd->setGraphicsEffect(effect);
       // wd->setLayout(widgetlayout);

}

void SnookerSettings::retourAccueil()
{
    SnookerAccueil *fenetre=new SnookerAccueil;
    this->close();
    fenetre->show();
}

void SnookerSettings::allerScoring()
{
    if ((nomJoueur1->text().isEmpty())||(nomJoueur2->text().isEmpty())){
        QMessageBox::information(this,"Name / Surname","Enter a name and a surname for player 1 and 2 !");
    }
    else {
    QVector<QString> historique1;
    QVector<QString> historique2;
    Joueur *player1=new Joueur(nomJoueur1->text(), "None", 0, 0, 0, true, historique1);
    Joueur *player2=new Joueur(nomJoueur2->text(), "None", 0, 0, 0, false, historique2);
    QString nbrFrames=ui->comboBox->currentText();
    SnookerScoring *fenetre=new SnookerScoring(player1,player2,nbrFrames);
    this->close();
    fenetre->show();
    }
}

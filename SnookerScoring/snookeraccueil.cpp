#include "snookeraccueil.h"
#include "ui_snookeraccueil.h"
#include "snookersettings.h"
#include <QMessageBox>

SnookerAccueil::SnookerAccueil(QWidget *parent) :
    QWidget(parent)
    ,boutonNouvellePartie (new QtMaterialRaisedButton("Start Game"))
    ,boutonQuitter (new QtMaterialRaisedButton("Exit"))
    ,ui(new Ui::SnookerAccueil)
{
    ui->setupUi(this);
    this->showFullScreen();
    QColor couleurBouton("#9c2b60");


    boutonNouvellePartie->setBackgroundColor(couleurBouton);
    ui->layoutNouvellePartie->addWidget(boutonNouvellePartie);

    boutonQuitter->setBackgroundColor(couleurBouton);
    ui->layoutQuitterPartie->addWidget(boutonQuitter);

    Card("#F1F0CC",ui->groupBox);

    shortcutLancer = new QShortcut(QKeySequence("Ctrl+s"), this);
    QObject::connect(shortcutLancer, SIGNAL(activated()), this, SLOT(allerSettings()));
    shortcutQuitter = new QShortcut(QKeySequence("e"), this);
    QObject::connect(shortcutQuitter, SIGNAL(activated()), qApp, SLOT(quit()));

    QObject::connect(boutonNouvellePartie,SIGNAL(clicked()),this,SLOT(allerSettings()));
    QObject::connect(boutonQuitter,SIGNAL(clicked()),qApp,SLOT(quit()));
}

void SnookerAccueil::Card(QString color, QWidget *wd)
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


SnookerAccueil::~SnookerAccueil()
{
    delete ui;
}

void SnookerAccueil::allerSettings()
{
    SnookerSettings *fenetre=new SnookerSettings;
    fenetre->show();
    this->close();
}


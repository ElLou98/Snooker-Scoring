#ifndef SNOOKERSETTINGS_H
#define SNOOKERSETTINGS_H


#include <QWidget>
#include "qtmaterialraisedbutton.h"
#include <QGraphicsDropShadowEffect>
#include "qtmaterialtextfield.h"
#include <QColor>
#include <QMessageBox>
#include <QVector>
#include <QShortcut>


namespace Ui {
class SnookerSettings;
}

class SnookerSettings : public QWidget
{
    Q_OBJECT
public slots:
    void retourAccueil();
    void allerScoring();

public:
    explicit SnookerSettings(QWidget *parent = nullptr);
    void Card(QString color, QWidget *wd);
    ~SnookerSettings();

private:
    Ui::SnookerSettings *ui;
    QtMaterialRaisedButton *boutonLancerPartie;
    QtMaterialRaisedButton *boutonRetour;
    QtMaterialTextField *nomJoueur1;
    QtMaterialTextField *nomJoueur2;
    QShortcut *shortcutRetour;
    QShortcut *shortcutLancerPartie;
};

#endif // SNOOKERSETTINGS_H

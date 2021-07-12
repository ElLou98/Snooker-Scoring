#ifndef SNOOKERACCUEIL_H
#define SNOOKERACCUEIL_H

#include <QWidget>
#include <QGraphicsDropShadowEffect>
#include <QVBoxLayout>
#include <QColor>
#include <QShortcut>
#include "qtmaterialraisedbutton.h"

namespace Ui {
class SnookerAccueil;
}

class SnookerAccueil : public QWidget
{
    Q_OBJECT

public slots:
    void allerSettings();

public:
    explicit SnookerAccueil(QWidget *parent = nullptr);
    void Card(QString color, QWidget *wd);
    ~SnookerAccueil();

private:
    Ui::SnookerAccueil *ui;
    QtMaterialRaisedButton *boutonNouvellePartie;
    QtMaterialRaisedButton *boutonQuitter;
    QShortcut *shortcutLancer;
    QShortcut *shortcutQuitter;
};

#endif // SNOOKERACCUEIL_H

#ifndef JOUEUR_H
#define JOUEUR_H

#include <QString>
#include <QVector>



class Joueur
{
private:
    QString username;
    QString fault;
    int score;
    int frames;
    int scoreBreak;
    bool etatBreak;
    struct etatBille {
        QString couleur;
        bool visited;
    };
    QVector<etatBille> historique;

public:
    Joueur(QString username,QString fault,int score,int frames,int scoreBreak, bool etatBreak,QVector<QString> historique);
    Joueur();
    QString getUsername();
    void setUsername(QString username);
    QString getFault();
    void setFault(QString fault);
    int getScore();
    void setScore(int score);
    int getFrames();
    void setFrames(int frames);
    int getScoreBreak();
    void setScoreBreak(int scoreBreak);
    bool isEtatBreak();
    void setEtatBreak(bool etatBreak);
    void ajouterHistorique(QString couleurBille);
    QString dernierHistorique();
    void setVisitedToFalse();
    QString dernierEtatBille();
    int compterScoreTotal();
    void viderHistorique();
    int tailleHistorique();
    ~Joueur();

};


#endif // JOUEUR_H

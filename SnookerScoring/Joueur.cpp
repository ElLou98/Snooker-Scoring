#include "Joueur.h"


Joueur::Joueur(QString username,QString fault,int score,int frames,int scoreBreak, bool etatBreak,QVector<QString> historique) {
    this->username=username;
    this->fault=fault;
    this->score=score;
    this->frames=frames;
    this->scoreBreak=scoreBreak;
    this->etatBreak=etatBreak;
}

Joueur::Joueur() {
    username="";
    fault="";
    score=0;
    frames=0;
    scoreBreak=0;
    etatBreak=false;
}

QString Joueur::getUsername() {
    return username;
}

void Joueur::setUsername(QString username) {
    this->username = username;
}

QString Joueur::getFault() {
    return fault;
}

void Joueur::setFault(QString fault) {
    this->fault = fault;
}

int Joueur::getScore() {
    return score;
}

void Joueur::setScore(int score) {
    this->score = score;
}

int Joueur::getFrames() {
    return frames;
}

void Joueur::setFrames(int frames) {
    this->frames = frames;
}

int Joueur::getScoreBreak() {
    return scoreBreak;
}

void Joueur::setScoreBreak(int scoreBreak) {
    this->scoreBreak = scoreBreak;
}

bool Joueur::isEtatBreak() {
    return etatBreak;
}

void Joueur::setEtatBreak(bool etatBreak) {
    this->etatBreak = etatBreak;
}

void Joueur::ajouterHistorique(QString couleurBille){

    etatBille nouveauEtatBille;
    nouveauEtatBille.couleur=couleurBille;
    nouveauEtatBille.visited=false;
    this->historique.append(nouveauEtatBille);
}

QString Joueur::dernierHistorique()
{
    if (historique.size()==0)
    {
        return "None";
    }
    else
    {
      return this->historique[historique.size()-1].couleur;
    }

}

void Joueur::setVisitedToFalse()
{
    for (int j=0;j<historique.size();j++)
    {
        historique[j].visited=false;
    }

}

QString Joueur::dernierEtatBille()
{
    if(historique.size()>0)
    {
        int i=historique.size()-1;
        while ((i>0)&&(historique[i].visited))
        {
            i--;
        }
        historique[i].visited=true;

        if (i==0)
        {
          setVisitedToFalse();
        }
        return historique[i].couleur;
    }
    else
        return "None";
}

int Joueur::compterScoreTotal()
{
    int scoreJoueur=0;
    setVisitedToFalse();
    for (int i=0;i<historique.size();i++)
    {
        if (historique[i].couleur=="Rouge")
        {
            scoreJoueur+=1;
        }
        else
        {
            if (historique[i].couleur=="Jaune")
            {
                scoreJoueur+=2;
            }
            else
            {
                if (historique[i].couleur=="Vert")
                {
                    scoreJoueur+=3;
                }
                else
                {
                    if (historique[i].couleur=="Marron")
                    {
                        scoreJoueur+=4;
                    }
                    else
                    {
                        if (historique[i].couleur=="Bleu")
                        {
                            scoreJoueur+=5;
                        }
                        else
                        {
                            if (historique[i].couleur=="Rose")
                            {
                                scoreJoueur+=6;
                            }
                            else
                            {
                                if (historique[i].couleur=="Noir")
                                {
                                    scoreJoueur+=7;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return scoreJoueur;

}

void Joueur::viderHistorique()
{
    historique.clear();
}

int Joueur::tailleHistorique()
{
    return historique.size();
}




#include "Caracteristiques.h"

using namespace state;

Caracteristiques :: Caracteristiques (int sante, int attaque, int defense,
                    int initiative, int vitesse) :sante(sante),attaque(attaque),defense(defense),initiative(initiative),vitesse(vitesse)
{}

Caracteristiques::Caracteristiques(){
  this->sante =0;
  this->attaque = 0;
  this->defense = 0;
  this->initiative = 0;
  this->vitesse = 0;
}

Caracteristiques ::   ~Caracteristiques(){}

int Caracteristiques ::  getSante() const{
    return sante;
  }
  void Caracteristiques :: setSante(int sante){
    this->sante = sante;
  }
  int Caracteristiques ::  getAttaque() const{
    return attaque;
  }
  void Caracteristiques :: setAttaque(int attaque){
    this->attaque = attaque;
  }
  int Caracteristiques :: getDefense() const{
    return defense;
  }
  void Caracteristiques :: setDefense(int defense){
    this->defense = defense;
  }

  int Caracteristiques :: getInitiative() const{
    return initiative;
  }
  void Caracteristiques :: setInitiative(int initiative){
    this->initiative = initiative;
  }
  int Caracteristiques :: getVitesse() const{
    return vitesse;
  }
  void Caracteristiques :: setVitesse(int vitesse){
    this->vitesse = vitesse;
  }

void Caracteristiques :: addBonus(int sante, int attaque, int defense, int initiative, int vitesse){
  setSante(this->sante+sante);
  setAttaque(this->attaque+attaque);
  setDefense(this->defense+defense);
  setInitiative(this->initiative+initiative);
  setVitesse(this->vitesse+vitesse);
}

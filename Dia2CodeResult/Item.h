// Generated by dia2code
#ifndef ITEM__H
#define ITEM__H
#include "Caracteristiques.h"
#include <iostream>
/// class Item -
class Item {
  // Attributes

private:
  Caracteristiques* bonus;
  std::string nom;
protected:
  int prix;
  // Operations
public:
  Item (std::string nom= "NomParDefaut", int prix = 100, Caracteristiques* bonus = new Caracteristiques());
  ~Item ();
  // Setters and Getters
  int getPrix() const;
  void setPrix(int prix);
  std::string getNom() const;
  void setNom(std::string nom);
  Caracteristiques* getBonus();
  void setBonus(Caracteristiques*  bonus);
};

#endif

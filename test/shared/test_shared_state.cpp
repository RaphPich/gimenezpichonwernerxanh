#include <boost/test/unit_test.hpp>

#include "../../src/shared/state.h"

using namespace std;
using namespace state;

BOOST_AUTO_TEST_CASE(TestStaticAssert)
{
  BOOST_CHECK(1);
}

BOOST_AUTO_TEST_CASE(TestStateNamespace)
{

  {
  //Position
    Position p {1,2,"NORTH"};
    BOOST_CHECK_EQUAL(p.getX(),1);
    BOOST_CHECK_EQUAL(p.getY(), 2);
    BOOST_CHECK_EQUAL(p.getOrientation(), "NORTH");
    p.deplacer(1,1);
    BOOST_CHECK_EQUAL(p.getX(), 2);
    BOOST_CHECK_EQUAL(p.getY(), 3);
    p.placer(5,6);
    BOOST_CHECK_EQUAL(p.getX(), 5);
    BOOST_CHECK_EQUAL(p.getY(), 6);
    p.rotate("SOUTH");
    Position p2 {1,2,"NORTH"};
    BOOST_CHECK_EQUAL(p.distance(p2),8);
    BOOST_CHECK_EQUAL(p.egale(p2),0);
    BOOST_CHECK_EQUAL(p.getPositionsAlentour()[0].getX(),5);
    BOOST_CHECK_EQUAL(p.getPositionsAlentour()[0].getY(),7);
    BOOST_CHECK_EQUAL(p.getPositionsAlentour()[1].getX(),5);
    BOOST_CHECK_EQUAL(p.getPositionsAlentour()[1].getY(),5);
    BOOST_CHECK_EQUAL(p.getPositionsAlentour()[2].getX(),4);
    BOOST_CHECK_EQUAL(p.getPositionsAlentour()[2].getY(),6);
    BOOST_CHECK_EQUAL(p.getPositionsAlentour()[3].getX(),6);
    BOOST_CHECK_EQUAL(p.getPositionsAlentour()[3].getY(),6);

  //Caracteristiques
    Caracteristiques ca {100,10,9,8,7};
    BOOST_CHECK_EQUAL(ca.getSante(),100);
    BOOST_CHECK_EQUAL(ca.getAttaque(),10);
    BOOST_CHECK_EQUAL(ca.getDefense(),9);
    BOOST_CHECK_EQUAL(ca.getInitiative(),8);
    BOOST_CHECK_EQUAL(ca.getVitesse(),7);
    ca.setSante(ca.getSante() - 10);
    ca.setAttaque(5);
    ca.setDefense(5);
    ca.setInitiative(5);
    ca.setVitesse(5);
    ca.addBonus(-10,5,5,5,5);
    BOOST_CHECK_EQUAL(ca.getSante(),80);
    BOOST_CHECK_EQUAL(ca.getAttaque(),10);
    BOOST_CHECK_EQUAL(ca.getDefense(),10);
    BOOST_CHECK_EQUAL(ca.getInitiative(),10);
    BOOST_CHECK_EQUAL(ca.getVitesse(),10);
    Caracteristiques ca2;

    //Entite
      string chaise = "Chaise";
      Entite e {ca,p,chaise};
      BOOST_CHECK_EQUAL(e.getCaracteristiques().getSante(),ca.getSante());
      BOOST_CHECK_EQUAL(e.getPosition().getX(),p.getX());
      BOOST_CHECK_EQUAL(e.getNom(),"Chaise");

      Entite empty_entity;
      empty_entity.setPosition(p);
      empty_entity.setCaracteristiques(ca);
      empty_entity.setNom("Chien");
      empty_entity.setTileCode(5);
      BOOST_CHECK_EQUAL(empty_entity.getTileCode(),5);

  //Item
    Caracteristiques ca_arme {100,10,9,8,7};
    Item item {"Epee",30,ca_arme};
    BOOST_CHECK_EQUAL(item.getPrix(),30);
    BOOST_CHECK_EQUAL(item.getNom(),"Epee");
    BOOST_CHECK_EQUAL(item.getBonus().getSante(),ca_arme.getSante());
    item.setPrix(40);
    item.setNom("Hache");
    BOOST_CHECK_EQUAL(item.getPrix(),40);
    BOOST_CHECK_EQUAL(item.getNom(),"Hache");
    Caracteristiques nca {8,8,8,4,8};
    item.setBonus(nca);
    // pas besoin de tester les autres getter ici on test le setBonus
    BOOST_CHECK_EQUAL(item.getBonus().getSante(),8);


  //Curseur
    Curseur curs{2,2};
    BOOST_CHECK_EQUAL(curs.getVisible(),false);
    curs.setVisible(true);
    BOOST_CHECK_EQUAL(curs.getVisible(),true);
    BOOST_CHECK_EQUAL(curs.getLastPosition().getX(),2);
    curs.deplacer(p); // p => {5,6} here
    curs.deplacer(p2);
    BOOST_CHECK_EQUAL(curs.getLastPosition().getX(),5);

  //Joueur
    Joueur jack {"Jack",10};
    jack.setStatut(CIBLE);
    jack.setMonnaie(15);
    jack.setDeplacementsBase(6);
    jack.setDeplacements(5);
    jack.setJoueurIndex(2);
    jack.setEstEnnemi(false);
    BOOST_CHECK_EQUAL(jack.getStatut(),CIBLE);
    BOOST_CHECK_EQUAL(jack.getMonnaie(),15);
    BOOST_CHECK_EQUAL(jack.getDeplacementsBase(),6);
    BOOST_CHECK_EQUAL(jack.getDeplacements(),5);
    BOOST_CHECK_EQUAL(jack.getJoueurIndex(),2);
    BOOST_CHECK_EQUAL(jack.getEstEnnemi(),false);

    jack.ajoueMonnaie(10);

    Joueur bob;
    bob.setNom("Bob");
    bob.setStatut(DISP);
    bob.setMonnaie(10);
    bob.setDeplacementsBase(5);
    bob.setDeplacements(3);
    bob.setJoueurIndex(1);
  //!!!!!!!!!!!!!!!!DESTRUCTORS!!!!!!!!!!!!!!!!


  }
}

//Name: John Sorhannus
//Class: CSCI330, Sec 1
//Semester: Fall 2018
//Program 5 Implementation (monster5.h)
//This is the header file for Monster in the game "Saving Syra."

#ifndef MONSTER5_h
#define MONSTER5_h

#include "player5.h"

class Monster : public PlayerClass {
public:
    virtual Monster* Clone() const = 0;
    //Pure virtual function
    
    virtual void Write(ostream& stream) const;
    //Prints out all of the player's attributes on the command line
    //Pre: stream must be of type ostream
    //Post: All of the player's attributes are printed out on the command line
    
    virtual vector<string> InitialWeaponList() const = 0;
    //Pure virtual function
protected:
    Monster(string name, const int abilityAdj[], const int hitDie[]);
    //Parameterized constructor for monster
    //Pre: None
    //Post: Creates a monster
    
    Monster& operator=(const Monster& m);
    //Overloaded assignment operator -- helps copy over HIT_DIE pointer
    //Pre: m should not have the same address as 'this'
    //Post: A monster that is identical to 'm'
    
    int RollHitDie() const;
    //Rolls the monster's hit die
    //Pre: None
    //Post: Results of the hit die roll is returned
    
    virtual int RollAttack(const int attackBonus[]) const;
    //Rolls for attack
    //Pre: None
    //Post: Results of the attack roll is returned
    
    virtual int RollSavingThrow(SavingThrowType kind, const int savingThrows[]) const;
    //Rolls for saving throw
    //Pre: kind must be valid
    //Post: Results of saving throw roll is returned
private:
    enum MeleeRangeType {MELEE, RANGE};
    
    /********* ATTRIBUTES ***********/
    const int *const HIT_DIE;
    
    /*********** METHODS ***********/
    Monster();
    //A default constructor for Monster
    //Not meant to be used
    
    int AttackBonus(const int baseAttackBonus[]) const;
    //Returns monster's attack bonus
    //Pre: None
    //Post: Monster's attack roll is returned
    
    int SavingThrowBonus(SavingThrowType kind, const int savingThrows[]) const;
    //Returns monster's saving throw bonus
    //Pre: kind must be valid
    //Post: Monster's saving throw bonus is returned

};


#endif

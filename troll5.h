//Name: John Sorhannus
//Class: CSCI330, Sec 1
//Semester: Fall 2018
//Program 5 Implementation (troll5.h)
//This is the header file for Troll in the game "Saving Syra."

#ifndef TROLL5_h
#define TROLL5_h

#include "monster5.h"

class Troll : public Monster {
public:
    Troll(string name);
    //A parameterized constructor which initializes all instance attributes for an Troll
    //Pre: None
    //Post: Creates a Troll
    
    string RaceStr() const;
    //Returns RACE
    //Pre: None
    //Post: RACE is returned
    
    virtual vector<string> InitialWeaponList() const;
    //Returns a vector containing the initial weapon
    //Pre: None
    //Post: A vector containing INIT_WEAPON is returned
    
    virtual int RollAttack() const;
    //Calculates and returns the attack roll for an troll
    //Pre: None
    //Post: The attack roll will be returned if the player is active, 0 if otherwise.
    
    virtual int RollSavingThrow(SavingThrowType kind) const;
    //Returns result of a saving throw roll for an troll
    //Pre: kind must be valid
    //Post: The result of a saving throw roll for an troll is returned
    
    virtual void Write(ostream& stream) const;
    //Prints out all of the player's attributes on the command line
    //Pre: stream must be of type ostream
    //Post: All of the player's attributes are printed out on the command line
    
    friend class Player;
protected:
    virtual Troll* Clone() const;

private:
    static const string RACE;
    //Holds the player's race in the form of a string
    
    static const int ABILITY_ADJ[NUM_ABILITIES];
    //Holds the player's ability scores. Indexed using AbilityType
    
    static const int HIT_DIE[NUM_ROLL_DIE_INFO];
    //Holds the player's hit die. Indexed using RollDieInfoType
    
    static const int SAVING_THROW[NUM_SAVINGTHROW];
    //Holds the player's saving throw values. Indexed using SavingThrowType
    
    static const int BASE_ATTACK_BONUS[NUM_MELEE_RANGE];
    //Holds the player's base attack bonus
    
    static const string INIT_WEAPON;
    //Holds the player's inital weapon in string form
    
    static const int NUM_INIT_SKILLS = 2;
    //Holds number of weapons player starts out with
    
    static const string INIT_SKILLS[NUM_INIT_SKILLS];
    //Holds player's initial skills.
    
    /************* METHODS ****************/
    Troll();
    //A default constructor for Troll
    //Not meant to be used
    
    virtual void InitSkills();
    //Initializes player's skills
    //Pre: None
    //Post: None
};

#endif

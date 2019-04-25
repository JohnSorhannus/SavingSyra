//Name: John Sorhannus
//Class: CSCI330, Sec 1
//Semester: Fall 2018
//Program 5 Implementation (human5.h)
//This is the header file for Human in the game "Saving Syra."

#ifndef HUMAN5_h
#define HUMAN5_h

#include "humanoid5.h"

class Human : public Humanoid {
public:
    Human(string name, VocRules::VocType voc = DEFAULT_VOC);
    //A parameterized constructor which initializes all instance attributes for a Human
    //Pre: None
    //Post: Creates an Human
    
    string RaceStr() const;
    //Returns RACE
    //Pre: None
    //Post: RACE is returned
    
    virtual vector<string> InitialWeaponList() const;
    //Returns a vector containing the initial weapon
    //Pre: None
    //Post: A vector containing INIT_WEAPON is returned
    
    virtual void Write(ostream& out) const;
    //Prints out all of the player's attributes on the command line
    //Pre: stream must be of type ostream
    //Post: All of the player's attributes are printed out on the command line
    
    friend class Player;
protected:
    virtual Human* Clone() const;
    //Creates copy of an instance
    //Pre: None
    //Post: Returns a pointer to a copy of the current instance
private:
    static const string RACE;
    //Holds the player's race in the form of a string
    
    static const int ABILITY_ADJ[NUM_ABILITIES];
    //Holds the player's ability scores. Indexed using AbilityType

    static const VocRules::VocType DEFAULT_VOC;
    //Holds player's default vocation
    
    static const string INIT_WEAPON[VocRules::NUM_VOC];
    //Holds the player's inital weapon in string form
    
    Human();
    //A default constructor for Human
    //Not meant to be used
};

#endif

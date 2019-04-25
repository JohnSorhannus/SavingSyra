//Name: John Sorhannus
//Class: CSCI330, Sec 1
//Semester: Fall 2018
//Program 5 Implementation (halfelf5.h)
//This is the header file for Half Elf in the game "Saving Syra."

#ifndef HALFELF5_h
#define HALFELF5_h

#include "humanoid5.h"

class HalfElf : public Humanoid {
public:
    HalfElf(string name, VocRules::VocType voc = DEFAULT_VOC);
    //A parameterized constructor which initializes all instance attributes for an Half Elf
    //Pre: None
    //Post: Creates an HalfElf
    
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
    
    virtual int RollSavingThrow(SavingThrowType kind) const;
    //Rolls saving throw for half elf
    
    virtual Weapon::Weapon* FindWeapon(Weapon::Weapon* wpn);
    //Changes weapon based on weight limit
    //Pre: wpn cannot be null
    //Post: wpn returned if it cannot be replaced
    
    friend class Player;
protected:
    virtual HalfElf* Clone() const;
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
    
    static const int MAX_WEAPON = 2;
    //stores maximum number of initial weapons
    
    static const int WEAPON_WEIGHT_LIMIT;
    //stores weight of heaviest weapon a Half Elf can carry
    
    static const string INIT_WEAPON[VocRules::NUM_VOC][MAX_WEAPON];
    //Holds the player's inital weapon in string form
    
    HalfElf();
    //A default constructor for Half Elf
    //Not meant to be used
};

#endif


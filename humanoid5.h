//Name: John Sorhannus
//Class: CSCI330, Sec 1
//Semester: Fall 2018
//Program 5 Implementation (humanoid5.h)
//This is the header file for Humanoid in the game "Saving Syra."

#ifndef HUMANOID5_h
#define HUMANOID5_h

#include "player5.h"
#include "pack.h"

class Humanoid : public PlayerClass {
public:
    virtual Humanoid* Clone() const = 0;
    //Pure virtual function
    
    virtual ~Humanoid();
    //Destructor
    
    VocRules::VocType Voc() const;
    // returns the enum value for vocation
    
    string VocStr() const;
    // returns the vocation
    // pre:  none.
    // post: returns the vocation as a string
    
    int Level() const;
    //Returns the player's current level within the vocation.
    //Pre: None
    //Post: The player's level within the vocation will be returned.
    
    long XP() const;
    //Returns the player's XP (experience points)
    //Pre: None
    //Post: The player's XP will be returned.
    
    vector<string> Pack() const;
    //Returns the player's pack as a sorted vector of weapon names
    //Pre: None
    //Post: The player's pack as a sorted vector of weapon names is returned
    
    virtual vector<string> InitialWeaponList() const = 0;
    // returns the list of initial equipment
    // pre:  array of strings must be large enough
    // post: returns the list of equipment
    
    virtual Weapon::Weapon* FindWeapon(Weapon::Weapon* wpn);
    //Changes the current weapon and returns current weapon
    
    Weapon::Weapon* ChangeWeapon(string wName);
    // Player should change the current weapon with wName
    // pre: none
    // post: if player is active and player has the wName
    //  in inventory then current weapon is put in pack
    //  and current weapon is wName.
    
    virtual int RollAttack() const;
    //Determines the AttackRoll value
    
    virtual int RollSavingThrow(SavingThrowType kind) const;
    //Determines the savingthrow value
    
    long UpdateXP(int value);
    // Updates the xp (experience points) with the val
    //  (XP will always be >=0)
    // pre: val has a value
    // post: xp is updated xp = xp + val
    
    Humanoid& operator=(const Humanoid& h);
    //Overloaded assignment operator -- helps copy attributes in Humanoid
    //Pre: h should not have the same address as 'this'
    //Post: A Humanoid that is identical to 'm' is returned
    
    virtual void Write(ostream& out) const;
    // Writes the player data to an output stream
    // pre:  stream must be open, headers already printed
    //       if necessary.
    // post: all member data in player object has been inserted
    //       into output stream.
protected:
    Humanoid(string name, VocRules::VocType voc, const int abilityAdj[]);
    //Parameterized constructor for Humanoid
    //Pre: None
    //Post: Creates a Humanoid
    
    Humanoid(const Humanoid& h);
    //Copy constructor -- copies h into a newly created object
    //Pre: h exists
    //Post: h is copied into a newly created Humanoid
    
    void CopyHumanoid(const Humanoid& h);
    //Performs deep copy of a humanoid
    //Pre: h must exist
    //Post: Attributes of h will be copied over to a new player
    
    int RollHitDice() const;
    //Rolls hit dice
    //Pre: None
    //Post: Returns value of hit dice roll
private:
    static const int NUM_INIT_SKILLS = 3;
    //stores number of initial skills a humanoid has
    
    static const string INIT_SKILLS[VocRules::NUM_VOC][NUM_INIT_SKILLS];
    //stores initial skills for a humanoid
    
    static const int HIT_DIE_NUM_DIE;
    //holds the number of die for a humanoid's hit die
    
    /******* ATTRIBUTES **********/
    VocRules::VocType vocation;
    //stores Humanoid's vocation
    
    int level;
    //stores humanoid's current level
    
    long xp;
    //stores humanoid's XP
    
    PackClass* pack;
    //The humanoid's pack of weapons
    
    /******** METHODS ***********/
    Humanoid();
    //A default constructor for Monster
    //Not meant to be used
    
    void InitVoc(VocRules::VocType voc);
    //Initializes the player's vocation
    //Pre: playerVoc must be within the range of declared VocTypes
    //Post: Vocation is initialized
    
    void InitSkills();
    //Initializes a humanoids's default skills
    //Pre: None
    //Post: A humanoids's skills are initialized
    
    void InitPack();
    //Initializes a pack for a Humanoid
    //Pre: None
    //Post: Pack is initialized
    
    void HitDie(int hitDie[]) const;
    //Inserts appropriate values into hitDie to be indexed using RollDieInfoType
    //Pre: None
    //Post: hitDie has the values corresponding to a Humanoid's hit die roll info
    
    int AttackBonus() const;
    //Calculates a humanoid's attack bonus for RollAttack()
    //Pre: None
    //Post: The humanoid's attack bonus is returned
    
    int SavingThrowBonus(SavingThrowType kind) const;
    //Calculates a Humanoid's saving throw bonus for RollSavingThrow()
    //Pre: KindofThrow must be valid
    //Post: The Humanoid's saving throw bonus is returned
};

#endif

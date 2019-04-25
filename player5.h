//Name: John Sorhannus
//Class: CSCI330, Sec 1
//Semester: Fall 2018
//Program 5 Implementation (player5.h)
//This is the header file for PlayerClass in the game "Saving Syra."
//Special Note: The function "UpdateXP" contains a default parameter that was not speicified in the specification in order to cut down on repeated code.

#ifndef PLAYER5_h
#define PLAYER5_h

#include <string>
#include <ctype.h>
#include <vector>
#include <map>
#include "voc.h"
#include "wpn.h"
#include "dice.h"
#include "gamespace.h"

class PlayerClass {
public:
    virtual PlayerClass* Clone() const = 0;
    
    enum AbilityType {DEX, CON, INT, CHA, STR, WIS};
    // DEX - Dexterity
    // CON - Constitution
    // INT - Intelligence
    // CHA - Charisma
    // STR - Strength
    // WIS - Wisdom
    
    typedef map<string, AbilityType> MapType;
    
    static const int NUM_ABILITIES = 6;
    //stores number of abilities
    
    virtual ~PlayerClass();
    //Destructor
    
    /*********************************** GETTERS ***********************************************/
    string Name() const;
    //Returns the object's name
    //Pre: None
    //Post: The player's name will be returned.
    
    virtual string RaceStr() const = 0;
    //Pure virtual function
    
    int Row() const;
    //Returns the player's current row.
    //Pre: None
    //Post: The player's cell row position will be returned.
    
    int Col() const;
    //Returns the player's current column.
    //Pre: None
    //Post: The player's cell column position will be returned.
    
    int HP() const;
    //Returns the player's current HP (health points)
    //Pre: None
    //Post: The player's current HP will be returned.
    
    int MaxHP() const;
    //Returns the player's max HP (health points)
    //Pre: None
    //Post: The player's max HP will be returned
    
    int Ability(AbilityType ability) const;
    //Returns the player's ability score based on the ability type passed into the function.
    //Pre: Ability must be valid
    //Post: The player's ability score for the ability passed into the function will be returned.
    
    vector<int> Abilities() const;
    //Returns the player's ability scores as a vector
    //Pre: None
    //Post: returns the player's ability scores as a vector
    
    string WeaponNameAndNum() const;
    //Returns name and the serial number of the weapon
    //Pre: Player must have weapon
    //Post: Returns name and serial number of the weapon or an empty string
    
    string WeaponName() const;
    //Returns name of the weapon
    //Pre: Player must have weapon
    //Post: Returns name of the weapon or an empty string
    
    vector<string> Skills() const;
    //Returns a player's current skills in alphabetical order as a vector.
    //Pre: None
    //Post: A vector of the player's current skills will be returned.
    
    bool IsActive() const;
    //Returns a bool (true/false) speicifing if the player is active (is neither dead, dying or disabled)
    //Pre: None
    //Post: A bool speicifing if the player is active will be returned.
    
    bool IsDead() const;
    //Checks the player's HP (-10 or below) and Constitution (0) and returns a bool saying whether or not the player is dead.
    //Pre: None
    //Post: A bool speicifing if the player is dead will be returned.
    
    bool IsDying() const;
    //Checks the player's HP (-1 to -9)and returns a bool saying whether or not the player is dying.
    //Pre: None
    //Post: A bool speicifing if the player is dying will be returned.
    
    bool IsDisabled() const;
    //Checks the player's HP (0 or below) and returns a bool saying whether or not the player is disabled.
    //Pre: None
    //Post: A bool speicifing if the player is disabled will be returned.
    
    bool HasWeapon() const;
    //Returns a bool (true/false) speicifing if the player has a weapon
    //Pre: None
    //Post: A bool speicifing if the player has a weapon will be returned.
    
    int UpdateHP(int modification, bool levelUp = false);
    //This function updates the player's current HP by the number passed into the function. If 'modification' is positive, current HP increases. If 'modification' is negative, HP decreases.
    //Pre: Modification must be an integer and levelUp (parameter not required) must be a boolean.
    //Post: currentHP is updated and the updated currentHP is returned.
    
    bool SetCell(int newRow, int newCol);
    //This function updates the row and column coordinates and returns true if the coordinates given are valid.
    //Pre: newRow and newCol must both be between DEFAULT_ROW/NUMROWS and DEFAULT_COLUMN/NUMCOLS respectively or both newRow and newCol must equal DEFAULT_ROW and DEFAULT_COLUMN respectively
    //Post: If newRow and newCol are valid, row and column are updated and true is returned. If newRol and newCol are not valid, row and column remain the same and false is returned.

    int SkillCheck(string skill) const;
    //Calculates and returns a skill check for the player based on value of "skill"
    //Pre: skill must be valid
    //Post: The skill will be returned if the player is not dead, 0 if otherwise.
    
    bool AddSkill(string skill);
    //Adds skill to playerSkills
    //Pre: skill must be valid
    //Post: Returns true if skill was added or already exists. Returns false other
    
    void Amnesia();
    //Clears playerSkills
    //Pre: None
    //Post: playerSkills is empty
    
    virtual vector<string> InitialWeaponList() const = 0;
    //Returns a player's initial weapon as a vector.
    //Pre: None
    //Post: A vector of the player's initial weapon will be returned.

    Weapon::Weapon* LoseWeapon();
    //Assigns the weapon pointer to NULL
    //Pre: None
    //Post: Returns a pointer to the weapon lost
    
    virtual Weapon::Weapon* FindWeapon(Weapon::Weapon* wpn);
    //Replaces the current weapon with the weapon being pointed to by *wpn
    //Pre: Weapon cannot be NULL
    //Post: Returns pointer to the weapon that has been replaced
    
    int RollInitiative() const;
    //Calculates and returns the initiative roll for the player
    //Pre: None
    //Post: The initiative roll will be returned if the player is active, 0 if otherwise.
    
    virtual int RollAttack() const = 0;
    //Calculates and returns the attack roll for the player
    //Pre: None
    //Post: The attack roll will be returned if the player is active, 0 if otherwise.
    
    virtual int RollSavingThrow(SavingThrowType KindofThrow) const = 0;
    //Calculates and returns the roll saving throw for the player based on KindofThrow
    //Pre: KindofThrow must be valid
    //Post: The initiative roll will be returned if the player is active, 0 if otherwise.
    
    int RollDefense() const;
    //Calculates and returns the defense roll for the player
    //Pre: None
    //Post: The defense roll will be returned if the player is active, 0 if otherwise.
    
    int RollDamage() const;
    //Calculates and returns the damage roll for the player
    //Pre: None
    //Post: The damage roll will be returned if the player is active, 0 if otherwise.
    
    virtual void Write(ostream& out) const;
    //Prints out all of the player's attributes on the command line
    //Pre: p must be of type ostream
    //Post: All of the player's attributes are printed out on the command line
    
    bool operator==(const PlayerClass& p) const;
    //Overloads the '==' to see if 'name' of two PlayerClasses are equal. The comparison is noncase sensitive
    //Pre: p must be an initialized PlayerClass
    //Post: True is returned if 'name' in two PlayerClass objects are equal.
    
    bool operator!=(const PlayerClass& p) const;
    //Overloads the '!=' to see if 'name' of two PlayerClasses are not equal. The comparison is noncase sensitive
    //Pre: p must be an initialized PlayerClass
    //Post: True is returned if 'name' in two PlayerClass objects are not equal.
    
    bool operator<(const PlayerClass& p) const;
    //Overloads the '<' operator by comparing 'name' (non-case sensitive)
    //Pre: p must exist
    //Post: Returns true if this->name < p.name
    
    bool operator<=(const PlayerClass& p) const;
    //Overloads the '<=' operator by comparing 'name' (non-case sensitive)
    //Pre: p must exist
    //Post: Returns true if this->name <= p.name
    
    bool operator>(const PlayerClass& p) const;
    //Overloads the '>' operator by comparing 'name' (non-case sensitive)
    //Pre: p must exist
    //Post: Returns true if this->name > p.name
    
    bool operator>=(const PlayerClass& p) const;
    //Overloads the '>=' operator by comparing 'name' (non-case sensitive)
    //Pre: p must exist
    //Post: Returns true if this->name >= p.name

protected:
    enum RollDieInfoType {NUM_DIE, NUM_FACES, MODIFIER}; //MIGHT BELONG IN PUBLIC -- WE WILL SEE
    // NUM_DIE - Number of dice rolled
    // NUM_FACES - Number of faces each die should have
    // MODIFIER - Modifier for and HP roll
    
    static const int NUM_ROLL_DIE_INFO = 3;
    //Stores number of declared values for RollDieInfoType
    
    static const int NUM_MELEE_RANGE = 2;
    //Stores number of types of weapons (melee or range)

    static const int DICE[NUM_ROLLTYPE][NUM_ROLL_DIE_INFO];
    //Holds dice information. Row indexed using RollType and column indexed using RollDieInfoType
    
    /********* METHODS ************/
    
    PlayerClass(string initName, const int abilityAdj[], bool rollAbil);
    //A 3 parameter constructor which initializes all instance attributes in PlayerClass
    //Pre: None
    //Post: Creates a player in which the name, race type, and vocation type are all known.
    
    PlayerClass(const PlayerClass& p);
    //Copy constructor -- copies p into a newly created object
    //Pre: p exists
    //Post: p is copied into a newly creating player
    
    void CopyPlayer(const PlayerClass& p);
    //Copies attributes (except NAME and RACE) of a player in the copy constructor/assignment operator
    //Pre: p must exist
    //Post: Attributes from one player to will be copied to another player
    
    void InitHP(const int hitDie[]);
    //Initializes maxHP and currentHP by rolling dice
    //Pre: None
    //Post: maxHP and currentHP are initialized
    
    int Roll(const int dice[], RollType roll) const;
    //Rolls dice when dice info and roll type is known
    //Pre: None
    //Post: Results of roll is returned
    
    int Roll(RollType roll) const;
    //Rolls dice when dice info is known
    //Pre: None
    //Post: Results of roll is returned
    
    int AbilityMod(AbilityType ability) const;
    //Returns the calculated ability modifier for the ability passed into the method.
    //Pre: Ability must be valid
    //Post: The calculated ability modifier for the ability passed into the method will be returned.
    
    Weapon::Weapon* CurrentWeapon() const;
    //Returns pointer to player's current weapon
    //Pre: Player must have weapon
    //Post: A pointer to the player's current weapon is returned
    
    PlayerClass& operator=(const PlayerClass& p);
    //Overloaded assignment operator -- copies 'p' into an already existing player
    //Pre: p must exist
    //Post: p is copied into an already existing player
    
private:
    static MapType availableSkills;
    //Container for possible skills a player can possess and associated ability
    
    static const int DISABLED_HP;
    //Stores HP value needed to be considered disabled
    
    static const int DEAD_HP;
    //Stores HP value needed to be considered dead
    
    static const int DEAD_CON;
    //Stores consitution value needed to be considered dead
    
    static const int MAX_NAME_SIZE;
    //stores max size of a name
    
    static const int DEFAULT_ROW;
    //stores default row position of player
    
    static const int DEFAULT_COLUMN;
    //stores default column position of player
    
    static const int DEFENSE;
    //stores value for rolling defense
    
    const string NAME;
    //Name of the player
    
    int row;
    //Row position of the player
    
    int column;
    //Column position of the player
    
    int currentHP;
    //Current HP of the player
    
    int maxHP;
    //Max HP of the player
    
    vector<int> abilityScores;
    //Ability scores for the player. Indexed using AbilityType
    
    Weapon::Weapon* weapon;
    //Pointer to player's weapon
    
    vector<string> playerSkills;
    //Container for a player's skills
    
    /********************************* PRIVATE METHODS *********************************************/
    PlayerClass();
    //Default constructor
    //Not meant to be used
    
    string InitName(string playerName);
    //Validates the players name and trims the passed in name of whitespace
    //Pre: playerName must have a length greater than 1 and no more than 10
    //Post: Valid name is returned
    
    void InitAbilities(const int abilityAdj[], bool rollAbil);
    //Initializes player's ability scores
    //Pre: None
    //Post: Initializes player's ability scores
    
    static void LoadSkills(); //
    //Loads skills from SKILLS_FILE and stores them in availableSkills
    //Pre: None
    //Post: availableSkills will contain information from SKILLS_FILE
    
    static AbilityType StrToAbilityType(string abil);
    //Converts strings to AbilityType in order to be loaded into availableSkills
    //Pre: abil must be valud
    //Post: abil will be converted into corresponding AbilityType value
    
    bool IsPlayersSkill(string skill) const;
    //Checks to see if a skill already exists in playersSkills
    //Pre: skill must be valud
    //Post: Returns a bool speicifying whether skill exists in playersSkills
    
    static AbilityType GetAbilityForSkill(string skill);
    //Searches availableSkills for the ability associated with a certain skill
    //Pre: skill must be valid
    //Post: Returns AbilityType associated with a particular skill
    
    static bool IsValidSkill(string skill);
    //Checks if skill is in availableSkills when added to playersSkills
    //Pre: skill must be valid
    //Post: Returns a bool speicifying whether skill exists in availableSkills
};

/********************************* TOP LEVEL FUNCTIONS *********************************************/

ostream& operator<<(ostream& out, const PlayerClass* p);
//Overloads the '<<' operation to print out the player 'p''s attributes on the command line
//Pre: out must be of type ostream and p must be an initialized PlayerClass. p must not be NULL
//Post: Player 'p''s attributes will be printed out on the command line

#endif /* player3_h */

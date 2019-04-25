//Name: John Sorhannus
//Class: CSCI330, Sec 1
//Semester: Fall 2018
//Program 5 Implementation (ogre5.cpp)
//This is the implementation file for Ogre in the game "Saving Syra."

#include "ogre5.h"

using namespace GameSpace;

const string Ogre::RACE = "OGRE";
const int Ogre::ABILITY_ADJ[NUM_ABILITIES] = {8, 15, 6, 7, 21, 10};
const int Ogre::HIT_DIE[NUM_ROLL_DIE_INFO] = {4, 8, 8};
const int Ogre::SAVING_THROW[NUM_SAVINGTHROW] = {0, 6, 0, 1};
const int Ogre::BASE_ATTACK_BONUS[NUM_MELEE_RANGE] = {8, 1};
const string Ogre::INIT_WEAPON = "Spear";
const int Ogre::NUM_INIT_SKILLS;
const string Ogre::INIT_SKILLS[NUM_INIT_SKILLS] = {"INTIMIDATE", "LISTEN","SPOT"};

Ogre::Ogre() : Monster(RACE, ABILITY_ADJ, HIT_DIE) {
    //not meant to be called
    return;
}

Ogre::Ogre(string name) : Monster(name, ABILITY_ADJ, HIT_DIE) {
    InitSkills();
}

string Ogre::RaceStr() const {
    return RACE;
}

vector<string> Ogre::InitialWeaponList() const {
    vector<string> initWpn; //holds vector containing initial weapon
    
    initWpn.push_back(INIT_WEAPON);
    
    return initWpn;
}

int Ogre::RollAttack() const {
    return (Monster::RollAttack(BASE_ATTACK_BONUS));
}

int Ogre::RollSavingThrow(SavingThrowType kind) const {
    return (Monster::RollSavingThrow(kind, SAVING_THROW));
}

void Ogre::InitSkills() {
    int i; //index for INIT_SKILLS
    
    for (i = 0; i < NUM_INIT_SKILLS; i++) {
        AddSkill(INIT_SKILLS[i]);
    }
    
    return;
}

void Ogre::Write(ostream& stream) const {
    stream << RaceStr() << DEL;
    Monster::Write(stream);
    
    return;
}

Ogre* Ogre::Clone() const {
    return new Ogre(*this);
}


//Name: John Sorhannus
//Class: CSCI330, Sec 1
//Semester: Fall 2018
//Program 5 Implementation (troll5.cpp)
//This is the implementation file for Troll in the game "Saving Syra."

#include "troll5.h"

using namespace GameSpace;

const string Troll::RACE = "TROLL";
const int Troll::ABILITY_ADJ[NUM_ABILITIES] = {14, 23, 6, 6, 23, 9};
const int Troll::HIT_DIE[NUM_ROLL_DIE_INFO] = {6, 8, 36};
const int Troll::SAVING_THROW[NUM_SAVINGTHROW] = {0, 11, 4, 3};
const int Troll::BASE_ATTACK_BONUS[NUM_MELEE_RANGE] = {9, 1};
const string Troll::INIT_WEAPON = "Club";
const int Troll::NUM_INIT_SKILLS;
const string Troll::INIT_SKILLS[NUM_INIT_SKILLS] = {"LISTEN", "SPOT"};

Troll::Troll() : Monster(RACE, ABILITY_ADJ, HIT_DIE) {
    //not meant to be called
    return;
}

Troll::Troll(string name) : Monster(name, ABILITY_ADJ, HIT_DIE) {
    InitSkills();
    
    return;
}

string Troll::RaceStr() const {
    return RACE;
}

vector<string> Troll::InitialWeaponList() const {
    vector<string> initWpn; //holds vector containing initial weapon
    
    initWpn.push_back(INIT_WEAPON);
    
    return initWpn;
}

int Troll::RollAttack() const {
    return (Monster::RollAttack(BASE_ATTACK_BONUS));
}

int Troll::RollSavingThrow(SavingThrowType kind) const {
    return (Monster::RollSavingThrow(kind, SAVING_THROW));
}

void Troll::InitSkills() {
    int i; //index for INIT_SKILLS
    
    for (i = 0; i < NUM_INIT_SKILLS; i++) {
        AddSkill(INIT_SKILLS[i]);
    }
    
    return;
}

void Troll::Write(ostream& stream) const {
    stream << RaceStr() << DEL;
    Monster::Write(stream);
    
    return;
}

Troll* Troll::Clone() const {
    return new Troll(*this);
}


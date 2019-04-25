//Name: John Sorhannus
//Class: CSCI330, Sec 1
//Semester: Fall 2018
//Program 5 Implementation (human5.cpp)
//This is the implementation file for Human in the game "Saving Syra."

#include "human5.h"

const string Human::RACE = "HUMAN";
const int Human::ABILITY_ADJ[NUM_ABILITIES] = {0, 0, 0, 0, 0, 0};
const VocRules::VocType Human::DEFAULT_VOC = VocRules::FTR;
const string Human::INIT_WEAPON[VocRules::NUM_VOC] = {"", "Dagger", "Crossbow", "Sword", "Rapier", "Club"};

Human::Human() : Humanoid("", VocRules::NNE, 0) {
    //not meant to be used
}

Human::Human(string name, VocRules::VocType voc) : Humanoid(name, voc, ABILITY_ADJ) {
    return;
}

string Human::RaceStr() const {
    return RACE;
}

vector<string> Human::InitialWeaponList() const {
    vector<string> initWpn; //holds vector containing initial weapon
    
    initWpn.push_back(INIT_WEAPON[Voc()]);
    
    return initWpn;
}

void Human::Write(ostream& out) const {
    Humanoid::Write(out);
    
    return;
}

Human* Human::Clone() const {
    return new Human(*this);
}

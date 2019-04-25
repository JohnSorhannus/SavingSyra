//Name: John Sorhannus
//Class: CSCI330, Sec 1
//Semester: Fall 2018
//Program 5 Implementation (orc5.cpp)
//This is the implementation file for Orc in the game "Saving Syra."

#include "orc5.h"

using namespace GameSpace;

const string Orc::RACE = "ORC";
const int Orc::ABILITY_ADJ[NUM_ABILITIES] = {0, 0, -2, -2, 2, -1};
const VocRules::VocType Orc::DEFAULT_VOC = VocRules::BBN;
const string Orc::INIT_WEAPON[VocRules::NUM_VOC] = {"", "Dagger", "Crossbow", "Sword", "Short Bow", "Light Crossbow"};

Orc::Orc() : Humanoid("", VocRules::NNE, 0) {
    //not meant to be used
}

Orc::Orc(string name, VocRules::VocType voc) : Humanoid(name, voc, ABILITY_ADJ) {
    return;
}

string Orc::RaceStr() const {
    return RACE;
}

vector<string> Orc::InitialWeaponList() const {
    vector<string> initWpn; //holds vector containing initial weapon
    
    initWpn.push_back(INIT_WEAPON[Voc()]);
    
    return initWpn;
}

void Orc::Write(ostream& out) const {
    Humanoid::Write(out);
    
    return;
}

Orc* Orc::Clone() const {
    return new Orc(*this);
}

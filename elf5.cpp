//Name: John Sorhannus
//Class: CSCI330, Sec 1
//Semester: Fall 2018
//Program 5 Implementation (elf5.cpp)
//This is the implementation file for Elf in the game "Saving Syra."

#include "elf5.h"

using namespace GameSpace;

const string Elf::RACE = "ELF";
const int Elf::ABILITY_ADJ[NUM_ABILITIES] = {2, -2, 0, 0, 0, 0};
const VocRules::VocType Elf::DEFAULT_VOC = VocRules::WIZ;
const string Elf::INIT_WEAPON[VocRules::NUM_VOC] = {"", "Dagger", "Long Sword", "Sword", "Rapier", "Short Bow"};

Elf::Elf() : Humanoid("", VocRules::NNE, 0) {
    //not meant to be used
}

Elf::Elf(string name, VocRules::VocType voc) : Humanoid(name, voc, ABILITY_ADJ) {
    return;
}

string Elf::RaceStr() const {
    return RACE;
}

vector<string> Elf::InitialWeaponList() const {
    vector<string> initWpn; //holds vector containing initial weapon
    
    initWpn.push_back(INIT_WEAPON[Voc()]);
    
    return initWpn;
}

void Elf::Write(ostream& out) const {
    Humanoid::Write(out);
    
    return;
}

Elf* Elf::Clone() const {
    return new Elf(*this);
}

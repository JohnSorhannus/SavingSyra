//Name: John Sorhannus
//Class: CSCI330, Sec 1
//Semester: Fall 2018
//Program 5 Implementation (halfelf5.cpp)
//This is the implementation file for Half Elf in the game "Saving Syra."

#include "halfelf5.h"

using namespace GameSpace;

const string HalfElf::RACE = "HALF ELF";
const int HalfElf::ABILITY_ADJ[NUM_ABILITIES] = {0, 0, 1, 2, 0, 1};
const VocRules::VocType HalfElf::DEFAULT_VOC = VocRules::ROG;
const int HalfElf::MAX_WEAPON;
const int HalfElf::WEAPON_WEIGHT_LIMIT = 10;
const string HalfElf::INIT_WEAPON[VocRules::NUM_VOC][MAX_WEAPON] = {
    /*NNE*/ {"", ""},
    /*BBN*/ {"Dagger", "Short Bow"},
    /*CLR*/ {"Long Sword", ""},
    /*FTR*/ {"Sword", ""},
    /*ROG*/ {"Rapier", "Short Bow"},
    /*WIZ*/ {"Club", "Long Crossbow"}
};

HalfElf::HalfElf() : Humanoid("", VocRules::NNE, 0) {
    //not meant to be used
}

HalfElf::HalfElf(string name, VocRules::VocType voc) : Humanoid(name, voc, ABILITY_ADJ) {
    AddSkill("MOVE SILENTLY");
    return;
}

string HalfElf::RaceStr() const {
    return RACE;
}

vector<string> HalfElf::InitialWeaponList() const {
    vector<string> initWpn; //holds vector containing initial weapon
    int i; //iterator
    
    for (i = 0; i < MAX_WEAPON; i++) {
        if (INIT_WEAPON[Voc()][i] != "") {
            initWpn.push_back(INIT_WEAPON[Voc()][i]);
        }
    }
    
    return initWpn;
}

void HalfElf::Write(ostream& out) const {
    Humanoid::Write(out);
    
    return;
}

int HalfElf::RollSavingThrow(SavingThrowType kind) const {
    return (Humanoid::RollSavingThrow(kind) * 1.5);
}

Weapon::Weapon* HalfElf::FindWeapon(Weapon::Weapon* wpn) {
    Weapon::Weapon* retWeapon = NULL; //holds weapon to be returned
    
    if (wpn != NULL and wpn->Wt() <= WEAPON_WEIGHT_LIMIT) {
        retWeapon = Humanoid::FindWeapon(wpn);
    } else if (wpn != NULL) {
        retWeapon = wpn;
    }
    
    return retWeapon;
}

HalfElf* HalfElf::Clone() const {
    return new HalfElf(*this);
}

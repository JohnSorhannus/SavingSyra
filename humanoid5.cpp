//Name: John Sorhannus
//Class: CSCI330, Sec 1
//Semester: Fall 2018
//Program 5 Implementation (humanoid5.cpp)
//This is the implementation file for Humanoid in the game "Saving Syra."

#include "humanoid5.h"

using namespace GameSpace;

const int Humanoid::NUM_INIT_SKILLS;
const string Humanoid::INIT_SKILLS[VocRules::NUM_VOC][NUM_INIT_SKILLS] = {
    /* NNE */  {"" , "", ""},
    /* BBN */  {"CLIMB", "LISTEN", "SWIM"},
    /* CLR */  {"HEAL", "USE MAGIC DEVICES", ""},
    /* FTR */  {"INTIMIDATE", "SWIM", ""},
    /* ROG */  {"BLUFF", "CLIMB", "HIDE"},
    /* WIZ */  {"CONCENTRATION", "HIDE", "USE MAGIC DEVICES"}
};
const int Humanoid::HIT_DIE_NUM_DIE = 1;

Humanoid::Humanoid() : PlayerClass("", 0, true), pack(NULL) {
    //not meant to be used
}

Humanoid::Humanoid(string name, VocRules::VocType voc, const int abilityAdj[]) : PlayerClass(name, abilityAdj, true), pack(NULL) {
    InitVoc(voc);
    InitPack();
    InitSkills();
    
    int hitDie[3];
    HitDie(hitDie);
    InitHP(hitDie);
    
    level = 1;
    xp = 0;
    
    return;
}

Humanoid::Humanoid(const Humanoid& h) : PlayerClass(h), pack(NULL) {
    CopyHumanoid(h);
    
    return;
}

Humanoid::~Humanoid() {
    delete pack;
    pack = NULL;
    
    return;
}

void Humanoid::CopyHumanoid(const Humanoid& h) {
    delete pack;
    pack = NULL;
    
    vocation = h.vocation;
    level = h.level;
    xp = h.xp;
    
    if (h.pack != NULL) {
        pack = new PackClass(*h.pack);
    }
    
    return;
}

Humanoid& Humanoid::operator=(const Humanoid& h) {
    if (this != &h) {
        PlayerClass::operator=(h);
        CopyHumanoid(h);
    }
    
    return *this;
}

void Humanoid::InitVoc(VocRules::VocType voc) {
    if (voc <= VocRules::VocType(0) or voc > VocRules::VocType(VocRules::NUM_VOC - 1)) {
        throw INVALID_VOC;
    } else {
        vocation = voc;
    }
    
    return;
}

void Humanoid::InitSkills() {
    int i; //index for INIT_SKILLS
    
    for (i = 0; i < NUM_INIT_SKILLS; i++) {
        if (INIT_SKILLS[vocation][i] != "") {
            AddSkill(INIT_SKILLS[vocation][i]);
        }
    }
    
    return;
}

void Humanoid::InitPack() {
    pack = new PackClass(25 + (AbilityMod(STR) * 5));
    
    return;
}

void Humanoid::HitDie(int hitDie[]) const {
    hitDie[0] = HIT_DIE_NUM_DIE; //NUM_DICE
    
    VocRules* vrPtr = VocRules::GetVocRules();
    hitDie[1] = vrPtr->HitDie(vocation); //NUM_FACES
    
    hitDie[2] = AbilityMod(CON); //MODIFIER
    
    return;
}

int Humanoid::RollHitDice() const {
    int hitDie[3];
    HitDie(hitDie);
    
    return (Roll(hitDie, GameSpace::HP));
}

VocRules::VocType Humanoid::Voc() const {
    return vocation;
}

string Humanoid::VocStr() const {
    return VocRules::VocToStr(vocation);
}

int Humanoid::Level() const {
    return level;
}

long Humanoid::XP() const {
    return xp;
}

vector<string> Humanoid::Pack() const {
    return (pack->PackStr());
}

Weapon::Weapon* Humanoid::FindWeapon(Weapon::Weapon* wpn) {
    Weapon::Weapon* replacedWpn = wpn;
    
    if (wpn != NULL and IsActive()) {
        replacedWpn = PlayerClass::FindWeapon(wpn);
        //add replaced weapon to pack
        bool addedToPack = pack->AddWeapon(replacedWpn);
        if (addedToPack) {
            replacedWpn = NULL;
        }
    }

    return replacedWpn;
}

Weapon::Weapon* Humanoid::ChangeWeapon(string wName) {
    bool wpnInPack = pack->InPack(wName); //bool to check if weapon is in the pack
    Weapon::Weapon* retWeapon = NULL; //holds the weapon being returned
    bool wpnAdded = false; //bool to check if current weapon was added into the pack
    
    if (IsActive() and wpnInPack) {
        Weapon::Weapon* packWpn = pack->RemoveWeapon(wName); //weapon being removed from pack
        wpnAdded = pack->AddWeapon(CurrentWeapon());
        if (not wpnAdded) {
            retWeapon = CurrentWeapon();
        }
        PlayerClass::FindWeapon(packWpn);
    }
    
    return retWeapon;
}

int Humanoid::RollAttack() const {
    int attackRoll; //holds value of attack roll
    
    if (IsActive()) {
        attackRoll = Roll(GameSpace::ATT) + AttackBonus();
        if (attackRoll < 0) {
            attackRoll = 0;
        }
    } else {
        attackRoll = 0;
    }
    
    return attackRoll;
}

int Humanoid::AttackBonus() const {
    int attackBonus; //holds attack bonus value
    VocRules* vrPtr = VocRules::GetVocRules();
    
    attackBonus = vrPtr->BaseAttackBonus(vocation, level);
    
    if (HasWeapon() and CurrentWeapon()->IsRange()) {
        attackBonus += AbilityMod(DEX);
    } else {
        attackBonus += AbilityMod(STR);
    }
    
    return attackBonus;
}

int Humanoid::RollSavingThrow(SavingThrowType kind) const {
    int savingThrow; //holds value of saving throw roll
    
    if (kind < SavingThrowType(1) or kind > SavingThrowType(NUM_SAVINGTHROW - 1)) {
        throw INVALID_SAVINGTHROW;
    } else if (IsActive()) {
        savingThrow = Roll(GameSpace::SVTH) + SavingThrowBonus(kind);
    } else {
        savingThrow = 0;
    }
    
    return savingThrow;
}

int Humanoid::SavingThrowBonus(SavingThrowType kind) const {
    int savingThrowBonus; //holds value of saving throw bonus
    VocRules* vrPtr = VocRules::GetVocRules(); //pointer to VocRules
    
    savingThrowBonus = vrPtr->BaseSaveBonus(vocation, level, kind);
    
    switch (kind) {
        case FORT:
            savingThrowBonus += AbilityMod(CON);
            break;
        case REFLEX:
            savingThrowBonus += AbilityMod(DEX);
            break;
        case WILL:
            savingThrowBonus += AbilityMod(WIS);
            break;
    }
    
    return savingThrowBonus;
}

long Humanoid::UpdateXP(int value) {
    VocRules *vrPtr = VocRules::GetVocRules(); //A pointer to an instance of VocRules
    int hpRoll; //Expresses what the player rolled for HP
    
    if (value > 0 and not IsDisabled()) {
        xp += value;
        while (vrPtr->XPforPromotion(level + 1) <= xp and level < VocRules::LEVEL_MAX) {
            level++;
            hpRoll = RollHitDice();
            if (hpRoll > 0) {
                UpdateHP(hpRoll, true);
            } else {
                UpdateHP(1, true);
            }
        }
    }
    
    return xp;
}

void Humanoid::Write(ostream& out) const {
    out << RaceStr() << DEL << VocStr() << DEL << Level() << DEL << XP() << DEL;
    PlayerClass::Write(out);
    
    out << "\t";
    vector<string> packStr = Pack();
    vector<string>::const_iterator iter;
    
    out << "(";
    
    for (iter = packStr.begin(); iter != packStr.end() - 1; iter++) {
        out << *iter << ",";
    }
    
    out << *iter << ")" << DEL << endl;
    
    return;
}

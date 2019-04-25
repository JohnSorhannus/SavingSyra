//Name: John Sorhannus
//Class: CSCI330, Sec 1
//Semester: Fall 2018
//Program 5 Implementation (monster5.cpp)
//This is the implementation file for Monster in the game "Saving Syra."

#include "monster5.h"

using namespace GameSpace;

Monster::Monster() : PlayerClass("", 0, false), HIT_DIE(NULL) {
    //this function is not meant to be used
}

Monster::Monster(string name, const int abilityAdj[], const int hitDie[]) : PlayerClass(name, abilityAdj, false), HIT_DIE(hitDie) {
    InitHP(HIT_DIE);
    
    return;
}

Monster& Monster::operator=(const Monster& m) {
    if (this != &m) {
        PlayerClass::operator=(m);
        *const_cast<const int**>(&HIT_DIE) = m.HIT_DIE;
    }
    
    return *this;
}

int Monster::RollHitDie() const {
    return (PlayerClass::Roll(HIT_DIE, GameSpace::HP));
}

int Monster::RollAttack(const int attackBonus[]) const {
    int attackRoll; //holds value of attack roll
    
    if (IsActive()) {
        attackRoll = PlayerClass::Roll(GameSpace::ATT) + AttackBonus(attackBonus);
        if (attackRoll < 0) {
            attackRoll = 0;
        }
    } else {
        attackRoll = 0;
    }
    
    return attackRoll;
}

int Monster::AttackBonus(const int baseAttackBonus[]) const {
    int attackBonus; //hold attack bonus value
    
    if (HasWeapon() and CurrentWeapon()->IsRange()) {
        attackBonus = baseAttackBonus[RANGE] + AbilityMod(DEX);
    } else {
        attackBonus = baseAttackBonus[MELEE] + AbilityMod(STR);
    }
    
    return attackBonus;
}

int Monster::RollSavingThrow(SavingThrowType kind, const int savingThrows[]) const {
    int savingThrow; //holds value of saving throw roll
    
    if (kind < SavingThrowType(1) or kind > SavingThrowType(NUM_SAVINGTHROW - 1)) {
        throw INVALID_SAVINGTHROW;
    } else if (IsActive()) {
        savingThrow = Dice::Roll(Name(), GameSpace::SVTH, DICE[SVTH][NUM_DIE], DICE[SVTH][NUM_FACES]) + SavingThrowBonus(kind, savingThrows);
    } else {
        savingThrow = 0;
    }
    
    return savingThrow;

}

int Monster::SavingThrowBonus(SavingThrowType kind, const int savingThrows[]) const {
    int savingThrowBonus; //holds value of saving throw bonus

    savingThrowBonus = savingThrows[kind];
    
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

void Monster::Write(ostream& stream) const {
    PlayerClass::Write(stream);
    
    return;
}


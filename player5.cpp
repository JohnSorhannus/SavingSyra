//Name: John Sorhannus
//Class: CSCI330, Sec 1
//Semester: Fall 2018
//Program 5 Implementation (player5.cpp)
//This is the implementation file for PlayerClass in the game "Saving Syra."
//Special Note: The function "UpdateXP" contains a default parameter that was not speicified in the specification in order to cut down on repeated code.

#include <string>
#include "player5.h"

PlayerClass::MapType PlayerClass::availableSkills;
const int PlayerClass::NUM_ABILITIES;
const int PlayerClass::DISABLED_HP = 0;
const int PlayerClass::DEAD_HP = -10;
const int PlayerClass::DEAD_CON = 0;
const int PlayerClass::NUM_MELEE_RANGE;
const int PlayerClass::MAX_NAME_SIZE = 10;
const int PlayerClass::NUM_ROLL_DIE_INFO;
const int PlayerClass::DEFAULT_ROW = -1;
const int PlayerClass::DEFAULT_COLUMN = -1;
const int PlayerClass::DEFENSE = 10;
const int PlayerClass::DICE[NUM_ROLLTYPE][NUM_ROLL_DIE_INFO] = {
    /*DEX*/  {3, 6, 0},
    /*CON*/  {3, 6, 0},
    /*INT*/  {3, 6, 0},
    /*CHA*/  {3, 6, 0},
    /*STR*/  {3, 6, 0},
    /*WIS*/  {3, 6, 0},
    /*GP*/   {0, 0, 0},
    /*HP*/   {0, 0, 0},
    /*INIT*/ {1, 20, 0},
    /*ATT*/  {1, 20, 0},
    /*SVTH*/ {1, 20, 0},
    /*SKCK*/ {1, 20, 0},
    /*DMG*/  {0, 0, 0}
};

using namespace GameSpace;

PlayerClass::PlayerClass() : NAME(InitName("")), weapon(NULL) {
    //Function not meant to be used
    return;
}

PlayerClass::PlayerClass(string playerName, const int abilityAdj[], bool rollAbil) : NAME(InitName(playerName)), weapon(NULL) {
    row = DEFAULT_ROW;
    column = DEFAULT_COLUMN;
    
    currentHP = 1;
    maxHP = 1;
    
    if (availableSkills.empty()) {
        LoadSkills();
    }
    
    InitAbilities(abilityAdj, rollAbil);
    
    //playerSkills will be initialized
    playerSkills;
    
    return;
}

PlayerClass::PlayerClass(const PlayerClass& p) : NAME(p.NAME), weapon(NULL) {
    CopyPlayer(p);
    
    return;
}

void PlayerClass::CopyPlayer(const PlayerClass& p) {
    delete weapon;
    weapon = NULL;
    
    row = p.row;
    column = p.column;
    currentHP = p.currentHP;
    maxHP = p.maxHP;
    abilityScores = p.abilityScores;
    
    //make sure p.weapon is not null
    if (p.weapon != NULL) {
        weapon = new Weapon(*p.weapon);
    }
    
    playerSkills = p.playerSkills;
    
    return;
}

PlayerClass::~PlayerClass() {
    delete weapon;
    weapon = NULL;
    
    return;
}

void PlayerClass::InitHP(const int hitDie[]) {
    maxHP = Roll(hitDie, GameSpace::HP);
    if (maxHP < 1) {
        maxHP = 1;
    }
    currentHP = maxHP;
    
    return;
}

int PlayerClass::Roll(const int dice[], RollType roll) const {
    return (Dice::Roll(Name(), roll, dice[NUM_DIE], dice[NUM_FACES]) + dice[MODIFIER]);
}

int PlayerClass::Roll(RollType roll) const {
    return (Dice::Roll(Name(), roll, DICE[roll][NUM_DIE], DICE[roll][NUM_FACES]) + DICE[roll][MODIFIER]);
}

void PlayerClass::InitAbilities(const int abilityAdj[], bool rollAbil) {
    AbilityType abil; //Variable used to iterate through the player's ability scores in a for loop.
    
    for (abil = DEX; abil <= AbilityType(NUM_ABILITIES - 1); abil = static_cast<AbilityType>(abil + 1)) { //abil++
        if (rollAbil) {
            abilityScores.push_back(Dice::Roll(NAME, RollType(abil), DICE[RollType(abil)][NUM_DIE], DICE[RollType(abil)][NUM_FACES]) + abilityAdj[abil]);
        } else {
            abilityScores.push_back(abilityAdj[abil]);
        }
    }
    
    return;
}

string PlayerClass::InitName(string playerName) {
    playerName = playerName.substr(0, MAX_NAME_SIZE);
    playerName = TrimStr(playerName);
    
    if (playerName.length() <= 1) {
        throw INVALID_NAME;
    }
    
    return playerName;
}

string PlayerClass::Name() const {
    return NAME;
}

int PlayerClass::Row() const {
    return row;
}

int PlayerClass::Col() const {
    return column;
}

int PlayerClass::HP() const {
    return currentHP;
}

int PlayerClass::MaxHP() const {
    return maxHP;
}

int PlayerClass::Ability(AbilityType ability) const {
    int abil; //holds ability rating
    
    if (ability >= AbilityType(0) and ability <= AbilityType(NUM_ABILITIES - 1)) {
        abil = abilityScores[ability];
    } else {
        throw INVALID_ABILITY;
    }
    
    return abil;
}

vector<int> PlayerClass::Abilities() const {
    return abilityScores;
}

int PlayerClass::AbilityMod(AbilityType ability) const {
    int mod; //holds abililty modifier
    
    if (ability >= AbilityType(0) and ability <= AbilityType(NUM_ABILITIES - 1)) {
        mod = (abilityScores[ability]/2) - 5;
    } else {
        throw INVALID_ABILITY;
    }
    
    return mod;
}

string PlayerClass::WeaponName() const {
    string wpnName; //holds name of weapon
    
    if (HasWeapon()) {
        wpnName = weapon->Name();
    } else {
        wpnName = "";
    }
    
    return wpnName;
}

string PlayerClass::WeaponNameAndNum() const {
    string wpnName; //holds name and serial number of weapon
    
    if (HasWeapon()) {
        wpnName = weapon->NameAndNum();
    } else {
        wpnName = "";
    }
    
    return wpnName;
}

vector<string> PlayerClass::Skills() const {
    vector<string> skills = playerSkills; //holds value of playerSkills vector
    Sort(skills);
    
    return skills;
}

bool PlayerClass::IsActive() const {
    return (not(IsDead() or IsDying() or IsDisabled()));
}

bool PlayerClass::IsDead() const {
    return (currentHP <= DEAD_HP or abilityScores[CON] == DEAD_CON);
}

bool PlayerClass::IsDying() const {
    return (currentHP > DEAD_HP and currentHP < DISABLED_HP);
}

bool PlayerClass::IsDisabled() const {
    return (currentHP <= DISABLED_HP);
}

bool PlayerClass::HasWeapon() const {
    return (weapon != NULL);
}

int PlayerClass::UpdateHP(int modification, bool levelUp) {
    if (not IsDead()) {
        currentHP += modification;
        if (currentHP > maxHP and levelUp) {
            maxHP = currentHP; //upgrade maxHP
        } else if (currentHP > maxHP) {
            currentHP = maxHP; //prevent currentHP from surpassing maxHP
        }
    }
    
    return currentHP;
}

bool PlayerClass::SetCell(int newRow, int newCol) {
    bool validCoord; //A bool which expresses if the coordinates passed into the method are valid.
    
    //If newRow and newCol are both between DEFAULT_ROW and DEFAULT_COLUMN or if both newRow and newCol equal DEFAULF_ROW and DEFAULT_COLUMN
    if (((newRow > DEFAULT_ROW and newCol > DEFAULT_COLUMN) and (newRow < NUMROWS and newCol < NUMCOLS)) or (newRow == DEFAULT_ROW and newCol == DEFAULT_COLUMN)) {
        row = newRow;
        column = newCol;
        validCoord = true;
    } else {
        validCoord = false;
    }
    
    return validCoord;
}

int PlayerClass::SkillCheck(string skill) const {
    int skillCheck; //holds value of skill check roll
    
    if (not IsDead() and IsPlayersSkill(skill)) {
        skillCheck = Dice::Roll(NAME, GameSpace::SKCK, DICE[SKCK][NUM_DIE], DICE[SKCK][NUM_FACES]) + AbilityMod(GetAbilityForSkill(skill));
    } else if (not IsValidSkill(skill)) {
        throw INVALID_SKILL;
    } else {
        skillCheck = 0;
    }
    
    return skillCheck;
}

bool PlayerClass::AddSkill(string skill) {
    bool added; //bool that specifies whether a skills has been added/already exists or has not been added
    
    if (IsActive() and IsValidSkill(skill) and not IsPlayersSkill(skill)) {
        playerSkills.push_back(skill);
        added = true;
    } else if (IsPlayersSkill(skill)) {
        added = true;
    } else if (not IsValidSkill(skill)) {
        throw INVALID_SKILL;
    } else if (not IsActive()) {
        added = false;
    }
    
    return added;
}

void PlayerClass::Amnesia() {
    if (IsActive()) {
        playerSkills.clear();
    }
    
    return;
}

Weapon::Weapon* PlayerClass::LoseWeapon() {
    Weapon::Weapon* retWeapon = weapon; //pointer to weapon that is lost
    weapon = NULL;
    
    return retWeapon;
}

Weapon::Weapon* PlayerClass::FindWeapon(Weapon::Weapon* wpn) {
    Weapon::Weapon* retWeapon = wpn; //points to weapon being passed into function
    
    if (IsActive() and wpn != NULL) {
        retWeapon = weapon;
        weapon = wpn;
    }
    
    return retWeapon;
}

Weapon::Weapon* PlayerClass::CurrentWeapon() const {
    Weapon::Weapon* retWeapon = NULL;
    
    if (weapon != NULL) {
        retWeapon = weapon;
    }
    
    return retWeapon;
}

int PlayerClass::RollInitiative() const {
    int initRoll; //holds value of initiative roll
    
    if (IsActive()) {
        initRoll = Dice::Roll(NAME, GameSpace::INIT, DICE[INIT][NUM_DIE], DICE[INIT][NUM_FACES]) + AbilityMod(DEX);
    } else {
        initRoll = 0;
    }
    
    return initRoll;
}

int PlayerClass::RollDefense() const {
    int defenseRoll; //holds value of defense roll
    
    if (IsActive()) {
        defenseRoll = DEFENSE + AbilityMod(DEX);
    } else {
        defenseRoll = 0;
    }
    
    return defenseRoll;
}

int PlayerClass::RollDamage() const {
    int damageRoll; //holds value of damage roll
    
    if (HasWeapon() and IsActive()) {
        damageRoll = weapon->RollWeaponDamage(NAME);
        if (weapon->IsMelee()) {
            damageRoll += AbilityMod(STR);
        }
    } else if (IsActive()) {
        damageRoll = AbilityMod(STR);
    } else {
        damageRoll = 0;
    }
    
    if (damageRoll < 0) {
        damageRoll = 0;
    }
    
    return damageRoll;
}

void PlayerClass::Write(ostream& out) const {
    AbilityType abil; //Variable used to iterate through the player's ability scores in a for loop.
    vector<string> orderedSkills; //holds skill ordered by alphabetical order
    vector<string>::const_iterator iter; //iterator for iterating through orderedSkills
    
    out << Name() << DEL << '(' << Row() << ',' << Col() << ')' << DEL << HP() << DEL << MaxHP() << DEL << '[';
    
    //Print abilities
    for (abil = DEX; abil <= AbilityType(NUM_ABILITIES - 2); abil = static_cast<AbilityType>(abil + 1)) { //abil++
        out << Ability(abil) << DEL;
    }
    
    out << Ability(AbilityType(NUM_ABILITIES - 1)) << ']' << DEL;
    
    //Print ordered skills map
    out << WeaponNameAndNum() << DEL << '(';
    orderedSkills = Skills();
    
    if (not orderedSkills.empty()) {
        for (iter = orderedSkills.begin(); iter != orderedSkills.end() - 1; iter++) {
            out << *iter << ',';
        }
        out << *(iter++);
    }
    
    out << ')' << DEL << endl;
    
    return;
}

bool PlayerClass::operator==(const PlayerClass& p) const {
    return (Ucase(Name()) == Ucase(p.Name()));
}

bool PlayerClass::operator!=(const PlayerClass& p) const {
    return (not (operator==(p)));
}

bool PlayerClass::operator<(const PlayerClass& p) const {
    return (Ucase(Name()) < Ucase(p.Name()));
}

bool PlayerClass::operator<=(const PlayerClass& p) const {
    return (Ucase(Name()) <= Ucase(p.Name()));
}

bool PlayerClass::operator>(const PlayerClass& p) const {
    return (Ucase(Name()) > Ucase(p.Name()));
}

bool PlayerClass::operator>=(const PlayerClass& p) const {
    return (Ucase(Name()) >= Ucase(p.Name()));
}

PlayerClass& PlayerClass::operator=(const PlayerClass& p) {
    if (this != &p) {
        *const_cast<string*>(&NAME) = p.NAME;
        CopyPlayer(p);
    }
    
    return *this;
}

bool PlayerClass::IsPlayersSkill(string skill) const {
    bool found = false; //bool that speicifies whether "skill" has been found in playerSkills
    vector<string>::const_iterator iter = playerSkills.begin(); //iterator for iterating through playerSkills
    
    while (not found and iter != playerSkills.end()) {
        found = (Ucase(*iter) == Ucase(skill));
        iter++;
    }
    
    return found;
}

PlayerClass::AbilityType PlayerClass::GetAbilityForSkill(string skill) {
    AbilityType abil; //holds ability associated with a skill
    
    if (IsValidSkill(skill)) {
        MapType::iterator iter = availableSkills.find(Ucase(skill));
        abil = iter->second;
    }
    
    return abil;
}

bool PlayerClass::IsValidSkill(string skill) {
    return (availableSkills.find(Ucase(skill)) != availableSkills.end());
}

void PlayerClass::LoadSkills() {
    ifstream file; //stream for reading in file
    string skill, abilStr; //skill -- holds skill name    abilStr -- holds associated skill
    AbilityType abil; //holds AbilityType equivalent of abilStr
    
    file.open(SKILLS_FILE.c_str());
    
    getline(file, skill, '#');
    getline(file, abilStr);
    
    while (file) {
        abil = StrToAbilityType(abilStr);
        
        availableSkills.insert(make_pair(Ucase(skill), abil));
        getline(file, skill, '#');
        getline(file, abilStr);
    }
    
    return;
}

PlayerClass::AbilityType PlayerClass::StrToAbilityType(string abilStr) {
    AbilityType ability; //hold AbilityType equivalent of abilStr
    abilStr = Ucase(abilStr);
    
    if (abilStr == "DEX") {
        ability = DEX;
    } else if (abilStr == "CON") {
        ability = CON;
    } else if (abilStr == "INT") {
        ability = INT;
    } else if (abilStr == "CHA") {
        ability = CHA;
    } else if (abilStr == "STR") {
        ability = STR;
    } else if (abilStr == "WIS") {
        ability = WIS;
    }
    
    return ability;
}

ostream& operator<<(ostream& out, const PlayerClass* p) {
    if (p != NULL) {
        p->Write(out);
    }
    
    return out;
}

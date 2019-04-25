//Name: John Sorhannus
//Class: CSCI330, Sec 1
//Semester: Fall 2018
//Program 4 Implementation (pack.cpp)
//This is the implementation file for Pack in the game "Saving Syra."

#include "pack.h"
using namespace std;
using namespace GameSpace;

PackClass::PackClass(int wt) : MAX_WT(wt) {
	if (MAX_WT < 0) {
		throw INVALID_MISC;
	}

	return;
}

PackClass::PackClass(const PackClass& p) : MAX_WT(p.MAX_WT) {
	CopyPack(p);

	return;
}

PackClass::~PackClass() {
	EmptyPack();

	return;
}

PackClass& PackClass::operator=(const PackClass& p) {
	if (this != &p) {
		CopyPack(p);
	}

	return *this;
}

bool PackClass::AddWeapon(Weapon* w) {
	bool added = false; //holds bool which says if weapon added in pack

	if (w != NULL and (Wt() + w->Wt()) <= MaxWt()) {
		pack.push_back(w);
		added = true;
	}

	return added;
}

Weapon* PackClass::RemoveWeapon(string wName) {
	vector<Weapon*>::iterator wpnIt; //iterator pointing to weapon of name wName
	Weapon* lostWeapon = NULL; //holds weapon that is removed

	if (InPack(wName)) {
		wpnIt = FindWeapon(wName);
		lostWeapon = *wpnIt;
		pack.erase(wpnIt);
	}

	return lostWeapon;
}

void PackClass::EmptyPack() {
	vector<Weapon*>::iterator iter; //iterating through pack
	
	for (iter = pack.begin(); iter != pack.end(); iter++) {
		delete *iter;
		*iter = NULL;
	}

	pack.clear();
	
	return;
}

bool PackClass::InPack(string wName) const {
	bool found = false; //bool holding if weapon is in pack
	vector<Weapon*>::const_iterator iter = pack.begin(); //iterating through pack
	
	while (not found and iter != pack.end()) {
		found = (Ucase(wName) == Ucase((*iter)->Name()));
		iter++;
	}

	return found;
}

int PackClass::Size() const {
	return pack.size();
}

int PackClass::Wt() const {
	int weight = 0; //hold current weight
	vector<Weapon*>::const_iterator iter; //iterating through pack

	for (iter = pack.begin(); iter != pack.end(); iter++) {
		weight += (*iter)->Wt();
	}

	return weight;
}

int PackClass::MaxWt() const {
	return MAX_WT;
}

bool PackClass::IsEmpty() const {
	return pack.empty();
}

bool PackClass::IsFull() const {
	return (Wt() == MaxWt());
}

void PackClass::Write(ostream& out) const {
	vector<Weapon*>::const_iterator iter; //iterating through pack

	if (not IsEmpty()) {
		for (iter = pack.begin(); iter != pack.end() - 1; iter++) {
			out << (*iter)->NameAndNum() << DEL;
		}

		out << (*iter)->NameAndNum() << endl;
	}

	return;
}	

void PackClass::CopyPack(const PackClass& p) {
	EmptyPack();
	*const_cast<int*>(&MAX_WT) = p.MAX_WT;
	
    vector<Weapon*>::const_iterator iter; //iterating through pack
	for (iter = p.pack.begin(); iter != p.pack.end(); iter++) {
		if (*iter != NULL) {
			pack.push_back(new Weapon(**iter)); //copy con makes exact copy -- copies serial number
		}
	}

	return;
}

vector<Weapon*>::iterator PackClass::FindWeapon(string wName) {
	bool found = false; //bool saying if weapon was found
	vector<Weapon*>::iterator iter = pack.begin(); //iterating through pack
	vector<Weapon*>::iterator lastW = pack.end(); //holds last iterated weapon
	
	if (InPack(wName)) {
		while (not found) {
			found = (Ucase(wName) == Ucase((*iter)->Name()));
			lastW = iter;
			iter++;
		}
	}

	return lastW;
}

vector<string> PackClass::PackStr() const {
    vector<string> packStr; //holds pack of strings for weapons
    vector<Weapon*>::const_iterator iter; //iterating through pack
    
    if (not IsEmpty()) {
        for (iter = pack.begin(); iter != pack.end(); iter++) {
            packStr.push_back((*iter)->NameAndNum());
        }
    } else {
        packStr.push_back("");
    }
    
    Sort(packStr);
    
    return packStr;
}

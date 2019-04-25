//Name: John Sorhannus
//Class: CSCI330, Sec 1
//Semester: Fall 2018
//Program 4 Implementation (pack.h)
//This is the header file for Pack in the game "Saving Syra."

#ifndef PACK_H
#define PACK_H
#include <iostream>
#include <string>
#include <vector>
#include "wpn.h"
#include "gamespace.h"

class PackClass {
	public:
		PackClass(int wt);
        //Initializes a pack where its max weight = wt
        //Pre: wt must be greater than 0
        //Post: Pack with max weight of wt is created
    
		PackClass(const PackClass& p);
        //Copy constructor -- copies p into a new instance
        //Pre: p must exist
        //Post: p is copied over into another instance
    
		~PackClass();
        //Destructor
		
		PackClass& operator=(const PackClass& p);
        //Assignment operator -- copies p into already existing pack
        //Pre: p must not have same address as instance
        //Post: p is copied into an already existing pack
		
		bool AddWeapon(Weapon* w);
        //Adds weapon into pack
        //Pre: w must not be NULL
        //Post: true if weapon added, false if not
    
		Weapon* RemoveWeapon(string wName);
        //Removes weapon from pack
        //Pre: None
        //Post: Pointer of removed weapon returned, NULL if weapon does not exist in pack
    
		void EmptyPack();
        //Empties pack of all its contents
        //Pre: None
        //Post: Pack is emptied

		bool InPack(string wName) const;
        //Checks to see if weapon that is of name wName exists in pack
        //Pre: None
        //Post: returns bool telling whether or not the weapon is in the pack
    
		int Size() const;
        //Returns number of weapons in the pack
        //Pre: None
        //Post: Number of weapons in pack returned
    
		int Wt() const;
        //Returns current weight of pack
        //Pre: None
        //Post: Current weight of pack returned
    
		int MaxWt() const;
        //Returns maximum weight of pack
        //Pre: None
        //Post: returns max weight of pack
    
		bool IsEmpty() const;
        //Returns bool telling if pack has no contents
        //Pre: None
        //Post: Returns bool telling if pack has no contents
    
		bool IsFull() const;
        //Returns bool telling if current weight is equal to max weight
        //Pre: None
        //Post: Returns bool telling if current weight is equal to max weight

        vector<string> PackStr() const;
        //Returns pack as a sorted vector of weapon names
        //Pre: None
        //Post: The pack as a sorted vector of weapon names is returned
    
		void Write(ostream& out) const;
        //Writes contents of pack to command line
        //Pre: None
        //Post: Writes contents of pack to command line
		
	private:
		void CopyPack(const PackClass& p);
        //Performs deep copy of pack
        //Pre: None
        //Post: Deep copy performed of a pack
    
		vector<Weapon*>::iterator FindWeapon(string wName);
        //Returns iterator pointing to weapon of name wName in pack
        //Pre: None
        //Post: Iterator pointing to weapon of name wName is returned
		
		vector<Weapon*> pack;
        //Holds weapons
    
		const int MAX_WT;
        //holds max weight of pack
};

#endif

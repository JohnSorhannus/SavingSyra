//Name: John Sorhannus
//Class: CSCI330, Sec 1
//Semester: Fall 2018
//Program 4 Implementation (hc.cpp)
//This is the implementation file for Player (hanlde class) in the game "Saving Syra."

#include "hc.h"
#include "typeinfo"

//********************************************* Constructors    
Player::Player( ) : p(NULL)
{


}
		
Player::Player(const Player& player) : p(NULL)
{
	CopyIntoMe(player);
}

Player::Player(PlayerClass * ptr) : p(ptr)
{
    return;
}
	
Player::~Player( ) 
{
      delete p;
      p = NULL;
}

void Player::CopyIntoMe(const Player &player)
{
	//deep copy of obj
	delete p;
	p = NULL;

	if (player.p != NULL) {
        p = (player.p)->Clone();
	}
    
    return;
}

//********************************************* Assignment    
Player& Player::operator=(const Player & player)
{
	if (this != &player) {
		CopyIntoMe(player);
	}

	return *this;

}

//********************************************* Getters    
string Player::Name( ) const
{
	if (p != NULL) {
		return p->Name();
	}
        return "";

}
  
string Player::RaceStr( ) const
{
	if (p) {
		return p->RaceStr();
	}
	return "";

}


string Player::VocStr( ) const
{
	Humanoid* h = dynamic_cast<Humanoid *>(p);

	if (h) {
		return h->VocStr();
	}
	return "";
}

int Player::Voc( ) const
{
    Humanoid* h = dynamic_cast<Humanoid*>(p);
    
    if (h) {
        return h->Voc();
    }
    
    return 0;
}


int Player::HP( ) const
{
	if (p)
	  return p->HP();
        return 0;
}

int Player::MaxHP() const {
    if (p) {
        return p->MaxHP();
    }
    return 0;
}

     
long Player::XP( ) const
{
	Humanoid * h =
	   dynamic_cast<Humanoid * > (p);
	   
	if (h)
	  return h->XP( );
        return 0;

}

int Player::Level( ) const
{
	Humanoid * h =
	   dynamic_cast<Humanoid * > (p);
	   
	if (h)
	  return h->Level( );
	return 0;

}

int Player::Row( ) const
{
	if (p)
	  return p->Row( );
	return 0;
}

int Player::Col( ) const
{
	if (p)
	  return p->Col( );
	return 0;
}
    
int Player::Ability(PlayerClass::AbilityType ability ) const
{
	if (p)
	  return p->Ability(PlayerClass::AbilityType(ability));
	return 0;
}


vector<int> Player::Abilities( ) const
{
        vector<int> a;
	if (p)
	  return p->Abilities( );
	return a;
}


string Player::WeaponName( ) const
{
	if (p)
	  return p->WeaponName( );
        return "";
}

string Player::WeaponNameAndNum( ) const
{
	if (p)
	  return p->WeaponNameAndNum( );
        return "";
}

bool Player::HasWeapon( ) const
{
        if (p)
          return p->HasWeapon( );
        return false;
}

vector<string> Player::Pack( ) const
{
       Humanoid *h = dynamic_cast<Humanoid *>(p);

        vector<string> e;
	if (h)
	  return h->Pack( );
        return e;
}

vector<string> Player::InitialWeaponList( ) const
{
    vector<string> s;
    
    if (p)
        return p->InitialWeaponList();
    return s; 
}
     
vector<string> Player::Skills( ) const
{
        vector<string> s;
	if (p)
	  return p->Skills( );
        return s;
}


bool Player::IsActive( ) const
{
        if (p)
          return p->IsActive( );
        return false;
}


bool Player::IsDisabled( ) const
{
        if (p)
          return p->IsDisabled( );
        return false;
}


bool Player::IsDying( ) const
{
        if (p)
          return p->IsDying( );
        return false;
}


bool Player::IsDead( ) const
{
        if (p)
          return p->IsDead( );
        return false;
}


bool Player::IsMonster( ) const
{
    Monster* m = dynamic_cast<Monster*>(p);
    
    return (m);
}

bool Player::IsHumanoid( ) const
{
    Humanoid* h = dynamic_cast<Humanoid*>(p);
    
    return (h);
}      


//********************************************* Updates    


int Player::UpdateHP(int val)
{
	if (p)
	  return p->UpdateHP(val);
        return 0;
}


long Player::UpdateXP(long val)
{
	Humanoid * h =
	   dynamic_cast<Humanoid * > (p);
	   
	if (h)
	  return h->UpdateXP(val);
        return 0;

}

bool Player::SetCell(int row, int col)
{
        if (p)
          return p->SetCell(row,col);
        return false;
}  
          

//********************************************* EQUIPMENT    
Weapon* Player::LoseWeapon( )
{
	if (p)
	  return p->LoseWeapon( );
        return NULL;

}

Weapon * Player::FindWeapon(Weapon* w)
{
	if (p)
	  return p->FindWeapon(w);
        return w;
}

Weapon *Player::ChangeWeapon(string wName)
{
	Humanoid *h = dynamic_cast<Humanoid *>(p);
	if (h)
	  return h->ChangeWeapon(wName );
        return NULL;

}

//********************************************* SKILL    
bool Player::AddSkill(string skill)
{
	if (p)
	  return p->AddSkill(skill );
        return false;

}

void Player::Amnesia( )
{
	if (p)
	  p->Amnesia( );

}
     
//********************************************* Updates & Calculations    
    
int Player::RollInitiative( ) const
{
	if (p)
	  return p->RollInitiative( );
        return 0;
}
 
int Player::RollAttack( )const
{
	if (p)
	  return p->RollAttack();
	return 0;
}

int Player::RollSavingThrow(SavingThrowType s) const
{
	if (p)
	  return p->RollSavingThrow(s);
        return 0;
}

int Player::RollDefense( ) const
{
	if (p)
	  return p->RollDefense( );
	return 0;
}

int Player::RollDamage( ) const
{
	if (p)
	  return p->RollDamage( );
        return 0;
}

int Player::SkillCheck(string skill) const
{
	if (p)
	  return p->SkillCheck(skill);
        return 0;

}



//********************************************* Relational operators
bool Player::operator==(const Player& h) const 
{
        if ((!p) && (!h.p)) // if both are NULL
            return false;
       	else if ((!p)||(!h.p))   // if either are NULL
      		return false;
	else
		return (*p == *h.p);
       	      					
}

bool Player::operator!=(const Player& h) const
{
        if ((!p) && (!h.p)) // if both are NULL
          return false;
       	else if ((!p)||(!h.p))   // if either are NULL
       		return true;
	else
		return (*p != *h.p);

}

bool Player::operator<(const Player& h) const 
{
       	if ((!p)||(!h.p))   // if either are NULL
      		return false;
	else
		return (*p < *h.p);

}

bool Player::operator<=(const Player& h) const
{
       	if ((!p)||(!h.p))   // if either are NULL
      		return false;
	else
		return (*p <= *h.p);

}

bool Player::operator>(const Player& h) const 
{
       	if ((!p)||(!h.p))   // if either are NULL
      		return false;
	else
		return (*p > *h.p);

}

bool Player::operator>=(const Player& h) const
{
       	if ((!p)||(!h.p))   // if either are NULL
      		return false;
	else
		return (*p >= *h.p);

}

//********************************************* Write
void Player::Write(ostream& stream) const
{
	if (p)
	  p->Write(stream);

    return;
}

		  



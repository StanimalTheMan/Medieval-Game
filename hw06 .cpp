/*
Stan Choi
hw06.cpp
This program aims to output the desired output for hw06.
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Noble {
public:
	Noble(const string& name) : name(name), isDead(false) {}
	//virtual void battle(Noble& noble) = 0;
	void battle(Noble& noble) {
		cout << name << " battles " << noble.name << endl; //applicable in all situations
		//noble.getStrength();
		if (this->getStrength() > noble.getStrength()) {
			if (noble.isDead) { // am I doing this right?
				cout << "He's dead, " << name << endl;
			}
			else {
				//cout << name << " defeats " << noble.name << endl;
				//noble.isDead = true;
				this->setStrength(this->getStrength() - noble.getStrength());
				noble.setStrength(0);
				noble.isDead = true;
				cout << name << " defeats " << noble.name << endl;
			}
		}
		else if (noble.getStrength() > this->getStrength()) {
			if (this->isDead) {
				cout << "He's dead, " << noble.name << endl;
			}
			else {
				//cout << noble.name << " defeats " << name << endl;
				//isDead = true;
				this->setStrength(0);
				noble.setStrength(noble.getStrength() - this->getStrength());
				isDead = true;
				cout << noble.name << " defeats " << name << endl;
			}
		}
		else {
			cout << "Oh, NO!  They're both dead!  Yuck!" << endl;
		}
	}
	virtual double getStrength() const = 0;
	virtual void setStrength(double new_str) = 0;
	const string& getName() const {
		return name;
	}
protected:
	bool getStatus() const {
		return isDead;
	}
private:
	const string name;
	bool isDead;
};

class Lord; //I probably am not allowed to use forward declaration for this assignment, but I couldn't find a way to absolve the fact that Protector class
             //didn't know that Lord class existed.  Errors kept arising.  

class Protector {
public:
	Protector(const string& name, double strength) : name(name), strength(strength), employee(nullptr), isDead(false) {}
	virtual void defend() = 0;
	Lord* getHiredStatus() const {
		return employee;
	}
	double getStrength() const {
		return strength;
	}
	void setStrength(double new_str) {
		strength = new_str;
	}
	bool getStatus() const { 
		return isDead;
	}
	void setStatus(bool update) {
		isDead = update;
	}
protected:
	const string& getName() const {
		return name;
	}
private:
	const string name;
	double strength;
	Lord* employee;
	bool isDead;
};



class Wizard : public Protector {
public:
	Wizard(const string& name, double strength) : Protector(name, strength) {}
	void defend() {
		if (!this->getStatus()) {//if not dead
			cout << "POOF!" << endl;
		}
		//cout << "POOF" << endl;
	}
private:
};

class Warrior : public Protector {
public:
	Warrior(const string& name, double strength) : Protector(name, strength) {}
private:
};

class Archer : public Warrior {
public:
	Archer(const string& name, double strength) : Warrior(name, strength) {}
	void defend() {
		if (!this->getStatus()) {//if not dead
			cout << "TWANG!   " << getName() << " says: Take that in the name of my lord, ";
		}
		//cout << "TWANG!   " << getName() << " says: Take that in the name of my lord, ";
	}
private:
};

class Swordsman : public Warrior {
public:
	Swordsman(const string& name, double strength) : Warrior(name, strength) {}
	void defend() {
		if (!this->getStatus()) {//if not dead
			cout << "CLANG!   " << getName() << " says: Take that in the name of my lord, ";
		}
		//cout << "CLANG!   " << getName() << " says: Take that in the name of my lord, ";
	}
private:
};

class Lord : public Noble {
public:
	Lord(const string& name) : Noble(name) {}
	virtual void hires(Protector& protector) {
		if (this->getStatus()) {
			return;
			//if noble is dead, he can't hire
		}
		else {
			if (protector.getHiredStatus() == nullptr && !protector.getStatus()) {//if protector is both unemployed and alive
				protectors.push_back(&protector);
			}
		}
	}
	double getStrength() const {
		double tot_str(0);
		for (Protector* p : protectors) {
			//p->defend();
			//cout << endl;
			//cout << this->getName();
			//cout << endl;
			tot_str += p->getStrength();
		}
		return tot_str;
	}
	void setStrength(double new_str) {
		for (Protector* p : protectors) {
			p->defend();//probabaly doesn't belong here
						//p->setStrength(new_str);
			cout << getName() << endl;
			if (new_str == 0) {
				p->setStatus(true);
				p->setStrength(new_str);
				//(*p).isDead = true;
			}
			else {
				p->setStrength(new_str);
			}
		}
	}
	/*void battle(Noble& noble) {
	for (Protector* protector : protectors) {
	protector->defend();
	cout << getName() << endl;
	}
	double strength(0);
	for (Protector* protector : protectors) {
	strength += protector->getStrength();
	}
	}*/
private:
	vector<Protector*> protectors;
};


class PersonWithStrengthToFight : public Noble {
public:
	PersonWithStrengthToFight(const string& name, double strength) : Noble(name), strength(strength) {}
	double getStrength() const {
		return strength;
	}
	void setStrength(double new_str) {
		strength = new_str;
	}
private:
	double strength;
};



int main() {
	Lord sam("Sam");
	Archer samantha("Samantha", 200);
	sam.hires(samantha);
	Lord joe("Joe");
	PersonWithStrengthToFight randy("Randolf the Elder", 250);
	joe.battle(randy);
	joe.battle(sam);
	Lord janet("Janet");
	Swordsman hardy("TuckTuckTheHardy", 100);
	Swordsman stout("TuckTuckTheStout", 80);
	janet.hires(hardy);
	janet.hires(stout);
	PersonWithStrengthToFight barclay("Barclay the Bold", 300);
	janet.battle(barclay);
	janet.hires(samantha);
	Archer pethora("Pethora", 50);
	Archer thora("Thorapleth", 60);
	Wizard merlin("Merlin", 150);
	janet.hires(pethora);
	janet.hires(thora);
	sam.hires(merlin);
	janet.battle(barclay);
	sam.battle(barclay);
	joe.battle(barclay);

	system("pause");
}
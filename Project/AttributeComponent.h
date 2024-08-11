#ifndef ATTRIBUTECOMPONENT_H
#define ATTRIBUTECOMPONENT_H
class AttributeComponent
{
private:

public:
	//Leveling
	unsigned level;
	unsigned exp;
	unsigned expNext;
	unsigned AttributePoints;
	//Attributes
	unsigned vitality;
	unsigned strength;
	unsigned dexterity;
	unsigned agility;
	unsigned intelligence;
	//Stats
	int hp;
	int hpMax;
	int damageMin;
	int damageMax;
	int accuracy;
	int defence;
	int luck;
	//Con /Des
	AttributeComponent(unsigned level);
	virtual ~AttributeComponent();
	//Functions
	void calculateExpNext();
	void updateStates();
	void levelup();
	void update();
};
#endif


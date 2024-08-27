#ifndef ATTRIBUTECOMPONENT_H
#define ATTRIBUTECOMPONENT_H
class AttributeComponent
{
private:

public:
	//Leveling
	int level;
	int exp;
	int expNext;
	int AttributePoints;
	//Attributes
	
	int vitality;
	int strength;
	int dexterity;
	int agility;
	int intelligence;
	//Stats
	int hp;
	int hpMax;
	int damageMin;
	int damageMax;
	int accuracy;
	int defence;
	int luck;
	//Con /Des
	AttributeComponent(int level);
	virtual ~AttributeComponent();
	//Functions
	void loseHP(const int hp);
	void loseEXP(const int exp);
	void gainHP(const int hp);
	void calcExpNext();
	std::string debugPrint() const;
	void gainExp(const int exp);
	const bool isDead() const;
	void updateStates(const bool rest);
	void updateLevel();
	void update();
};
#endif


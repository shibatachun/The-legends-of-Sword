#ifndef ITEM_H
#define ITEM_H

enum ItemTypes{ITEM_DEFAULT=0,RANGEDWEAPON, MEELEEWEAPON};
enum ItemRarities { COMMON = 0, UNCOMMON, RARE, EPIC, LEGENDARY, MYTHIC };
class Item
{
private:
	void initVariables();
protected:
	//Variables
	short unsigned type;
	unsigned value;
public:




	Item(unsigned value);
	virtual ~Item();

	//Function
	virtual Item* clone() = 0;
};

#endif //Item


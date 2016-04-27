//needed for including in a MFC-App
#ifdef __MFC__
#include "../gui/stdafx.h" 
#endif // __MFC__

//include the correct header-file
#include "HWLFairyFood.h"

//use the project-namespace
using namespace HWLSaveEdit;

/* @var vs_fairyFood			vector for holding all names of fairyFood-Items */
const vector<string> HWLFairyFood::vs_fairyFood =
{
	"Weird Egg",
	"Tasty Weird Egg",
	"Delicious Weird Egg",
	"Lon Lon Milk",
	"Tasty Lon Lon Milk",
	"Delicious Lon Lon Milk",
	"Odd Mushroom",
	"Tasty Odd Mushroom",
	"Delicious Odd Mushroom",
	"Deku Nut",
	"Tasty Deku Nut",
	"Delicious Deku Nut",
	"Magic Beans",
	"Tasty Magic Beans",
	"Delicious Magic Beans",
	"Pumpkin Soup",
	"Tasty Pumpkin Soup",
	"Delicious Pumpkin Soup",
	"Sacred Water",
	"Tasty Sacred Water",
	"Delicious Sacred Water",
	"Life Tree Fruit",
	"Tasty Life Tree Fruit",
	"Delicious Life Tree Fruit",
	"Light Fruit",
	"Tasty Light Fruit",
	"Delicious Light Fruit",
	"Stamina Fruit",
	"Tasty Stamina Fruit",
	"Delicious Stamina Fruit",
	"Water Fruit",
	"Tasty Water Fruit",
	"Delicious Water Fruit",
	"Mushroom Spores",
	"Tasty Mushroom Spores",
	"Delicious Mushroom Spores",
	"All-Purpose Bait",
	"Tasty All-Purpose Bait",
	"Delicious All-Purpose Bait",
	"Elixir Soup",
	"Tasty Elixir Soup",
	"Delicious Elixir Soup",
	"Hyoi Pear",
	"Tasty Hyoi Pear",
	"Delicious Hyoi Pear",
	"Ordon Goat Cheese",
	"Tasty Ordon Goat Cheese",
	"Delicious Ordon Goat Cheese",
	"Great Fairy's Tears",
	"Tasty Great Fairy's Tears",
	"Delicious Great Fairy's Tears",
	"Greengill",
	"Tasty Greengill",
	"Delicious Greengill",
	"Ordon Catfish",
	"Tasty Ordon Catfish",
	"Delicious Ordon Catfish",
	"Hyrule Bass",
	"Tasty Hyrule Bass",
	"Delicious Hyrule Bass",
	"Hylian Pike",
	"Tasty Hylian Pike",
	"Delicious Hylian Pike",
	"Reekfish",
	"Tasty Reekfish",
	"Delicious Reekfish",
	"Hylian Loach",
	"Tasty Hylian Loach",
	"Delicious Hylian Loach",
	"Skullfish",
	"Tasty Skullfish",
	"Delicious Skullfish",
	"Bombfish",
	"Tasty Bombfish",
	"Delicious Bombfish",
	"Chu Jelly",
	"Tasty Chu Jelly",
	"Delicious Chu Jelly",
	"Bee Larvae",
	"Tasty Bee Larvae",
	"Delicious Bee Larvae",
	"Chateau Romani",
	"Tasty Chateau Romani",
	"Delicious Chateau Romani",
	"Bottled Water",
	"Tasty Bottled Water",
	"Delicious Bottled Water",
	"Hot Spring Water",
	"Tasty Hot Spring Water",
	"Delicious Hot Spring Water",
	"Rock Sirloin",
	"Tasty Rock Sirloin",
	"Delicious Rock Sirloin",
	"Meat",
	"Tasty Meat",
	"Delicious Meat",
	"Carrot",
	"Tasty Carrot",
	"Delicious Carrot",
	"Ember Seeds",
	"Tasty Ember Seeds",
	"Delicious Ember Seeds",
	"Scent Seeds",
	"Tasty Scent Seeds",
	"Delicious Scent Seeds",
	"Pegasus Seeds",
	"Tasty Pegasus Seeds",
	"Delicious Pegasus Seeds",
	"Gale Seeds",
	"Tasty Gale Seeds",
	"Delicious Gale Seeds",
	"Mystery Seeds",
	"Tasty Mystery Seeds",
	"Delicious Mystery Seeds",
	"Gratitude Crystal Red S",
	"Gratitude Crystal Red M",
	"Gratitude Crystal Red L",
	"Gratitude Crystal Blue S",
	"Gratitude Crystal Blue M",
	"Gratitude Crystal Blue L",
	"Gratitude Crystal Orange S",
	"Gratitude Crystal Orange M",
	"Gratitude Crystal Orange L",
	"Gratitude Crystal Pink S",
	"Gratitude Crystal Pink M",
	"Gratitude Crystal Pink L",
	"Gratitude Crystal Purple S",
	"Gratitude Crystal Purple M",
	"Gratitude Crystal Purple L",
	"Pumpkin",
	"Tasty Pumpkin",
	"Delicious Pumpkin"
};

/* @var fairyFoodlValueMax				maximal-value of a fairyFood item*/
const int HWLFairyFood::fairyFoodlValueMax = 255;

/* @var fairyGratitudeCrystalIDBegin	ÌD of the first gratitude crystal */
const int HWLFairyFood::fairyGratitudeCrystalIDBegin = 114;

/* @var fairyGratitudeCrystalIDEnd		ÌD of the last gratitude crystal */
const int HWLFairyFood::fairyGratitudeCrystalIDEnd = 128;



/**
* Only the initialization of the normal-constructor
*/
HWLFairyFood::HWLFairyFood(string s_name, int i_offset)
{
	//set or calculate all needed members
	this->s_name = s_name;
	this->i_offset = i_offset;
	this->i_value = this->calc_value();
}

/**
* Only the initialization of the normal-destructor
*/
HWLFairyFood::~HWLFairyFood()
{
}



/**
* This method calculates the current fairyFood value
*
*	@return int		the current fairyFood-value
*
*/
int HWLFairyFood::calc_value()
{
	//declare/define needed variables
	string s_fairyFood_value;
	int i_fairyFood_offset = this->i_offset;

	//get hex-value from the file-content holder and convert it to int
	s_fairyFood_value = this->getHexStringFromFileContent(i_fairyFood_offset, this->fairyFoodOffsetLength);
	int i_fairyFood_value = this->HexStringToInt(s_fairyFood_value);

	//return the current int-value
	return i_fairyFood_value;
}

/**
* This method set the current fairyFood-value
* to the file-content holder
*
*/
void HWLFairyFood::save_value()
{
	//declare/define needed variables
	int i_value_tmp = this->i_value;
	string s_fairyFood_value;
	int i_fairyFood_offset = this->i_offset;

	//convert the current integer-value to hex and add needed zeros, if we
	//don't have the complete length (calculate with offset-length multiplied by 2)
	s_fairyFood_value = this->intToHexString(i_value_tmp, false);
	this->addZeroToHexString(s_fairyFood_value, this->fairyFoodOffsetLength * 2);

	//set converted hex-value to the file-content holder
	this->setHexStringToFileContent(s_fairyFood_value, i_fairyFood_offset);
}



/**
* Setter for the fairyFood-value
*
*	@var int	i_value		fairyFood-value to set
*
*/
void HWLFairyFood::set_value(int i_value)
{
	//check if fairyFood-value smaller then 0, then set it directly to 0
	//also check for the maximal-value
	if (i_value < 0)
		i_value = 0;
	else if (i_value > this->fairyFoodlValueMax)
		i_value = this->fairyFoodlValueMax;

	this->i_value = i_value;
}



/**
* Getter for the fairyFood-name
*
*	@return string		the name of the fairyFood
*
*/
string HWLFairyFood::get_name()
{
	return this->s_name;
}

/**
* Getter for the fairyFood-offset
*
*	@return int		the offset of the fairyFood
*
*/
int HWLFairyFood::get_offset()
{
	return this->i_offset;
}

/**
* Getter for the fairyFood-value
*
*	@return int		the value of the fairyFood
*
*/
int HWLFairyFood::get_value()
{
	return this->i_value;
}



/**
* This method returns an formatted string, which contain all needed member-values
*
*	@return string		formatted output with all needed member-values
*
*/
string HWLFairyFood::get_FairyFoodForOutput()
{
	string s_output = "Name: " + this->s_name + "\n"
		+ "  Value: " + to_string(this->i_value) + "\n";

	return s_output;
}

/**
* This method is a wrapper for all known save-methods of the class
*
*/
void HWLFairyFood::save_FairyFood()
{
	this->save_value();
}

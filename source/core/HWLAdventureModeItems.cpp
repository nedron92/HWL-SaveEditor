//needed for including in a MFC-App
#ifdef __MFC__
#include "../gui/stdafx.h" 
#endif // __MFC__

//include the correct header-file
#include "HWLAdventureModeItems.h"

//use the project-namespace
using namespace HWLSaveEdit;

/* @var vs_amItems			vector for holding all names of AdventureMode-Items */
const vector<string> HWLAdventureModeItems::vs_amItems =
{
	"Compass", //Adventure-Map Items Begin
	"Bombs",
	"Candle",
	"Ladder",
	"Power Bracelet",
	"Water Bombs",
	"Digging Mitts",
	"Ice Arrow",
	"Raft",
	"Hookshot",
	"Recorder",
	"Goddess's Harp",  //Adventure-Map Items End

	"Compass", //GreatSea-Map Items Begin
	"Hookshot",
	"Wind Waker",
	"Cannon",
	"Boomerang",
	"Hero's Bow",
	"Grappling Hook",
	"Hyoi Pears",
	"Deku Leaf",
	"Sea Chart",
	"Power Bracelet",
	"Hammer",  //GreatSea-Map Items End

	"Compass",  //MasterQuest-Map Items Begin
	"Bombs",
	"Candle",
	"Ladder",
	"Power Bracelet",
	"Water Bombs",
	"Digging Mitts",
	"Ice Arrow",
	"Raft",
	"Hookshot",
	"Recorder",
	"Goddess's Harp",  //MasterQuest-Map Items End

	"Compass",  //Twilight-Map Items Begin
	"Bombs",
	"Water Bombs",
	"Digging Mitts",
	"Lantern",
	"Jar",
	"Fishing Rod",
	"Clawshot",
	"Spinner",
	"Ooccoo",
	"Tears of Light",
	"Tears of Twilight", //Twilight-Map Items End

	"Compass",  //Termina-Map Items Begin
	"Bombs",
	"Ice Arrow",
	"Song of Time",
	"Song of Time (Inv.)",
	"Deku Stick",
	"Deku Mask",
	"Goron Mask",
	"Zora Mask",
	"Mask of Truth",
	"Majora's Mask",
	"Giants",  //Termina-Map Items End

	//only 1st DLC: Master Wind Waker DLC
	"Compass", //MasterWindWaker-Map Items Begin
	"Hookshot",
	"Wind Waker",
	"Cannon",
	"Boomerang",
	"Hero's Bow",
	"Grappling Hook",
	"Hyoi Pears",
	"Deku Leaf",
	"Sea Chart",
	"Power Bracelet",
	"Hammer",  //MasterWindWaker-Map Items End

	//only 2nd DLC: Link's Awakening DLC
	"Compass", //KoholintIsland-Map Items Begin
	"Full Moon Cello",
	"Conch Horn",
	"Sea Lily Bell",
	"Surf Harp",
	"Wind Marimba",
	"Coral Triangle",
	"Organ of Evening Calm",
	"Thunder Drum",
	"Grandpa Ulrira",
	"Power Bracelet",
	"Magic Powder",  //KoholintIsland-Map Items End

	//only 3rd DLC: Phantom Hourglass & Spirit Tracks DLC
	"Compass", //GrandTravels-Map Items Begin
	"Whirlwind",
	"Fishing Rod",
	"Cannon",
	"Railway Track",
	"Cyclone Slate",
	"S.S. Linebeck",
	"Iron Ship",
	"Golden Ship",
	"Spirit Train",
	"Steel Train",
	"Golden Train",  //GrandTravels-Map Items End

	//only 4th DLC: A Link Between Worlds DLC
	"Bomb", //Lorule-Map Items Begin
	"Wall Painting",
	"Power Glove",
	"Fire Rod",
	"Tornado-Rod",
	"Ice-Rod",
	"Sand-Rod",
	"Baby Maimai",
	"Hammer",
	"Boomerang",
	"Bow",
	"Hookshot",  //Lorule-Map Items End

};

/* @var amItemValueMax		maximal-value of an AdventureMode-Item */
const int HWLAdventureModeItems::amItemValueMax = 5;



/**
* Only the initialization of the normal-constructor
*/
HWLAdventureModeItems::HWLAdventureModeItems(int i_id, int i_offset, int i_map_id)
{
	//set or calculate all needed members
	this->i_id = i_id;
	this->s_name = this->vs_amItems[this->i_id];
	this->i_offset = i_offset;
	this->i_map_id = i_map_id;
	this->i_value = this->calc_value();
}


/**
* Only the initialization of the normal-destructor
*/
HWLAdventureModeItems::~HWLAdventureModeItems()
{
}



/**
* This method calculates the current AM-Item value
*
*	@return int		the current material-value
*
*/
int HWLAdventureModeItems::calc_value()
{
	//declare/define needed variables
	string s_amItem_value;
	int i_amItem_offset = this->i_offset;

	//get hex-value from the file-content holder and convert it to int
	s_amItem_value = this->getHexStringFromFileContent(i_amItem_offset, this->amItemOffsetLength);
	int i_amItem_value = this->HexStringToInt(s_amItem_value);

	//return the current int-value
	return i_amItem_value;
}



/**
* This method set the current AM-Item value
* to the file-content holder
*
*/
void HWLAdventureModeItems::save_value()
{
	//declare/define needed variables
	int i_value_tmp = this->i_value;
	string s_amItem_value;
	int i_amItem_offset = this->i_offset;

	//convert the current integer-value to hex and add needed zeros, if we
	//don't have the complete length (calculate with offset-length multiplied by 2)
	s_amItem_value = this->intToHexString(i_value_tmp, false);
	this->addZeroToHexString(s_amItem_value, this->amItemOffsetLength * 2);

	//set converted hex-value to the file-content holder
	this->setHexStringToFileContent(s_amItem_value, i_amItem_offset);
}



/**
* Setter for the AM-Item value
*
*	@var int	i_value		AM-Item value to set
*
*/
void HWLAdventureModeItems::set_value(int i_value)
{
	//check if AM-Item value smaller then 0, then set it directly to 0
	//also check for the maximal-value
	if (i_value < 0)
		i_value = 0;
	else if (i_value > this->amItemValueMax)
		i_value = this->amItemValueMax;

	this->i_value = i_value;

}



/**
* Getter for the AM-Item-name
*
*	@return string		the name of the AM-Item
*
*/
string HWLAdventureModeItems::get_name()
{
	return this->s_name;
}

/**
* Getter for the AM-Item-ID
*
*	@return int		the ID of the AM-Item
*
*/
int HWLAdventureModeItems::get_id()
{
	return this->i_id;
}

/**
* Getter for the AM-Item-offset
*
*	@return int		the offset of the AM-Item
*
*/
int HWLAdventureModeItems::get_offset()
{
	return this->i_offset;
}

/**
* Getter for the AM-Item-type
*
*	@return int		the type of the AM-Item
*
*/
int HWLAdventureModeItems::get_map_id()
{
	return this->i_map_id;
}

/**
* Getter for the AM-Item-value
*
*	@return int		the value of the AM-Item
*
*/
int HWLAdventureModeItems::get_value()
{
	return this->i_value;
}



/**
* This method returns an formatted string, which contain all needed member-values
*
*	@return string		formatted output with all needed member-values
*
*/
string HWLAdventureModeItems::get_AMItemForOutput()
{
	string s_output = "Name: " + this->s_name + "\n"
		//+ "  ID: " + to_string(this->i_id) + "\n"
		//+ "  Map-ID: " + to_string(this->i_map_id) + "\n"
		+ "  Value: " + to_string(this->i_value) + "\n";
		//+ "  Offset: " + to_string(this->i_offset) + "\n";

	return s_output;
}



/**
* This method is a wrapper for all known save-methods of the class
*
*/
void HWLAdventureModeItems::save_AMItem()
{
	this->save_value();
}

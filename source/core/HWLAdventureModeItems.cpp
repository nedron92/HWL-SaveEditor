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
	"Giants"  //Termina-Map Items End
};

/* @var amItemValueMax		maximal-value of an AdventureMode-Item */
const int HWLAdventureModeItems::amItemValueMax = 5;

/* @var amItemPerMapMax		maximal-value of AdventureMode-Items per AM-Map */
const int HWLAdventureModeItems::amItemPerMapMax = 12;



/**
* Only the initialization of the normal-constructor
*/
HWLAdventureModeItems::HWLAdventureModeItems(string s_name, int i_offset, int i_type)
{
	//set or calculate all needed members
	this->s_name = s_name;
	this->i_offset = i_offset;
	this->i_type = i_type;
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
	int i_amItem_value= this->HexStringToInt(s_amItem_value);

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
int HWLAdventureModeItems::get_type()
{
	return this->i_type;
}

/**
* Getter for the AM-Item-type as string
*
*	@return string		the type of the AM-Item as a string
*
*/
string HWLAdventureModeItems::get_type(bool b_get_string)
{
	switch (this->i_type)
	{
	case 0:
		return "Adventure-Map Item";
		break;

	case 1:
		return "GreatSea-Map Item";
		break;

	case 2:
		return "MasterQuest-Map Item ";
		break;

	case 3:
		return "Twilight-Map Item ";
		break;

	case 4:
		return "Termina-Map Item ";
		break;

	default:
		return to_string(i_type);
	}
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
		+ "  Type: " + this->get_type(true) + "\n"
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

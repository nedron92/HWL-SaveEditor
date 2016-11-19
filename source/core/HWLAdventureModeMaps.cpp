//needed for including in a MFC-App
#ifdef __MFC__
#include "../gui/stdafx.h" 
#endif // __MFC__

//include the correct header-file
#include "HWLAdventureModeMaps.h"

//use the project-namespace
using namespace HWLSaveEdit;


//private constants
/* @var amItemOffsetBegin	vector for holding the offsets-begin for AdventureMode items */
const vector<int> HWLAdventureModeMaps::amItemOffsetBegin =
{
	0x2EFA,  //Start of Adventure-Map Items
	0xEB73,  //Start of GreatSea-Map Items (WindWaker and so on)
	0x7A52,  //Start of MasterQuest-Map Items
	0xA00A,  //Start of Twilight-Map Items (Lantern and so on)
	0xC5BE,	 //Start of Termina-Map Items (Song of Time and so on)
	0x11120,  //Start of MasterWindWaker-Map Items (Cannon and so on), only 1st DLC: Master Wind Waker DLC
	0x136D5,  //Start of KoholintIsland-Map Items (Full Moon Cello and so on), only 2nd DLC: Link's Awakening DLC
	0x15C8D,  //Start of GrandTravels-Map Items (Railway Track and so on), only 3rd DLC: Phantom Hourglass & Spirit Tracks DLC
};

/* @var amItemOffsetBeginSpecial	vector for holding the offsets-begin for AdventureMode items */
const vector<int> HWLAdventureModeMaps::amItemOffsetBeginSpecial =
{
	0xEB56,  //Compass of GreatSea-Map
	0xEB5F,  //Hookshot of GreatSea-Map

	0x9FFE,  //Compass of Twilight-Map (+1 = Bombs)
	0xA003,  //Waterbombs of Twilight-Map (+1 = Digging Mitts)

	0xC5AA, //Compass of Termina-Map (+1 = Bombs)
	0xC5B1, //Ice Arrow of Termina-Map

	//only 1st DLC: Master Wind Waker DLC
	0x11102, //Compass of MasterWindWaker-Map
	0x1110B, //Hookshot of MasterWindWaker-Map
	0x1111F, //WindWaker of MasterWindWaker-Map

	//only 2nd DLC: Link's Awakening DLC
	0x136AE, //Compass of KoholintIsland-Map

	//only 3rd DLC: Phantom Hourglass & Spirit Tracks DLC
	0x15C5A, //Compass of GrandTravels-Map
	0x15C8C, //Whirlwind of GrandTravels-Map
	0x15C68, //Fishing Rod of GrandTravels-Map
	0x15C78, //Cannon of GrandTravels-Map
};

/* @var si_disabledMapCounter	Counter which holds the current value of disabled AM-Maps */
int HWLAdventureModeMaps::si_disabledMapCounter = 0;


//public constants

/* @var vs_map_names		vector, which hold all current names of all known AM-Maps */
const vector<string> HWLAdventureModeMaps::vs_map_names =
{
	"Adventure-Map",
	"GreatSea-Map",
	"MasterQuest-Map",
	"Twilight-Map",
	"Termina-Map",
	"MasterWindWaker-Map", //only 1st DLC: Master Wind Waker DLC
	"KoholintIsland-Map",  //only 2nd DLC: Link's Awakening DLC
	"GrandTravels-Map",   //only 3rd DLC: Phantom Hourglass & Spirit Tracks DLC
};

/* @var amItemPerMapMax		maximal-value of AdventureMode-Items per AM-Map */
const int HWLAdventureModeMaps::amm_MaxItemsPerMap = 12;



/**
* Only the initialization of the normal-constructor
*/
HWLAdventureModeMaps::HWLAdventureModeMaps(int i_id)
{
	//Reset static values if new saveFile is opened
	if (this->b_isNewSaveFile)
		this->si_disabledMapCounter = 0;

	//set or calculate all needed members
	this->i_id = i_id;
	this->s_name = this->vs_map_names[this->i_id];
	this->b_isDisabled = false;
	this->vsp_hwlami_items = this->calc_amiItems();
}


/**
* Only the initialization of the normal-destructor
*/
HWLAdventureModeMaps::~HWLAdventureModeMaps()
{
}



/**
* This method calculate the AdventureMode-Item-Objects
*
*/
vector<shared_ptr<HWLAdventureModeItems>> HWLAdventureModeMaps::calc_amiItems()
{
	//decalre/define needed variables
	int i_offset;
	vector<shared_ptr<HWLAdventureModeItems>> vsp_hwlami_items_tmp;

	//Iterate over the current correct Items of the map
	for (int i = (this->i_id * this->amm_MaxItemsPerMap); i < (this->i_id * this->amm_MaxItemsPerMap) + this->amm_MaxItemsPerMap; i++)
	{

		//switch of iterate-variable i, cause we have to check some special AdventureMode Items, they are called
		//"shared-items" like Compass,...that we found on nearly every AdventureMode-Map. They have special-offsets then
		//Else: Get the normal offset of the Item
		switch (i)
		{
			//BEGIN SPECIAL ITEMS-OFFSETS
		case 12: //Compass, Great-Sea Map
			i_offset = this->amItemOffsetBeginSpecial[0];
			break;

		case 13: //Hookshot, Great-Sea Map
			i_offset = this->amItemOffsetBeginSpecial[1];
			break;

		case 36: //Compass, Twilight Map
			i_offset = this->amItemOffsetBeginSpecial[2];
			break;

		case 38: //Water Bombs, Twilight Map
			i_offset = this->amItemOffsetBeginSpecial[3];
			break;

		case 48: //Compass, Termina Map
			i_offset = this->amItemOffsetBeginSpecial[4];
			break;

		case 50: //Ice Arrow, Termina Map
			i_offset = this->amItemOffsetBeginSpecial[5];
			break;

		case 60: //Compass, MasterWindWaker Map, only 1st DLC: Master Wind Waker DLC
			i_offset = this->amItemOffsetBeginSpecial[6];
			break;

		case 61: //Hookshot, MasterWindWaker Map, only 1st DLC: Master Wind Waker DLC
			i_offset = this->amItemOffsetBeginSpecial[7];
			break;

		case 62: //Wind Waker, MasterWindWaker Map, only 1st DLC: Master Wind Waker DLC
			i_offset = this->amItemOffsetBeginSpecial[8];
			break;

		case 72: //Compass, KoholintIsland Map, only 2nd DLC: Link's Awakening DLC
			i_offset = this->amItemOffsetBeginSpecial[9];
			break;

		case 84: //Compass, GrandTravels Map, only 3rd DLC: Phantom Hourglass & Spirit Tracks DLC
			i_offset = this->amItemOffsetBeginSpecial[10];
			break;

		case 85: //Whirlwind, GrandTravels Map, only 3rd DLC: Phantom Hourglass & Spirit Tracks DLC
			i_offset = this->amItemOffsetBeginSpecial[11];
			break;

		case 86: //Fishing Rod, GrandTravels Map, only 3rd DLC: Phantom Hourglass & Spirit Tracks DLC
			i_offset = this->amItemOffsetBeginSpecial[12];
			break;

		case 87: //Cannon, GrandTravels Map, only 3rd DLC: Phantom Hourglass & Spirit Tracks DLC
			i_offset = this->amItemOffsetBeginSpecial[13];
			break;
			//END SPECIAL ITEMS-OFFSETS

			//BEGIN NORMAL ITEMS-OFFSETS
		case 14: //Wind Waker, Great-Sea map
		case 40: //Lantern, Twilight Map
		case 51: //Song of Time, Termina Map
		case 63: //Cannon, MasterWindWaker Map, only 1st DLC: Master Wind Waker DLC
		case 73: //Full Moon Cello, KoholintIsland Map, only 2nd DLC: Link's Awakening DLC
		case 88: //Railway Track, GrandTravels Map, only 3rd DLC: Phantom Hourglass & Spirit Tracks DLC
			i_offset = this->amItemOffsetBegin[this->i_id];
			break;

		default: //normal
			i_offset = this->amItemOffsetBegin[this->i_id];
			break;
			//END NORMAL ITEMS-OFFSETS
		}

		//create new AdventureMode-item object, based on offset and type (also name)
		shared_ptr<HWLAdventureModeItems> hwlami_tmp = make_shared<HWLAdventureModeItems>(i, i_offset, this->i_id);

		//bind object to the map of them
		vsp_hwlami_items_tmp.push_back(hwlami_tmp);

		//calculate the next offset
		i_offset = i_offset + this->amItemOffsetLength;
	}

	return vsp_hwlami_items_tmp;


}



/**
* Setter for the AM-Map Disabled-State (and increment/decrement Counter-Member)
*
*	@var bool	b_isDisabled		Disabled-State to set
*
*/
void HWLAdventureModeMaps::set_isDisabled(bool b_isDisabled)
{
	if (b_isDisabled)
		this->si_disabledMapCounter++;
	else if (this->si_disabledMapCounter > 0)
		this->si_disabledMapCounter--;

	this->b_isDisabled = b_isDisabled;
}

/**
* Setter for the AM-Map Item, explicit by a given item-id and 
* a correct object
*
*	@var int	i_item_id		given Item-ID to set (=vector-index) (0-11)
*	@var shared_ptr<HWLAdventureModeItems>		sp_hwlami_item		shared-pointer (object) to set on given item-id / slot
*
*/
void HWLAdventureModeMaps::set_amItem(int i_item_id, shared_ptr<HWLAdventureModeItems> sp_hwlami_item)
{
	if (i_item_id < this->amm_MaxItemsPerMap)
		this->vsp_hwlami_items[i_item_id] = sp_hwlami_item;
}

/**
* Setter for the AM-Map Item-Vector itself (all items)
*
*	@var vector<shared_ptr<HWLAdventureModeItems>>		vsp_hwlami_item		vector, which holds al items of that map
*
*/
void HWLAdventureModeMaps::set_all_amItems(vector<shared_ptr<HWLAdventureModeItems>> vsp_hwlami_item)
{
	this->vsp_hwlami_items = vsp_hwlami_item;
}



/**
* Getter for the AM-Map-ID
*
*	@return int		the ID of the AM-Map
*
*/
int HWLAdventureModeMaps::get_id()
{
	return this->i_id;
}

/**
* Getter for the AM-Map-Name
*
*	@return string		the Name of the AM-Map
*
*/
string HWLAdventureModeMaps::get_name()
{
	return this->s_name;
}

/**
* Getter for the AM-Map Disabled-State
*
*	@return bool		the Disabled-State of the AM-Map
*
*/
bool HWLAdventureModeMaps::get_isDisabled()
{
	return this->b_isDisabled;
}

/**
* Getter for the AM-Map Item, explicit by a given item-id
*
*	@var int	i_item_id		given Item-ID to get (=vector-index) (0-11)
*
*	@return shared_ptr<HWLAdventureModeItems>		shared-pointer (object) to get on given item-id / slot
*
*/
shared_ptr<HWLAdventureModeItems> HWLAdventureModeMaps::get_amItem(int i_item_id)
{
	return this->vsp_hwlami_items[i_item_id];
}

/**
* Getter for the all AM-Map Items
*
*	@return vector<shared_ptr<HWLAdventureModeItems>>		vector of all AM-items of that map
*
*/
vector<shared_ptr<HWLAdventureModeItems>> HWLAdventureModeMaps::get_all_amItems()
{
	return this->vsp_hwlami_items;
}

/**
* Getter for the disbaledMapCounter
*
*	@return int		the disabled-MapCounter
*
*/
int HWLAdventureModeMaps::get_disabledMapCounter()
{
	return si_disabledMapCounter;
}



/**
* This method returns an formatted string, which contain all Output
* of the AM-items of the current map
*
*	@return string		formatted output with all needed information
*
*/
string HWLAdventureModeMaps::get_AllAMItemsForOutput()
{
	string s_output = "\n ";

	for (int i = 0; i < this->amm_MaxItemsPerMap; i++)
	{
		s_output = s_output + this->vsp_hwlami_items[i]->get_AMItemForOutput() + "\n ";
	}

	return s_output;
}

/**
* This method returns an formatted string, which contain all needed member-values
*
*	@var bool	b_with_item_output		TRUE: show output of items, FALSE: not
*
*	@return string		formatted output with all needed member-values
*
*/
string HWLAdventureModeMaps::get_AMMapForOutput(bool b_with_item_output)
{
	string s_output = "";

	if (b_with_item_output)
	{
		s_output = s_output + "Map-ID: " + to_string(this->i_id) + " | Name: " + this->s_name + "\n"
			+ "Items: \n" + this->get_AllAMItemsForOutput() + "\n";
	}
	else
	{
		s_output = s_output + "Map-ID: " + to_string(this->i_id) + " | Name: " + this->s_name + "\n";
	}

	return s_output;
}
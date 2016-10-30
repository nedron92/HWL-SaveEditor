//needed for including in a MFC-App
#ifdef __MFC__
#include "../gui/stdafx.h" 
#endif // __MFC__

//include the correct header-file
#include "HWLGeneral.h"

//use the project-namespace
using namespace HWLSaveEdit;

//offsets definitions
/* @var rubyOffset				the offset-begin for rubies */
const int HWLGeneral::rubyOffset = 0xde;

/* @var rubyOffsetLength		length for ruby-offset */
const int HWLGeneral::rubyOffsetLength = 0x3;


/* @var unlockIngameSmithyOffset			the offset-begin for unlocking-state of the ingame-smithy */
const int HWLGeneral::unlockIngameSmithyOffset = 0xD2;

/* @var unlockIngameSmithyOffsetLength		the offset-length for unlocking-state of the ingame-smithy */
const int HWLGeneral::unlockIngameSmithyOffsetLength = 1;

/* @var unlockIngameSmithyOffsetPart		offset-part where the unlocking-state of the ingame-smithy is located */
const int HWLGeneral::unlockIngameSmithyOffsetPart = 2;


/* @var unlockAllNormalWeaponsOffset			the offset-begin for unlocking-state of all normal-weapons (for MS-Skill 1) */
const int HWLGeneral::unlockAllNormalWeaponsOffset = 0xD4;

/* @var unlockAllNormalWeaponsOffsetLength		the offset-length for unlocking-state of all normal-weapons  */
const int HWLGeneral::unlockAllNormalWeaponsOffsetLength = 1;


/* @var unlockAllPlusWeaponsOffset				the offset-begin for unlocking-state of all plus-weapons (for MS-Skill 2) */
const int HWLGeneral::unlockAllPlusWeaponsOffset = 0xD2;

/* @var unlockAllPlusWeaponsOffsetLength		the offset-length for unlocking-state of all plus-weapons  */
const int HWLGeneral::unlockAllPlusWeaponsOffsetLength = 1;

/* @var unlockAllPlusWeaponsOffsetPart			offset-part where the unlocking-state of all plus-weapons is located */
const int HWLGeneral::unlockAllPlusWeaponsOffsetPart = 1;


/* @var unlockAllMaterialsOffsets				offset-begins for all material-found-flags */
const vector<int> HWLGeneral::unlockAllMaterialsOffsets =
{
	0x1A24, //first part, Metal Plate -> Impa's Hair Band
	0x1A28, //second part, Ganondorf's Gauntlet -> Wizzro's Ring
	0x1A2C, //third part, Link's Scarf -> Keaton Mask
	0x1A30, //fourth part, Tingle's Watch -> King Daphnes's Crown
};

/* @var unlockAllMaterialsOffsetsLength			offset-length of all material-found-flag-offsets */
const int HWLGeneral::unlockAllMaterialsOffsetsLength = 0x4;


/* @var unlockIngameSmithyValue			value to unlock the ingame-smithy */
const int HWLGeneral::unlockIngameSmithyValue = 0xF;

/* @var unlockAllPlusWeaponsValue		value to set the unlock-state of all plus-weapons to TRUE */
const int HWLGeneral::unlockAllPlusWeaponsValue = 0xF;

/* @var unlockAllPlusWeaponsValueMin	min-value to set the unlock-state of all plus-weapons to TRUE */
const int HWLGeneral::unlockAllPlusWeaponsValueMin = 0x6;

/* @var unlockAllMaterialsMinValue			value for first-to-third part to set materials to "Not-found" */
const unsigned int HWLGeneral::unlockAllMaterialsMinValue = 0x00FFFFFF;

/* @var unlockAllMaterialsMaxValue			max-value for first-to-third part to set all materials to "found" */
const unsigned int HWLGeneral::unlockAllMaterialsMaxValue = 0xFFFFFFFF;

/* @var unlockAllMaterialsMinValueLastOffset		value for fourth part to set materials to "Not-found"  */
const int HWLGeneral::unlockAllMaterialsMinValueLastOffset = 0x0F;

/* @var unlockAllMaterialsMaxValueLastOffset		max-value for fourth part to set all materials to "found"  */
const int HWLGeneral::unlockAllMaterialsMaxValueLastOffset = 0x3F;


/* @var savefileGameVersionOffset				the offset-begin for get the current savefile-game-version */
const int HWLGeneral::savefileGameVersionOffset = 0xD3;

/* @var savefileGameVersionOffsetLength			offset-length for the current-savefie-game-version offset */
const int HWLGeneral::savefileGameVersionOffsetLength = 0x1;

/* @var savefileGameVersionOffsetPart			offset-part where the savefile-game-version is located */
const int HWLGeneral::savefileGameVersionOffsetPart = 2;

/* @var vs_version_strings		vector, which hold the version strings for calculation  */
const vector<string> HWLGeneral::vs_game_version_strings =
{
	"1.0.0", //X0, offset D3
	"1.2.0", //X1, offset D3
	"1.3.0", //X2, offset D3
	"1.3.0", //X3, offset D3
	"1.4.0", //X4, offset D3
	"1.4.0", //X5, offset D3
	"1.4.0", //X6, offset D3
	"1.4.0", //X7, offset D3
	"1.5.0", //X8, offset D3
	"1.5.0", //X9, offset D3
	"1.5.0", //XA, offset D3
	"1.5.0", //XB, offset D3
	"1.5.0", //XC, offset D3
	"1.5.0", //XD, offset D3
	"1.5.0", //XE, offset D3
	"1.5.0", //XF, offset D3
};

/* @var vi_game_dlc_identifier_offsets_begin		vector, which hold the offset-begins of the DLC-Content */
const vector<int> HWLGeneral::vi_game_dlc_identifier_offsets_begin =
{
	0x25D5, //Check for 'Master Wind Waker DLC' BEGIN
	0X2F11E, //Check for 'Link's Awakening DLC' BEGIN
	0x2F14E, //Check for 'Phantom Hourglass and Spirit Tracks DLC' BEGIN
	0x0, //Check for 'A Link Between Worlds DLC' BEGIN
};

/* @var vi_game_dlc_identifier_offsets_end		vector, which hold the offset-ends of the DLC-Content */
const vector<int> HWLGeneral::vi_game_dlc_identifier_offsets_end =
{
	0x25DD, //Check for 'Master Wind Waker DLC' END
	0x2F121, //Check for 'Link's Awakening DLC' END
	0x2F151, //Check for 'Phantom Hourglass and Spirit Tracks DLC' END
	0x0, //Check for 'A Link Between Worlds DLC' END
};

/* @var vs_game_dlc_hexstring_standard_values		vector, which hold the dlc-default-hexStrings (if they NOT installed) */
const vector<string> HWLGeneral::vs_game_dlc_default_hexStrings =
{
	"ffffffffffffffffff", //Default-hexString if NOT 'Master Wind Waker DLC' installed
	"ffff00ff", //Default-hexString if NOT 'Link's Awakening DLC' installed
	"ffff00ff", //Default-hexString if NOT 'Phantom Hourglass and Spirit Tracks DLC' installed
	"00000000", //Default-hexString if NOT 'A Link Between Worlds DLC installed
};

/* @var vs_game_dlc_strings		vector, which hold the dlc-strings  */
const vector<string> HWLGeneral::vs_game_dlc_strings =
{
	"Master Wind Waker DLC",
	"Link's Awakening DLC",
	"Phantom Hourglass and Spirit Tracks DLC",
	"A Link Between Worlds DLC",
};



//public members
/* @var rubyMax			max value for rubies */
const int HWLGeneral::rubyMax = 9999999;

/* @var fairiesMax		maximal count of fairies*/
const int HWLGeneral::fairiesMax = 14;



/**
* Only the initialization of the normal-constructor
*/
HWLGeneral::HWLGeneral()
{
	//set or calculate all needed members
	s_savefile_game_version = this->calc_current_savefile_game_version();

	vb_game_dlc_installed = this->calc_installed_dlcs();

	this->i_rubies = this->calc_rubies();
	this->b_unlocked_smithy = this->calc_unlocked_smithy_state();
	this->b_unlocked_all_normal_weapons = this->calc_unlocked_normal_weapons_state();
	this->b_unlocked_all_plus_weapons = this->calc_unlocked_plus_weapons_state();
	this->b_unlocked_all_materials = this->calc_unlock_all_materials_state();
}

/**
* Only the initialization of the normal-destructor
*/
HWLGeneral::~HWLGeneral()
{
}


/**
* This method calculate the current savefile-game
* version
*
*	@return string		the current savefile-game-version
*
*/
string HWLGeneral::calc_current_savefile_game_version()
{
	//declare needed variables
	string s_savefile_game_version, s_savefile_game_version_tmp;
	int i_savefile_game_version_offset = this->savefileGameVersionOffset;

	//get the current savefile-version as an hexString
	s_savefile_game_version = this->getHexStringFromFileContent(i_savefile_game_version_offset, this->savefileGameVersionOffsetLength);

	//we need only one part of the offset, get it here
	s_savefile_game_version_tmp = s_savefile_game_version[this->savefileGameVersionOffsetPart - 1];

	//return the current version based on the value and the vector-index
	return (this->vs_game_version_strings[this->HexStringToInt(s_savefile_game_version_tmp)]);
}

/**
* This method calculate the current installed DLCs
*
*	@return vector<bool>		the installed-state of each known DLC
*
*/
vector<bool> HWLGeneral::calc_installed_dlcs()
{
	//declare needed variables, fucntion-global-scope
	vector<bool> vb_savefile_installed_dlcs;

	//define a standard-FALSE-state of each known DLC
	for (int i = 0; i < this->vs_game_dlc_strings.size(); i++)
		vb_savefile_installed_dlcs.push_back(false);

	//iterate over all known DLCs and get there state
	for (int i = 0; i < this->vs_game_dlc_strings.size(); i++)
	{
		//get offset begin, end and the length
		string s_savefile_installed_dlc;
		int i_savefile_installed_dlc_offset_begin = this->vi_game_dlc_identifier_offsets_begin[i];
		int i_savefile_installed_dlc_offset_end = this->vi_game_dlc_identifier_offsets_end[i];
		int i_savefile_installed_dlc_offset_length = (i_savefile_installed_dlc_offset_end - i_savefile_installed_dlc_offset_begin) + 1;

		//if the offset begin/or end is 0x00, then the DLC is not known yet
		if (i_savefile_installed_dlc_offset_begin == 0x0)
			continue;

		//get the complete hexString
		s_savefile_installed_dlc = this->getHexStringFromFileContent(i_savefile_installed_dlc_offset_begin, i_savefile_installed_dlc_offset_length, true);

		//check if the hexString NOT MATCH the default hexString.
		//TRUE: it is installed, FALSE otherwise
		if (s_savefile_installed_dlc != this->vs_game_dlc_default_hexStrings[i])
			vb_savefile_installed_dlcs[i] = true;
		else
			continue;
	}

	//return the current install-state of all DLCs
	return vb_savefile_installed_dlcs;
}

/**
* This method calculate the current ruby-value
*
*	@return int		the current rubies
*
*/
int HWLGeneral::calc_rubies()
{
	//declare needed variables
	string s_rubies;
	int i_ruby_offset = this->rubyOffset;

	//get the current ruby-value as an hexString
	s_rubies = this->getHexStringFromFileContent(i_ruby_offset, this->rubyOffsetLength);

	//return the converted ruby-value
	return this->HexStringToInt(s_rubies);
}

/**
* This method calculate the current state, if
*  the ingame smithy is unlocked
*
*	@return bool		the unlock-state
*
*/
bool HWLGeneral::calc_unlocked_smithy_state()
{
	//declare needed variables
	string s_unlock_state, s_unlock_state_tmp;
	int i_unlock_state_offset = this->unlockIngameSmithyOffset;

	//get the current unlock-state-value as an hexString
	s_unlock_state = this->getHexStringFromFileContent(i_unlock_state_offset, this->unlockIngameSmithyOffsetLength);

	//we need only one part of the offset, get it here
	s_unlock_state_tmp = s_unlock_state[this->unlockIngameSmithyOffsetPart - 1];

	//return the true or false, based on the converted unlock-state value
	if (this->HexStringToInt(s_unlock_state_tmp) >= this->unlockIngameSmithyValue)
		return true;
	else
		return false;
}

/**
* This method calculate the current state, if
*  all normal weapons are unlocked (only the state itself)
*
*	@return bool		the unlock-state
*
*/
bool HWLGeneral::calc_unlocked_normal_weapons_state()
{
	//declare needed variables
	string s_unlock_state;
	int i_unlock_state_offset = this->unlockAllNormalWeaponsOffset;

	//get the current unlock-state-value as an hexString
	s_unlock_state = this->getHexStringFromFileContent(i_unlock_state_offset, this->unlockAllNormalWeaponsOffsetLength);

	//return the true or false, based on the converted unlock-state value
	if (this->HexStringToInt(s_unlock_state) >= 1)
		return true;
	else
		return false;
}

/**
* This method calculate the current state, if
*  all plus-weapons are unlocked (only the state itself)
*
*	@return bool		the unlock-state
*
*/
bool HWLGeneral::calc_unlocked_plus_weapons_state()
{
	//declare needed variables
	string s_unlock_state, s_unlock_state_tmp;
	int i_unlock_state_offset = this->unlockAllPlusWeaponsOffset;

	//get the current unlock-state-value as an hexString
	s_unlock_state = this->getHexStringFromFileContent(i_unlock_state_offset, this->unlockAllPlusWeaponsOffsetLength);

	//we need only one part of the offset, get it here
	s_unlock_state_tmp = s_unlock_state[this->unlockAllPlusWeaponsOffsetPart - 1];

	//return the true or false, based on the converted unlock-state value
	if (this->HexStringToInt(s_unlock_state_tmp) >= this->unlockAllPlusWeaponsValueMin)
		return true;
	else
		return false;
}

/**
* This method calculate the current state, if
*  all materials were already found
*
*	@return bool		the unlock-state
*
*/
bool HWLGeneral::calc_unlock_all_materials_state()
{
	//declare needed variables
	string s_unlock_state;
	int i_bool_counter = 0;

	//iterate over all unlock-materials-offsets we have
	for (int i = 0; i < this->unlockAllMaterialsOffsets.size(); i++)
	{
		int i_unlock_state_offset = this->unlockAllMaterialsOffsets[i];

		//get the current unlock-state-value as an hexString
		s_unlock_state = this->getHexStringFromFileContent(i_unlock_state_offset, this->unlockAllMaterialsOffsetsLength);

		//if we have not the last flag-offset, then proof with the MaxValue, else proof
		//with the MaxValue for the last Offset
		if (i != (this->unlockAllMaterialsOffsets.size() - 1))
		{
			if (this->HexStringToInt(s_unlock_state) == this->unlockAllMaterialsMaxValue)
				i_bool_counter++;
			else
				i_bool_counter--;
		}
		else{
			if (this->HexStringToInt(s_unlock_state) >= this->unlockAllMaterialsMaxValueLastOffset)
				i_bool_counter++;
			else
				i_bool_counter--;
		}
	}

	//return the calculated unlock-state
	if (i_bool_counter == this->unlockAllMaterialsOffsets.size())
		return true;
	else
		return false;
}



/**
* This method save the current ruby-value to the file-content holder
*
*/
void HWLGeneral::save_rubies()
{
	//declare/define needed variables
	int i_ruby_tmp = this->i_rubies; //tmp variable of current ruby-value
	string s_rubies; //needed for hold the hex-value
	int i_ruby_offset = this->rubyOffset; //the offset

	//convert the integer ruby-value to hex-value and save to string, also added
	//missed zeros
	s_rubies = this->intToHexString(i_ruby_tmp, false);
	this->addZeroToHexString(s_rubies, this->rubyOffsetLength * 2);

	//set the current hex-value to the file-content holder, based on offset
	this->setHexStringToFileContent(s_rubies, i_ruby_offset);
}

/**
* This method save the current unlock-state-value of the
*  ingame smithy to the file-content holder
*
*/
void HWLGeneral::save_unlocked_smithy_state()
{
	//declare/define needed variables
	int i_unlock_state;
	string s_unlock_state, s_unlock_state_tmp;
	int i_unlock_state_offset = this->unlockIngameSmithyOffset;

	//set the current unlock-state-value (integer) to val to unlock or 0,
	//based on the aquivalent boolean-member
	if (this->b_unlocked_smithy)
		i_unlock_state = this->unlockIngameSmithyValue;
	else
		i_unlock_state = 0;

	//get the old/current hexValue of the unlock-offset, to only change the
	//correct part of it and not the hole offset itself
	s_unlock_state = this->getHexStringFromFileContent(i_unlock_state_offset, this->unlockIngameSmithyOffsetLength);

	//convert the integer unlock-state-value to hex-value and save to string
	s_unlock_state_tmp = (this->intToHexString(i_unlock_state, false))[1];

	//change the correct part of the offset to the new value
	s_unlock_state.replace(this->unlockIngameSmithyOffsetPart - 1, 1, s_unlock_state_tmp);

	//set the current hex-value to the file-content holder, based on offset
	this->setHexStringToFileContent(s_unlock_state, i_unlock_state_offset);
}

/**
* This method save the current unlock-state-value of the
*  normal weapons to the file-content holder
*
*/
void HWLGeneral::save_unlocked_normal_weapons_state()
{
	//declare/define needed variables
	int i_unlock_state;
	string s_unlock_state;
	int i_unlock_state_offset = this->unlockAllNormalWeaponsOffset;

	//set the current unlock-state-value (integer) to 0 or 1,
	//based on the aquivalent boolean-member
	if (this->b_unlocked_all_normal_weapons)
		i_unlock_state = 1;
	else
		i_unlock_state = 0;

	//convert the integer unlock-state-value to hex-value and save to string, also added
	//missed zeros
	s_unlock_state = this->intToHexString(i_unlock_state, false);
	this->addZeroToHexString(s_unlock_state, this->unlockAllNormalWeaponsOffsetLength * 2);

	//set the current hex-value to the file-content holder, based on offset
	this->setHexStringToFileContent(s_unlock_state, i_unlock_state_offset);
}

/**
* This method save the current unlock-state-value of the
*  plus-weapons to the file-content holder
*
*/
void HWLGeneral::save_unlocked_plus_weapons_state()
{
	//declare/define needed variables
	int i_unlock_state;
	string s_unlock_state, s_unlock_state_tmp;
	int i_unlock_state_offset = this->unlockAllPlusWeaponsOffset;

	//set the current unlock-state-value (integer) to val to unlock or min-val-1,
	//based on the aquivalent boolean-member
	if (this->b_unlocked_all_plus_weapons)
		i_unlock_state = this->unlockAllPlusWeaponsValue;
	else
		i_unlock_state = (this->unlockAllPlusWeaponsValueMin - 1);

	//get the old/current hexValue of the unlock-offset, to only change the
	//correct part of it and not the hole offset itself
	s_unlock_state = this->getHexStringFromFileContent(i_unlock_state_offset, this->unlockAllPlusWeaponsOffsetLength);

	//convert the integer unlock-state-value to hex-value and save to string
	s_unlock_state_tmp = (this->intToHexString(i_unlock_state, false))[1];

	//change the correct part of the offset to the new value
	s_unlock_state.replace(this->unlockAllPlusWeaponsOffsetPart - 1, 1, s_unlock_state_tmp);

	//set the current hex-value to the file-content holder, based on offset
	this->setHexStringToFileContent(s_unlock_state, i_unlock_state_offset);
}

/**
* This method save the current unlock-state-value of the
*  materials to the file-content holder
*
*/
void HWLGeneral::save_unlock_all_materials_state()
{
	//declare/define needed variables
	unsigned int i_unlock_state;
	string s_unlock_state;

	//iterate over all unlock-materials-offsets we have
	for (int i = 0; i < this->unlockAllMaterialsOffsets.size(); i++)
	{
		int i_unlock_state_offset = this->unlockAllMaterialsOffsets[i];

		//set the current unlock-state-value (integer) to max or min,
		//based on the aquivalent boolean-member
		if (this->b_unlocked_all_materials)
		{
			//if we have not the last flag-offset, then set i_unlock_state to MaxValue, else set
			//i_unlock_state to MaxValue for the last Offset
			if (i != (this->unlockAllMaterialsOffsets.size() - 1))
			{
				i_unlock_state = this->unlockAllMaterialsMaxValue;
			}
			else
			{
				i_unlock_state = this->unlockAllMaterialsMaxValueLastOffset;
			}
		}
		else
		{
			//if we have not the last flag-offset, then set i_unlock_state to MinValue, else set
			//i_unlock_state to MinValue for the last Offset
			if (i != (this->unlockAllMaterialsOffsets.size() - 1))
			{
				i_unlock_state = this->unlockAllMaterialsMinValue;
			}
			else
			{
				i_unlock_state = this->unlockAllMaterialsMinValueLastOffset;
			}
		}

		//convert the integer unlock-state-value to hex-value and save to string, also added
		//missed zeros
		s_unlock_state = this->intToHexString(i_unlock_state, false);
		this->addZeroToHexString(s_unlock_state, this->unlockAllMaterialsOffsetsLength * 2);

		//set the current hex-value to the file-content holder, based on offset
		this->setHexStringToFileContent(s_unlock_state, i_unlock_state_offset);
	}
}



/**
* Getter for the current game-version of the savefile
*
*	@return string		the current game-version of the savefile
+
*/
string HWLGeneral::get_current_savefile_game_version()
{
	return this->s_savefile_game_version;
}

/**
* Getter for max-Value of available DLCs
*
*	@return int		max-Value of known DLCs
+
*/
int HWLGeneral::get_dlc_max_available_dlcs()
{
	return (this->vs_game_dlc_strings.size());
}

/**
* Getter for a int-Value of installed DLCs
*
*	@return int		Value of installed DLCs
*
*/
int HWLGeneral::get_dlc_installed_dlcs_value()
{
	int i_dlc_installed_counter = 0;
	for (int i = 0; i < this->vs_game_dlc_strings.size(); i++)
	{
		if (this->vb_game_dlc_installed[i])
			i_dlc_installed_counter++;
	}

	return i_dlc_installed_counter;
}

/**
* Getter for install-state of given DLC-ID
*
*	@return bool		state, if given DLC is installed
+
*/
bool HWLGeneral::get_dlc_installed_state(int i_dlc_id)
{
	return (this->vb_game_dlc_installed[i_dlc_id]);
}

/**
* Getter for print-name of given DLC-ID
*
*	@return string		print-name of given DLC
+
*/
string HWLGeneral::get_dlc_name(int i_dlc_id)
{
	return (this->vs_game_dlc_strings[i_dlc_id]);
}

/**
* Getter for the current ruby-value
*
*	@return int		the current ruby-value
+
*/
int HWLGeneral::get_rubies()
{
	return this->i_rubies;
}

/**
* Getter for the current unlocked-smithy-state-value
*
*	@return bool		the unlocked-smithy-state
*
*/
bool HWLGeneral::get_unlocked_smithy_state()
{
	return this->b_unlocked_smithy;
}

/**
* Getter for the current unlocked-normal-weapons-state-value
*
*	@return bool		the unlocked-normal-weapons-state
*
*/
bool HWLGeneral::get_unlocked_normal_weapons_state()
{
	return this->b_unlocked_all_normal_weapons;
}

/**
* Getter for the current unlocked-plus-weapons-state-value
*
*	@return bool		the unlocked-plus-weapons-state
*
*/
bool HWLGeneral::get_unlocked_plus_weapons_state()
{
	return this->b_unlocked_all_plus_weapons;
}

/**
* Getter for the current unlocked-all-materials-state-value
*
*	@return bool		the unlocked-all-materials-state
*
*/
bool HWLGeneral::get_unlocked_all_materials_state()
{
	return this->b_unlocked_all_materials;
}



/**
* Setter for the ruby-value
*
*	@var int	i_rubies		ruby-value to set
*
*/
void HWLGeneral::set_rubies(int i_rubies)
{
	if (i_rubies < 0)
		i_rubies = 0;
	else if (i_rubies > this->rubyMax)
		i_rubies = rubyMax;

	this->i_rubies = i_rubies;
}

/**
* Setter for the unlocked-smithy-state-value
*
*	@var bool	b_unlocked_smithy		unlocked-smithy-state-value
*
*/
void HWLGeneral::set_unlocked_smithy_state(bool b_unlocked_smithy)
{
	this->b_unlocked_smithy = b_unlocked_smithy;
}

/**
* Setter for the unlocked-normal-weapons-state-value
*
*	@var bool	b_unlocked_all_normal_weapons		unlocked-normal-weapons-state-value
*
*/
void HWLGeneral::set_unlocked_normal_weapons_state(bool b_unlocked_all_normal_weapons)
{
	this->b_unlocked_all_normal_weapons = b_unlocked_all_normal_weapons;
}

/**
* Setter for the unlocked-normal-plus-state-value
*
*	@var bool	b_unlocked_all_plus_weapons		unlocked-plus-weapons-state-value
*
*/
void HWLGeneral::set_unlocked_plus_weapons_state(bool b_unlocked_all_plus_weapons)
{
	this->b_unlocked_all_plus_weapons = b_unlocked_all_plus_weapons;
}

/**
* Setter for the unlocked-all-materials-state-value
*
*	@var bool	b_unlocked_all_materials		unlocked-all-materials-state-value
*
*/
void HWLGeneral::set_unlocked_all_materials_state(bool b_unlocked_all_materials)
{
	this->b_unlocked_all_materials = b_unlocked_all_materials;
}



/**
* This method returns an formatted string, which contain a listing of installed DLCs
*
*	@return string		formatted output with installed DLCs
*
*/
string HWLGeneral::get_DLCsForOutput()
{
	string s_output = "\n";

	for (int i = 0; i < this->vs_game_dlc_strings.size(); i++)
	{
		if (!this->vb_game_dlc_installed[i])
			continue;
		else
			s_output = s_output + "  " + this->vs_game_dlc_strings[i] + "\n";
	}

	if (s_output == "\n")
		s_output = "None DLC installed";

	return s_output;
}

/**
* This method returns an formatted string, which contain all needed member-values
*
*	@return string		formatted output with all needed member-values
*
*/
string HWLGeneral::get_GeneralThingsForOutput()
{
	string s_begin = "General-things: \n";

	string s_output = s_begin
		+ " Savefile-Game-Version: " + this->s_savefile_game_version + "\n"
		+ " Installed DLCs: " + this->get_DLCsForOutput() + "\n"
		+ " Unlock-State: Ingame-Smithy: " + to_string(this->b_unlocked_smithy) + "\n"
		+ " Unlock-State: All normal weapons found  : " + to_string(this->b_unlocked_all_normal_weapons) + "\n"
		+ " Unlock-State: All 'plus' weapons found  : " + to_string(this->b_unlocked_all_plus_weapons) + "\n"
		+ " Unlock-State: All materials found: " + to_string(this->b_unlocked_all_materials) + "\n";

	return s_output;
}



/**
* This method is a wrapper for all known save-methods of the class
*
*/
void HWLGeneral::save_General()
{
	this->save_rubies();
	this->save_unlocked_smithy_state();
	this->save_unlocked_normal_weapons_state();
	this->save_unlocked_plus_weapons_state();
	this->save_unlock_all_materials_state();
}
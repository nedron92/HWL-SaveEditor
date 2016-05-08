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


/* @var unlockAllNormalWeaponsOffset			the offset-begin for unlocking-state of all normal-weapons (for MW-Skill 1) */
const int HWLGeneral::unlockAllNormalWeaponsOffset = 0xD4;

/* @var unlockAllNormalWeaponsOffsetLength		the offset-length for unlocking-state of all normal-weapons  */
const int HWLGeneral::unlockAllNormalWeaponsOffsetLength = 1;


/* @var unlockAllPlusWeaponsOffset				the offset-begin for unlocking-state of all plus-weapons (for MW-Skill 2) */
const int HWLGeneral::unlockAllPlusWeaponsOffset = 0xD2;

/* @var unlockAllPlusWeaponsOffsetLength		the offset-length for unlocking-state of all plus-weapons  */
const int HWLGeneral::unlockAllPlusWeaponsOffsetLength = 1;

/* @var unlockAllPlusWeaponsOffsetPart			offset-part where the unlocking-state of all plus-weapons is located */
const int HWLGeneral::unlockAllPlusWeaponsOffsetPart = 1;


/* @var unlockIngameSmithyValue			value to unlock the ingame-smithy */
const int HWLGeneral::unlockIngameSmithyValue = 0xF;

/* @var unlockAllPlusWeaponsValue		value to set the unlock-state of all plus-weapons to TRUE */
const int HWLGeneral::unlockAllPlusWeaponsValue = 0xF;

/* @var unlockAllPlusWeaponsValueMin	min-value to set the unlock-state of all plus-weapons to TRUE */
const int HWLGeneral::unlockAllPlusWeaponsValueMin = 0x6;


//public members
/* @var rubyMax			max value for rubies */
const int HWLGeneral::rubyMax = 9999999;

/* @var fairiesMax		maximal count of fairies*/
const int HWLGeneral::fairiesMax = 10;



/**
* Only the initialization of the normal-constructor
*/
HWLGeneral::HWLGeneral()
{
	this->i_rubies = this->calc_rubies();
	this->b_unlocked_smithy = this->calc_unlocked_smithy_state();
	this->b_unlocked_all_normal_weapons = this->calc_unlocked_normal_weapons_state();
	this->b_unlocked_all_plus_weapons = this->calc_unlocked_plus_weapons_state();

}

/**
* Only the initialization of the normal-destructor
*/
HWLGeneral::~HWLGeneral()
{
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
	if (this->b_unlocked_smithy)
		i_unlock_state = this->unlockAllPlusWeaponsValue;
	else
		i_unlock_state = (this->unlockAllPlusWeaponsValueMin-1);

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
* This method returns an formatted string, which contain all needed member-values
*
*	@return string		formatted output with all needed member-values
*
*/
string HWLGeneral::get_GeneralThingsForOutput()
{
	string s_begin = "General-things: \n";

	string s_output = s_begin
		+ " Unlock-State: Ingame-Smithy: " + to_string(this->b_unlocked_smithy) + "\n"
		+ " Unlock-State: All normal weapons found  : " + to_string(this->b_unlocked_all_normal_weapons) + "\n"
		+ " Unlock-State: All 'plus' weapons found  : " + to_string(this->b_unlocked_all_plus_weapons) + "\n";

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
}
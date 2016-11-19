//needed for including in a MFC-App
#ifdef __MFC__
#include "../gui/stdafx.h" 
#endif // __MFC__

//include the correct header-file
#include "HWLPlayer.h"

//use the project-namespace
using namespace HWLSaveEdit;

/* @var si_disabledPlayerCounter	Counter which holds the current value of disabled Characters */
int HWLPlayer::si_disabledPlayerCounter = 0;


/* @var playerLVLOffsetLength		offset length of the characters LVL */
const int HWLPlayer::playerLVLOffsetLength = 0x1;

/* @var playerEXPOffsetLength		offset length of the characters EXP */
const int HWLPlayer::playerEXPOffsetLength = 0x4;

/* @var playerATKOffsetLength		offset length of the characters ATK */
const int HWLPlayer::playerATKOffsetLength = 0x2;

/* @var playerHeartsOffsetLength		offset length of the characters Hearts */
const int HWLPlayer::playerHeartsOffsetLength = 0x1;

/* @var playerIsUnlockOffsetLength	offset length of the characters Unlock-State */
const int HWLPlayer::playerIsUnlockOffsetLength = 0x1;

/* @var playerCanUseAttackBadgesOffsetLength	offset length of the characters Attack-Badges using state */
const int HWLPlayer::playerCanUseAttackBadgesOffsetLength = 0x1;


/* @var playerLVLOffsetDiff			offset-diff from begin of the characters LVL */
const int HWLPlayer::playerLVLOffsetDiff = 0x20;

/* @var playerEXPOffsetDiff			offset-diff from begin of the characters EXP */
const int HWLPlayer::playerEXPOffsetDiff = 0x18;

/* @var playerATKOffsetDiff			offset-diff from begin of the characters ATK */
const int HWLPlayer::playerATKOffsetDiff = 0x12;

/* @var playerHeartsOffsetDiff			offset-diff from begin of the characters Hearts */
const int HWLPlayer::playerHeartsOffsetDiff = 0x22;

/* @var playerIsUnlockOffsetDiff	offset-diff from begin of the characters Unlock-State */
const int HWLPlayer::playerIsUnlockOffsetDiff = 0x10;

/* @var playerCanUseAttackBadgesOffsetDiff	offset-diff from begin of the characters Attack-Badges using state */
const int HWLPlayer::playerCanUseAttackBadgesOffsetDiff = 0x1E;


/* @var vs_players					vector for holding all names of the characters */
const vector<string> HWLPlayer::vs_players =
{
	"Link",
	"Zelda",
	"Sheik",
	"Impa",
	"Ganon",
	"Darunia",
	"Ruto",
	"Agitha",
	"Imp Midna",
	"Fi",
	"Ghirahim",
	"Zant",
	"Lana",
	"Cia",
	"Volga",
	"Wizzro",
	"Twili Midna",
	"Young Link",
	"Tingle",
	"???_1",
	"???_2",
	"Linkle",
	"Skull Kid",
	"Toon Link",
	"Tetra",
	"King Daphnes",
	"Medli", //Update 1.3.0 (no LVL4-Weapon without any DLC)
	"Marin", //only 2nd DLC: Link's Awakening DLC
	"Toon Zelda" //only 3rd DLC: Phantom Hourglass and Spirit Tracks DLC
};

/* @var playerLVLMax				maximal-values of the characters LVL */
const vector<int> HWLPlayer::playerLVLMax =
{
	99,  //till Update 1.3.0
	150, //Update 1.4.0
	200  //Update 1.5.0 
};

/* @var playerEXPMax				maximal-values of the characters EXP */
const vector<int> HWLPlayer::playerEXPMax =
{
	3178257, //till Update 1.3.0
	6337707, //Update 1.4.0
	9435207  //Update 1.5.0 
};

/* @var playerATKMax				maximal-values of the characters ATK */
const vector<int> HWLPlayer::playerATKMax =
{
	999, //till Update 1.4.0
	1300 //Update 1.5.0
};

/* @var playerHeartsMax				maximal-values of the characters hearts*/
const vector<int> HWLPlayer::playerHeartsMax =
{
	18, //till Update 1.3.0
	23, //Update 1.4.0
	25  //Update 1.5.0
};


/* @var playerIsUnlockMax			maximal-value of the characters isUnlock-State*/
const int HWLPlayer::playerIsUnlockMax = 0xF;

/* @var playerWeaponSlotsMax		maximal-value of the characters Weapons, which it can take */
const int HWLPlayer::playerWeaponSlotsMax = 10;



/**
* Only the initialization of the normal-constructor
*/
HWLPlayer::HWLPlayer(int i_id, string s_name, int i_offset, int i_weapon_type_count)
{
	//Reset static values if new saveFile is opened
	if (this->b_isNewSaveFile)
		this->si_disabledPlayerCounter = 0;

	//set or calculate all needed members
	this->i_id = i_id;
	this->s_name = s_name;
	this->i_offset = i_offset;
	this->i_weapon_type_count = i_weapon_type_count;
	this->i_lvl = this->calc_players_lvl();
	this->i_exp = this->calc_players_exp();
	this->i_atk = this->calc_players_atk();
	this->i_hearts = this->calc_players_hearts();
	this->b_isUnlock = this->calc_players_isUnlockState();
	this->b_canUseAttackBadges = this->calc_players_canUseAttackBadgesState();
	this->b_isDisabled = false;
	this->vi_weapon_disabled_ids;
}

/**
* Only the initialization of the normal-destructor
*/
HWLPlayer::~HWLPlayer()
{
}



/**
* This method calculates the current characters LVL-value
*
*	@return int		the current lvl
*
*/
int HWLPlayer::calc_players_lvl()
{
	//declare/define needed variables
	string s_playerLVL;
	int i_player_lvl_offset = this->i_offset + this->playerLVLOffsetDiff;

	//get hex-value from the file-content holder and convert it to int
	//increment players-Level value, because it is save as LVL-Shown  - 1
	s_playerLVL = this->getHexStringFromFileContent(i_player_lvl_offset, this->playerLVLOffsetLength);
	int i_playerLVL = this->HexStringToInt(s_playerLVL) + 1;

	//return the current int-value
	return i_playerLVL;
}

/**
* This method calculates the current characters EXP-value
*
*	@return int		the current exp
*
*/
int HWLPlayer::calc_players_exp()
{
	//declare/define needed variables
	string s_playerEXP;
	int i_player_exp_offset = this->i_offset + this->playerEXPOffsetDiff;

	//get hex-value from the file-content holder and convert it to int
	s_playerEXP = this->getHexStringFromFileContent(i_player_exp_offset, this->playerEXPOffsetLength);
	int i_playerEXP = this->HexStringToInt(s_playerEXP);

	//return the current int-value
	return i_playerEXP;
}

/**
* This method calculates the current characters ATK-value
*
*	@return int		the current atk
*
*/
int HWLPlayer::calc_players_atk()
{
	//declare/define needed variables
	string s_playerATK;
	int i_player_atk_offset = this->i_offset + this->playerATKOffsetDiff;

	//get hex-value from the file-content holder and convert it to int
	s_playerATK = this->getHexStringFromFileContent(i_player_atk_offset, this->playerATKOffsetLength);
	int i_playerATK = this->HexStringToInt(s_playerATK);

	//return the current int-value
	return i_playerATK;
}

/**
* This method calculates the current characters Hearts-value
*
*	@return int		the current hearts
*
*/
int HWLPlayer::calc_players_hearts()
{
	//declare/define needed variables
	string s_playerHearts;
	int i_player_hearts_offset = this->i_offset + this->playerHeartsOffsetDiff;

	//get hex-value from the file-content holder and convert it to int
	s_playerHearts = this->getHexStringFromFileContent(i_player_hearts_offset, this->playerHeartsOffsetLength);
	int i_playerHearts = this->HexStringToInt(s_playerHearts);

	//return the current int-value
	return i_playerHearts;
}

/**
* This method calculates the current characters Unlock-State
*
*	@return bool		the current Unlock-State
*
*/
bool HWLPlayer::calc_players_isUnlockState()
{
	//declare/define needed variables
	string s_playerIsUnlock;
	int i_player_isUnlock_offset = this->i_offset + this->playerIsUnlockOffsetDiff;

	//get hex-value from the file-content holder and convert it to int
	s_playerIsUnlock = this->getHexStringFromFileContent(i_player_isUnlock_offset, this->playerIsUnlockOffsetLength);
	int i_playerIsUnlock = this->HexStringToInt(s_playerIsUnlock);

	//return the current int-value, casted as bool here
	return (bool)i_playerIsUnlock;
}

/**
* This method calculates the current characters Attack-Badges using state
*
*	@return bool		the current Using-State
*
*/
bool HWLPlayer::calc_players_canUseAttackBadgesState()
{
	//declare/define needed variables
	string s_playerCanUseAttackBadges;
	int i_player_canUseAttackBadges_offset = this->i_offset + this->playerCanUseAttackBadgesOffsetDiff;

	//get hex-value from the file-content holder and convert it to int
	s_playerCanUseAttackBadges = this->getHexStringFromFileContent(i_player_canUseAttackBadges_offset, this->playerCanUseAttackBadgesOffsetLength);
	int i_playerCanUseAttackBadges = this->HexStringToInt(s_playerCanUseAttackBadges);

	//return the current int-value, casted as bool here
	return (bool)i_playerCanUseAttackBadges;
}



/**
* This method set the current characters LVL-value
* to the file-content holder
*
*/
void HWLPlayer::save_players_lvl()
{
	//declare/define needed variables
	int i_lvl_tmp = this->i_lvl - 1; //we need LVL-Shown - 1, like it's in the savefile
	string s_playerLVL;
	int i_player_lvl_offset = this->i_offset + this->playerLVLOffsetDiff;

	//convert the current integer-value to hex and add needed zeros, if we
	//don't have the complete length (calculate with offset-length multiplied by 2)
	s_playerLVL = this->intToHexString(i_lvl_tmp, false);
	this->addZeroToHexString(s_playerLVL, this->playerLVLOffsetLength * 2);

	//set converted hex-value to the file-content holder
	this->setHexStringToFileContent(s_playerLVL, i_player_lvl_offset);
}

/**
* This method set the current characters EXP-value
* to the file-content holder
*
*/
void HWLPlayer::save_players_exp()
{
	//declare/define needed variables
	int i_exp_tmp = this->i_exp;
	string s_playerEXP;
	int i_player_exp_offset = this->i_offset + this->playerEXPOffsetDiff;

	//convert the current integer-value to hex and add needed zeros, if we
	//don't have the complete length (calculate with offset-length multiplied by 2)
	s_playerEXP = this->intToHexString(i_exp_tmp, false);
	this->addZeroToHexString(s_playerEXP, this->playerEXPOffsetLength * 2);

	//set converted hex-value to the file-content holder
	this->setHexStringToFileContent(s_playerEXP, i_player_exp_offset);
}

/**
* This method set the current characters ATK-value
* to the file-content holder
*
*/
void HWLPlayer::save_players_atk()
{
	//declare/define needed variables
	int i_atk_tmp = this->i_atk;
	string s_playerATK;
	int i_player_atk_offset = this->i_offset + this->playerATKOffsetDiff;

	//convert the current integer-value to hex and add needed zeros, if we
	//don't have the complete length (calculate with offset-length multiplied by 2)
	s_playerATK = this->intToHexString(i_atk_tmp, false);
	this->addZeroToHexString(s_playerATK, this->playerATKOffsetLength * 2);

	//set converted hex-value to the file-content holder
	this->setHexStringToFileContent(s_playerATK, i_player_atk_offset);
}

/**
* This method set the current characters Hearts
* to the file-content holder
*
*/
void HWLPlayer::save_players_hearts()
{
	//declare/define needed variables
	int i_hearts_tmp = this->i_hearts;
	string s_playerHearts;
	int i_player_hearts_offset = this->i_offset + this->playerHeartsOffsetDiff;

	//convert the current integer-value to hex and add needed zeros, if we
	//don't have the complete length (calculate with offset-length multiplied by 2)
	s_playerHearts = this->intToHexString(i_hearts_tmp, false);
	this->addZeroToHexString(s_playerHearts, this->playerHeartsOffsetLength * 2);

	//set converted hex-value to the file-content holder
	this->setHexStringToFileContent(s_playerHearts, i_player_hearts_offset);
}

/**
* This method set the current characters Unlock-State
* to the file-content holder
*
*/
void HWLPlayer::save_players_isUnlockState()
{
	//declare/define needed variables
	bool b_isUnlock_tmp = this->b_isUnlock;
	int i_isUnlock_tmp = 0;
	string s_playerIsUnlock;
	int i_player_isUnlock_offset = this->i_offset + this->playerIsUnlockOffsetDiff;

	//if we have an unlocked character, set the Value to 0xF (highest value for one-offset-part)
	if (b_isUnlock_tmp)
		i_isUnlock_tmp = this->playerIsUnlockMax;

	//convert the current integer-value to hex and add needed zeros, if we
	//don't have the complete length (calculate with offset-length multiplied by 2)
	s_playerIsUnlock = this->intToHexString(i_isUnlock_tmp, false);
	this->addZeroToHexString(s_playerIsUnlock, this->playerIsUnlockOffsetLength * 2);

	//set converted hex-value to the file-content holder
	this->setHexStringToFileContent(s_playerIsUnlock, i_player_isUnlock_offset);
}

/**
* This method set the current characters Attack-Badges using state-value
* to the file-content holder
*
*/
void HWLPlayer::save_players_canUseAttackBadgesState()
{
	//declare/define needed variables
	bool b_canUseAttackBadges_tmp = this->b_canUseAttackBadges;
	string s_playerCanUseAttackBadges;
	int i_player_canUseAttackBadges_offset = this->i_offset + this->playerCanUseAttackBadgesOffsetDiff;

	//convert the current integer-value (casted from bool) to hex and add needed zeros, if we
	//don't have the complete length (calculate with offset-length multiplied by 2)
	s_playerCanUseAttackBadges = this->intToHexString(b_canUseAttackBadges_tmp, false);
	this->addZeroToHexString(s_playerCanUseAttackBadges, this->playerCanUseAttackBadgesOffsetLength * 2);

	//set converted hex-value to the file-content holder
	this->setHexStringToFileContent(s_playerCanUseAttackBadges, i_player_canUseAttackBadges_offset);
}



/**
* Setter for the characters-LVL
*
*	@var int	i_lvl		lvl-value to set
*
*/
void HWLPlayer::set_lvl(int i_lvl)
{
	//check if lvl-value smaller then 1, then set it directly to 1
	//also check for the maximal-value
	if (i_lvl < 1)
		i_lvl = 1;
	else if (i_lvl > this->get_max_stati_value(0))
		i_lvl = this->get_max_stati_value(0);

	this->i_lvl = i_lvl;
}

/**
* Setter for the characters-EXP
*
*	@var int	i_exp		exp-value to set
*
*/
void HWLPlayer::set_exp(int i_exp)
{
	//check if exp-value smaller then 100 then set it directly to 100
	//also check for the maximal-value
	if (i_exp < 100)
		i_exp = 100;
	else if (i_exp > this->get_max_stati_value(1))
		i_exp = this->get_max_stati_value(1);

	this->i_exp = i_exp;

}

/**
* Setter for the characters-ATK
*
*	@var int	i_atk		atk-value to set
*
*/
void HWLPlayer::set_atk(int i_atk)
{
	//check if atk-value smaller then 50 then set it directly to 50
	//also check for the maximal-value
	if (i_atk < 50)
		i_atk = 50;
	else if (i_atk > this->get_max_stati_value(2))
		i_atk = this->get_max_stati_value(2);

	this->i_atk = i_atk;

}

/**
* Setter for the characters-Hearts
*
*	@var int	i_hearts		hearts-value to set
*
*/
void HWLPlayer::set_hearts(int i_hearts)
{
	//check if heart-value smaller then 5 then set it directly to 5
	//also check for the maximal-value
	if (i_hearts < 5)
		i_hearts = 5;
	else if (i_hearts > this->get_max_stati_value(3))
		i_hearts = this->get_max_stati_value(3);

	this->i_hearts = i_hearts;

}

/**
* Setter for the characters Unlock-State
*
*	@var bool	b_isUnlock		unlock-state to set
*
*/
void HWLPlayer::set_isUnlock(bool b_isUnlock)
{
	this->b_isUnlock = b_isUnlock;

	//check if character will be unlock and due to a security-reason ingame, we have
	//to set, that the character can use his Attack-Badges then
	if (b_isUnlock)
		this->b_canUseAttackBadges = true;
}

/**
* Setter for the characters Disabled-State
*
*	@var bool	b_isDisabled		disabled-state to set
*
*/
void HWLPlayer::set_isDisabled(bool b_isDisabled)
{
	if (b_isDisabled)
		this->si_disabledPlayerCounter++;
	else if (this->si_disabledPlayerCounter > 0)
		this->si_disabledPlayerCounter--;

	this->b_isDisabled = b_isDisabled;
}

/**
* Setter for the characters disabled Weapon-Type IDs
*
*	@var bool	i_weapon_type		id of weapon-type to add to disable-list
*
*/
void HWLPlayer::set_disabled_weaponTypeID(int i_weapon_type)
{
	this->vi_weapon_disabled_ids.push_back(i_weapon_type);
}

/**
* Setter for the characters Weapon, identified by weapon-type without a specific slot
*
*	@var int					i_weapon_type	identify the weapon-type for the weapon-object
*	@var shared_ptr<HWLWeapon>	hwlw_weapon		weapon-object to set
*
*/
void HWLPlayer::set_weapon_slot(int i_weapon_type, shared_ptr<HWLWeapon> hwlw_weapon)
{
	//added the weapon-object as the last entry
	this->m_player_weapon[i_weapon_type].push_back(hwlw_weapon);
}

/**
* Setter for the characters Weapon, identified by weapon-type and a specific slot
*
*	@var int	i_weapon_type		identify the weapon-type for the weapon-object
*	@var int	i_weapon_slot		identify the weapon-slot for the weapon-object
*	@var shared_ptr<HWLWeapon>	hwlw_weapon		weapon-object to set
*
*/
void HWLPlayer::set_weapon_slot(int i_weapon_type, int i_weapon_slot, shared_ptr<HWLWeapon> hwlw_weapon)
{
	//add the object to the specific slot
	this->m_player_weapon[i_weapon_type][i_weapon_slot] = hwlw_weapon;
}



/**
* Getter for the characters-ID
*
*	@return int		the ID of the character
*
*/
int HWLPlayer::get_id()
{
	return this->i_id;
}

/**
* Getter for the characters-name
*
*	@return string		 the name of the character
*
*/
string HWLPlayer::get_name()
{
	return this->s_name;
}

/**
* Getter for the characters-offset
*
*	@return int		the offset of the character
*
*/
int HWLPlayer::get_offset()
{
	return this->i_offset;
}

/**
* Getter for the number of weapon-types of the character
*
*	@return int		the number of weapon-types of the character
*
*/
int HWLPlayer::get_weapon_type_count()
{
	return this->i_weapon_type_count;
}

/**
* Getter for the characters-LVL
*
*	@return int		the current characters-lvl
*
*/
int HWLPlayer::get_lvl()
{
	return this->i_lvl;
}

/**
* Getter for the characters-EXP
*
*	@return int		the current characters-exp
*
*/
int HWLPlayer::get_exp()
{
	return this->i_exp;
}

/**
* Getter for the characters-ATK
*
*	@return int		the current characters-atk
*
*/
int HWLPlayer::get_atk()
{
	return this->i_atk;
}

/**
* Getter for the characters-hearts
*
*	@return int		the current characters-hearts
*
*/
int HWLPlayer::get_hearts()
{
	return this->i_hearts;
}

/**
* Getter for the characters Unlock-State
*
*	@return bool	the current characters Unlock-State
*
*/
bool HWLPlayer::get_isUnlock()
{
	return this->b_isUnlock;
}

/**
* Getter for the characters Disabled-State
*
*	@return bool	the current characters Disabled-State
*
*/
bool HWLPlayer::get_isDisabled()
{
	return this->b_isDisabled;
}

/**
* Getter for the characters disabled Weapon-Type IDs
* Return bool, if given weapon-type-id is within the vector
*
*	@var bool	i_weapon_type		id of weapon-type to check
*
*/
bool HWLPlayer::get_isWeaponTypeDisabled(int i_weapon_type)
{
	for (int i = 0; i < this->vi_weapon_disabled_ids.size(); i++)
	{
		if (this->vi_weapon_disabled_ids[i] == i_weapon_type)
			return true;
	}

	return false;
}

/**
* Getter for the characters weapons, based on given type and slot
*
*	@return shared_ptr<HWLWeapon>		the weapon at the given slot with the given type
*
*/
shared_ptr<HWLWeapon> HWLPlayer::get_weapon_slot(int i_weapon_type, int i_weapon_slot)
{
	return this->m_player_weapon[i_weapon_type][i_weapon_slot];
}

/**
* This Getter-Method return the length of the disabled-Weapon-Type-ID vector or
*  better how many weapon-types of this character are disabled.
*
*	@return int		the disabled-MapCounter
*
*/
int HWLPlayer::get_disabledWeaponTypeCounter()
{
	return vi_weapon_disabled_ids.size();
}

/**
* Getter for the disbaledPlayerCounter
*
*	@return int		the disabled-PlayerCounter
*
*/
int HWLPlayer::get_disabledPlayerCounter()
{
	return si_disabledPlayerCounter;
}



/**
* This method return the value how many used weapons of an type
* the character has
*
*	@var int	i_weapon_type		identify the weapon-type for the counter
*
*	@return int		value, how many weapons of the given type are used
*
*/
int HWLPlayer::get_weapon_count(int i_weapon_type)
{
	//declare/define needed variables
	int i_weapon_count = 0;
	int i_max_iterations = 0;

	//check if we have Link's Master Sword, so we have only ONE Iteration,
	//cause of that unique weapon, else we have the maximal-value
	if (this->i_id == 0 && i_weapon_type == 4)
		i_max_iterations = 1;
	else
		i_max_iterations = this->playerWeaponSlotsMax;

	//iterate over the iterations-max-variable and count the weapons, they are used
	for (int i = 0; i < i_max_iterations; i++)
	{
		//check if the weapon is NOT an Unsed one, increment the counter then
		if (!this->m_player_weapon[i_weapon_type][i]->get_IsUnused())
			i_weapon_count++;
	}

	//return the counter-value
	return i_weapon_count;
}

/**
* This method returns an formatted string, which contain all needed stati-values
*
*	@return string		formatted output with all needed stati-values, without
*						 weapons
*
*/
string HWLPlayer::get_playersStatiForOutput()
{
	string s_output = "Name: " + this->s_name + "\n"
		//+ "  Offset: " + this->intToHexString(this->i_offset, false) + "\n" //offset for testing purpose
		+ "  Unlock?: " + to_string(this->b_isUnlock) + "\n"
		//+ "  Can Use Attack-Badges?: " + to_string(this->b_canUseAttackBadges) + "\n" //for testing purpose
		+ "  Level: " + to_string(this->i_lvl) + "\n"
		+ "  EXP: " + to_string(this->i_exp) + "\n"
		+ "  ATK: " + to_string(this->i_atk) + "\n"
		+ "  Hearts: " + to_string(this->i_hearts) + "\n";

	return s_output;
}


/**
* This method return the max-value of an given-stati-id
*
*	@var int        i_stati_id		id of the stati that you want
*
*	@return int		maximal-value of the given stati
*
*/
int HWLPlayer::get_max_stati_value(int i_stati_id)
{
	//switch-case of the given stati-id
	//do a check which version the savefile is and return the corressponding max-value
	switch (i_stati_id)
	{
		//case 0: max LVL-Value
	case 0:
	{
			  if (s_savefile_game_version == "1.5.0")
				  return playerLVLMax[2];
			  else
			  if (s_savefile_game_version == "1.4.0")
				  return playerLVLMax[1];
			  else
				  return playerLVLMax[0];
			  break;
	}

		//case 1: max EXP-Value
	case 1:
	{
			  if (s_savefile_game_version == "1.5.0")
				  return playerEXPMax[2];
			  else
			  if (s_savefile_game_version == "1.4.0")
				  return playerEXPMax[1];
			  else
				  return playerEXPMax[0];
			  break;
	}

		//case 2: max ATK-Value
	case 2:
	{
			  if (s_savefile_game_version == "1.5.0")
				  return playerATKMax[1];
			  else
				  return playerATKMax[0];
			  break;
	}

		//case 3: max Hearts-Value
	case 3:
	{
			  if (s_savefile_game_version == "1.5.0")
				  return playerHeartsMax[2];
			  else
			  if (s_savefile_game_version == "1.4.0")
				  return playerHeartsMax[1];
			  else
				  return playerHeartsMax[0];
			  break;
	}

		//default, if no case matches: -1 
	default:
		return -1;
	}
}

/**
* This method return the max-value of an given-stati-name
*
*	@var string         s_stati_id		name of the stati that you want
*
*	@return int		maximal-value of the given stati
*
*/
int HWLPlayer::get_max_stati_value(string s_stati_id)
{
	//check for an empty-string, true: return -1, false: check what kind of
	//stati was given and return the corressponding value (or also -1)
	if (s_stati_id != "")
	{
		if (s_stati_id == "LVL") return get_max_stati_value(0);
		if (s_stati_id == "EXP") return get_max_stati_value(1);
		if (s_stati_id == "ATK") return get_max_stati_value(2);
		if (s_stati_id == "Hearts") return get_max_stati_value(3);
		if (s_stati_id == "HEARTS") return get_max_stati_value(3);

		else
			return -1;
	}
	else
		return -1;
}

/**
* This method is a wrapper for all known save-methods of the class
*
*/
void HWLPlayer::save_Player()
{
	this->save_players_lvl();
	this->save_players_exp();
	this->save_players_atk();
	this->save_players_isUnlockState();
	this->save_players_canUseAttackBadgesState();
}

/*
//for testing purpose, the sizes of weapon-map and their weapons

string HWLPlayer::get_sizes()
{
string s_map_size = "Map Size: " + to_string(this->m_player_weapon.size()) + "\n";
string s_vector_size = "";

for (int i = 0; i < this->m_player_weapon.size(); i++)
{
s_vector_size = s_vector_size + "  Vector Size [" + to_string(i) + "]: "
+ to_string(this->m_player_weapon[i].size()) + "\n";
}

return s_map_size + s_vector_size;

}
*/
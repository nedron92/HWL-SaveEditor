//needed for including in a MFC-App
#ifdef __MFC__
#include "../gui/stdafx.h" 
#endif // __MFC__

//include the correct header-file
#include "HWLPlayer.h"

//use the project-namespace
using namespace HWLSaveEdit;

/* @var playerLVLOffsetLength		offset length of the characters LVL */
const int HWLPlayer::playerLVLOffsetLength = 0x1;

/* @var playerEXPOffsetLength		offset length of the characters EXP */
const int HWLPlayer::playerEXPOffsetLength = 0x4;

/* @var playerATKOffsetLength		offset length of the characters ATK */
const int HWLPlayer::playerATKOffsetLength = 0x2;

/* @var playerIsUnlockOffsetLength	offset length of the characters Unlock-State */
const int HWLPlayer::playerIsUnlockOffsetLength = 0x1;


/* @var playerLVLOffsetDiff			offset-diff from begin of the characters LVL */
const int HWLPlayer::playerLVLOffsetDiff = 0x20;

/* @var playerEXPOffsetDiff			offset-diff from begin of the characters EXP */
const int HWLPlayer::playerEXPOffsetDiff = 0x18;

/* @var playerATKOffsetDiff			offset-diff from begin of the characters ATK */
const int HWLPlayer::playerATKOffsetDiff = 0x12;

/* @var playerIsUnlockOffsetDiff	offset-diff from begin of the characters Unlock-State */
const int HWLPlayer::playerIsUnlockOffsetDiff = 0x10;


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
	"???",
	"???",
	"Linkle",
	"Skull Kid",
	"Toon Link",
	"Tetra",
	"King Daphnes"
};

/* @var playerLVLMax				maximal-value of the characters LVL */
const int HWLPlayer::playerLVLMax = 99;

/* @var playerEXPMax				maximal-value of the characters EXP */
const int HWLPlayer::playerEXPMax = 3178257;

/* @var playerATKMax				maximal-value of the characters ATK */
const int HWLPlayer::playerATKMax = 999;

/* @var playerWeaponSlotsMax		maximal-value of the characters Weapons, which it can take */
const int HWLPlayer::playerWeaponSlotsMax = 15;



/**
* Only the initialization of the normal-constructor
*/
HWLPlayer::HWLPlayer(int i_id, string s_name, int i_offset)
{
	//set or calculate all needed members
	this->i_id = i_id;
	this->s_name = s_name;
	this->i_offset = i_offset;
	this->i_lvl = this->calc_players_lvl();
	this->i_exp = this->calc_players_exp();
	this->i_atk = this->calc_players_atk();
	this->b_isUnlock = this->calc_players_isUnlockState();
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
* This method set the current characters Unlock-State
* to the file-content holder
*
*/
void HWLPlayer::save_players_isUnlockState()
{
	//declare/define needed variables
	bool b_isUnlock_tmp = this->b_isUnlock;
	string s_playerIsUnlock;
	int i_player_isUnlock_offset = this->i_offset + this->playerIsUnlockOffsetDiff;

	//convert the current integer-value (casted from bool) to hex and add needed zeros, if we
	//don't have the complete length (calculate with offset-length multiplied by 2)
	s_playerIsUnlock = this->intToHexString(b_isUnlock_tmp, false);
	this->addZeroToHexString(s_playerIsUnlock, this->playerIsUnlockOffsetLength * 2);

	//set converted hex-value to the file-content holder
	this->setHexStringToFileContent(s_playerIsUnlock, i_player_isUnlock_offset);
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
	else if (i_lvl > this->playerLVLMax)
		i_lvl = playerLVLMax;

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
	else if (i_exp > this->playerEXPMax)
		i_exp = playerEXPMax;

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
	else if (i_atk > this->playerATKMax)
		i_atk = playerATKMax;

	this->i_atk = i_atk;

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
* This method return the value how many used weapons of an type
* the charachter has
*
*	@var int	i_weapon_type		identify the weapon-type for the counter
*
*	@return int		value, how many weapons, of the given type, are used
*
*/
int HWLPlayer::get_weapon_count(int i_weapon_type)
{
	//declare/define needed variables
	int i_weapon_count = 0;
	int i_max_iterations = 0;

	//check if we have Link's Master Sword, so we have only ONE Iteration,
	//cause of that unique weapon, esle we have the maximal-value
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
		//  + "  Offset: " + this->intToHexString(this->i_offset,false) + "\n" //offset for testing purpose
		+ "  Unlock?: " + to_string(this->b_isUnlock) + "\n"
		+ "  Level: " + to_string(this->i_lvl) + "\n"
		+ "  EXP: " + to_string(this->i_exp) + "\n"
		+ "  ATK: " + to_string(this->i_atk) + "\n";

	return s_output;
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
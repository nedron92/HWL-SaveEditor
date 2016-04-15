//needed for including in a MFC-App
#ifdef __MFC__
#include "../gui/stdafx.h" 
#endif // __MFC__

#include "HWLPlayer.h"

//use the project-namespace
using namespace HWLSaveEdit;

const int HWLPlayer::playerLVLOffsetLength = 0x1;
const int HWLPlayer::playerEXPOffsetLength = 0x4;
const int HWLPlayer::playerATKOffsetLength = 0x2;
const int HWLPlayer::playerIsUnlockOffsetLength = 0x1;

const int HWLPlayer::playerLVLOffsetDiff = 0x20;
const int HWLPlayer::playerEXPOffsetDiff = 0x18;
const int HWLPlayer::playerATKOffsetDiff = 0x12;
const int HWLPlayer::playerIsUnlockOffsetDiff = 0x10;

const int HWLPlayer::playerLVLMax = 99;
const int HWLPlayer::playerEXPMax = 3178257;
const int HWLPlayer::playerATKMax = 999;
const int HWLPlayer::playerWeaponSlotsMax = 15;

HWLPlayer::HWLPlayer(int i_id, string s_name, int i_offset)
{
	this->i_id = i_id;
	this->s_name = s_name;
	this->i_offset = i_offset;
	this->i_lvl = this->calc_players_lvl();
	this->i_exp = this->calc_players_exp();
	this->i_atk = this->calc_players_atk();
	this->b_isUnlock = this->calc_players_isUnlockState();
}


HWLPlayer::~HWLPlayer()
{
}



int HWLPlayer::calc_players_lvl()
{
	string s_playerLVL;
	int i_player_lvl_offset = this->i_offset + this->playerLVLOffsetDiff;
	
	s_playerLVL = this->getHexStringFromFileContent(i_player_lvl_offset, this->playerLVLOffsetLength);
	
	int i_playerLVL = this->HexStringToInt(s_playerLVL) + 1;

	return i_playerLVL;
}

int HWLPlayer::calc_players_exp()
{
	string s_playerEXP;
	int i_player_exp_offset = this->i_offset + this->playerEXPOffsetDiff;

	s_playerEXP = this->getHexStringFromFileContent(i_player_exp_offset, this->playerEXPOffsetLength);

	int i_playerEXP = this->HexStringToInt(s_playerEXP);

	return i_playerEXP;
}

int HWLPlayer::calc_players_atk()
{
	string s_playerATK;

	int i_player_atk_offset = this->i_offset + this->playerATKOffsetDiff;

	s_playerATK = this->getHexStringFromFileContent(i_player_atk_offset, this->playerATKOffsetLength);

	int i_playerATK = this->HexStringToInt(s_playerATK);

	return i_playerATK;
}

bool HWLPlayer::calc_players_isUnlockState()
{
	string s_playerIsUnlock;
	int i_player_isUnlock_offset = this->i_offset + this->playerIsUnlockOffsetDiff;

	s_playerIsUnlock = this->getHexStringFromFileContent(i_player_isUnlock_offset, this->playerIsUnlockOffsetLength);

	int i_playerIsUnlock = this->HexStringToInt(s_playerIsUnlock);

	return (bool)i_playerIsUnlock;
}

void HWLPlayer::save_players_lvl()
{
	int i_lvl_tmp = this->i_lvl - 1;
	string s_playerLVL;
	int i_player_lvl_offset = this->i_offset + this->playerLVLOffsetDiff;

	s_playerLVL = this->intToHexString(i_lvl_tmp, false);
	this->addZeroToHexString(s_playerLVL, this->playerLVLOffsetLength * 2);

	this->setHexStringToFileContent(s_playerLVL, i_player_lvl_offset);
}

void HWLPlayer::save_players_exp()
{
	int i_exp_tmp = this->i_exp;
	string s_playerEXP;
	int i_player_exp_offset = this->i_offset + this->playerEXPOffsetDiff;

	s_playerEXP = this->intToHexString(i_exp_tmp, false);
	this->addZeroToHexString(s_playerEXP, this->playerEXPOffsetLength * 2);

	this->setHexStringToFileContent(s_playerEXP, i_player_exp_offset);
}

void HWLPlayer::save_players_atk()
{
	int i_atk_tmp = this->i_atk;
	string s_playerATK;
	int i_player_atk_offset = this->i_offset + this->playerATKOffsetDiff;

	s_playerATK = this->intToHexString(i_atk_tmp, false);
	this->addZeroToHexString(s_playerATK, this->playerATKOffsetLength * 2);

	this->setHexStringToFileContent(s_playerATK, i_player_atk_offset);
}

void HWLPlayer::save_players_isUnlockState()
{
	bool b_isUnlock_tmp = this->b_isUnlock;
	string s_playerIsUnlock;
	int i_player_isUnlock_offset = this->i_offset + this->playerIsUnlockOffsetDiff;

	s_playerIsUnlock = this->intToHexString(b_isUnlock_tmp, false);
	this->addZeroToHexString(s_playerIsUnlock, this->playerIsUnlockOffsetLength * 2);

	this->setHexStringToFileContent(s_playerIsUnlock, i_player_isUnlock_offset);
}

//setter/Getter
void HWLPlayer::set_lvl(int i_lvl)
{
	if (i_lvl < 1)
		i_lvl = 1;
	else if (i_lvl > this->playerLVLMax)
		i_lvl = playerLVLMax;

	this->i_lvl = i_lvl;
}

void HWLPlayer::set_exp(int i_exp)
{
	if (i_exp < 100)
		i_exp = 100;
	else if (i_exp > this->playerEXPMax)
		i_exp = playerEXPMax;

	this->i_exp = i_exp;

}

void HWLPlayer::set_atk(int i_atk)
{
	if (i_atk < 50)
		i_atk = 50;
	else if (i_atk > this->playerATKMax)
		i_atk = playerATKMax;

	this->i_atk = i_atk;

}

void HWLPlayer::set_isUnlock(bool b_isUnlock)
{
	this->b_isUnlock = b_isUnlock;
}

void HWLPlayer::set_weapon_slot(int i_weapon_type, shared_ptr<HWLWeapon> hwlw_weapon)
{
	this->m_player_weapon[i_weapon_type].push_back(hwlw_weapon);
}

void HWLPlayer::set_weapon_slot(int i_weapon_type, int i_weapon_slot, shared_ptr<HWLWeapon> hwlw_weapon)
{
	this->m_player_weapon[i_weapon_type][i_weapon_slot] = hwlw_weapon;
}


int HWLPlayer::get_id()
{
	return this->i_id;
}

string HWLPlayer::get_name()
{
	return this->s_name;
}

int HWLPlayer::get_offset()
{
	return this->i_offset;
}

int HWLPlayer::get_lvl()
{
	return this->i_lvl;
}

int HWLPlayer::get_exp()
{
	return this->i_exp;
}

int HWLPlayer::get_atk()
{
	return this->i_atk;
}

bool HWLPlayer::get_isUnlock()
{
	return this->b_isUnlock;
}

shared_ptr<HWLWeapon> HWLPlayer::get_weapon_slot(int i_weapon_type, int i_weapon_slot)
{
	return this->m_player_weapon[i_weapon_type][i_weapon_slot];
}



string HWLPlayer::get_playersStatiForOutput()
{
	string s_output = "Name: " + this->s_name + "\n"
		+ "  Unlock?: " + to_string(this->b_isUnlock) + "\n"
		+ "  Level: " + to_string(this->i_lvl) + "\n"
		+ "  EXP: " + to_string(this->i_exp) + "\n"
		+ "  ATK: " + to_string(this->i_atk) + "\n";

	return s_output;
}

void HWLPlayer::save_Player()
{
	this->save_players_lvl();
	this->save_players_exp();
	this->save_players_atk();
	this->save_players_isUnlockState();
}

int HWLPlayer::get_weapon_count(int i_weapon_type)
{
	int i_weapon_count = 0;
	int i_max_iterations = 0;

	if (this->i_id == 0 && i_weapon_type == 4)
		i_max_iterations = 1;
	else
		i_max_iterations = this->playerWeaponSlotsMax;

	for (int i = 0; i < i_max_iterations; i++)
	{
		if (!this->m_player_weapon[i_weapon_type][i]->get_IsUnused())
			i_weapon_count++;
	}

	return i_weapon_count;
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
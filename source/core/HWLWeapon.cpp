//needed for including in a MFC-App
#ifdef __MFC__
#include "../gui/stdafx.h" 
#endif // __MFC__

#include "HWLWeapon.h"

//use the project-namespace
using namespace HWLSaveEdit;

//constants
const int HWLWeapon::weaponSkillSlotKillsLength = 0x2;
const int HWLWeapon::weaponSkillSlotsLength = 0x1;

const int HWLWeapon::weaponSkillSlotKillsOffsetLength = 0x10;
const int HWLWeapon::weaponIDOffsetLength = 0x2;
const int HWLWeapon::weaponDamageBaseOffsetLength = 0x2;
const int HWLWeapon::weaponStarsOffsetLength = 0x2;
const int HWLWeapon::weaponSkillSlotsOffsetLength = 0x8;
const int HWLWeapon::weaponStateOffsetLength = 0x1;

const int HWLWeapon::weaponSkillSlotKillsOffsetDiff = 0x0;
const int HWLWeapon::weaponIDOffsetDiff = 0x10;
const int HWLWeapon::weaponDamageBaseOffsetDiff = 0x12;
const int HWLWeapon::weaponStarsOffsetDiff = 0x14;
const int HWLWeapon::weaponSkillSlotsOffsetDiff = 0x16;
const int HWLWeapon::weaponStateOffsetDiff = 0x1E;

const int HWLWeapon::weaponSkillSlotKillMax = 65000;
const int HWLWeapon::weaponDamageBaseMax = 999;
const int HWLWeapon::weaponStarsMax = 5;

const string HWLWeapon::weaponBlankWeaponHex = "00000000000000000000000000000000ffff00000000ffffffffffffffff00";

HWLWeapon::HWLWeapon(int i_offset)
{
	this->i_offset = i_offset;
	this->vi_skill_slot_kills = this->calc_skill_slot_kills();
	this->i_id = this->calc_weapon_id();
	this->i_damage_base = this->calc_damage_base();
	this->i_stars = this->calc_stars();
	this->vi_skill_slots = this->calc_skill_slots();
	this->i_state = this->calc_state();

	this->i_type = -1;
	this->i_lvl = -1;
}


HWLWeapon::~HWLWeapon()
{
}

vector<int> HWLWeapon::calc_skill_slot_kills()
{
	string s_skill_slot_kills;
	vector<int> vi_temp;
	int i_skill_slot_kills_offset = this->i_offset + this->weaponSkillSlotKillsOffsetDiff;

	s_skill_slot_kills = this->getHexStringFromFileContent(i_skill_slot_kills_offset, this->weaponSkillSlotKillsOffsetLength,true);

	for (int i = 0; i < s_skill_slot_kills.size(); i += (this->weaponSkillSlotKillsLength * 2))
	{
		string s_skill_slot_kill = s_skill_slot_kills.substr(i, (this->weaponSkillSlotKillsLength * 2));
		this->convertByteOrder(s_skill_slot_kill);
		vi_temp.push_back(this->HexStringToInt(s_skill_slot_kill));
	}

	return vi_temp;
}

int HWLWeapon::calc_weapon_id()
{
	string s_weapon_id;
	int i_weapon_id_offset = this->i_offset + this->weaponIDOffsetDiff;

	s_weapon_id = this->getHexStringFromFileContent(i_weapon_id_offset, this->weaponIDOffsetLength);
	int i_weapon_id = this->HexStringToInt(s_weapon_id);

	return i_weapon_id;
}

int HWLWeapon::calc_damage_base()
{
	string s_damage_base;
	int i_damage_base_offset = this->i_offset + this->weaponDamageBaseOffsetDiff;

	s_damage_base = this->getHexStringFromFileContent(i_damage_base_offset, this->weaponDamageBaseOffsetLength);
	int i_damage_base = this->HexStringToInt(s_damage_base);

	return i_damage_base;
}

int HWLWeapon::calc_stars()
{
	string s_stars;
	int i_stars_offset = this->i_offset + this->weaponStarsOffsetDiff;

	s_stars = this->getHexStringFromFileContent(i_stars_offset, this->weaponStarsOffsetLength);
	int i_stars = this->HexStringToInt(s_stars);

	return i_stars;
}

vector<int> HWLWeapon::calc_skill_slots()
{
	string s_skill_slots;
	vector<int> vi_temp;
	int i_skill_slots_offset = this->i_offset + this->weaponSkillSlotsOffsetDiff;

	s_skill_slots = this->getHexStringFromFileContent(i_skill_slots_offset, this->weaponSkillSlotsOffsetLength, true);

	for (int i = 0; i < s_skill_slots.size(); i += (this->weaponSkillSlotsLength * 2))
	{
		string s_skill_slot = s_skill_slots.substr(i, (this->weaponSkillSlotsLength * 2));
		this->convertByteOrder(s_skill_slot);
		vi_temp.push_back(this->HexStringToInt(s_skill_slot));
	}

	return vi_temp;
}

int HWLWeapon::calc_state()
{
	string s_state;
	int i_state_offset = this->i_offset + this->weaponStateOffsetDiff;

	s_state = this->getHexStringFromFileContent(i_state_offset, this->weaponStateOffsetLength);
	int i_state = this->HexStringToInt(s_state);

	return i_state;
}




void HWLWeapon::save_skill_slot_kills()
{
	string s_skill_slot_kills;
	int i_skill_slot_kills_offset = this->i_offset + this->weaponSkillSlotKillsOffsetDiff;
	
	for (int i = 0; i < this->vi_skill_slot_kills.size(); i++)
	{
		string s_skill_slot_kill = this->intToHexString(vi_skill_slot_kills[i],false);
		this->addZeroToHexString(s_skill_slot_kill, (this->weaponSkillSlotKillsLength * 2));
		this->convertByteOrder(s_skill_slot_kill);
		s_skill_slot_kills.append(s_skill_slot_kill);
	}

	this->setHexStringToFileContent(s_skill_slot_kills, i_skill_slot_kills_offset);

}

void HWLWeapon::save_weapon_id()
{
	int i_id_tmp = this->i_id;
	string s_weapon_id;
	int i_weapon_id_offset = this->i_offset + this->weaponIDOffsetDiff;

	s_weapon_id = this->intToHexString(i_id_tmp, false);
	this->addZeroToHexString(s_weapon_id, this->weaponIDOffsetLength * 2);

	this->setHexStringToFileContent(s_weapon_id, i_weapon_id_offset);
}

void HWLWeapon::save_damage_base()
{
	int i_damage_base_tmp = this->i_damage_base;
	string s_damage_base;
	int i_damage_base_offset = this->i_offset + this->weaponDamageBaseOffsetDiff;

	s_damage_base = this->intToHexString(i_damage_base_tmp, false);
	this->addZeroToHexString(s_damage_base, this->weaponDamageBaseOffsetLength * 2);

	this->setHexStringToFileContent(s_damage_base, i_damage_base_offset);
}

void HWLWeapon::save_stars()
{
	int i_stars_tmp = this->i_stars;
	string s_stars;
	int i_stars_offset = this->i_offset + this->weaponStarsOffsetDiff;

	s_stars = this->intToHexString(i_stars_tmp, false);
	this->addZeroToHexString(s_stars, this->weaponStarsOffsetLength * 2);

	this->setHexStringToFileContent(s_stars, i_stars_offset);
}

void HWLWeapon::save_skill_slots()
{
	string s_skill_slots;
	int i_skill_slots_offset = this->i_offset + this->weaponSkillSlotsOffsetDiff;

	for (int i = 0; i < this->vi_skill_slots.size(); i++)
	{
		string s_skill_slot = this->intToHexString(vi_skill_slots[i], false);
		this->addZeroToHexString(s_skill_slot, (this->weaponSkillSlotsLength * 2));
		this->convertByteOrder(s_skill_slot);
		s_skill_slots.append(s_skill_slot);
	}

	this->setHexStringToFileContent(s_skill_slots, i_skill_slots_offset);

}

void HWLWeapon::save_state()
{
	int i_state_tmp = this->i_state;
	string s_state;
	int i_state_offset = this->i_offset + this->weaponStateOffsetDiff;

	s_state = this->intToHexString(i_state_tmp, false);
	this->addZeroToHexString(s_state, this->weaponStateOffsetLength * 2);

	this->setHexStringToFileContent(s_state, i_state_tmp);
}

void HWLWeapon::save_weapon()
{
	this->save_skill_slot_kills();
	this->save_weapon_id();
	this->save_damage_base();
	this->save_stars();
	this->save_skill_slots();
	this->save_state();
}

string HWLWeapon::get_WeaponsForOutput()
{
	string s_output = "Name: " + this->s_name + "\n"
		+ "  Offset: " + this->intToHexString(this->i_offset,false) + "\n"
		+ "  i_id: " + to_string(this->i_id) + "\n"
		+ "  i_damage_base: " + to_string(this->i_damage_base) + "\n"
		+ "  i_stars: " + to_string(this->i_stars) + "\n"
		+ "  i_state: " + to_string(this->i_state) + "\n";

	return s_output;
}
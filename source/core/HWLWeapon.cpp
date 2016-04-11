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
const int HWLWeapon::weaponLVLMax = 4;
const int HWLWeapon::weaponSkillValueNoSkill = 0xFF;

const string HWLWeapon::weaponBlankWeaponHex = "00000000000000000000000000000000ffff00000000ffffffffffffffff00";

const vector<string> HWLWeapon::weaponSkillNames =
{
	"Open Slot",
	"Str Attack I+",
	"Str Attack II +",
	"Str Attack III + ",
	"Str Attack IV +",
	"Str Attack V +",
	"Str Attack VI +",
	"Fire +",
	"Water +",
	"Lightning +",
	"Light +",
	"Darkness +",
	"VS Legend",
	"VS Time",
	"VS Twilight",
	"VS Skyward",
	"VS Sorceress",
	"VS Beast",
	"VS Dragon",
	"VS Undead",
	"VS Soldier",
	"VS Ganon",
	"EXP +",
	"Rupees +",
	"Materials +",
	"Slots +",
	"Stars +",
	"Hearts +",
	"Health +",
	"Special +",
	"Bombs +",
	"Arrows +",
	"Boomerang +",
	"Hookshot +",
	"One - Hit Kill",
	"Sturdy Feet",
	"Regen",
	"Defenseless",
	"No Healing",
	"Adversity",
	"Compatriot",
	"Master Sword Skill I",
	"Master Sword Skill II",
	"Sp.Attack +",
	"Fin.Blow +",
	"Reg.Attack +",
	"Heart - strong",
	"Focus Spirit +",
	"Hasty Attacks",
	"Food +",
	"Hammer +",
	"VS Sea",
	"VS Termina",
	"No Slot",
};

const vector<int> HWLWeapon::vi_damage_base_defaults =
{
	80,
	150,
	280,
	500,
};

const vector<int> HWLWeapon::weaponStateValuesHex =
{
	0x03,
	0x13,
	0x0B,
};

const vector<string> HWLWeapon::weaponStateValuesNames =
{
	"Normal Weapon",
	"Legendary",
	"Master Sword",
};



HWLWeapon::HWLWeapon(int i_offset, int i_character_id, bool b_is_unsued_weapon)
{
	this->i_offset = i_offset;
	this->vi_skill_slot_kills = this->calc_skill_slot_kills();
	this->i_id = this->calc_weapon_id();
	this->i_damage_base = this->calc_damage_base();
	this->i_stars = this->calc_stars();
	this->vi_skill_slots = this->calc_skill_slots();
	this->i_state = this->calc_state();
	this->b_is_unsued_weapon = b_is_unsued_weapon;

	this->i_character_id = i_character_id;
	this->i_type = 0;
	this->i_lvl = 1;
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
		//	+ "  Offset: " + this->intToHexString(this->i_offset,false) + "\n"
		// + "  i_id: " + this->intToHexString(this->i_id,false) + "\n"
		//+ "  i_character_id: " + to_string(this->i_character_id) + "\n"
		+ "  Damage Base: " + to_string(this->i_damage_base) + "\n"
		+ "  Stars: " + to_string(this->i_stars) + "\n"
		+ "  Lvl: " + to_string(this->i_lvl) + "\n"
		+ "  Skills: " + this->get_WeaponsSkillsForOutput() + "\n"
		+ "  Weapon State: " + this->get_state(true) + "\n";

	return s_output;
}

string HWLWeapon::get_WeaponsSkillsForOutput()
{
	string s_output;

	for (int i = 0; i < 8; i++)
	{
		s_output = s_output + "\n   Slot " + to_string(i + 1) + ": " + this->get_skill_slot(i, true) + " (" + to_string(this->get_skill_slot_kill(i)) + " Kills to Unlock) \n";
	}

	return s_output;
}


void HWLWeapon::set_name(string s_name)
{
	this->s_name = s_name;
}

void HWLWeapon::set_skill_slot_kill(int i_slot_id, int i_kill_value)
{
	if (i_slot_id >= 0 && i_slot_id < 8)
	{
		if (i_kill_value > this->weaponSkillSlotKillMax)
			i_kill_value = this->weaponSkillSlotKillMax;
		else if (i_kill_value <= 0)
			i_kill_value = 0;

		this->vi_skill_slot_kills[i_slot_id] = i_kill_value;
	}

}

void HWLWeapon::set_id(int i_id)
{
	this->i_id = i_id;
}

void HWLWeapon::set_damage_base(int i_damage_base)
{
	if (i_damage_base > this->weaponDamageBaseMax)
		i_damage_base = this->weaponDamageBaseMax;
	else if (i_damage_base <= 0)
		i_damage_base = 1;

	this->i_damage_base = i_damage_base;
}

void HWLWeapon::set_stars(int i_stars)
{
	if (i_stars > this->weaponStarsMax)
		i_stars = this->weaponStarsMax;
	else if (i_stars < 0)
		i_stars = 0;

	this->i_stars = i_stars;
}

void HWLWeapon::set_skill_slot(int i_slot_id, int i_skill_id)
{
	if (i_slot_id >= 0 && i_slot_id < 8)
	{
		this->vi_skill_slots[i_slot_id] = i_skill_id;
	}
}

void HWLWeapon::set_state(int i_state)
{
	this->i_state = i_state;
}

void HWLWeapon::set_character_id(int i_character_id)
{
	this->i_character_id = i_character_id;
}

void HWLWeapon::set_type(int i_type)
{
	if (this->i_type == -1)
		this->i_type = i_type;
}

void HWLWeapon::set_lvl(int i_lvl)
{
	if (i_lvl != this->i_lvl)
	{
		if (i_lvl > this->weaponLVLMax)
			i_lvl = this->weaponLVLMax;
		else if (i_lvl <= 1)
			i_lvl = 1;

		this->i_lvl = i_lvl;
	}
}

void HWLWeapon::set_IsUnused(bool b_is_unsued_weapon)
{
	this->b_is_unsued_weapon = b_is_unsued_weapon;
}

void HWLWeapon::set_lvl_hex(vector<int> vi_lvl_hex)
{
	this->vi_lvl_hex = vi_lvl_hex;
}



string HWLWeapon::get_name()
{
	return this->s_name;
}

int HWLWeapon::get_skill_slot_kill(int i_slot_id)
{
	if (i_slot_id >= 0 && i_slot_id < 8)
	{
		return vi_skill_slot_kills[i_slot_id];
	}
	else{
		return -1;
	}
}

int HWLWeapon::get_id()
{
	return this->i_id;
}

int HWLWeapon::get_damage_base()
{
	return this->i_damage_base;
}

int HWLWeapon::get_stars()
{
	return this->i_stars;
}

int HWLWeapon::get_skill_slot(int i_slot_id)
{
	if (i_slot_id >= 0 && i_slot_id < 8)
	{
		return this->vi_skill_slots[i_slot_id];
	}
	else{
		return -1;
	}
}
string HWLWeapon::get_skill_slot(int i_slot_id, bool b_get_string)
{
	if (i_slot_id >= 0 && i_slot_id < 8)
	{
		int i_skill_value = this->vi_skill_slots[i_slot_id];
		
		if (i_skill_value != this->weaponSkillValueNoSkill)
		{
			string name = this->weaponSkillNames[i_skill_value];
			return name;
		}
		else
			return this->weaponSkillNames[weaponSkillNames.size() - 1];
	}
	else{
		return "";
	}
}

int HWLWeapon::get_state()
{
	return this->i_state;
}

string HWLWeapon::get_state(bool b_return_as_string)
{
	string s_state;
	switch (this->i_state)
	{

	case 0x03:
		s_state = this->weaponStateValuesNames[0];
		break;

	case 0x13:
		s_state = this->weaponStateValuesNames[1];
		break;

	case 0x0B:
		s_state = this->weaponStateValuesNames[2];
		break;

	default:
		s_state = "Unkown";
		break;
	}

	return s_state;
}


int HWLWeapon::get_character_id()
{
	return this->i_character_id;
}

int HWLWeapon::get_type()
{
	return this->i_type;
}

int HWLWeapon::get_lvl()
{
	return this->i_lvl;
}

bool HWLWeapon::get_IsUnused()
{
	return this->b_is_unsued_weapon;
}

vector<int> HWLWeapon::get_lvl_hex()
{
	return this->vi_lvl_hex;
}

void HWLWeapon::change_lvl(int i_lvl)
{
	if (this->i_lvl != i_lvl)
	{
		this->set_lvl(i_lvl);
		this->set_damage_base(this->vi_damage_base_defaults[i_lvl - 1]);
		this->set_id(this->vi_lvl_hex[i_lvl - 1]);
	}
}

void HWLWeapon::delete_weapon()
{
	this->setHexStringToFileContent(this->weaponBlankWeaponHex, i_offset, true);

	this->vi_skill_slot_kills = this->calc_skill_slot_kills();
	this->i_id = this->calc_weapon_id();
	this->i_damage_base = this->calc_damage_base();
	this->i_stars = this->calc_stars();
	this->vi_skill_slots = this->calc_skill_slots();
	this->i_state = this->calc_state();
	this->b_is_unsued_weapon = true;

	this->i_type = 0;
	this->i_lvl = 1;
}


/*
* @author: nedron92, 2016
*/
//needed for including in a MFC-App
#ifdef __MFC__
#include "../gui/stdafx.h" 
#endif // __MFC__

//include the correct header-file
#include "HWLWeapon.h"

//use the project-namespace
using namespace HWLSaveEdit;

//initialization of the static-vector
vector<int> HWLWeapon::vi_disabledweaponSkillIDs;


/* @var weaponIDOffsetLength				offset length of the weapon-id */
const int HWLWeapon::weaponIDOffsetLength = 0x2;

/* @var weaponDamageBaseOffsetLength		offset length of the weapon damage-base */
const int HWLWeapon::weaponDamageBaseOffsetLength = 0x2;

/* @var weaponStarsOffsetLength				offset length of the weapon-stars */
const int HWLWeapon::weaponStarsOffsetLength = 0x2;

/* @var weaponStateOffsetLength				offset length of the weapon legendary-state */
const int HWLWeapon::weaponStateOffsetLength = 0x1;

/* @var weaponSkillSlotKillsOffsetLength	offset length of the weapon Kills for all Skill-Slots */
const int HWLWeapon::weaponSkillSlotKillsOffsetLength = 0x10;

/* @var weaponSkillSlotsOffsetLength		offset length of the weapon skills */
const int HWLWeapon::weaponSkillSlotsOffsetLength = 0x8;


/* @var weaponIDOffsetDiff					offset-diff from begin of the weapon-id */
const int HWLWeapon::weaponIDOffsetDiff = 0x10;

/* @var weaponDamageBaseOffsetDiff			offset-diff from begin of the weapon damage-base */
const int HWLWeapon::weaponDamageBaseOffsetDiff = 0x12;

/* @var weaponStarsOffsetDiff				offset-diff from beginof the weapon-stars */
const int HWLWeapon::weaponStarsOffsetDiff = 0x14;

/* @var weaponStateOffsetDiff				offset-diff from begin of the weapon legendary-state */
const int HWLWeapon::weaponStateOffsetDiff = 0x1E;

/* @var weaponSkillSlotKillsOffsetDiff		offset-diff from begin of the weapon Kills for all Skill-Slots */
const int HWLWeapon::weaponSkillSlotKillsOffsetDiff = 0x0;

/* @var weaponSkillSlotsOffsetDiff			offset-diff from begin of the weapon skills */
const int HWLWeapon::weaponSkillSlotsOffsetDiff = 0x16;


/* @var weaponSkillSlotKillsLength			length of each weapon Kill-Value of a Skill-Slot */
const int HWLWeapon::weaponSkillSlotKillsLength = 0x2;

/* @var weaponSkillSlotsLength				length of each weapon skill-slot */
const int HWLWeapon::weaponSkillSlotsLength = 0x1;



/* @var vi_playerWeaponTypeCount	vector for holding information about how many weapon types a chara have */
const vector<int> HWLWeapon::vi_playerWeaponTypeCount =
{
	7, 3, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 0, 0, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1
	// 0.Link, 1.Zelda, 2.Shiek, 3.Impa, 4.Ganondorf, 5.Darunia, 6.Ruto, 7.Agitha, 8.Imp Midna, 
	// 9.Fi, 10.Ghirahim, 11.Zant, 12.Lana, 13.Cia, 14.Volga, 15.Wizzro, 16.Twili Midna, 17.Young Link, 
	// 18.Tingle, 19.??? 20.???, 21.Linkle, 22.Skull Kid, 23.Toon Link, 24.Tetra, 25.King Daphnes, 26.Medli
	// 27.Marin, 28.Toon Zelda, 29.Ravio, 30.Yuga
};

/* @var vs_playerWeaponTypeNames	vector for holding all weapon-type names */
const vector<string> HWLWeapon::vs_playerWeaponTypeNames =
{
	//Link - Weapon Types
	"Hylian Sword",
	"Magic Rod",
	"Great Fairy",
	"Gauntlets",
	"Master Sword",
	"Horse (Epona)",
	"Spinner",

	//Zelda - Weapon Types
	"Rapier",
	"Baton",
	"Dominion Rod",

	//Shiek - Weapon Types
	"Harp",

	//Impa - Weapon Types
	"Giant Blade",
	"Naginata",

	//Ganondorf - Weapon Types
	"Great Swords",
	"Trident",

	//Darunia - Weapon Types
	"Hammer",

	//Ruto - Weapon Types
	"Zora Scale",

	//Agitha - Weapon Types
	"Parasol",

	//Imp Midna - Weapon Types
	"Shackle",

	//Fi - Weapon Types
	"Goddess Blade",

	//Ghirahim - Weapon Types
	"Demon Blade",

	//Zant - Weapon Types
	"Scimitars",

	//Lana - Weapon Types
	"Book of Sorcery",
	"Spear",
	"Summoning Gate",

	//Cia - Weapon Types
	"Scepter",

	//Volga - Weapon Types
	"Dragon Spear",

	//Wizzro - Weapon Types
	"Ring",

	//Twili Midna - Weapon Types
	"Mirror",

	//Young Link - Weapon Types
	"Mask",

	//Tingle - Weapon Types
	"Balloon",

	//??? - Weapon Types, 2 times, without any weapon-type name

	//Linkle - Weapon Types
	"Crossbows",
	"Boots", //only 2nd DLC: Link's Awakening DLC

	//Skull Kid - Weapon Types
	"Ocarina",

	//Toon Link - Weapon Types
	"Light Sword",
	"Sand Wand",

	//Tetra - Weapon Types
	"Cutlass",

	//King Daphnes - Weapon Types
	"Sail",

	//Medli - Weapon Types
	"Rito Harp", //Update 1.3.0 (no LVL4-Weapon without any DLC)

	//Marin - Weapon Types
	"Bell", //only 2nd DLC: Link's Awakening DLC

	//Toon Zelda - Weapon Types
	"Phantom Arms", //only 3rd DLC: Phantom Hourglass and Spirit Tracks DLC

	//Ravio - Weapon Types
	"Hammer", //only 4th DLC: A Link Between Worlds DLC

	//Yuga - Weapon Types
	"Frame", //only 4th DLC: A Link Between Worlds DLC
};

/* @var vi_playerWeaponTypeHexValues	vector for holding information about all weapon-type offsets-begin */
const vector<int> HWLWeapon::vi_playerWeaponTypeHexValues =
{
	//Link - Weapon Types Hex
	0x00,
	0x03,
	0x06,
	0x09,
	0x3C,
	0x5A,
	0x60,

	//Zelda - Weapon Types Hex
	0x15,
	0x18,
	0x63,

	//Shiek - Weapon Types Hex
	0x24,

	//Impa - Weapon Types Hex
	0x1B,
	0x1E,

	//Ganondorf - Weapon Types Hex
	0x21,
	0x6E,

	//Darunia - Weapon Types Hex
	0x27,

	//Ruto - Weapon Types Hex
	0x2A,

	//Agitha - Weapon Types Hex
	0x2D,

	//Imp Midna - Weapon Types Hex
	0x30,

	//Fi - Weapon Types Hex
	0x33,

	//Ghirahim - Weapon Types Hex
	0x36,

	//Zant - Weapon Types Hex
	0x39,

	//Lana - Weapon Types Hex
	0x0C,
	0x0F,
	0x12,

	//Cia - Weapon Types Hex
	0x51,

	//Volga - Weapon Types Hex
	0x54,

	//Wizzro - Weapon Types Hex
	0x57,

	//Twili Midna - Weapon Types Hex
	0x5D,

	//Young Link - Weapon Types Hex
	0x66,

	//Tingle - Weapon Types Hex
	0x69,

	//??? - Weapon Types Hex, 2 times, without any weapon-type hex

	//Linkle - Weapon Types Hex
	0x71,
	0x97,

	//Skull Kid - Weapon Types Hex
	0x74,

	//Toon Link - Weapon Types Hex
	0x77,
	0xAB,

	//Tetra - Weapon Types Hex
	0x7A,

	//King Daphnes - Weapon Types Hex
	0x7D,

	//Medli - Weapon Types Hex
	0x8F, //Update 1.3.0 (no LVL4-Weapon without any DLC)

	//Marin - Weapon Types Hex
	0x93, //only 2nd DLC: Link's Awakening DLC

	//Toon Zelda - Weapon Types Hex
	0xA7, //only 3rd DLC: Phantom Hourglass and Spirit Tracks DLC

	//Ravio - Weapon Types Hex 
	0xBB, //only 4th DLC: A Link Between Worlds DLC

	//Yuga - Weapon Types Hex
	0xBF, //only 4th DLC: A Link Between Worlds DLC
};

/* @var vi_playerWeaponTypeHexValuesLVL4	vector for holding information about all weapon-type offsets, LVL 4*/
const vector<int> HWLWeapon::vi_playerWeaponTypeHexValuesLVL4 =
{
	//Link - Weapon Types Hex LVL 4
	0x3D,
	0x3E,
	0x3F,
	0x40,
	0x3C,
	0x83,
	0x85,

	//Zelda - Weapon Types Hex LVL 4
	0x44,
	0x45,
	0x86,

	//Shiek - Weapon Types Hex LVL 4
	0x49,

	//Impa - Weapon Types Hex LVL 4
	0x46,
	0x47,

	//Ganondorf - Weapon Types Hex LVL 4
	0x48,
	0x89,

	//Darunia - Weapon Types Hex LVL 4
	0x4A,

	//Ruto - Weapon Types Hex LVL 4
	0x4B,

	//Agitha - Weapon Types Hex LVL 4
	0x4C,

	//Imp Midna - Weapon Types Hex LVL 4
	0x4D,

	//Fi - Weapon Types Hex LVL 4
	0x4E,

	//Ghirahim - Weapon Types Hex LVL 4
	0x4F,

	//Zant - Weapon Types Hex LVL 4
	0x50,

	//Lana - Weapon Types Hex LVL 4
	0x41,
	0x42,
	0x43,

	//Cia - Weapon Types Hex LVL 4
	0x80,

	//Volga - Weapon Types Hex LVL 4
	0x81,

	//Wizzro - Weapon Types Hex LVL 4
	0x82,

	//Twili Midna - Weapon Types Hex LVL 4
	0x84,

	//Young Link - Weapon Types Hex LVL 4
	0x87,

	//Tingle - Weapon Types Hex LVL 4
	0x88,

	//??? - Weapon Types Hex  LVL 4, 2 times, without any weapon-type hex for LVL 4

	//Linkle - Weapon Types Hex  LVL 4
	0x8A,
	0x9A,

	//Skull Kid - Weapon Types Hex  LVL 4
	0x8B,

	//Toon Link - Weapon Types Hex LVL 4
	0x8C,
	0xAE,

	//Tetra - Weapon Types Hex LVL 4
	0x8D,

	//King Daphnes - Weapon Types Hex LVL 4
	0x8E,

	//Medli - Weapon Types Hex LVL 4
	0x92, //Update 1.3.0 (no LVL4-Weapon without any DLC)

	//Marin - Weapon Types Hex LVL 4
	0x96, //only 2nd DLC: Link's Awakening DLC        

	//Toon Zelda - Weapon Hex LVL 4
	0xAA, //only 3rd DLC: Phantom Hourglass and Spirit Tracks DLC

	//Ravio - Weapon Types Hex LVL 4
	0xBE, //only 4th DLC: A Link Between Worlds DLC

	//Yuga - Weapon Types Hex LVL 4
	0xC2, //only 4th DLC: A Link Between Worlds DLC
};

//only from 2nd DLC on. 0x00 => no Multi-Element Weapon for that type
/* @var vi_playerWeaponTypeHexValuesMultiElement	vector for holding information about all weapon-type offsets, Multi-Element Weapons */
const vector<int> HWLWeapon::vi_playerWeaponTypeHexValuesMultiElement =
{
	//Link - Weapon Types Hex Multi-Element
	0xC3, //Hylian Sword - Multi
	0xAF, //Magic Rod - Multi
	0xC4, //Great Fairy - Multi
	0x9B, //Gauntlets - Multi
	0x00, //Master Sword - Multi, not possible :D 
	0xC5, //Horse (Epona) - Multi
	0xC6, //Spinner - Multi

	//Zelda - Weapon Types Hex Multi-Element
	0xC9, //Rapier - Multi
	0xB2, //Baton - Multi
	0xCA, //Dominion Rod - Multi

	//Shiek - Weapon Types Hex Multi-Element
	0x9C, //Harp - Multi

	//Impa - Weapon Types Hex Multi-Element
	0xC7, //Giant Blade - Multi
	0xB0, //Naginata - Multi

	//Ganondorf - Weapon Types Hex Multi-Element
	0xCB, //Great Swords - Multi
	0xB3, //Trident - Multi

	//Darunia - Weapon Types Hex Multi-Element
	0x9E, //Hammer - Multi

	//Ruto - Weapon Types Hex Multi-Element
	0x9F, //Zora Scale - Multi

	//Agitha - Weapon Types Hex Multi-Element
	0xA0, //Parasol - Multi

	//Imp Midna - Weapon Types Hex Multi-Element
	0xA1, //Shackle - Multi

	//Fi - Weapon Types Hex Multi-Element
	0xA2, //Goddess Blade - Multi

	//Ghirahim - Weapon Types Hex Multi-Element
	0xB5, //Demon Blade - Multi

	//Zant - Weapon Types Hex Multi-Element
	0xB4, //Scimitars - Multi

	//Lana - Weapon Types Hex Multi-Element
	0xC8, //Book of Sorcery - Multi
	0xB1, //Spear - Multi
	0x9D, //Summoning Gate - Multi

	//Cia - Weapon Types Hex Multi-Element
	0xB6, //Scepter - Multi

	//Volga - Weapon Types Hex Multi-Element
	0xB7, //Dragon Spear - Multi

	//Wizzro - Weapon Types Hex Multi-Element
	0xB8, //Ring - Multi

	//Twili Midna - Weapon Types Hex Multi-Element
	0xB9, //Mirror - Multi

	//Young Link - Weapon Types Hex Multi-Element
	0xA3, //Mask - Multi

	//Tingle - Weapon Types Hex Multi-Element
	0xBA, //Balloon - Multi

	//??? - Weapon Types Hex  Multi-Element, 2 times, without any weapon-type hex for Multi-Element

	//Linkle - Weapon Types Hex  Multi-Element
	0xCC, //Crossbows - Multi
	0x00, //Boots (only 2nd DLC: Link's Awakening DLC) - Multi

	//Skull Kid - Weapon Types Hex  Multi-Element
	0xA4, //Ocarina - Multi

	//Toon Link - Weapon Types Hex Multi-Element
	0xCD, //Light Sword - Multi
	0x00, //Sand Wand - Multi

	//Tetra - Weapon Types Hex Multi-Element
	0xA5, //Cutlass - Multi

	//King Daphnes - Weapon Types Hex Multi-Element
	0xA6, //Sail - Multi

	//Medli - Weapon Types Hex Multi-Element
	0x00, //Rito Harp (Update 1.3.0 (no LVL4-Weapon without any DLC) ) - Multi

	//Marin - Weapon Types Hex Multi-Element
	0x00, //Bell (only 2nd DLC: Link's Awakening DLC) - Multi     

	//Toon Zelda - Weapon Hex Multi-Element
	0x00, //Phantom Arms (only 3rd DLC: Phantom Hourglass and Spirit Tracks DLC) - Multi

	//Ravio - Weapon Types Hex Multi-Element
	0x00, //Hammer (only 4th DLC: A Link Between Worlds DLC) - Multi

	//Yuga - Weapon Types Hex Multi-Element
	0x00, //Frame (only 4th DLC: A Link Between Worlds DLC) - Multi
};


/* @var vi_damage_base_defaults		vector for holding all default weapon damage-bases */
const vector<int> HWLWeapon::vi_damage_base_defaults =
{
	80,  //Base-Damage LVL-1
	150, //Base-Damage LVL-2
	280, //Base-Damage LVL-3
	500, //Base-Damage LVL-4
	300, //Base-Damage Master-Sword
	560, //Base-Damage Legendary-Weapon
};

/* @var weaponStateValuesHex		vector for holding all legendary-state values as hex*/
const vector<int> HWLWeapon::weaponStateValuesHex =
{
	0x03, //State - Normal Weapon
	0x13, //State - Legendary Weapon
	0x0B, //State - Master-Sword
};

/* @var weaponStateValuesNames		vector for holding all legendary-state values as string*/
const vector<string> HWLWeapon::weaponStateValuesNames =
{
	"Normal Weapon", //State - 0x03
	"Legendary",     //State - 0x13
	"Master Sword",  //State - 0x0B
};

/* @var weaponSkillNames			vector for holding skill-names, index as hex = Weapon-ID*/
const vector<string> HWLWeapon::weaponSkillNames =
{
	"Free Slot",
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
	"MS: Evil's Ban",
	"Legendary",
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
	"MS: Exorcism",
	"Heart Power", //only with Update 1.6.0
	"No Slot",
};

/* @var weaponLVLMax				maximal-value of the weapon-LVL */
const int HWLWeapon::weaponLVLMax = 4;

/* @var weaponDamageBaseMax			maximal-value of the weapon damage-base */
const int HWLWeapon::weaponDamageBaseMax = 650;

/* @var weaponStarsMax				maximal-value of the weapon-stars */
const int HWLWeapon::weaponStarsMax = 5;

/* @var weaponSkillSlotKillMax		maximal-value of the weapon Kills for a Skill-Slot */
const int HWLWeapon::weaponSkillSlotKillMax = 65000;


/* @var weaponSkillValueNoSkill		hex-Value of the 'No-Skill' entry (locked skill-slot) */
const int HWLWeapon::weaponSkillValueNoSkill = 0xFF;

/* @var weaponBlankWeaponHex		hex-representation of a unused weapon */
const string HWLWeapon::weaponBlankWeaponHex = "00000000000000000000000000000000ffff00000000ffffffffffffffff00";



/**
* Only the initialization of the normal-constructor
*/
HWLWeapon::HWLWeapon(int i_offset, int i_character_id, bool b_is_unsued_weapon, bool b_will_copied)
{
	if (!b_will_copied)
	{
		//Reset static values if new saveFile is opened
		if (this->b_isNewSaveFile)
			vi_disabledweaponSkillIDs.clear();

		//set or calculate all needed members
		this->i_offset = i_offset;
		this->i_id = this->calc_weapon_id();
		this->i_lvl = 1;
		this->i_damage_base = this->calc_damage_base();
		this->i_stars = this->calc_stars();
		this->i_damage = this->calc_damage();
		this->i_state = this->calc_state();
		this->vi_skill_slot_kills = this->calc_skill_slot_kills();
		this->vi_skill_slots = this->calc_skill_slots();
		this->i_character_id = i_character_id;
		this->i_type = 0;
		this->b_is_unsued_weapon = b_is_unsued_weapon;
		this->b_is_multi_element_weapon = false;
		this->b_weapon_has_changed = false;
	}


}

/**
* Only the initialization of the normal-destructor
*/
HWLWeapon::~HWLWeapon()
{
}



/**
* This method calculates the current weapon-id
*
*	@return int		the current weapon-id
*
*/
int HWLWeapon::calc_weapon_id()
{
	//declare/define needed variables
	string s_weapon_id;
	int i_weapon_id_offset = this->i_offset + this->weaponIDOffsetDiff;

	//get hex-value from the file-content holder and convert it to int
	s_weapon_id = this->getHexStringFromFileContent(i_weapon_id_offset, this->weaponIDOffsetLength);
	int i_weapon_id = this->HexStringToInt(s_weapon_id);

	//return the current int-value
	return i_weapon_id;
}

/**
* This method calculates the current weapon damage-base
*
*	@return int		the current weapon damage-base
*
*/
int HWLWeapon::calc_damage_base()
{
	//declare/define needed variables
	string s_damage_base;
	int i_damage_base_offset = this->i_offset + this->weaponDamageBaseOffsetDiff;

	//get hex-value from the file-content holder and convert it to int
	s_damage_base = this->getHexStringFromFileContent(i_damage_base_offset, this->weaponDamageBaseOffsetLength);
	int i_damage_base = this->HexStringToInt(s_damage_base);

	//return the current int-value
	return i_damage_base;
}

/**
* This method calculates the current weapon-stars
*
*	@return int		the current weapon-stars
*
*/
int HWLWeapon::calc_stars()
{
	//declare/define needed variables
	string s_stars;
	int i_stars_offset = this->i_offset + this->weaponStarsOffsetDiff;

	//get hex-value from the file-content holder and convert it to int
	s_stars = this->getHexStringFromFileContent(i_stars_offset, this->weaponStarsOffsetLength);
	int i_stars = this->HexStringToInt(s_stars);

	//return the current int-value
	return i_stars;
}

/**
* This method calculates the current weapon-damage
*
*	@return int		the current weapon-damage
*
*/
int HWLWeapon::calc_damage()
{
	//calculate the real damage of a weapon: 
	// DamageBase + ( DamageBase * (Stars * 0.1) )
	//because every star give 10% of the current damage-base, we have to add those values
	int i_damage = this->i_damage_base + (this->i_damage_base * (this->i_stars * 0.1));

	//return the current int-value
	return i_damage;
}

/**
* This method calculates the current weapon legendary-state
*
*	@return int		the current weapon legendary-state
*
*/
int HWLWeapon::calc_state()
{
	//declare/define needed variables
	string s_state;
	int i_state_offset = this->i_offset + this->weaponStateOffsetDiff;

	//get hex-value from the file-content holder and convert it to int
	s_state = this->getHexStringFromFileContent(i_state_offset, this->weaponStateOffsetLength);
	int i_state = this->HexStringToInt(s_state);

	//return the current int-value
	return i_state;
}

/**
* This method calculates the current weapon Kills for each Skill-Slot
*
*	@return vector<int>		the current Kills of all Skill-Slots
*
*/
vector<int> HWLWeapon::calc_skill_slot_kills()
{
	//declare/define needed variables
	string s_skill_slot_kills;  //holds the hex-value
	vector<int> vi_temp;  //hold all current calculated kills, index = skill-slot
	int i_skill_slot_kills_offset = this->i_offset + this->weaponSkillSlotKillsOffsetDiff; //offset-begin

	//get hex-value from the file-content holder and because we need the "normal-order", the last
	//parameter = true
	s_skill_slot_kills = this->getHexStringFromFileContent(i_skill_slot_kills_offset, this->weaponSkillSlotKillsOffsetLength, true);

	//iterate over the hex-string and calculate each kill-value of an Skill-Slot
	for (int i = 0; i < (signed)s_skill_slot_kills.size(); i += (this->weaponSkillSlotKillsLength * 2))
	{
		//make substring of the form XX XX (Kill-Value of an Skill-Slot )
		//and convert the Byte-Order to Little-Endian, cause we got the 
		// "normal-order" of the hole hex-string before
		string s_skill_slot_kill = s_skill_slot_kills.substr(i, (this->weaponSkillSlotKillsLength * 2));
		this->convertByteOrder(s_skill_slot_kill);

		//Add the hex-value, converted to int, to the temp-vector
		vi_temp.push_back(this->HexStringToInt(s_skill_slot_kill));
	}

	//return the temp-vector
	return vi_temp;
}

/**
* This method calculates the current weapon skill-values for each Skill-Slot
*
*	@return vector<int>		the current skill-values of all Skill-Slots
*
*/
vector<int> HWLWeapon::calc_skill_slots()
{
	//declare/define needed variables
	string s_skill_slots; //holds the hex-value
	vector<int> vi_temp;  //hold all current calculated skill-IDs, index = skill-slot
	int i_skill_slots_offset = this->i_offset + this->weaponSkillSlotsOffsetDiff; //offset-begin

	//get hex-value from the file-content holder and because we need the "normal-order", the last
	//parameter = true
	s_skill_slots = this->getHexStringFromFileContent(i_skill_slots_offset, this->weaponSkillSlotsOffsetLength, true);

	//iterate over the hex-string and calculate each skill-ID of an Skill-Slot
	for (int i = 0; i < (signed)s_skill_slots.size(); i += (this->weaponSkillSlotsLength * 2))
	{
		//make substring of the form XX (skill-ID of an Skill-Slot )
		//and convert the Byte-Order to Little-Endian, cause we got the 
		// "normal-order" of the hole hex-string before
		string s_skill_slot = s_skill_slots.substr(i, (this->weaponSkillSlotsLength * 2));
		this->convertByteOrder(s_skill_slot);

		//Add the hex-value, converted to int, to the temp-vector
		vi_temp.push_back(this->HexStringToInt(s_skill_slot));
	}

	//return the temp-vector
	return vi_temp;
}



/**
* This method set the current weapon ID-value
* to the file-content holder
*
*/
void HWLWeapon::save_weapon_id()
{
	//declare/define needed variables
	int i_id_tmp = this->i_id;
	string s_weapon_id;
	int i_weapon_id_offset = this->i_offset + this->weaponIDOffsetDiff;

	//convert the current integer-value to hex and add needed zeros, if we
	//don't have the complete length (calculate with offset-length multiplied by 2)
	s_weapon_id = this->intToHexString(i_id_tmp, false);
	this->addZeroToHexString(s_weapon_id, this->weaponIDOffsetLength * 2);

	//set converted hex-value to the file-content holder
	this->setHexStringToFileContent(s_weapon_id, i_weapon_id_offset);
}

/**
* This method set the current weapon damage-base-value
* to the file-content holder
*
*/
void HWLWeapon::save_damage_base()
{
	//declare/define needed variables
	int i_damage_base_tmp = this->i_damage_base;
	string s_damage_base;
	int i_damage_base_offset = this->i_offset + this->weaponDamageBaseOffsetDiff;

	//convert the current integer-value to hex and add needed zeros, if we
	//don't have the complete length (calculate with offset-length multiplied by 2)
	s_damage_base = this->intToHexString(i_damage_base_tmp, false);
	this->addZeroToHexString(s_damage_base, this->weaponDamageBaseOffsetLength * 2);

	//set converted hex-value to the file-content holder
	this->setHexStringToFileContent(s_damage_base, i_damage_base_offset);
}

/**
* This method set the current weapon stars-value
* to the file-content holder
*
*/
void HWLWeapon::save_stars()
{
	//declare/define needed variables
	int i_stars_tmp = this->i_stars;
	string s_stars;
	int i_stars_offset = this->i_offset + this->weaponStarsOffsetDiff;

	//convert the current integer-value to hex and add needed zeros, if we
	//don't have the complete length (calculate with offset-length multiplied by 2)
	s_stars = this->intToHexString(i_stars_tmp, false);
	this->addZeroToHexString(s_stars, this->weaponStarsOffsetLength * 2);

	//set converted hex-value to the file-content holder
	this->setHexStringToFileContent(s_stars, i_stars_offset);
}

/**
* This method set the current weapon legendary-state-value
* to the file-content holder
*
*/
void HWLWeapon::save_state()
{
	//declare/define needed variables
	int i_state_tmp = this->i_state;
	string s_state;
	int i_state_offset = this->i_offset + this->weaponStateOffsetDiff;

	//convert the current integer-value to hex and add needed zeros, if we
	//don't have the complete length (calculate with offset-length multiplied by 2)
	s_state = this->intToHexString(i_state_tmp, false);
	this->addZeroToHexString(s_state, this->weaponStateOffsetLength * 2);

	//set converted hex-value to the file-content holder
	this->setHexStringToFileContent(s_state, i_state_offset);
}

/**
* This method set the current weapon Kills of each Skill-Slot
* to the file-content holder
*
*/
void HWLWeapon::save_skill_slot_kills()
{
	//declare/define needed variables
	string s_skill_slot_kills; //hold the kills of all skill-slots (as hex)
	int i_skill_slot_kills_offset = this->i_offset + this->weaponSkillSlotKillsOffsetDiff; //offset-begin

	//iterate over all skill-slots to get the current needed kills of them
	for (int i = 0; i < (signed)this->vi_skill_slot_kills.size(); i++)
	{
		//convert the current integer-value of a Skill-Slot
		//to hex and add needed zeros, if we don't have the 
		//complete length (calculate with offset-length multiplied by 2)
		string s_skill_slot_kill = this->intToHexString(vi_skill_slot_kills[i], false);
		this->addZeroToHexString(s_skill_slot_kill, (this->weaponSkillSlotKillsLength * 2));

		//convert the ByteOrder to BigEndian, because we need the real-order of the
		//hex-string, how it's save in the savefile
		this->convertByteOrder(s_skill_slot_kill);

		//add the hex-representation of the current needed Kills of the current Skill-Slot
		//to the hex-string (to the end)
		s_skill_slot_kills.append(s_skill_slot_kill);
	}

	//set converted hex-value to the file-content holder and because we set the
	//string directly, without any converting of the ByteOrder, we neeed the last
	//parameter = true
	this->setHexStringToFileContent(s_skill_slot_kills, i_skill_slot_kills_offset, true);

}

/**
* This method set the current weapon skill-values of each Skill-Slot
* to the file-content holder
*
*/
void HWLWeapon::save_skill_slots()
{
	//declare/define needed variables
	string s_skill_slots; //hold the skill-IDs of all skill-slots (as hex)
	int i_skill_slots_offset = this->i_offset + this->weaponSkillSlotsOffsetDiff; //offset-begin

	//iterate over all skill-slots to get the current skill-IDs of them
	for (int i = 0; i < (signed)this->vi_skill_slots.size(); i++)
	{
		//convert the current integer-value of a Skill-Slot
		//to hex and add needed zeros, if we don't have the 
		//complete length (calculate with offset-length multiplied by 2)
		string s_skill_slot = this->intToHexString(vi_skill_slots[i], false);
		this->addZeroToHexString(s_skill_slot, (this->weaponSkillSlotsLength * 2));

		//convert the ByteOrder to BigEndian, because we need the real-order of the
		//hex-string, how it's save in the savefile
		this->convertByteOrder(s_skill_slot);

		//add the hex-representation of the current skill-IDs of the current Skill-Slot
		//to the hex-string (to the end)
		s_skill_slots.append(s_skill_slot);
	}

	//set converted hex-value to the file-content holder and because we set the
	//string directly, without any converting of the ByteOrder, we neeed the last
	//parameter = true
	this->setHexStringToFileContent(s_skill_slots, i_skill_slots_offset, true);

}



/**
* Setter for the weapons-name
*
*	@var string		s_name		name to set
*
*/
void HWLWeapon::set_name(string s_name)
{
	this->s_name = s_name;
}

/**
* Setter for the weapons-ID
*
*	@var int	i_id		ID-value to set
*
*/
void HWLWeapon::set_id(int i_id)
{
	this->i_id = i_id;
}

/**
* Setter for the weapons-LVL
*
*	@var int	i_lvl		lvl-value to set
*
*/
void HWLWeapon::set_lvl(int i_lvl)
{
	//only change lvl, if we have not the same as before
	if ((i_lvl != this->i_lvl))
	{
		//check if lvl-value smaller then 1, then set it directly to 1
		//also check for the maximal-value
		if (i_lvl > this->weaponLVLMax)
			i_lvl = this->weaponLVLMax;
		else if (i_lvl <= 1)
			i_lvl = 1;


		if (!this->b_is_unsued_weapon)
			this->i_lvl = i_lvl;
		else
			this->i_lvl = 0;
	}
}

/**
* Setter for the weapons-LVL-Hex (for all other LVLs
* of that weapon)
*
*	@var vector<int>	vi_lvl_hex		vector of int of the LVL-hex to set
*
*/
void HWLWeapon::set_lvl_hex(vector<int> vi_lvl_hex)
{
	this->vi_lvl_hex = vi_lvl_hex;
}

/**
* Setter for the weapons damage-base
*
*	@var int	i_damage_base	damage-base-value to set
*
*/
void HWLWeapon::set_damage_base(int i_damage_base)
{
	//check if damage-base-value smaller then (or equal) 0, then set it directly to 1
	//also check for the maximal-value
	if (i_damage_base > this->weaponDamageBaseMax)
		i_damage_base = this->weaponDamageBaseMax;
	else if (i_damage_base <= 0)
		i_damage_base = 1;

	if (!this->b_is_unsued_weapon)
		this->i_damage_base = i_damage_base;
	else
		this->i_damage_base = 0;
}

/**
* Setter for the weapons-stars
*
*	@var int	i_stars		stars-value to set
*
*/
void HWLWeapon::set_stars(int i_stars)
{
	//check if stars-value smaller then (or equal) 0, then set it directly to 0
	//also check for the maximal-value
	if (i_stars > this->weaponStarsMax)
		i_stars = this->weaponStarsMax;
	else if (i_stars < 0)
		i_stars = 0;

	this->i_stars = i_stars;
}

/**
* Setter for the weapons-legendary-state
*
*	@var int	i_state		legendary-state-value to set
*
*/
void HWLWeapon::set_state(int i_state)
{
	if (!this->b_is_unsued_weapon)
		this->i_state = i_state;
	else
		this->i_state = 0x00;
}

/**
* Setter for the weapons Kills of a Skill-Slot
*
*	@var int	i_slot_id		slot-id to identify the slot
*
*	@var int	i_kill_value	Kills-value to set
*
*/
void HWLWeapon::set_skill_slot_kill(int i_slot_id, int i_kill_value)
{
	//check if the slot-id is bigger or equal 0 and smaller then 8
	//then check if we have a kill-value smaller then 0 and set it 
	//to 0 directly, also check for the maximal-value
	if (i_slot_id >= 0 && i_slot_id < 8)
	{
		if (i_kill_value > this->weaponSkillSlotKillMax)
			i_kill_value = this->weaponSkillSlotKillMax;
		else if (i_kill_value <= 0)
			i_kill_value = 0;

		this->vi_skill_slot_kills[i_slot_id] = i_kill_value;
	}

}

/**
* Setter for the weapons Kills-vector
*
*	@var vector<int>	vi_skill_slot_kills		the vector which holds the new data
*
*/
void HWLWeapon::set_skill_kills(vector<int> vi_skill_slot_kills)
{
	this->vi_skill_slot_kills = vi_skill_slot_kills;
}

/**
* Setter for the weapons skills-value/ID of a Skill-Slot
*
*	@var int	i_slot_id		slot-id to identify the slot
*
*	@var int	i_skill_id		skills-value/ID to set
*
*/
void HWLWeapon::set_skill_slot(int i_slot_id, int i_skill_id)
{
	//check if the slot-id is bigger or equal 0 and smaller then 8
	if (i_slot_id >= 0 && i_slot_id < 8)
	{
		this->vi_skill_slots[i_slot_id] = i_skill_id;
	}
}

/**
* Setter for the weapons skills-vector
*
*	@var vector<int>	vi_skill_slots		the vector which holds the new data
*
*/
void HWLWeapon::set_skills(vector<int> vi_skill_slots)
{
	this->vi_skill_slots = vi_skill_slots;
}


/**
* Setter for the character-ID the weapon belongs to
*
*	@var int	i_character_id		the belonging character-id
*
*/
void HWLWeapon::set_character_id(int i_character_id)
{
	this->i_character_id = i_character_id;
}

/**
* Setter for the weapons-type
*
*	@var int	i_type		type-value to set
*
*/
void HWLWeapon::set_type(int i_type)
{
	//check if the type is bigger or equal -1
	//we need -1 for unused weapons
	if (this->i_type >= -1)
		this->i_type = i_type;
}

/**
* Setter for the weapons Unused-State
*
*	@var bool	b_is_unsued_weapon		Unused-State to set
*
*/
void HWLWeapon::set_IsUnused(bool b_is_unsued_weapon)
{
	this->b_is_unsued_weapon = b_is_unsued_weapon;
}

/**
* Setter for the weapons Multi-Elements-State
*
*	@var bool	b_is_multi_element_weapon		Multi-Elements-State to set
*
*/
void HWLWeapon::set_IsMultiElement(bool b_is_multi_element_weapon)
{
	this->b_is_multi_element_weapon = b_is_multi_element_weapon;
}

/**
* Setter for the weapons Multi-Element-Hex
*
*	@var int	i_multi_element_weapon_hex		Multi-Element-Hex to set
*
*/
void HWLWeapon::set_multi_element_hex(int i_multi_element_weapon_hex)
{
	this->i_multi_element_weapon_hex = i_multi_element_weapon_hex;
}

/**
* Setter for the disabled-WeaponSkills
*
*	@var int	i_skill_id		Skill-ID to set to disabled
*
*/
void HWLWeapon::set_isWeaponSkillDisabled(int i_skill_id)
{
	vi_disabledweaponSkillIDs.push_back(i_skill_id);
}



/**
* Getter for the weapons-name
*
*	@return string		the name of the weapon
*
*/
string HWLWeapon::get_name()
{
	return this->s_name;
}

/**
* Getter for the weapons-ID
*
*	@return int		the ID of the weapon
*
*/
int HWLWeapon::get_id()
{
	return this->i_id;
}

/**
* Getter for the weapons-LVL
*
*	@return int		the LVL of the weapon
*
*/
int HWLWeapon::get_lvl()
{
	return this->i_lvl;
}

/**
* Getter for the weapons LVL-hex (for all 4 LVLs)
*
*	@return vector<int>		vector, which contain all LVL-hex of that weapon
*
*/
vector<int> HWLWeapon::get_lvl_hex()
{
	return this->vi_lvl_hex;
}

/**
* Getter for the weapons-damage-base
*
*	@return int		the damage-base of the weapon
*
*/
int HWLWeapon::get_damage_base()
{
	return this->i_damage_base;
}

/**
* Getter for the weapons-stars
*
*	@return int		the stars of the weapon
*
*/
int HWLWeapon::get_stars()
{
	return this->i_stars;
}

/**
* Getter for the weapons-damage
*
*	@return int		the damage of the weapon
*
*/
int HWLWeapon::get_damage()
{
	return this->i_damage;
}

/**
* Getter for the weapons-legendary-state
*
*	@return bool	the legendary-state of the weapon
*
*/
bool HWLWeapon::get_state()
{
	switch (this->i_state)
	{

	case 0x00: //unused-weapon, no legendary-state
	case 0x03: //normal-weapon, no legendary-state
		return false;
		break;

	case 0x13: //normal-weapon, legendary-state
		return true;
		break;

	case 0x0B: //Master-Sword (implicit the legendary-unique-state)
		return true;
		break;

	default: //if we have some other-value, return false
		return false;
		break;
	}
}

/**
* Getter for the weapons-legendary-state as a String
*
*	@return string		the legendary-state of the weapon as String
*
*/
string HWLWeapon::get_state(bool b_return_as_string)
{
	string s_state;
	switch (this->i_state)
	{

	case 0x00: //unused-weapon, no legendary-state
	case 0x03: //normal-weapon, no legendary-state
		s_state = this->weaponStateValuesNames[0];
		break;

	case 0x13: //normal-weapon, legendary-state
		s_state = this->weaponStateValuesNames[1];
		break;

	case 0x0B: //Master-Sword (implicit the legendary-unique-state)
		s_state = this->weaponStateValuesNames[2];
		break;

	default: //if we have some other-value, return a "Unknown"-State
		s_state = "Unknown";
		break;
	}

	return s_state;
}

/**
* Getter for the weapons Kills of a given Skill-Slot
*
*	@var int	i_slot_id		slot-id to identify the slot
*
*	@return int		the needed Kills of the given Skill-Slot
*
*/
int HWLWeapon::get_skill_slot_kill(int i_slot_id)
{
	//check if the slot-id is bigger or equal 0 and smaller then 8
	if (i_slot_id >= 0 && i_slot_id < 8)
	{
		return this->vi_skill_slot_kills[i_slot_id];
	}
	else{
		return -1;
	}
}

/**
* Getter for the weapons Kills-vector
*
*	@return vector<int>		the needed Kills of all slots
*
*/
vector<int> HWLWeapon::get_skill_kills()
{
	return this->vi_skill_slot_kills;
}

/**
* Getter for the weapons Skills-Value/ID of a given Skill-Slot
*
*	@var int	i_slot_id		slot-id to identify the slot
*
*	@return int		the Skill-Value/ID of the given Skill-Slot
*
*/
int HWLWeapon::get_skill_slot(int i_slot_id)
{
	//check if the slot-id is bigger or equal 0 and smaller then 8
	if (i_slot_id >= 0 && i_slot_id < 8)
	{
		return this->vi_skill_slots[i_slot_id];
	}
	else{
		return 0;
	}
}

/**
* Getter for the weapons Skills-Value/ID of a given Skill-Slot
* as the correct Name of the Skill
*
*	@var int	i_slot_id		slot-id to identify the slot
*
*	@return string		the correct Skill-Name of a given Skill-Slot
*
*/
string HWLWeapon::get_skill_slot(int i_slot_id, bool b_get_string)
{
	//check if the slot-id is bigger or equal 0 and smaller then 8
	if (i_slot_id >= 0 && i_slot_id < 8)
	{
		//get the current skill-ID of the given Skill-Slot
		int i_skill_value = this->vi_skill_slots[i_slot_id];

		//check if we have the "No-Skill" ID (0xFF), then set the
		//name to the last entry of the name-vector, if not
		//skill-ID = name-vector index
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

/**
* Getter for the weapons Skills-vector
*
*	@return vector<int>		the current skill-ids of all slots
*
*/
vector<int> HWLWeapon::get_skills()
{
	return this->vi_skill_slots;
}

/**
* Getter for the character-ID that the weapon belongs to
*
*	@return int		the character-ID of the weapon
*
*/
int HWLWeapon::get_character_id()
{
	return this->i_character_id;
}

/**
* Getter for the weapons-type
*
*	@return int		the type of the weapon
*
*/
int HWLWeapon::get_type()
{
	return this->i_type;
}

/**
* Getter for the weapons Unused-State
*
*	@return bool		the Unused-State of the weapon
*
*/
bool HWLWeapon::get_IsUnused()
{
	return this->b_is_unsued_weapon;
}

/**
* Getter for the weapons Multi-Elements-State
*
*	@return bool		the Multi-Elements-State of the weapon
*
*/
bool HWLWeapon::get_IsMultiElement()
{
	return this->b_is_multi_element_weapon;
}

/**
* Getter for the weapons Multi-Element-Hex
*
*	@return int		the Multi-Element-Hex of the weapon
*
*/
int HWLWeapon::get_multi_element_hex()
{
	return this->i_multi_element_weapon_hex;
}

/**
* Getter for the weapons Changed-State
*
*	@return int		the Changed-State of the weapon
*
*/
bool HWLWeapon::get_HasWeaponChanged()
{
	return this->b_weapon_has_changed;
}

/**
* Getter if given Skill-ID is a disbaled-one
*
*	@var int	i_skill_id		skill-id to check
*
*	@return bool		TRUE if Skill-ID is diabsled, FALSE otherwise
*
*/
bool HWLWeapon::get_isWeaponSkillDisabled(int i_skill_id)
{
	for (int i = 0; i < vi_disabledweaponSkillIDs.size(); i++)
	{
		if (vi_disabledweaponSkillIDs[i] == i_skill_id)
			return true;
	}

	return false;
}

/**
* Getter for how many Weapon-Skills are disabled
*
*	@return int		value how many Skills are disabled
*
*/
int HWLWeapon::get_WeaponSkillDisabledCounter()
{
	return vi_disabledweaponSkillIDs.size();
}



/**
* This method change the current damage-base and re-calculate
*  the real damage
*
*	@var int	i_damage_base		the new damage-base to set
*
*/
void HWLWeapon::change_damage_base(int i_damage_base)
{
	//change only, if we have not the same damage-base value
	if (this->i_damage_base != i_damage_base)
	{
		//set new damage-base and re-calculate the damage itself
		this->set_damage_base(i_damage_base);
		this->i_damage = this->calc_damage();
	}
}


/**
* This method change the current weapon-lvl and re-calculate
*  the damage-base and real damage (also set the new weapon-id,
*  based on the given lvl)
*
*	@var int	i_lvl		the new lvl-value to set
*
*/
void HWLWeapon::change_lvl(int i_lvl)
{
	//only do a lvl-change if we don't have a multi-element weapon, cause there are only LVL-4 Weapons
	//with a second element, nth more. So no LVL-Change with it.
	if (!this->b_is_multi_element_weapon)
	{
		//get the DlcSafetyCheck-State
		bool b_dlc_safety_checks = stoi(this->hwlc_config->get_param_value("DlcSafetyCheck", this->hwlc_config->get_sectionID("General")));

		//check if we have "MedlI" as character (ID: 26) and if we have no DLCs installed
		//If TRUE and if we want to set the Max-LVL (4) set it to 3. Cause game will freeze otherwise.
		// only if DlcSafetyCheck is activated
		if (i_lvl == this->weaponLVLMax && this->i_character_id == 26 && this->i_type == 0
			&& this->s_savefile_game_version != "1.0.0" && this->s_savefile_game_version != "1.2.0")
		{
			if (b_dlc_safety_checks)
			{
				int i_dlcs_installed = 0;
				for (int i = 0; i < this->vb_game_dlc_installed.size(); i++)
				{
					if (this->vb_game_dlc_installed[i])
						i_dlcs_installed++;
				}

				if (i_dlcs_installed == 0)
					i_lvl--;
			}

		}


		//change only, if we have not the same lvl-value
		if (this->i_lvl != i_lvl)
		{
			//set new lvl and the standard damage-base of that lvl
			this->set_lvl(i_lvl);
			this->set_damage_base(this->vi_damage_base_defaults[i_lvl - 1]);

			//change the current weapon-id, based on the given-lvl - 1,
			//because the entries begins with zero. (check the lvl-hex-
			//vector for that
			this->set_id(this->vi_lvl_hex[i_lvl - 1]);

			//re-calculate the damage itself
			this->i_damage = this->calc_damage();
		}
	}

}


/**
* This method change the current stars and re-calculate
*  the real damage
*
*	@var int	i_stars		the new stars-value to set
*
*/
void HWLWeapon::change_stars(int i_stars)
{
	//change only, if we have not the same stars-value
	if (this->i_stars != i_stars)
	{
		//set new stars-value and re-calculate the damage itself
		this->set_stars(i_stars);
		this->i_damage = this->calc_damage();
	}
}

/**
* This method change the current legendary-sate with safety-checks
*
*	@var bool	b_is_legendary		the legendary-state to set
*
*/
void HWLWeapon::change_legendary_state(int b_is_legendary)
{
	//check if we have the MasterSword and set the special state then, else: normal behaviour
	if (this->i_id != HWLSaveEdit::HWLWeapon::vi_playerWeaponTypeHexValues[4])
	{
		//change only if we have it set to TRUE
		if (b_is_legendary)
			this->set_state(HWLSaveEdit::HWLWeapon::weaponStateValuesHex[1]);
		else
			this->set_state(HWLSaveEdit::HWLWeapon::weaponStateValuesHex[0]);
	}
	else
	{
		this->set_state(HWLSaveEdit::HWLWeapon::weaponStateValuesHex[2]);
	}

}

/**
* This method change the current Multi-Element state and re-calculate
*  lvl and implicit others.
*
*	@var bool	b_is_multi_element_weapon       the multi-element-state to set
*
*/
void HWLWeapon::change_multi_element_state(bool b_is_multi_element_weapon)
{
	//get the DlcSafetyCheck-State
	bool b_dlc_safety_checks = stoi(this->hwlc_config->get_param_value("DlcSafetyCheck", this->hwlc_config->get_sectionID("General")));

	bool b_really_change = false;
	if (this->s_savefile_game_version != "1.0.0" && this->s_savefile_game_version != "1.2.0"
		&& this->s_savefile_game_version != "1.3.0" && (this->vb_game_dlc_installed[1] || this->vb_game_dlc_installed[2]
		|| this->vb_game_dlc_installed[3])
		)
	{
		b_really_change = true;
	}
	else{
		if (b_dlc_safety_checks || this->s_savefile_game_version == "1.0.0" || this->s_savefile_game_version == "1.2.0"
			|| this->s_savefile_game_version == "1.3.0")
			b_really_change = false;
		else
			b_really_change = true;
	}

	//do it only if we have a right game-version and one of the needed DLCs is installed
	// and DlcSafetyCheck is activated
	if (b_really_change)
	{
		//change only, if we have not the same multi-element-state and if we have a valid-hex for that type
		if ((this->b_is_multi_element_weapon != b_is_multi_element_weapon)
			&& this->i_multi_element_weapon_hex != 0x00)
		{
			//set multi-element-state  and re-calculate the LVL itself
			//First: Set to false and LVL to 1 to re-calculate Weapons LVL to MAX.
			this->set_IsMultiElement(false);
			this->set_lvl(1);
			this->change_lvl(this->weaponLVLMax);

			//if the state change to TRUE, set the new ID
			if (b_is_multi_element_weapon)
				this->set_id(this->i_multi_element_weapon_hex);

			//finally, set the new state
			this->set_IsMultiElement(b_is_multi_element_weapon);
		}
	}


}



/**
* This method create a new default-weapon on the current object, based on the current
*  character and weapon-type.
* All needed member-variables are setting to their default values
*  (also a special-check for the unique Master-Sword)
*
*	@var bool	b_is_first_weapon       state, if its charas first-weapon
*/
void HWLWeapon::generate_default_weapon(bool b_is_first_weapon)
{
	//If we have an unsued weapon and NOT the first calculated weapon
	// that we changed/add - noticed it for later-usage
	if (this->b_is_unsued_weapon && !b_is_first_weapon)
		this->b_weapon_has_changed;

	//define an weapon-counter, and calculate all used weapon-types
	int i_weapon_count = 0;
	for (int i = 0; i < this->i_character_id; i++)
	{
		//count all weapon-types, from first-chara to current chara - 
		//so we know then which weapon-type we have to use for that character or better which it's the first weapon-
		//type of this character
		i_weapon_count = i_weapon_count + this->vi_playerWeaponTypeCount[i];
	}

	//calculate the default-weapon-id ( = LVl-1 Weapon of that type), based on the weappon-count
	//and the current-type
	int i_default_weapon_id = this->vi_playerWeaponTypeHexValues[i_weapon_count + this->i_type];

	//set the id, lvl and also the Unused-State and Multi-Element-State (to false)
	this->set_id(i_default_weapon_id);
	this->set_lvl(1);
	this->set_IsUnused(false);
	this->set_IsMultiElement(false);

	//Check if we have the Master Sword and set the Damage base to the correct defaults
	if (i_default_weapon_id == this->vi_playerWeaponTypeHexValues[4])
		this->set_damage_base(this->vi_damage_base_defaults[4]); //Master-Sword Damage-Base
	else
		this->set_damage_base(this->vi_damage_base_defaults[0]); //Normal Weapon Damage-base

	//do a little trick, first set the stars to 1 and then change the stars to 
	//zero, so we re-calculate the real-damage automatically
	this->set_stars(1);
	this->change_stars(0);

	//Set legendary state and check if we have the Master sword
	if (i_default_weapon_id == this->vi_playerWeaponTypeHexValues[4])
		this->set_state(this->weaponStateValuesHex[2]); //Master-Sword, unique Legendary-State
	else
		this->set_state(this->weaponStateValuesHex[0]); //Normal Weapon, no Legendary-State

	//iterate over all Skill-Slots, to set the needed Kills of all to zero
	//and the Skill-IDs to "No-Slot", except the first one - it's a "Free-Slot"
	for (int i = 0; i < 8; i++)
	{
		this->set_skill_slot_kill(i, 0);

		if (i == 0)
			this->set_skill_slot(i, 0);
		else
			this->set_skill_slot(i, this->weaponSkillValueNoSkill);
	}

	//re-calculate the hex-values of all weapon-lvls to zero (it's a security reason)
	vector<int> vi_lvl_hexValues(this->weaponLVLMax);
	for (int i = 0; i < (signed)vi_lvl_hexValues.size(); i++)
		vi_lvl_hexValues[i] = 0;

	//re-calculate the hex-values of all weapon-lvls of that type (it's a security reason)
	vi_lvl_hexValues[0] = (i_default_weapon_id);
	vi_lvl_hexValues[1] = (i_default_weapon_id + 1);
	vi_lvl_hexValues[2] = (i_default_weapon_id + 2);
	vi_lvl_hexValues[3] = (HWLWeapon::vi_playerWeaponTypeHexValuesLVL4[i_weapon_count + this->i_type]);

	//set the new lvl-hex-values
	this->set_lvl_hex(vi_lvl_hexValues);

	//re-calculate and set the hex-value of the multi-element-type of this weapon 
	//and then we're done with a new default-weapon
	this->set_multi_element_hex((HWLWeapon::vi_playerWeaponTypeHexValuesMultiElement[i_weapon_count + this->i_type]));

}


/**
* This method delete the current weapon and set it to an unused one.
* Also re-calculate all needed members, based on the new unused-weapon
*
*/
void HWLWeapon::delete_weapon()
{
	//set the complete-hex value of that weapon to the blank-weapon-hex (based on offset),
	//to the file-content holder directly
	this->setHexStringToFileContent(this->weaponBlankWeaponHex, this->i_offset, true);

	//simply re-calculate all current members, based on the new weapon-hex we read-out
	this->vi_skill_slot_kills = this->calc_skill_slot_kills();
	this->i_id = this->calc_weapon_id();
	this->i_damage_base = this->calc_damage_base();
	this->i_stars = this->calc_stars();
	this->vi_skill_slots = this->calc_skill_slots();
	this->i_state = this->calc_state();
	this->b_is_unsued_weapon = true;
	this->b_is_multi_element_weapon = false;

	//lvl to 1
	this->i_lvl = 1;
}



/**
* This method returns an formatted string, which contain all needed skill-IDs as Names
*
*	@return string		formatted output with all needed skill-IDs as Names
*
*/
string HWLWeapon::get_WeaponsSkillsForOutput()
{
	string s_output;

	for (int i = 0; i < 8; i++)
	{
		s_output = s_output + "\n   Slot " + to_string(i + 1) + ": " + this->get_skill_slot(i, true) + " (" + to_string(this->get_skill_slot_kill(i)) + " Kills to Unlock) \n";
	}

	return s_output;
}

/**
* This method returns an formatted string, which contain all needed stati-values
*
*	@return string		formatted output with all needed stati-values
*
*/
string HWLWeapon::get_WeaponsForOutput()
{
	string s_output = "Name: " + this->s_name + "\n"
		//+ "  Offset: " + this->intToHexString(this->i_offset,false) + "\n"
		//+ "  i_id: " + this->intToHexString(this->i_id,false) + "\n"
		//+ "  i_character_id: " + to_string(this->i_character_id) + "\n"
		+"  Damage: " + to_string(this->i_damage) + "\n"
		+ "  Damage Base: " + to_string(this->i_damage_base) + "\n"
		+ "  Stars: " + to_string(this->i_stars) + "\n"
		+ "  Lvl: " + to_string(this->i_lvl) + "\n"
		+ "  Is Multi-Element Weapon: " + to_string(this->b_is_multi_element_weapon) + "\n"
		+ "  Skills: " + this->get_WeaponsSkillsForOutput() + "\n"
		+ "  Weapon State: " + this->get_state(true) + "\n";

	return s_output;
}



/**
* This method is a wrapper for all known save-methods of the class
*
*/
void HWLWeapon::save_weapon()
{
	this->save_skill_slot_kills();
	this->save_weapon_id();
	this->save_damage_base();
	this->save_stars();
	this->save_skill_slots();
	this->save_state();
}
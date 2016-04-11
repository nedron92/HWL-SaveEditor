//needed for including in a MFC-App
#ifdef __MFC__
#include "../gui/stdafx.h" 
#endif // __MFC__


#include "HWLSaveEditor.h"
//#include <stdio.h>  //for testing purpose as comment
//#include <iostream> //for testing purpose as comment

using namespace HWLSaveEdit;

//offsets definitions
/* @var fileHeaderOffsetBegin	the offset-begin for the file-header */
const int HWLSaveEditor::fileHeaderOffsetBegin = 0x0;

/* @var rubyOffset				the offset-begin for rubies */
const int HWLSaveEditor::rubyOffset = 0xde;

/* @var rubyOffsetLength		length for ruby-offset */
const int HWLSaveEditor::rubyOffsetLength = 0x3;

/* @var rubyMax					max value for rubies */
const int HWLSaveEditor::rubyMax = 9999999;

/* @var playerOffsetBegin		beginning of player-offsets (first character) */
const int HWLSaveEditor::playerOffsetBegin = 0x2EBF2;

/* @var vs_players				vector for holding all names of the characters */
const vector<string> HWLSaveEditor::vs_players =
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

/* @var bronzeMaterialsOffsetBegin	offset begin of first bronze-material */
const int HWLSaveEditor::bronzeMaterialsOffsetBegin = 0x1924; 

/* @var bronzeMaterialsOffsetBegin	offset begin of first new bronze-material */
const int HWLSaveEditor::bronzeMaterialsOffsetBeginNew = 0x19BE;

/* @var vs_bronzeMaterials			vector for holding all names of bronze Materials */
const vector<string> HWLSaveEditor::vs_bronzeMaterials =
{
	"Metal Plate",
	"Monster Tooth",
	"Old Rag",
	"Soldier's Uniform",
	"Rock",
	"Aeralfos Leather",
	"Fiery Aeralfos Leather",
	"Gibdo Bandage",
	"Redead Bandage",
	"Lizalfos Scale",
	"Dinolfos Fang",
	"Moblin Flank",
	"Sheild-Moblin Helmet",
	"Piece of Darknut Armor",
	"Stalmaster Wrist Bone",
	"Big Poe Necklace",
	"Essence of Icy Big Poe",
	"Hylian Captain Gauntlet",
	"Goron Armor Breastplate",
	"Big Blin Hide",
	"Stone Blin Buckler",
	"Monster Horn"
};

/* @var silverMaterialsOffsetBeginNew	offset begin of first silver-material */
const int HWLSaveEditor::silverMaterialsOffsetBegin = 0x194A;

/* @var silverMaterialsOffsetBeginNew	offset begin of first new silver-material */
const int HWLSaveEditor::silverMaterialsOffsetBeginNew = 0x19C4;

/* @var vs_silverMaterials				vector for holding all names of silver Materials */
const vector<string> HWLSaveEditor::vs_silverMaterials =
{
	"Ganon's Mane",
	"King Dodongo's Claw",
	"Gohma's Acid",
	"Manhandla's Toxic Dust",
	"Argorok's Ember",
	"Imprisoned Scale",
	"Cia's Bracelet",
	"Volga's Helmet",
	"Wizzro's Robe",
	"Link's Boots",
	"Lana's Hair Clip",
	"Zelda's Brooch",
	"Impa's Hair Band",
	"Ganondorf's Gauntlet",
	"Sheik's Kunai",
	"Darunia's Spikes",
	"Ruto's Earrings",
	"Agitha's Basket",
	"Midna's Hair",
	"Fi's Heels",
	"Ghirahim's Sash",
	"Zant's Magic Gem",
	"Round Aeralfos Shield",
	"Fiery Aeralfos Wing",
	"Heavy Gibdo Sword",
	"ReDead Knight Ashes",
	"Lizalfos Gauntlet",
	"Dinolfos Arm Guard",
	"Moblin Spear",
	"Metal Moblin Shield",
	"Large Darknut Sword",
	"Stalmaster's Skull",
	"Big Poe's Lantern",
	"Icy Big Poe's Talisman",
	"Holy Hylian Shield",
	"Thick Goron Helmet",
	"Big Blin Club",
	"Stone Blin Helmet",
	"Helmaroc Plume",
	"Phantom Ganon's Cape",
	"Twili Midna's Hairpin",
	"Young Link's Belt",
	"Tingle's Map",
	"Linkle's Boots",
	"Skull Kid's Hat",
	"Pirate's Charm",
	"Tetra's Sandals",
	"King Daphnes's Robe"
};

/* @var goldMaterialsOffsetBegin	offset begin of first gold-material */
const int HWLSaveEditor::goldMaterialsOffsetBegin = 0x1992;

/* @var goldMaterialsOffsetBegin	offset begin of first gold-material */
const int HWLSaveEditor::goldMaterialsOffsetBeginNew = 0x19DC;

/* @var vs_goldMaterials			vector for holding all names of gold Materials */
const vector<string> HWLSaveEditor::vs_goldMaterials =
{
	"Ganon's Fang",
	"King Dodongo's Crystal",
	"Gohma's Lens",
	"Manhandla's Sapling",
	"Argorok's Stone",
	"The Imprisoned's Pillar",
	"Cia's Staff",
	"Volga's Dragon Spear",
	"Wizzro's Ring",
	"Link's Scarf",
	"Lana's Cloak",
	"Zelda's Tiara",
	"Impa's Breastplate",
	"Ganondorf's Jewel",
	"Sheik's Turban",
	"Darunia's Bracelet",
	"Ruto's Scale",
	"Agitha's Pendant",
	"Midna's Fused Shadow",
	"Fi's Crystal",
	"Ghirahim's Cape",
	"Zant's Helmet",
	"Helmaroc King's Mask",
	"Phantom Ganon's Sword",
	"Twili Midna's Robe",
	"Keaton Mask",
	"Tingle's Watch",
	"Linkle's Compass",
	"Majora's Mask",
	"Island Outfit",
	"Tetra's Bandana",
	"King Daphnes's Crown",
};

/* @var fairyFoodOffsetBegin	offset begin of first fairyfood-item */
const int HWLSaveEditor::fairyFoodOffsetBegin = 0x233A;

/* @var vs_fairyFood			vector for holding all names of fairyFood-Items */
const vector<string> HWLSaveEditor::vs_fairyFood =
{
	"Weird Egg",
	"Tasty Weird Egg",
	"Delicious Weird Egg",
	"Lon Lon Milk",
	"Tasty Lon Lon Milk",
	"Delicious Lon Lon Milk",
	"Odd Mushroom",
	"Tasty Odd Mushroom",
	"Delicious Odd Mushroom",
	"Deku Nut",
	"Tasty Deku Nut",
	"Delicious Deku Nut",
	"Magic Beans",
	"Tasty Magic Beans",
	"Delicious Magic Beans",
	"Pumpkin Soup",
	"Tasty Pumpkin Soup",
	"Delicious Pumpkin Soup",
	"Sacred Water",
	"Tasty Sacred Water",
	"Delicious Sacred Water",
	"Life Tree Fruit",
	"Tasty Life Tree Fruit",
	"Delicious Life Tree Fruit",
	"Light Fruit",
	"Tasty Light Fruit",
	"Delicious Light Fruit",
	"Stamina Fruit",
	"Tasty Stamina Fruit",
	"Delicious Stamina Fruit",
	"Water Fruit",
	"Tasty Water Fruit",
	"Delicious Water Fruit",
	"Mushroom Spores",
	"Tasty Mushroom Spores",
	"Delicious Mushroom Spores",
	"All-Purpose Bait",
	"Tasty All-Purpose Bait",
	"Delicious All-Purpose Bait",
	"Elixir Soup",
	"Tasty Elixir Soup",
	"Delicious Elixir Soup",
	"Hyoi Pear",
	"Tasty Hyoi Pear",
	"Delicious Hyoi Pear",
	"Ordon Goat Cheese",
	"Tasty Ordon Goat Cheese",
	"Delicious Ordon Goat Cheese",
	"Great Fairy's Tears",
	"Tasty Great Fairy's Tears",
	"Delicious Great Fairy's Tears",
	"Greengill",
	"Tasty Greengill",
	"Delicious Greengill",
	"Ordon Catfish",
	"Tasty Ordon Catfish",
	"Delicious Ordon Catfish",
	"Hyrule Bass",
	"Tasty Hyrule Bass",
	"Delicious Hyrule Bass",
	"Hylian Pike",
	"Tasty Hylian Pike",
	"Delicious Hylian Pike",
	"Reekfish",
	"Tasty Reekfish",
	"Delicious Reekfish",
	"Hylian Loach",
	"Tasty Hylian Loach",
	"Delicious Hylian Loach",
	"Skullfish",
	"Tasty Skullfish",
	"Delicious Skullfish",
	"Bombfish",
	"Tasty Bombfish",
	"Delicious Bombfish",
	"Chu Jelly",
	"Tasty Chu Jelly",
	"Delicious Chu Jelly",
	"Bee Larvae",
	"Tasty Bee Larvae",
	"Delicious Bee Larvae",
	"Chateau Romani",
	"Tasty Chateau Romani",
	"Delicious Chateau Romani",
	"Bottled Water",
	"Tasty Bottled Water",
	"Delicious Bottled Water",
	"Hot Spring Water",
	"Tasty Hot Spring Water",
	"Delicious Hot Spring Water",
	"Rock Sirloin",
	"Tasty Rock Sirloin",
	"Delicious Rock Sirloin",
	"Meat",
	"Tasty Meat",
	"Delicious Meat",
	"Carrot",
	"Tasty Carrot",
	"Delicious Carrot",
	"Ember Seeds",
	"Tasty Ember Seeds",
	"Delicious Ember Seeds",
	"Scent Seeds",
	"Tasty Scent Seeds",
	"Delicious Scent Seeds",
	"Pegasus Seeds",
	"Tasty Pegasus Seeds",
	"Delicious Pegasus Seeds",
	"Gale Seeds",
	"Tasty Gale Seeds",
	"Delicious Gale Seeds",
	"Mystery Seeds",
	"Tasty Mystery Seeds",
	"Delicious Mystery Seeds",
	"Gratitude Crystal Red S",
	"Gratitude Crystal Red M",
	"Gratitude Crystal Red L",            
	"Gratitude Crystal Blue S",
	"Gratitude Crystal Blue M",
	"Gratitude Crystal Blue L",         
	"Gratitude Crystal Orange S",
	"Gratitude Crystal Orange M",
	"Gratitude Crystal Orange L",        
	"Gratitude Crystal Pink S",
	"Gratitude Crystal Pink M",
	"Gratitude Crystal Pink L",         
	"Gratitude Crystal Purple S",
	"Gratitude Crystal Purple M",
	"Gratitude Crystal Purple L",        
	"Pumpkin",
	"Tasty Pumpkin",
	"Delicious Pumpkin"
};

/* @var amItemOffsetBegin	vector for holding the offsets-begin for AdventureMode items */
const vector<int> HWLSaveEditor::amItemOffsetBegin =
{
	0x2EFA,  //Start of Adventure-Map Items
	0xEB73,  //Start of GreatSea-Map Items (WindWaker and so on)
	0x7A52,  //Start of MasterQuest-Map Items
	0xA00A,  //Start of Twilight-Map Items (Lantern and so on)
	0xC5BE	 //Start of Termina-Map Items (Song of Time and so on)

};

/* @var amItemOffsetBegin	vector for holding the offsets-begin for AdventureMode items */
const vector<int> HWLSaveEditor::amItemOffsetBeginSpecial =
{
	0xEB56,  //Compass of GreatSea-Map
	0xEB5F,  //Hookshot of GreatSea-Map

	0x9FFE,  //Compass of Twilight-Map (+1 = Bombs)
	0xA003,  //Waterbombs of Twilight-Map (+1 = Digging Mitts)

	0xC5AA, //Compass of Termina-Map (+1 = Bombs)
	0xC5B1, //Ice Arrow of Termina-Map

};

/* @var vs_amItems			vector for holding all names of AdventureMode-Items */
const vector<string> HWLSaveEditor::vs_amItems =
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



/* @var fairyOffsetBegin	offset begin of first myFairy */
const int HWLSaveEditor::fairyOffsetBegin = 0x1AEA;

/* @var maxFairies			maximal count of fairies*/
const int HWLSaveEditor::fairiesMax = 10;



/* @var weaponOffsetBegin	offset begin of first weapon */
const int HWLSaveEditor::weaponOffsetBegin = 0x2F372;

/* @var vi_playerWeaponTypeCount	vector for holding information about how many weapon types a chara have */
const vector<int> HWLSaveEditor::vi_playerWeaponTypeCount =
{
	7, 3, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 
	// 0.Link, 1.Zelda, 2.Shiek, 3.Impa, 4.Ganondorf, 5.Darunia, 6.Ruto, 7.Agitha, 8.Imp Midna, 
	// 9.Fi, 10.Ghirahim, 11.Zant, 12.Lana, 13.Cia, 14.Volga, 15.Wizzro, 16.Twili Midna, 17.Young Link, 
	// 18.Tingle, 19.??? 20.???, 21.Linkle, 22.Skull Kid, 23.Toon Link, 24.Tetra, 25.King Daphnes
};

/* @var vs_playerWeaponTypeNames	vector for holding all weapon-type names */
const vector<string> HWLSaveEditor::vs_playerWeaponTypeNames =
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

	//Skull Kid - Weapon Types
	"Ocarina",

	//Toon Link - Weapon Types
	"Light Sword",

	//Tetra - Weapon Types
	"Cutlass",

	//King Daphnes - Weapon Types
	"Sail",
};

/* @var vi_playerWeaponTypeHexValues	vector for holding information about all weapon-type offsets-begin */
const vector<int> HWLSaveEditor::vi_playerWeaponTypeHexValues =
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

	//Skull Kid - Weapon Types Hex
	0x74,

	//Toon Link - Weapon Types Hex
	0x77,

	//Tetra - Weapon Types Hex
	0x7A,

	//King Daphnes - Weapon Types Hex
	0x7D,
};

/* @var vi_playerWeaponTypeHexValuesLVL4	vector for holding information about all weapon-type offsets, LVL 4*/
const vector<int> HWLSaveEditor::vi_playerWeaponTypeHexValuesLVL4 =
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

	//??? - Weapon Types Hex  LVL 4, 2 times, without any weapon-type hex for  LVL 4

	//Linkle - Weapon Types Hex  LVL 4
	0x8A,

	//Skull Kid - Weapon Types Hex  LVL 4
	0x8B,

	//Toon Link - Weapon Types Hex LVL 4
	0x8C,

	//Tetra - Weapon Types Hex LVL 4
	0x8D,

	//King Daphnes - Weapon Types Hex LVL 4
	0x8E,
};



HWLSaveEditor::HWLSaveEditor(string s_filepathname)
{
	setlocale(LC_ALL, "");

	//set the needed values for the file and program
	//(path/name of file and open it)
	this->s_filepathname = s_filepathname;
	this->fs_filehandler = fstream(s_filepathname, 
		fstream::binary | fstream::in | fstream::out );
	
	//check if file is open, else (throw later) set error
	if (this->fs_filehandler.is_open())
	{
		
		//do not skip whitespaces and calculate file-length
		this->fs_filehandler >> std::noskipws;
		this->fs_filehandler.seekg(0, this->fs_filehandler.end);
		this->i_filelength = this->fs_filehandler.tellg();
		this->fs_filehandler.seekg(0, this->fs_filehandler.beg);

		//allocate memory for file-content and read the file
		cp_filecontent = new unsigned char[this->i_filelength];
		this->fs_filehandler.read((char*)cp_filecontent, this->i_filelength);

		//calculate rubies, players and materials
		if (this->check_savefile())
		{
			this->i_rubies = this->calc_rubies();
			this->calc_weapons();
			this->calc_players();
			this->calc_materials();
			this->calc_fairyFood();
			this->calc_amItems();
			this->calc_myFairies();
		}
		else{
			this->i_error = 400;
			string s_tmp = "File '" + s_filepathname + "' is not valid. Sorry ;(";
			char *cstr = new char[s_tmp.length() + 1];
			strcpy(cstr, s_tmp.c_str());
			throw HWLException(cstr, this->i_error);

			delete[] cstr;
		}

	}
	else{
		this->i_error = 404;
		string s_tmp = "File '" + s_filepathname + "' not found ";
		char *cstr = new char[s_tmp.length() + 1];
		strcpy(cstr, s_tmp.c_str());
		throw HWLException(cstr, this->i_error);

		delete[] cstr;
	}
}

HWLSaveEditor::~HWLSaveEditor()
{
	if (this->fs_filehandler.is_open())
	{
		this->fs_filehandler.clear();
		this->fs_filehandler.close();
		delete cp_filecontent;
	}
}

int HWLSaveEditor::calc_rubies()
{
	string s_rubies;
	int i_ruby_offset = this->rubyOffset;

	s_rubies = this->getHexStringFromFileContent(i_ruby_offset, this->rubyOffsetLength);

	return this->HexStringToInt(s_rubies);
}

void HWLSaveEditor::calc_weapons()
{
	int i_offset = this->weaponOffsetBegin;

	int count = 0;
	for (int i = i_offset; i < (this->i_filelength - 1); i += this->weaponOffsetLengthComplete)
	{
		string s_weapon = this->getHexStringFromFileContent(i, this->weaponOffsetLength, true);

		if (s_weapon != HWLWeapon::weaponBlankWeaponHex)
		{
			shared_ptr<HWLWeapon> hwlw_tmp = make_shared<HWLWeapon>(i);
			this->v_weapon.push_back(hwlw_tmp);
		}
		else{
			vi_blank_weapons.push_back(i);
		}
	}
}

void HWLSaveEditor::calc_players()
{
	int i_offset = this->playerOffsetBegin;

	for (int i = 0; i < this->vs_players.size(); i++)
	{
		shared_ptr<HWLPlayer> hwlp_tmp = make_shared<HWLPlayer>(vs_players[i], i_offset);

		vector<int> i_count_weapon_slots;
		i_count_weapon_slots.resize(this->vi_playerWeaponTypeCount[i]);

		for (int j = 0; j < i_count_weapon_slots.size(); j++)
			i_count_weapon_slots[j] = 0;

		for (int j = 0; j < this->v_weapon.size(); j++)
		{
			int i_weapon_id = this->v_weapon[j]->get_id();
			string s_weapon_name;
			int i_weapon_type, i_weapon_lvl;
			vector<int> vi_lvl_hexValues(HWLWeapon::weaponLVLMax);
			for (int i = 0; i < vi_lvl_hexValues.size(); i++)
				vi_lvl_hexValues[i] = 0;

			if (this->calc_players_weapons(i, i_weapon_id, s_weapon_name, i_weapon_type, i_weapon_lvl, vi_lvl_hexValues))
			{
				this->v_weapon[j]->set_name(s_weapon_name);
				this->v_weapon[j]->set_type(i_weapon_type);
				this->v_weapon[j]->set_lvl(i_weapon_lvl);
				this->v_weapon[j]->set_character_id(i);
				this->v_weapon[j]->set_lvl_hex(vi_lvl_hexValues);

				hwlp_tmp->set_weapon_slot(i_weapon_type, this->v_weapon[j]);

				i_count_weapon_slots[i_weapon_type]++;
			}
		}

		int i_weapon_types = this->vi_playerWeaponTypeCount[i];

		//Check for Link's Master Sword, cause we have only one
		if (i == 0 && i_count_weapon_slots[4] > 0)
			i_count_weapon_slots[4] = HWLPlayer::playerWeaponSlotsMax;
		else if (i == 0 && i_count_weapon_slots[4] == 0)
			i_count_weapon_slots[4] = (HWLPlayer::playerWeaponSlotsMax - 1);

		int i_weapon_count = 0;
		for (int j = 0; j < i; j++)
		{
			i_weapon_count = i_weapon_count + this->vi_playerWeaponTypeCount[j];
		}

		for (int j = 0; j < i_weapon_types; j++)
		{
			for (int k = i_count_weapon_slots[j]; k < HWLPlayer::playerWeaponSlotsMax; k++)
			{
				int i_offset_new = this->vi_blank_weapons[0];
				shared_ptr<HWLWeapon> hwlpw_tmp = make_shared<HWLWeapon>(i_offset_new, i, true);
				hwlpw_tmp->set_type(j);
				hwlp_tmp->set_weapon_slot(j, hwlpw_tmp);
				hwlpw_tmp->set_name(this->vs_playerWeaponTypeNames[i_weapon_count + j]);
				this->vi_blank_weapons.erase(this->vi_blank_weapons.begin(), this->vi_blank_weapons.begin() + 1);
			}
		}

		this->m_players[this->vs_players[i]] = hwlp_tmp;
		i_offset = i_offset + this->playerOffsetLength;
	}

}

bool HWLSaveEditor::calc_players_weapons(int i_player_id, int i_weapon_id, string &s_weapon_name, int &i_weapon_type, int &i_weapon_lvl, vector<int> &vi_lvl_hexValues)
{
	int i_weapon_count = 0;
	for (int j = 0; j < i_player_id; j++)
	{
		i_weapon_count = i_weapon_count + this->vi_playerWeaponTypeCount[j];
	}

	for (int j = 0; j < this->vi_playerWeaponTypeCount[i_player_id]; j++)
	{
		int i_current_lvl_2, i_current_lvl_3, i_current_lvl_4;

		if (this->vi_playerWeaponTypeHexValues[i_weapon_count + j] != this->vi_playerWeaponTypeHexValues[4])
		{
			i_current_lvl_2 = this->vi_playerWeaponTypeHexValues[i_weapon_count + j] + 1;
			i_current_lvl_3 = this->vi_playerWeaponTypeHexValues[i_weapon_count + j] + 2;
			i_current_lvl_4 = this->vi_playerWeaponTypeHexValuesLVL4[i_weapon_count + j];

		}
		else{
			i_current_lvl_2 = i_current_lvl_3 = i_current_lvl_4 = 0;
	
		}

		vi_lvl_hexValues[0] = this->vi_playerWeaponTypeHexValues[i_weapon_count + j];
		vi_lvl_hexValues[1] = i_current_lvl_2;
		vi_lvl_hexValues[2] = i_current_lvl_3;
		vi_lvl_hexValues[3] = i_current_lvl_4;

		if (i_weapon_id == this->vi_playerWeaponTypeHexValues[i_weapon_count + j])
		{
			s_weapon_name = this->vs_playerWeaponTypeNames[i_weapon_count + j];
			i_weapon_type = j;
			i_weapon_lvl = 1;
			return true;
		}
		else if (i_weapon_id == i_current_lvl_2)
		{
			s_weapon_name = this->vs_playerWeaponTypeNames[i_weapon_count + j];
			i_weapon_type = j;
			i_weapon_lvl = 2;
			return true;
		}
		else if (i_weapon_id == i_current_lvl_3)
		{
			s_weapon_name = this->vs_playerWeaponTypeNames[i_weapon_count + j];
			i_weapon_type = j;
			i_weapon_lvl = 3;
			return true;
		}
		else if (i_weapon_id == i_current_lvl_4)
		{
			s_weapon_name = this->vs_playerWeaponTypeNames[i_weapon_count + j];
			i_weapon_type = j;
			i_weapon_lvl = 4;
			return true;
		}
	}

	return false;
}

void HWLSaveEditor::calc_materials()
{
	int i_offset = this->bronzeMaterialsOffsetBegin;

	for (int i = 0; i < this->vs_bronzeMaterials.size(); i++)
	{
		if (i == (this->vs_bronzeMaterials.size() - 3))
			i_offset = this->bronzeMaterialsOffsetBeginNew;

		shared_ptr<HWLMaterial> hwlm_tmp = make_shared<HWLMaterial>(vs_bronzeMaterials[i], i_offset,0);
		this->m_materials[this->vs_bronzeMaterials[i]] = hwlm_tmp;
		i_offset = i_offset + this->materialOffsetLength;
	}

	i_offset = this->silverMaterialsOffsetBegin;

	for (int i = 0; i < this->vs_silverMaterials.size(); i++)
	{
		if (i == (this->vs_silverMaterials.size() - 12))
			i_offset = this->silverMaterialsOffsetBeginNew;

		shared_ptr<HWLMaterial> hwlm_tmp = make_shared<HWLMaterial>(vs_silverMaterials[i], i_offset, 1);
		this->m_materials[this->vs_silverMaterials[i]] = hwlm_tmp;
		i_offset = i_offset + this->materialOffsetLength;
	}

	i_offset = this->goldMaterialsOffsetBegin;

	for (int i = 0; i < this->vs_goldMaterials.size(); i++)
	{
		if (i == (this->vs_goldMaterials.size() - 10))
			i_offset = this->goldMaterialsOffsetBeginNew;

		shared_ptr<HWLMaterial> hwlm_tmp = make_shared<HWLMaterial>(vs_goldMaterials[i], i_offset, 2);
		this->m_materials[this->vs_goldMaterials[i]] = hwlm_tmp;
		i_offset = i_offset + this->materialOffsetLength;
	}
}

void HWLSaveEditor::calc_fairyFood()
{
	int i_offset = this->fairyFoodOffsetBegin;

	for (int i = 0; i < this->vs_fairyFood.size(); i++)
	{
		shared_ptr<HWLFairyFood> hwlff_tmp = make_shared<HWLFairyFood>(vs_fairyFood[i], i_offset);
		this->m_fairyfood[this->vs_fairyFood[i]] = hwlff_tmp;
		i_offset = i_offset + this->fairyFoodOffsetLength;
	}

}

void HWLSaveEditor::calc_amItems()
{
	int i_offset = this->amItemOffsetBegin[0];
	int i_type = 0;

	for (int i = 0; i < this->vs_amItems.size(); i++)
	{
		if (i == HWLSaveEdit::HWLAdventureModeItems::amItemPerMapMax * (i_type + 1))
		{
			i_type++;

			if (i_type == this->amItemOffsetBegin.size())
				break;

			switch (i)
			{
			case 12: 
				i_offset = this->amItemOffsetBeginSpecial[0];
				break;

			case 36:
				i_offset = this->amItemOffsetBeginSpecial[2];
				break;

			case 48:
				i_offset = this->amItemOffsetBeginSpecial[4];
				break;

			default:
				i_offset = this->amItemOffsetBegin[i_type];
				break;
			}

		}

		switch (i)
		{
		case 13:
			i_offset = this->amItemOffsetBeginSpecial[1];
			break;

		case 14:
		case 40:
		case 51:
			i_offset = this->amItemOffsetBegin[i_type];
			break;

		case 38:
			i_offset = this->amItemOffsetBeginSpecial[3];
			break;

		case 50:
			i_offset = this->amItemOffsetBeginSpecial[5];
			break;

		}

		shared_ptr<HWLAdventureModeItems> hwlami_tmp = make_shared<HWLAdventureModeItems>(vs_amItems[i], i_offset, i_type);
		this->m_amItem[i] = hwlami_tmp;
		i_offset = i_offset + this->amItemOffsetLength;
	}

}

void HWLSaveEditor::calc_myFairies()
{
	int i_offset = this->fairyOffsetBegin;

	for (int i = 0; i < this->fairiesMax; i++)
	{
		shared_ptr<HWLFairy> hwlf_tmp = make_shared<HWLFairy>(i_offset);
		this->m_fairy[i] = hwlf_tmp;
		i_offset = i_offset + this->fairyOffsetLength;
	}
}



void HWLSaveEditor::save_rubies()
{
	int i_ruby_tmp = this->i_rubies;
	string s_rubies;
	int i_ruby_offset = this->rubyOffset;

	s_rubies = this->intToHexString(i_ruby_tmp, false);
	this->addZeroToHexString(s_rubies, this->rubyOffsetLength * 2);

	this->setHexStringToFileContent(s_rubies, i_ruby_offset);
}


int HWLSaveEditor::get_error()
{
	return this->i_error;
}

int HWLSaveEditor::get_rubies()
{
	return this->i_rubies;
}

shared_ptr<HWLPlayer> HWLSaveEditor::get_player(int i_id)
{
	shared_ptr<HWLPlayer> hwlp_tmp = this->m_players[this->vs_players[i_id]];

	return hwlp_tmp;
}

shared_ptr<HWLPlayer> HWLSaveEditor::get_player(string s_name)
{
	shared_ptr<HWLPlayer> hwlp_tmp = this->m_players[s_name];

	return hwlp_tmp;
}

shared_ptr<HWLMaterial> HWLSaveEditor::get_material(int i_id, int i_type)
{
	shared_ptr<HWLMaterial> hwlm_tmp;
	switch (i_type)
	{
		case 0:
			hwlm_tmp = this->m_materials[this->vs_bronzeMaterials[i_id]];
			break;
		case 1:
			hwlm_tmp = this->m_materials[this->vs_silverMaterials[i_id]];
			break;
		case 2:
			hwlm_tmp = this->m_materials[this->vs_goldMaterials[i_id]];
			break;
	}


	return hwlm_tmp;
}

shared_ptr<HWLMaterial> HWLSaveEditor::get_material(string s_name)
{
	shared_ptr<HWLMaterial> hwlm_tmp = this->m_materials[s_name];

	return hwlm_tmp;
}

shared_ptr<HWLFairyFood> HWLSaveEditor::get_fairyFood(int i_id)
{
	shared_ptr<HWLFairyFood> hwlff_tmp = this->m_fairyfood[this->vs_fairyFood[i_id]];

	return hwlff_tmp;
}

shared_ptr<HWLFairyFood> HWLSaveEditor::get_fairyFood(string s_name)
{
	shared_ptr<HWLFairyFood> hwlff_tmp = this->m_fairyfood[s_name];

	return hwlff_tmp;
}

shared_ptr<HWLAdventureModeItems> HWLSaveEditor::get_amItem(int i_id)
{
	shared_ptr<HWLAdventureModeItems> hwlami_tmp = this->m_amItem[i_id];

	return hwlami_tmp;
}

shared_ptr<HWLAdventureModeItems> HWLSaveEditor::get_amItem(int i_id, int i_type)
{
	if (i_type >= this->amItemOffsetBegin.size())
		i_type = 0;

	if (i_type != 0)
		i_id = i_id + (HWLSaveEdit::HWLAdventureModeItems::amItemPerMapMax * i_type);

	shared_ptr<HWLAdventureModeItems> hwlami_tmp = this->m_amItem[i_id];

	return hwlami_tmp;
}

shared_ptr<HWLFairy> HWLSaveEditor::get_fairy(int i_id)
{
	shared_ptr<HWLFairy> hwlf_tmp = this->m_fairy[i_id];

	return hwlf_tmp;
}

void HWLSaveEditor::generate_default_weapon(int i_player_id, int i_weapon_type, int i_weapon_slot)
{
	int i_weapon_count = 0;
	for (int j = 0; j < i_player_id; j++)
	{
		i_weapon_count = i_weapon_count + this->vi_playerWeaponTypeCount[j];
	}

	int i_default_weapon_id = this->vi_playerWeaponTypeHexValues[i_weapon_count + i_weapon_type];

	shared_ptr<HWLWeapon> hwlpw_tmp = this->get_player(i_player_id)->get_weapon_slot(i_weapon_type, i_weapon_slot);
	hwlpw_tmp->set_id(i_default_weapon_id);
	hwlpw_tmp->set_lvl(1);
	hwlpw_tmp->set_IsUnused(false);
	hwlpw_tmp->set_damage_base(HWLWeapon::vi_damage_base_defaults[0]);
	hwlpw_tmp->set_stars(0);
	
	for (int i = 0; i < 8; i++)
	{
		hwlpw_tmp->set_skill_slot_kill(i, 0);
		
		if (i == 0)
			hwlpw_tmp->set_skill_slot(i, 0);
		else
			hwlpw_tmp->set_skill_slot(i, HWLWeapon::weaponSkillValueNoSkill);
	}
	vector<int> vi_lvl_hexValues(HWLWeapon::weaponLVLMax);
	for (int i = 0; i < vi_lvl_hexValues.size(); i++)
		vi_lvl_hexValues[i] = 0;

	vi_lvl_hexValues[0] = (i_default_weapon_id);
	vi_lvl_hexValues[1] = (i_default_weapon_id + 1);
	vi_lvl_hexValues[2] = (i_default_weapon_id + 2);
	vi_lvl_hexValues[3] = (this->vi_playerWeaponTypeHexValuesLVL4[i_weapon_count + i_weapon_type]);

	hwlpw_tmp->set_lvl_hex(vi_lvl_hexValues);
	this->get_player(i_player_id)->set_weapon_slot(i_weapon_type, i_weapon_slot, hwlpw_tmp);

}


int HWLSaveEditor::get_adventureMode_maxItemCount()
{
	return this->amItemOffsetBegin.size();
}


void HWLSaveEditor::set_rubies(int i_rubies)
{
	if (i_rubies < 0)
		i_rubies = 0;
	else if (i_rubies > this->rubyMax)
		i_rubies = rubyMax;

	this->i_rubies = i_rubies;
}




void HWLSaveEditor::save_file()
{
	if (this->fs_filehandler.is_open())
	{
		this->save_rubies();

		this->fs_filehandler.seekp(0, this->fs_filehandler.beg);
		this->fs_filehandler.clear();

		this->fs_filehandler.write((char*)cp_filecontent, this->i_filelength);
	}
	else{
		this->i_error = 401;
		string s_tmp = "File '" + this->s_filepathname + "' is not writeable.";
		char *cstr = new char[s_tmp.length() + 1];
		strcpy(cstr, s_tmp.c_str());
		throw HWLException(cstr, this->i_error);

		delete[] cstr;
	}
}

bool HWLSaveEditor::check_savefile()
{
	string s_file_header[5];

	for (int i = 0; i < 5; i++)
	{
		s_file_header[i] = this->getHexStringFromFileContent(this->fileHeaderOffsetBegin + i, 1);
	}

	if (s_file_header[0] == "00" && s_file_header[1] == "26" && s_file_header[2] == "10" && s_file_header[3] == "15"
		&& s_file_header[4] == "00")
		return true;
	else
		return false;
}

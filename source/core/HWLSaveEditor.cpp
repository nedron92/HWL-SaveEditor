//needed for including in a MFC-App
#ifdef __MFC__
#include "../gui/stdafx.h" 
#endif // __MFC__

//include the correct header-file
#include "HWLSaveEditor.h"
//#include <stdio.h>  //for testing purpose as comment
//#include <iostream> //for testing purpose as comment
#include <cstring> //needed for compiling with gcc

//use the project-namespace
using namespace HWLSaveEdit;

//activate auto-trim on default
bool HWLSaveEditor::b_auto_trim = true;

//offsets definitions
/* @var fileHeaderOffsetBegin	the offset-begin for the file-header */
const int HWLSaveEditor::fileHeaderOffsetBegin = 0x0;

/* @var fileNormalLength	the normal filelength in bytes */
const int HWLSaveEditor::fileNormalLength = 234594;


/* @var playerOffsetBegin		beginning of player-offsets (first character) */
const int HWLSaveEditor::playerOffsetBegin = 0x2EBF2;


/* @var bronzeMaterialsOffsetBegin	offset begin of first bronze-material */
const int HWLSaveEditor::bronzeMaterialsOffsetBegin = 0x1924;

/* @var bronzeMaterialsOffsetBegin	offset begin of first new bronze-material */
const int HWLSaveEditor::bronzeMaterialsOffsetBeginNew = 0x19BE;

/* @var silverMaterialsOffsetBeginNew	offset begin of first silver-material */
const int HWLSaveEditor::silverMaterialsOffsetBegin = 0x194A;

/* @var silverMaterialsOffsetBeginNew	offset begin of first new silver-material */
const int HWLSaveEditor::silverMaterialsOffsetBeginNew = 0x19C4;

/* @var goldMaterialsOffsetBegin	offset begin of first gold-material */
const int HWLSaveEditor::goldMaterialsOffsetBegin = 0x1992;

/* @var goldMaterialsOffsetBegin	offset begin of first gold-material */
const int HWLSaveEditor::goldMaterialsOffsetBeginNew = 0x19DC;


/* @var fairyFoodOffsetBegin	offset begin of first fairyfood-item */
const int HWLSaveEditor::fairyFoodOffsetBegin = 0x233A;


/* @var fairyOffsetBegin	offset begin of first myFairy */
const int HWLSaveEditor::fairyOffsetBegin = 0x1AEA;


/* @var weaponOffsetBegin	offset begin of first weapon */
const int HWLSaveEditor::weaponOffsetBegin = 0x2F372;



/* @var sp_http_request	offset  pointer for hwl-http-requests */
shared_ptr<HWLHttp> HWLSaveEditor::http_request = make_shared<HWLHttp>();



/**
* Only the initialization of the normal-constructor
*/
HWLSaveEditor::HWLSaveEditor(string s_filepathname, bool b_isNewSaveFile)
{
	//set locale to LC_ALL, for special names (myFairy and so on)
	setlocale(LC_ALL, "");

	//set the needed values for the file and program
	//(path/name of file and open it)
	this->s_filepathname = s_filepathname;
	this->fs_filehandler = fstream(s_filepathname,
		fstream::binary | fstream::in | fstream::out);

	//check if file is open, else throw Exception
	if (this->fs_filehandler.is_open())
	{
		//do not skip whitespaces and calculate file-length
		this->fs_filehandler >> std::noskipws;
		this->fs_filehandler.seekg(0, this->fs_filehandler.end);
		this->i_filelength = (int)this->fs_filehandler.tellg();
		this->fs_filehandler.seekg(0, this->fs_filehandler.beg);

		//allocate memory for file-content and read the file
		cp_filecontent = new unsigned char[this->i_filelength];
		this->fs_filehandler.read((char*)cp_filecontent, this->i_filelength);

		//check if we have an valid-savefile and then calculate rubies, players, ...
		//If not, throw Exception
		if (this->check_savefile())
		{
			//check if we have a valid savegame-filelength
			int i_check_savefile_length_state = this->check_savefile_length();
			if (i_check_savefile_length_state == 0)
			{
				this->b_isNewSaveFile = b_isNewSaveFile;

				this->calc_general();
				this->calc_weapons();
				this->calc_materials();
				this->calc_fairyFood();
				this->calc_amMaps();
				this->calc_myFairies();
				this->calc_players();
				this->calc_game_versions_restrictions();
			}
			else
			{
				this->i_error = 401;
				string s_tmp;
				char *cstr;

				switch (i_check_savefile_length_state)
				{
				case 1:
					s_tmp = "File '" + s_filepathname + "' is valid but too short. \nPlease try to export again.";
					break;

				case 2:
					s_tmp = "File '" + s_filepathname + "' is valid, but too long \nand the editor couldn't trimm it. Sorry.";
					break;

				case 3:
					s_tmp = "File '" + s_filepathname + "' is valid, but too long. The editor "
						+ "created a \ntrimmed file automatically and made a backup of the original save.\n"
						+ "The original savefile has the name '" + s_filepathname + ".bak' \nand the trimmed save "
						+ "has the normal name. \nPlease try to import the trimmed file back and if all is ok, then \n"
						+ "you can edit the savegame. :)";
					break;

				default:
					break;
				}

				cstr = new char[s_tmp.length() + 1];
				strcpy(cstr, s_tmp.c_str());
				throw HWLException(cstr, this->i_error);

				delete[] cstr;
			}

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

/**
* Only the initialization of the normal-destructor, delete/clear allocated memory
*/
HWLSaveEditor::~HWLSaveEditor()
{
	if (this->fs_filehandler.is_open())
	{
		this->fs_filehandler.clear();
		this->fs_filehandler.close();
		delete cp_filecontent;
	}
}



/**
* This method calculate the current general-thing-object
* and so all needed general ingame-things like rubies etc.
*
*/
void HWLSaveEditor::calc_general()
{
	this->sp_general = make_shared<HWLGeneral>();
}

/**
* This method calculate the current weapons-objects (for used ones
* and offsets of unused ones)
*
*/
void HWLSaveEditor::calc_weapons()
{
	//declare/define needed variables
	int i_offset = this->weaponOffsetBegin;

	//iterate from first-offset-begin to the end of the file with a distance of 
	//the length of the complete-weapon-offset
	for (int i = i_offset; i < this->i_filelength; i += this->weaponOffsetLengthComplete)
	{
		//check, if iterator + complete offset length is bigger then the current filelength
		//break the loop if its true
		if (i + this->weaponOffsetLengthComplete > this->i_filelength)
			break;

		//get the current weapon of that offset as an HexString
		string s_weapon = this->getHexStringFromFileContent(i, this->weaponOffsetLength, true);

		//if we have no blank weapon create a new weapon-object (based on offset)
		//else add the offset to the blank-weapon-vector
		if (s_weapon != HWLWeapon::weaponBlankWeaponHex)
		{
			shared_ptr<HWLWeapon> hwlw_tmp = make_shared<HWLWeapon>(i);

			if (hwlw_tmp->get_id() == 0x0000ffff)
			{
				vi_blank_weapons.push_back(i);
				continue;
			}

			this->v_weapon.push_back(hwlw_tmp);
		}
		else{
			vi_blank_weapons.push_back(i);
		}
	}
}

/**
* This method calculate the current characters-objects
*
*/
void HWLSaveEditor::calc_players()
{
	//declare/define needed variables
	int i_offset = this->playerOffsetBegin;

	//iterate over all characters and create new player-objects
	for (int i = 0; i < (signed)HWLPlayer::vs_players.size(); i++)
	{
		//create an new player-object, based on current name and offset
		shared_ptr<HWLPlayer> hwlp_tmp = make_shared<HWLPlayer>(i, HWLPlayer::vs_players[i], i_offset, HWLWeapon::vi_playerWeaponTypeCount[i]);

		//declare a counter for chara-specific weapon-types (eq. Link can have seven different weapon-types)
		vector<int> i_count_weapon_slots;
		i_count_weapon_slots.resize(HWLWeapon::vi_playerWeaponTypeCount[i]); //resize the vector to the correct size

		//due to security reasons set all integer-values within the vector to zero
		for (int j = 0; j < (signed)i_count_weapon_slots.size(); j++)
			i_count_weapon_slots[j] = 0;

		//iterate over all used weapons and bind each correct weapon to the current character
		for (int j = 0; j < (signed)this->v_weapon.size(); j++)
		{
			//declare/define needed variables now
			int i_weapon_id = this->v_weapon[j]->get_id();
			string s_weapon_name;
			int i_weapon_type, i_weapon_lvl;
			vector<int> vi_lvl_hexValues(HWLWeapon::weaponLVLMax); //create an vector, which hold the lvl offsets later (of current weapon)
			bool b_is_multi_element_weapon = false;
			int i_multi_element_weapon_hex = 0x00;

			//due to security reasons set all integer-values within the vector to zero
			for (int k = 0; k < (signed)vi_lvl_hexValues.size(); k++)
				vi_lvl_hexValues[k] = 0;

			//calculate weapons and check if its belong to the current chara, if yes, bind the new values
			if (this->calc_players_weapons(i, i_weapon_id, s_weapon_name, i_weapon_type, i_weapon_lvl, vi_lvl_hexValues, b_is_multi_element_weapon, i_multi_element_weapon_hex))
			{
				//set the current weapon-values to the belonging object itself
				this->v_weapon[j]->set_name(s_weapon_name);
				this->v_weapon[j]->set_type(i_weapon_type);
				this->v_weapon[j]->set_lvl(i_weapon_lvl);
				this->v_weapon[j]->set_character_id(i);
				this->v_weapon[j]->set_lvl_hex(vi_lvl_hexValues);
				this->v_weapon[j]->set_IsMultiElement(b_is_multi_element_weapon);
				this->v_weapon[j]->set_multi_element_hex(i_multi_element_weapon_hex);

				//do a check, if Multi-Element Weapons are unknown by the game-version
				// of the savefile. If TRUE: generate a default Weapon instead
				if ((this->s_savefile_game_version == "1.0.0" || this->s_savefile_game_version == "1.2.0"
					|| this->s_savefile_game_version == "1.3.0")
					|| (!this->vb_game_dlc_installed[1] || !this->vb_game_dlc_installed[2])
					&& (b_is_multi_element_weapon))
				{
					this->v_weapon[j]->generate_default_weapon();
				}

				//bind this weapon to to current chara
				hwlp_tmp->set_weapon_slot(i_weapon_type, this->v_weapon[j]);

				//increment the counter of the current weapon-type
				i_count_weapon_slots[i_weapon_type]++;
			}
		}

		//create an temp-variable which hold the current number of weapon-types of that chara
		int i_weapon_types = HWLWeapon::vi_playerWeaponTypeCount[i];

		//define an weapon-counter, and calculate all used weapon-types
		int i_weapon_count = 0;
		for (int j = 0; j < i; j++)
		{
			//count all weapon-types, from first-chara to this current chara - 
			//so we know then which weapon-type we have to use for that character or better which it's the first weapon-
			//type of this character
			i_weapon_count = i_weapon_count + HWLWeapon::vi_playerWeaponTypeCount[j];
		}

		//iterate over all weapon-types (of that chara) and over all free-slots of one-type
		//set a "unused" weapon-object to all of them
		for (int j = 0; j < i_weapon_types; j++)
		{
			for (int k = i_count_weapon_slots[j]; k < HWLPlayer::playerWeaponSlotsMax; k++)
			{
				//get the first free-offset and make an new weapon-object with default-values
				int i_offset_new = this->vi_blank_weapons[0];
				shared_ptr<HWLWeapon> hwlpw_tmp = make_shared<HWLWeapon>(i_offset_new, i, true);
				hwlpw_tmp->set_type(j);
				hwlpw_tmp->set_name(HWLWeapon::vs_playerWeaponTypeNames[i_weapon_count + j]);

				//bind this weapon to the character and delete this free-offset. because we use it now.
				hwlp_tmp->set_weapon_slot(j, hwlpw_tmp);
				this->vi_blank_weapons.erase(this->vi_blank_weapons.begin(), this->vi_blank_weapons.begin() + 1);
			}
		}

		//set the complete character-object to the chara-map and calculate the next offset
		this->m_players[HWLPlayer::vs_players[i]] = hwlp_tmp;
		i_offset = i_offset + this->playerOffsetLength;
	}

}

/**
* This method checks if a specific weapon belongs to the specific character and also calculate
* some needed things for that weapon with given parameters (some as reference)
*
*	@var int			 i_player_id				id of the specific character
*	@var int			 i_weapon_id				id of the specific weapon
*	@var string			 s_weapon_name				hold the name of an weapon (as a reference, calculate within the method)
*	@var int			 i_weapon_type				hold the type of an weapon (as a reference, calculate within the method)
*	@var int			 i_weapon_lvl				hold the level of an weapon (as a reference, calculate within the method)
*	@var vector<int>                vi_lvl_hexValues			hold the level-hex of all levels of a weapon
*													(as a reference, calculate within the method)
*	@var bool			b_is_multi_element_weapon	hold, if current weapon is a multi-element special weapon or not
*
*	@return bool		TRUE if weapon belongs to the given character and FALSE if not
*
*/
bool HWLSaveEditor::calc_players_weapons(int i_player_id, int i_weapon_id, string &s_weapon_name, int &i_weapon_type, int &i_weapon_lvl, vector<int> &vi_lvl_hexValues, bool &b_is_multi_element_weapon, int &i_multi_element_weapon_hex)
{
	//define an weapon-counter, and calculate all used weapon-types
	int i_weapon_count = 0;
	for (int j = 0; j < i_player_id; j++)
	{
		//count all weapon-types, from first-chara to this current chara - 
		//so we know then which weapon-type we have to use for that character or better which it's the first weapon-
		//type of this character
		i_weapon_count = i_weapon_count + HWLWeapon::vi_playerWeaponTypeCount[j];
	}

	//iterate over all weapon-types of the given character
	for (int j = 0; j < HWLWeapon::vi_playerWeaponTypeCount[i_player_id]; j++)
	{
		//declare all needed lvl-variables
		int i_current_lvl_2, i_current_lvl_3, i_current_lvl_4, i_current_multi_element_weapon_hex;

		//check if we have Links Master-Sword and if yes, set lvl2-4 to zero, because there is 
		//only one level of it, if not then calculate the level-offsets
		if (HWLWeapon::vi_playerWeaponTypeHexValues[i_weapon_count + j] != HWLWeapon::vi_playerWeaponTypeHexValues[4])
		{
			//calculate the level-offsets of the weapon (better the weapon-id, that belongs to the next-stronger
			//weapon of an weapon-type)
			//Form: level-2 = Weapon-ID Level-1 + 1; level-3 = Weapon-ID Level-1 + 2; 
			//and Level-4 is everytime a special new weapon-id
			i_current_lvl_2 = HWLWeapon::vi_playerWeaponTypeHexValues[i_weapon_count + j] + 1;
			i_current_lvl_3 = HWLWeapon::vi_playerWeaponTypeHexValues[i_weapon_count + j] + 2;
			i_current_lvl_4 = HWLWeapon::vi_playerWeaponTypeHexValuesLVL4[i_weapon_count + j];

			//calculate the current hex for the multi-element weapon of this type (available from 2nd DLC on)
			i_current_multi_element_weapon_hex = HWLWeapon::vi_playerWeaponTypeHexValuesMultiElement[i_weapon_count + j];

		}
		else{
			//we have the master-sword, so set all other level-hex and multi-element-hex to zero
			i_current_lvl_2 = i_current_lvl_3 = i_current_lvl_4 = i_current_multi_element_weapon_hex = 0;
		}

		//bind the calculated weapon-ids (levels) to the given vector (as reference-variable)
		vi_lvl_hexValues[0] = HWLWeapon::vi_playerWeaponTypeHexValues[i_weapon_count + j];
		vi_lvl_hexValues[1] = i_current_lvl_2;
		vi_lvl_hexValues[2] = i_current_lvl_3;
		vi_lvl_hexValues[3] = i_current_lvl_4;
		i_multi_element_weapon_hex = i_current_multi_element_weapon_hex;

		//Now checks the given weapon-id, if we have Level-1,2,3,4 or multi-element of the weapon-type and set 
		//the needed things correctly. And return true if all things went fine
		if (i_weapon_id == HWLWeapon::vi_playerWeaponTypeHexValues[i_weapon_count + j])
		{
			s_weapon_name = HWLWeapon::vs_playerWeaponTypeNames[i_weapon_count + j];
			i_weapon_type = j;
			i_weapon_lvl = 1;
			return true;
		}
		else if (i_weapon_id == i_current_lvl_2)
		{
			s_weapon_name = HWLWeapon::vs_playerWeaponTypeNames[i_weapon_count + j];
			i_weapon_type = j;
			i_weapon_lvl = 2;
			return true;
		}
		else if (i_weapon_id == i_current_lvl_3)
		{
			s_weapon_name = HWLWeapon::vs_playerWeaponTypeNames[i_weapon_count + j];
			i_weapon_type = j;
			i_weapon_lvl = 3;
			return true;
		}
		else if (i_weapon_id == i_current_lvl_4)
		{
			s_weapon_name = HWLWeapon::vs_playerWeaponTypeNames[i_weapon_count + j];
			i_weapon_type = j;
			i_weapon_lvl = 4;
			return true;
		}
		else if (i_weapon_id == i_current_multi_element_weapon_hex && i_weapon_id != 0)
		{
			s_weapon_name = HWLWeapon::vs_playerWeaponTypeNames[i_weapon_count + j];
			i_weapon_type = j;
			i_weapon_lvl = 4;
			b_is_multi_element_weapon = true;
			return true;
		}
	}

	//return false, if there was no bindable weapon for that character
	return false;
}

/**
* This method calculate the current materials-objects (bronze,silver and gold ones)
*
*/
void HWLSaveEditor::calc_materials()
{
	//declare/define needed variables
	int i_offset = this->bronzeMaterialsOffsetBegin;

	//iterate over all bronze-materials and calculate the values
	for (int i = 0; i < (signed)HWLMaterial::vs_bronzeMaterials.size(); i++)
	{
		//if we have the special-new-ones , then set an new offset
		if (i == (HWLMaterial::vs_bronzeMaterials.size() - 3))
			i_offset = this->bronzeMaterialsOffsetBeginNew;

		//create a new material-object, based on offset and name
		shared_ptr<HWLMaterial> hwlm_tmp = make_shared<HWLMaterial>(HWLMaterial::vs_bronzeMaterials[i], i_offset, 0);

		//bind the offset to the current map of them
		this->m_materials[HWLMaterial::vs_bronzeMaterials[i]] = hwlm_tmp;

		//calculate the next offset
		i_offset = i_offset + this->materialOffsetLength;
	}

	//define offset for the first silver-material
	i_offset = this->silverMaterialsOffsetBegin;

	//iterate over all silver-materials and calculate the values
	for (int i = 0; i < (signed)HWLMaterial::vs_silverMaterials.size(); i++)
	{
		//if we have the special-new-ones , then set an new offset
		if (i == (HWLMaterial::vs_silverMaterials.size() - 12))
			i_offset = this->silverMaterialsOffsetBeginNew;

		//create a new material-object, based on offset and name
		shared_ptr<HWLMaterial> hwlm_tmp = make_shared<HWLMaterial>(HWLMaterial::vs_silverMaterials[i], i_offset, 1);

		//bind the offset to the current map of them
		this->m_materials[HWLMaterial::vs_silverMaterials[i]] = hwlm_tmp;

		//calculate the next offset
		i_offset = i_offset + this->materialOffsetLength;
	}

	//define offset for the first gold-material
	i_offset = this->goldMaterialsOffsetBegin;

	//iterate over all gold-materials and calculate the values
	for (int i = 0; i < (signed)HWLMaterial::vs_goldMaterials.size(); i++)
	{
		//if we have the special-new-ones , then set an new offset
		if (i == (HWLMaterial::vs_goldMaterials.size() - 10))
			i_offset = this->goldMaterialsOffsetBeginNew;

		//create a new material-object, based on offset and name
		shared_ptr<HWLMaterial> hwlm_tmp = make_shared<HWLMaterial>(HWLMaterial::vs_goldMaterials[i], i_offset, 2);

		//bind the offset to the current map of them
		this->m_materials[HWLMaterial::vs_goldMaterials[i]] = hwlm_tmp;

		//calculate the next offset
		i_offset = i_offset + this->materialOffsetLength;
	}
}

/**
* This method calculate the fairyFood-objects
*
*/
void HWLSaveEditor::calc_fairyFood()
{
	//declare/define needed variables
	int i_offset = this->fairyFoodOffsetBegin;

	//iterate over all fairyFood items to create new objects
	for (int i = 0; i < (signed)HWLFairyFood::vs_fairyFood.size(); i++)
	{
		//create new fairyFood object, based on current offset
		shared_ptr<HWLFairyFood> hwlff_tmp = make_shared<HWLFairyFood>(HWLFairyFood::vs_fairyFood[i], i_offset);

		//bind the object to the map of them
		this->m_fairyfood[HWLFairyFood::vs_fairyFood[i]] = hwlff_tmp;

		//calculate the next offset
		i_offset = i_offset + this->fairyFoodOffsetLength;
	}

}

/**
* This method calculate the AdventureMode-Map-Objects
*
*/
void HWLSaveEditor::calc_amMaps()
{
	//iterate over Max-size of current known Maps and let the class
	//do its thing
	for (int i = 0; i < this->get_adventureMode_maxMaps(); i++)
	{
		shared_ptr<HWLAdventureModeMaps> hwlamm_tmp = make_shared<HWLAdventureModeMaps>(i);
		this->m_amMaps[i] = hwlamm_tmp;
	}
}

/**
* This method calculate the MyFairy-Objects
*
*/
void HWLSaveEditor::calc_myFairies()
{
	//declare/define needed variables
	int i_offset = this->fairyOffsetBegin;

	//iterate over all myFairies and create new objects
	for (int i = 0; i < HWLGeneral::fairiesMax; i++)
	{
		//create new object, based on offset
		shared_ptr<HWLFairy> hwlf_tmp = make_shared<HWLFairy>(i_offset);

		//bind object to the map of them
		this->m_fairy[i] = hwlf_tmp;

		//calculate the next offset
		i_offset = i_offset + this->fairyOffsetLength;
	}
}

/**
* This method calculate the restrictions for all objects due to the current game-version and DLCs
*
*/
void HWLSaveEditor::calc_game_versions_restrictions()
{
	//calc characters restrictions - disabled state -> BEGIN

	//disable the ??? characters
	this->get_player("???_1")->set_isDisabled(true);
	this->get_player("???_2")->set_isDisabled(true);

	//disable Medli on lower version as 1.3.0
	if (this->s_savefile_game_version == "1.0.0" || this->s_savefile_game_version == "1.2.0")
		this->get_player("Medli")->set_isDisabled(true);

	//disable Marin on lower versions as 1.4.0 or if DLC is not installed
	if (this->s_savefile_game_version == "1.0.0" || this->s_savefile_game_version == "1.2.0"
		|| this->s_savefile_game_version == "1.3.0" || !this->vb_game_dlc_installed[1])
		this->get_player("Marin")->set_isDisabled(true);

	//disable Toon-Zelda on lower versions as 1.5.0 or if DLC is not installed
	if (this->s_savefile_game_version == "1.0.0" || this->s_savefile_game_version == "1.2.0"
		|| this->s_savefile_game_version == "1.3.0" || this->s_savefile_game_version == "1.4.0" || !this->vb_game_dlc_installed[2])
		this->get_player("Toon Zelda")->set_isDisabled(true);

	//disable Ravio on lower versions as 1.6.0 or if DLC is not installed
	if (this->s_savefile_game_version == "1.0.0" || this->s_savefile_game_version == "1.2.0"
		|| this->s_savefile_game_version == "1.3.0" || this->s_savefile_game_version == "1.4.0" || this->s_savefile_game_version == "1.5.0"
		|| !this->vb_game_dlc_installed[3])
		this->get_player("Ravio")->set_isDisabled(true);

	//disable Yuga on lower versions as 1.6.0 or if DLC is not installed
	if (this->s_savefile_game_version == "1.0.0" || this->s_savefile_game_version == "1.2.0"
		|| this->s_savefile_game_version == "1.3.0" || this->s_savefile_game_version == "1.4.0" || this->s_savefile_game_version == "1.5.0"
		|| !this->vb_game_dlc_installed[3])
		this->get_player("Yuga")->set_isDisabled(true);


	//calc characters restrictions - disabled state -> END

	//calc characters restrictions - weapon-types-disabled state -> BEGIN

	//disable Linkles Boots, if DLC is not installed
	if (!this->vb_game_dlc_installed[1])
		this->get_player("Linkle")->set_disabled_weaponTypeID(1);

	//disable Toon-Links SandWand if DLC is not installed
	if (!this->vb_game_dlc_installed[2])
		this->get_player("Toon Link")->set_disabled_weaponTypeID(1);

	//calc characters restrictions - weapon-types-disabled state -> END

	//calc characters restrictions - AM-Maps disabled-state -> BEGIN

	//disable "MasterWindWaker-Map",  if DLC is not installed
	if (!this->vb_game_dlc_installed[0])
		this->get_amMap(5)->set_isDisabled(1);

	//disable "KoholintIsland-Map",  if DLC is not installed
	if (!this->vb_game_dlc_installed[1])
		this->get_amMap(6)->set_isDisabled(1);

	//disable "GrandTravels-Map",  if DLC is not installed
	if (!this->vb_game_dlc_installed[2])
		this->get_amMap(7)->set_isDisabled(1);

	//disable "Lorule-Map",  if DLC is not installed
	if (!this->vb_game_dlc_installed[3])
		this->get_amMap(8)->set_isDisabled(1);

	//calc characters restrictions - AM-Maps disabled-state -> END

	//calc characters restrictions - Weapon-Skils disabled-state -> BEGIN
	
	//disabed "Heart Power" - Skill below 1.6.0
	if (this->s_savefile_game_version == "1.0.0" || this->s_savefile_game_version == "1.2.0"
		|| this->s_savefile_game_version == "1.3.0" || this->s_savefile_game_version == "1.4.0" || this->s_savefile_game_version == "1.5.0")
		HWLWeapon::set_isWeaponSkillDisabled(0x36);

	//calc characters restrictions - Weapon-Skils  disabled-state -> END

}



/**
* This method return the current error-state
*
*/
int HWLSaveEditor::get_error()
{
	return this->i_error;
}

/**
* This method return the http-object for sending http-requests.
*
*/
shared_ptr<HWLHttp> HWLSaveEditor::get_http_object()
{
	return this->http_request;
}

/**
* This method return the general-object, with widely game-things
*
*/
shared_ptr<HWLGeneral> HWLSaveEditor::get_general_things()
{
	return this->sp_general;
}

/**
* This method return the coressponding character-object, based on character-id
*
*/
shared_ptr<HWLPlayer> HWLSaveEditor::get_player(int i_id)
{
	shared_ptr<HWLPlayer> hwlp_tmp = this->m_players[HWLPlayer::vs_players[i_id]];

	return hwlp_tmp;
}

/**
* This method return the coressponding character-object, based on character-name
*
*/
shared_ptr<HWLPlayer> HWLSaveEditor::get_player(string s_name)
{
	shared_ptr<HWLPlayer> hwlp_tmp = this->m_players[s_name];

	return hwlp_tmp;
}

/**
* This method return the coressponding material-object, based on material-id
* and type
*
*/
shared_ptr<HWLMaterial> HWLSaveEditor::get_material(int i_id, int i_type)
{
	shared_ptr<HWLMaterial> hwlm_tmp;
	switch (i_type)
	{
	case 0:
		hwlm_tmp = this->m_materials[HWLMaterial::vs_bronzeMaterials[i_id]];
		break;
	case 1:
		hwlm_tmp = this->m_materials[HWLMaterial::vs_silverMaterials[i_id]];
		break;
	case 2:
		hwlm_tmp = this->m_materials[HWLMaterial::vs_goldMaterials[i_id]];
		break;
	}


	return hwlm_tmp;
}

/**
* This method return the coressponding material-object, based on material-name
*
*/
shared_ptr<HWLMaterial> HWLSaveEditor::get_material(string s_name)
{
	shared_ptr<HWLMaterial> hwlm_tmp = this->m_materials[s_name];

	return hwlm_tmp;
}

/**
* This method return the coressponding fairyFood-object based on fairyFood-id
*
*/
shared_ptr<HWLFairyFood> HWLSaveEditor::get_fairyFood(int i_id)
{
	shared_ptr<HWLFairyFood> hwlff_tmp = this->m_fairyfood[HWLFairyFood::vs_fairyFood[i_id]];

	return hwlff_tmp;
}

/**
* This method return the coressponding fairyFood-object based on fairyFood-name
*
*/
shared_ptr<HWLFairyFood> HWLSaveEditor::get_fairyFood(string s_name)
{
	shared_ptr<HWLFairyFood> hwlff_tmp = this->m_fairyfood[s_name];

	return hwlff_tmp;
}

/**
* This method return the coressponding AdventureMode-Map-object,
*  based on AdventureMode-Map-id (unique ID)
*
*/
shared_ptr<HWLAdventureModeMaps> HWLSaveEditor::get_amMap(int i_map_id)
{
	shared_ptr<HWLAdventureModeMaps> hwlamm_tmp = this->m_amMaps[i_map_id];

	return hwlamm_tmp;
}

/**
* This method return the coressponding fairy-object based on fairy-id
*
*/
shared_ptr<HWLFairy> HWLSaveEditor::get_fairy(int i_id)
{
	shared_ptr<HWLFairy> hwlf_tmp = this->m_fairy[i_id];

	return hwlf_tmp;
}



/**
* This method return the size of the AdventureMode-MapNames-Vector,
* so we know how many Maps we have
*
*/
int HWLSaveEditor::get_adventureMode_maxMaps()
{
	return HWLSaveEdit::HWLAdventureModeMaps::vs_map_names.size();
}



/**
* This method checks, if we have a valid savegame-file length and truncate bigger
*  files.
*
*/
int HWLSaveEditor::check_savefile_length()
{
	//check if we have the normal length, then all is ok.
	if (this->i_filelength == this->fileNormalLength || !this->b_auto_trim)
		return 0;
	//check if we have a smaller savegame-file and return 1 
	// = throw exception with specified massage then
	else if (this->i_filelength < this->fileNormalLength)
	{
		return 1;
		//check if we have a bigger savegame file , do renaming stuff and
		//return 2 or 3, 2 = failure with renaming/create second file, 3 = all ok
	}
	else if (this->i_filelength > this->fileNormalLength)
	{
		//declare/define needed variables
		string s_filepathname_trimmed = this->s_filepathname + ".trimmed";
		string s_filepathname_backup = this->s_filepathname + ".bak";

		//create new trimmed-file, clear and close handler
		fstream fs_filehandler_trimmed = fstream(s_filepathname_trimmed, fstream::out);
		fs_filehandler_trimmed.clear();
		fs_filehandler_trimmed.close();

		//open new trimmed-file for writing and reading in binary mode
		fs_filehandler_trimmed = fstream(s_filepathname_trimmed,
			fstream::binary | fstream::in | fstream::out);

		//check if new trimmed-file is open, else return failure-state
		if (fs_filehandler_trimmed.is_open())
		{
			//set the new file-pointer to te begin of the file and clear all other things
			//before we will write
			fs_filehandler_trimmed.seekp(0, fs_filehandler_trimmed.beg);
			fs_filehandler_trimmed.clear();

			//calculate difference between normal-length and current length
			int i_filelength_diff = this->i_filelength - this->fileNormalLength;

			//write the current needed part of the file-cotent holder to the trimmed-savefile
			// and clear/close handler after it
			fs_filehandler_trimmed.write((char*)cp_filecontent, this->i_filelength - i_filelength_diff);
			fs_filehandler_trimmed.clear();
			fs_filehandler_trimmed.close();

			// clear and close filehandler of the current savefile (need for renaming)
			this->fs_filehandler.clear();
			this->fs_filehandler.close();

			//rename current savefile to backup and trimmed savefile to normal-savefile
			rename(this->s_filepathname.c_str(), s_filepathname_backup.c_str());
			rename(s_filepathname_trimmed.c_str(), this->s_filepathname.c_str());

			//return 3 and throw specified exception then
			return 3;
		}
		else{
			//return 2 and throw specified exception then
			return 2;
		}
	}
}

/**
* This method checks, if we have an valid savegame
*
*/
bool HWLSaveEditor::check_savefile()
{
	//declare needed variables
	string s_file_header[5];

	//iterate over the first five offsets of the file-header and
	//set them to the correct string-array entry
	for (int i = 0; i < 5; i++)
	{
		s_file_header[i] = this->getHexStringFromFileContent(this->fileHeaderOffsetBegin + i, 1);
	}

	//check if the first five offsets have these values, it's a hardcoded check! All savegame-files of 
	//Hyrule Warriors Legends must have those values at the beginning.
	if (s_file_header[0] == "00" && s_file_header[1] == "26" && s_file_header[2] == "10" && s_file_header[3] == "15"
		&& s_file_header[4] == "00")
		return true;
	else
		return false;
}



/**
* This method is for triggering the autmatic trim.
* Default: TRUE, and auto-trim is enabled.
*
*/
void HWLSaveEditor::enable_auto_trim(bool b_auto_trim_value)
{
	b_auto_trim = b_auto_trim_value;
}



/**
* This method save the current value of the file-content holder to the
* savefile itself
*
*/
void HWLSaveEditor::save_file()
{
	//check if the savefile is already opened, so that we can write
	//else throw an Exception
	if (this->fs_filehandler.is_open())
	{
		//set the file-pointer to te begin of the file and clear all other things
		//before we will write
		this->fs_filehandler.seekp(0, this->fs_filehandler.beg);
		this->fs_filehandler.clear();

		//write the current value of the file-content holder to the savefile 
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

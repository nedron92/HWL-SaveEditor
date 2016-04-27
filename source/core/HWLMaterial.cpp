//needed for including in a MFC-App
#ifdef __MFC__
#include "../gui/stdafx.h" 
#endif // __MFC__

//include the correct header-file
#include "HWLMaterial.h"

//use the project-namespace
using namespace HWLSaveEdit;

/* @var vs_bronzeMaterials			vector for holding all names of bronze Materials */
const vector<string> HWLMaterial::vs_bronzeMaterials =
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

/* @var vs_silverMaterials				vector for holding all names of silver Materials */
const vector<string> HWLMaterial::vs_silverMaterials =
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

/* @var vs_goldMaterials			vector for holding all names of gold Materials */
const vector<string> HWLMaterial::vs_goldMaterials =
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

/* @var materialValueMax	maximal-value of a material */
const int HWLMaterial::materialValueMax = 999;



/**
* Only the initialization of the normal-constructor
*/
HWLMaterial::HWLMaterial(string s_name, int i_offset, int i_type)
{
	//set or calculate all needed members
	this->s_name = s_name;
	this->i_offset = i_offset;
	this->i_type = i_type;
	this->i_value = this->calc_value();
}

/**
* Only the initialization of the normal-destructor
*/
HWLMaterial::~HWLMaterial()
{
}



/**
* This method calculates the current material value
*
*	@return int		the current material-value
*
*/
int HWLMaterial::calc_value()
{
	//declare/define needed variables
	string s_material_value;
	int i_material_offset = this->i_offset;

	//get hex-value from the file-content holder and convert it to int
	s_material_value = this->getHexStringFromFileContent(i_material_offset, this->materialOffsetLength);
	int i_material_value = this->HexStringToInt(s_material_value);

	//return the current int-value
	return i_material_value;
}

/**
* This method set the current material-value
* to the file-content holder
*
*/
void HWLMaterial::save_value()
{
	//declare/define needed variables
	int i_value_tmp = this->i_value;
	string s_material_value;
	int i_material_offset = this->i_offset;

	//convert the current integer-value to hex and add needed zeros, if we
	//don't have the complete length (calculate with offset-length multiplied by 2)
	s_material_value = this->intToHexString(i_value_tmp, false);
	this->addZeroToHexString(s_material_value, this->materialOffsetLength * 2);

	//set converted hex-value to the file-content holder
	this->setHexStringToFileContent(s_material_value, i_material_offset);
}



/**
* Setter for the material-value
*
*	@var int	i_value		material-value to set
*
*/
void HWLMaterial::set_value(int i_value)
{
	//check if material-value smaller then 0, then set it directly to 0
	//also check for the maximal-value
	if (i_value < 0)
		i_value = 0;
	else if (i_value > this->materialValueMax)
		i_value = this->materialValueMax;

	this->i_value = i_value;

}



/**
* Getter for the materials-name
*
*	@return string		the name of the material
*
*/
string HWLMaterial::get_name()
{
	return this->s_name;
}

/**
* Getter for the materials-offset
*
*	@return int		the offset of the material
*
*/
int HWLMaterial::get_offset()
{
	return this->i_offset;
}

/**
* Getter for the materials-type
*
*	@return int		the type of the material
*
*/
int HWLMaterial::get_type()
{
	return this->i_type;
}

/**
* Getter for the materials-type as string
*
*	@return string		the type of the material as a string
*
*/
string HWLMaterial::get_type(bool b_get_string)
{
	switch (this->i_type)
	{
		case 0:
			return "Bronze";
			break;

		case 1:
			return "Silver";
			break;

		case 2:
			return "Gold";
			break;

		default:
			return to_string(i_type);
	}
}

/**
* Getter for the materials-value
*
*	@return int		the value of the material
*
*/
int HWLMaterial::get_value()
{
	return this->i_value;
}



/**
* This method returns an formatted string, which contain all needed member-values
*
*	@return string		formatted output with all needed member-values
*
*/
string HWLMaterial::get_MaterialForOutput()
{
	string s_output = "Name: " + this->s_name + "\n"
		+ "  Type: " + this->get_type(true) + "\n"
		+ "  Value: " + to_string(this->i_value) + "\n";

	return s_output;
}



/**
* This method is a wrapper for all known save-methods of the class
*
*/
void HWLMaterial::save_Material()
{
	this->save_value();
}

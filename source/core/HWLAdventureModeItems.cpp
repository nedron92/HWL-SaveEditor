//needed for including in a MFC-App
#ifdef __MFC__
#include "../gui/stdafx.h" 
#endif // __MFC__

#include "HWLAdventureModeItems.h"

//use the project-namespace
using namespace HWLSaveEdit;

const int HWLAdventureModeItems::amItemValueMax = 5;

const int HWLAdventureModeItems::amItemPerMapMax = 12;

HWLAdventureModeItems::HWLAdventureModeItems(string s_name, int i_offset, int i_type)
{
	this->s_name = s_name;
	this->i_offset = i_offset;
	this->i_type = i_type;
	this->i_value = this->calc_value();
}


HWLAdventureModeItems::~HWLAdventureModeItems()
{
}

int HWLAdventureModeItems::calc_value()
{
	string s_amItem_value;
	int i_amItem_offset = this->i_offset;

	s_amItem_value = this->getHexStringFromFileContent(i_amItem_offset, this->amItemOffsetLength);

	int i_amItem_value= this->HexStringToInt(s_amItem_value);

	return i_amItem_value;
}

void HWLAdventureModeItems::save_value()
{
	int i_value_tmp = this->i_value;
	string s_amItem_value;
	int i_amItem_offset = this->i_offset;

	s_amItem_value = this->intToHexString(i_value_tmp, false);
	this->addZeroToHexString(s_amItem_value, this->amItemOffsetLength * 2);

	this->setHexStringToFileContent(s_amItem_value, i_amItem_offset);
}

void HWLAdventureModeItems::set_value(int i_value)
{
	if (i_value < 0)
		i_value = 0;
	else if (i_value > this->amItemValueMax)
		i_value = this->amItemValueMax;

	this->i_value = i_value;

}

string HWLAdventureModeItems::get_name()
{
	return this->s_name;
}

int HWLAdventureModeItems::get_offset()
{
	return this->i_offset;
}

int HWLAdventureModeItems::get_type()
{
	return this->i_type;
}

string HWLAdventureModeItems::get_type(bool b_get_string)
{
	switch (this->i_type)
	{
	case 0:
		return "Adventure-Map Item";
		break;

	case 1:
		return "GreatSea-Map Item";
		break;

	case 2:
		return "MasterQuest-Map Item ";
		break;

	default:
		return to_string(i_type);
	}
}

int HWLAdventureModeItems::get_value()
{
	return this->i_value;
}



string HWLAdventureModeItems::get_AMItemForOutput()
{
	string s_output = "Name: " + this->s_name + "\n"
		+ "  Type: " + this->get_type(true) + "\n"
		+ "  Value: " + to_string(this->i_value) + "\n";

	return s_output;
}

void HWLAdventureModeItems::save_AMItem()
{
	this->save_value();
}

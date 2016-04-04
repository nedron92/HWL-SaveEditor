//needed for including in a MFC-App
#ifdef __MFC__
#include "../gui/stdafx.h" 
#endif // __MFC__

#include "HWLFairyFood.h"

//use the project-namespace
using namespace HWLSaveEdit;

const int HWLFairyFood::fairyFoodlValueMax = 255;

const int HWLFairyFood::fairyGratitudeCrystalIDBegin = 114;
const int HWLFairyFood::fairyGratitudeCrystalIDEnd = 128;

HWLFairyFood::HWLFairyFood(string s_name, int i_offset)
{
	this->s_name = s_name;
	this->i_offset = i_offset;
	this->i_value = this->calc_value();
}


HWLFairyFood::~HWLFairyFood()
{
}

int HWLFairyFood::calc_value()
{
	string s_fairyFood_value;
	int i_fairyFood_offset = this->i_offset;

	s_fairyFood_value = this->getHexStringFromFileContent(i_fairyFood_offset, this->fairyFoodOffsetLength);

	int i_fairyFood_value = this->HexStringToInt(s_fairyFood_value);

	return i_fairyFood_value;
}

void HWLFairyFood::save_value()
{
	int i_value_tmp = this->i_value;
	string s_fairyFood_value;
	int i_fairyFood_offset = this->i_offset;

	s_fairyFood_value = this->intToHexString(i_value_tmp, false);
	this->addZeroToHexString(s_fairyFood_value, this->fairyFoodOffsetLength * 2);

	this->setHexStringToFileContent(s_fairyFood_value, i_fairyFood_offset);
}

void HWLFairyFood::set_value(int i_value)
{
	if (i_value < 0)
		i_value = 0;
	else if (i_value > this->fairyFoodlValueMax)
		i_value = this->fairyFoodlValueMax;

	this->i_value = i_value;
}

string HWLFairyFood::get_name()
{
	return this->s_name;
}

int HWLFairyFood::get_offset()
{
	return this->i_offset;
}

int HWLFairyFood::get_value()
{
	return this->i_value;
}


string HWLFairyFood::get_FairyFoodForOutput()
{
	string s_output = "Name: " + this->s_name + "\n"
		+ "  Value: " + to_string(this->i_value) + "\n";

	return s_output;
}

void HWLFairyFood::save_FairyFood()
{
	this->save_value();
}

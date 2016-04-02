//needed for including in a MFC-App
#ifdef __MFC__
#include "../gui/stdafx.h" 
#endif // __MFC__

#include "HWLMaterial.h"

using namespace HWLSaveEdit;

const int HWLMaterial::materialValueMax = 999;


HWLMaterial::HWLMaterial(string s_name, int i_offset, int i_type)
{
	this->s_name = s_name;
	this->i_offset = i_offset;
	this->i_type = i_type;
	this->i_value = this->calc_value();
}


HWLMaterial::~HWLMaterial()
{
}

int HWLMaterial::calc_value()
{
	string s_material_value;
	int i_material_offset = this->i_offset;

	s_material_value = this->getHexStringFromFileContent(i_material_offset, this->materialOffsetLength);

	int i_material_value = this->HexStringToInt(s_material_value);

	return i_material_value;
}

void HWLMaterial::save_value()
{
	int i_value_tmp = this->i_value;
	string s_material_value;
	int i_material_offset = this->i_offset;

	s_material_value = this->intToHexString(i_value_tmp, false);
	this->addZeroToHexString(s_material_value, this->materialOffsetLength * 2);

	this->setHexStringToFileContent(s_material_value, i_material_offset);
}

void HWLMaterial::set_value(int i_value)
{
	if (i_value < 0)
		i_value = 0;
	else if (i_value > this->materialValueMax)
		i_value = this->materialValueMax;

	this->i_value = i_value;

}

string HWLMaterial::get_name()
{
	return this->s_name;
}

int HWLMaterial::get_offset()
{
	return this->i_offset;
}

int HWLMaterial::get_type()
{
	return this->i_type;
}

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

int HWLMaterial::get_value()
{
	return this->i_value;
}



string HWLMaterial::get_MaterialForOutput()
{
	string s_output = "Name: " + this->s_name + "\n"
		+ "  Type: " + this->get_type(true) + "\n"
		+ "  Value: " + to_string(this->i_value) + "\n";

	return s_output;
}

void HWLMaterial::save_Material()
{
	this->save_value();
}

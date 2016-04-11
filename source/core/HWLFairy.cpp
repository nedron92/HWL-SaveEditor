//needed for including in a MFC-App
#ifdef __MFC__
#include "../gui/stdafx.h" 
#endif // __MFC__

#include "HWLFairy.h"

//use the project-namespace
using namespace HWLSaveEdit;

const int HWLFairy::fairyNameOffsetLength = 0x8;
const int HWLFairy::fairyLVLOffsetLength = 0x1;
const int HWLFairy::fairyTrustOffsetLength = 0x1;
const int HWLFairy::fairyIteratorOffsetLength = 0x1;
const int HWLFairy::fairyIsUnlockOffsetLength = 0x1;

const int HWLFairy::fairyNameOffsetDiff = 0xA;
const int HWLFairy::fairyLVLOffsetDiff = 0x1B;
const int HWLFairy::fairyTrustOffsetDiff = 0x24;
const int HWLFairy::fairyIteratorOffsetDiff = 0x6c;
const int HWLFairy::fairyIsUnlockOffsetDiff = 0x0;

const int HWLFairy::fairyLVLMax = 99;
const int HWLFairy::fairyTrustMax = 100;
const int HWLFairy::fairyIteratorMax = 99;

const int HWLFairy::fairyNameLength = HWLFairy::fairyNameOffsetLength;

HWLFairy::HWLFairy(int i_offset)
{
	this->i_offset = i_offset;
	this->s_name = this->calc_fairy_name();
	this->i_lvl = this->calc_fairy_lvl();
	this->i_trust = this->calc_fairy_trust();
	this->i_iterator = this->calc_fairy_iterator();
	this->b_isUnlock = this->calc_fairy_isUnlockState();
}


HWLFairy::~HWLFairy()
{
}



string HWLFairy::calc_fairy_name()
{
	string shex_fairyName;
	int i_fairy_name_offset = this->i_offset + this->fairyNameOffsetDiff;

	shex_fairyName = this->getHexStringFromFileContent(i_fairy_name_offset, this->fairyNameOffsetLength,true);

	string s_fairyName = this->HexStringToByteString(shex_fairyName);

	return s_fairyName;
}

int HWLFairy::calc_fairy_lvl()
{
	string s_fairyLVL;
	int i_fairy_lvl_offset = this->i_offset + this->fairyLVLOffsetDiff;

	s_fairyLVL = this->getHexStringFromFileContent(i_fairy_lvl_offset, this->fairyLVLOffsetLength);

	int i_fairyLVL = this->HexStringToInt(s_fairyLVL);

	return i_fairyLVL;
}

int HWLFairy::calc_fairy_trust()
{
	string s_fairyTrust;
	int i_fairy_trust_offset = this->i_offset + this->fairyTrustOffsetDiff;

	s_fairyTrust = this->getHexStringFromFileContent(i_fairy_trust_offset, this->fairyTrustOffsetLength);

	int i_fairyTrust = this->HexStringToInt(s_fairyTrust);

	return i_fairyTrust;
}

int HWLFairy::calc_fairy_iterator()
{
	string s_fairy_iterator;

	int i_fairy_iterator_offset = this->i_offset + this->fairyIteratorOffsetDiff;

	s_fairy_iterator = this->getHexStringFromFileContent(i_fairy_iterator_offset, this->fairyIteratorOffsetLength);

	int i_fairy_iterator = this->HexStringToInt(s_fairy_iterator);

	return i_fairy_iterator;
}

bool HWLFairy::calc_fairy_isUnlockState()
{
	string s_fairyIsUnlock;
	int i_fairy_isUnlock_offset = this->i_offset + this->fairyIsUnlockOffsetDiff;

	s_fairyIsUnlock = this->getHexStringFromFileContent(i_fairy_isUnlock_offset, this->fairyIsUnlockOffsetLength);

	int i_fairyIsUnlock = this->HexStringToInt(s_fairyIsUnlock);

	return (bool)i_fairyIsUnlock;
}





void HWLFairy::save_fairy_name()
{
	string s_fairyName = this->s_name;
	string shex_fairyName;
	int i_fairy_name_offset = this->i_offset + this->fairyNameOffsetDiff;

	shex_fairyName = this->ByteStringToHexString(s_fairyName);
	this->addZeroToHexString(shex_fairyName, this->fairyNameOffsetLength * 2,true);

	this->setHexStringToFileContent(shex_fairyName, i_fairy_name_offset,true);
}

void HWLFairy::save_fairy_lvl()
{
	int i_lvl_tmp = this->i_lvl;
	string s_fairyLVL;
	int i_fairy_lvl_offset = this->i_offset + this->fairyLVLOffsetDiff;

	s_fairyLVL = this->intToHexString(i_lvl_tmp, false);
	this->addZeroToHexString(s_fairyLVL, this->fairyLVLOffsetLength * 2);

	this->setHexStringToFileContent(s_fairyLVL, i_fairy_lvl_offset);
}

void HWLFairy::save_fairy_trust()
{
	int i_trust_tmp = this->i_trust;
	string s_fairyTrust;
	int i_fairy_trust_offset = this->i_offset + this->fairyTrustOffsetDiff;

	s_fairyTrust = this->intToHexString(i_trust_tmp, false);
	this->addZeroToHexString(s_fairyTrust, this->fairyTrustOffsetLength * 2);

	this->setHexStringToFileContent(s_fairyTrust, i_fairy_trust_offset);
}

void HWLFairy::save_fairy_iterator()
{
	int i_iterator_tmp = this->i_iterator;
	string s_fairyIterator;
	int i_fairy_iterator_offset = this->i_offset + this->fairyIteratorOffsetDiff;

	s_fairyIterator = this->intToHexString(i_iterator_tmp, false);
	this->addZeroToHexString(s_fairyIterator, this->fairyIteratorOffsetLength * 2);

	this->setHexStringToFileContent(s_fairyIterator, i_fairy_iterator_offset);
}

void HWLFairy::save_fairy_isUnlockState()
{
	bool b_isUnlock_tmp = this->b_isUnlock;
	string s_fairyIsUnlock;
	int i_fairy_isUnlock_offset = this->i_offset + this->fairyIsUnlockOffsetDiff;

	s_fairyIsUnlock = this->intToHexString(b_isUnlock_tmp, false);
	this->addZeroToHexString(s_fairyIsUnlock, this->fairyIsUnlockOffsetLength * 2);

	this->setHexStringToFileContent(s_fairyIsUnlock, i_fairy_isUnlock_offset);
}

//setter/Getter
void HWLFairy::set_name(string s_name)
{
	if (s_name.size() <= this->fairyNameLength)
	{
		this->s_name = s_name;
	}else
	{
		int i_size = s_name.size();
		int i_diff = i_size - this->fairyNameLength;


		for (int i = 1; i <= i_diff; i++)
		{
			s_name.erase(i_size-i);
		}

		this->s_name = s_name;
	}
}

void HWLFairy::set_lvl(int i_lvl)
{
	if (i_lvl < 1)
		i_lvl = 1;
	else if (i_lvl > this->fairyLVLMax)
		i_lvl = fairyLVLMax;

	this->i_lvl = i_lvl;
}

void HWLFairy::set_trust(int i_trust)
{
	if (i_trust < 1)
		i_trust = 1;
	else if (i_trust > this->fairyTrustMax)
		i_trust = fairyTrustMax;

	this->i_trust = i_trust;

}

void HWLFairy::set_iterator(int i_iterator)
{
	if (i_iterator < 0)
		i_iterator = 0;
	else if (i_iterator > this->fairyIteratorMax)
		i_iterator = fairyIteratorMax;

	this->i_iterator = i_iterator;

}

void HWLFairy::set_isUnlock(bool b_isUnlock)
{
	this->b_isUnlock = b_isUnlock;
}


string HWLFairy::get_name()
{
	return this->s_name;
}

int HWLFairy::get_offset()
{
	return this->i_offset;
}

int HWLFairy::get_lvl()
{
	return this->i_lvl;
}

int HWLFairy::get_trust()
{
	return this->i_trust;
}

int HWLFairy::get_iterator()
{
	return this->i_iterator;
}

bool HWLFairy::get_isUnlock()
{
	return this->b_isUnlock;
}

string HWLFairy::get_fairyForOutput()
{
	string s_output = "Name: " + this->s_name + "\n"
		+ "  Unlock?: " + to_string(this->b_isUnlock) + "\n"
		+ "  Level: " + to_string(this->i_lvl) + "\n"
		+ "  Trust: " + to_string(this->i_trust) + "\n"
		+ "  Refreshes: " + to_string(this->i_iterator) + "\n";

	return s_output;
}

void HWLFairy::save_Fairy()
{
	this->save_fairy_name();
	this->save_fairy_lvl();
	this->save_fairy_trust();
	this->save_fairy_iterator();
	this->save_fairy_isUnlockState();
}
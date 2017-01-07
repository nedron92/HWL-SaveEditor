/*
 * @author: nedron92, 2016
 */
//needed for including in a MFC-App
#ifdef __MFC__
#include "../gui/stdafx.h" 
#endif // __MFC__

//include the correct header-file
#include "HWLFairy.h"

//use the project-namespace
using namespace HWLSaveEdit;

/* @var fairyNameOffsetLength			offset length of the fairy name */
const int HWLFairy::fairyNameOffsetLength = 0x8;

/* @var fairyLVLOffsetLength			offset length of the fairy LVL */
const int HWLFairy::fairyLVLOffsetLength = 0x1;

/* @var fairyTrustOffsetLength			offset length of the fairy Trust */
const int HWLFairy::fairyTrustOffsetLength = 0x1;

/* @var fairyIteratorOffsetLength		offset length of the fairy Refreshes */
const int HWLFairy::fairyIteratorOffsetLength = 0x2;

/* @var fairyIsUnlockOffsetLength		offset length of the fairy Unlock-State */
const int HWLFairy::fairyIsUnlockOffsetLength = 0x1;


/* @var fairyNameOffsetDiff				offset-diff from begin of the fairy name */
const int HWLFairy::fairyNameOffsetDiff = 0xA;

/* @var fairyLVLOffsetDiff				offset-diff from begin of the fairy LVL */
const int HWLFairy::fairyLVLOffsetDiff = 0x1B;

/* @var fairyTrustOffsetDiff			offset-diff from beginof the fairy Trust */
const int HWLFairy::fairyTrustOffsetDiff = 0x24;

/* @var fairyIteratorOffsetDiff			offset-diff from begin of the fairy Refreshes */
const int HWLFairy::fairyIteratorOffsetDiff = 0x6c;

/* @var fairyIsUnlockOffsetDiff			offset-diff from begin of the fairy Unlock-State */
const int HWLFairy::fairyIsUnlockOffsetDiff = 0x0;


/* @var fairyNameLength					maximal-length of the fairy-name */
const int HWLFairy::fairyNameLength = HWLFairy::fairyNameOffsetLength;

/* @var fairyLVLMax						maximal-value of the fairy-lvl */
const int HWLFairy::fairyLVLMax = 99;

/* @var fairyTrustMax					maximal-value of the fairy-trust */
const int HWLFairy::fairyTrustMax = 100;

/* @var fairyIteratorMax				maximal-value of the fairy-refreshes */
const int HWLFairy::fairyIteratorMax = 999;



/**
* Only the initialization of the normal-constructor
*/
HWLFairy::HWLFairy(int i_offset)
{
	//set or calculate all needed members
	this->i_offset = i_offset;
	this->s_name = this->calc_fairy_name();
	this->i_lvl = this->calc_fairy_lvl();
	this->i_trust = this->calc_fairy_trust();
	this->i_iterator = this->calc_fairy_iterator();
	this->b_isUnlock = this->calc_fairy_isUnlockState();
}

/**
* Only the initialization of the normal-destructor
*/
HWLFairy::~HWLFairy()
{
}



/**
* This method calculates the current fairy-name
*
*	@return string		the current fairy-name
*
*/
string HWLFairy::calc_fairy_name()
{
	//declare/define needed variables
	string shex_fairyName;
	int i_fairy_name_offset = this->i_offset + this->fairyNameOffsetDiff;

	//get hex-value from the file-content holder and convert it to a ByteString (for special-chars)
	shex_fairyName = this->getHexStringFromFileContent(i_fairy_name_offset, this->fairyNameOffsetLength, true);
	string s_fairyName = this->HexStringToByteString(shex_fairyName);

	//return the current MultiByte-String
	return s_fairyName;
}

/**
* This method calculates the current fairy LVL-value
*
*	@return int		the current lvl
*
*/
int HWLFairy::calc_fairy_lvl()
{
	//declare/define needed variables
	string s_fairyLVL;
	int i_fairy_lvl_offset = this->i_offset + this->fairyLVLOffsetDiff;

	//get hex-value from the file-content holder and convert it to int
	s_fairyLVL = this->getHexStringFromFileContent(i_fairy_lvl_offset, this->fairyLVLOffsetLength);
	int i_fairyLVL = this->HexStringToInt(s_fairyLVL);

	//return the current int-value
	return i_fairyLVL;
}

/**
* This method calculates the current fairy Trust-value
*
*	@return int		the current trust
*
*/
int HWLFairy::calc_fairy_trust()
{
	//declare/define needed variables
	string s_fairyTrust;
	int i_fairy_trust_offset = this->i_offset + this->fairyTrustOffsetDiff;

	//get hex-value from the file-content holder and convert it to int
	s_fairyTrust = this->getHexStringFromFileContent(i_fairy_trust_offset, this->fairyTrustOffsetLength);
	int i_fairyTrust = this->HexStringToInt(s_fairyTrust);

	//return the current int-value
	return i_fairyTrust;
}

/**
* This method calculates the current fairy refreshes-value
*
*	@return int		the current refreshes
*
*/
int HWLFairy::calc_fairy_iterator()
{
	//declare/define needed variables
	string s_fairy_iterator;
	int i_fairy_iterator_offset = this->i_offset + this->fairyIteratorOffsetDiff;

	//get hex-value from the file-content holder and convert it to int
	s_fairy_iterator = this->getHexStringFromFileContent(i_fairy_iterator_offset, this->fairyIteratorOffsetLength);
	int i_fairy_iterator = this->HexStringToInt(s_fairy_iterator);

	//return the current int-value
	return i_fairy_iterator;
}

/**
* This method calculates the current fairy Unlock-State
*
*	@return bool		the current Unlock-State
*
*/
bool HWLFairy::calc_fairy_isUnlockState()
{
	//declare/define needed variables
	string s_fairyIsUnlock;
	int i_fairy_isUnlock_offset = this->i_offset + this->fairyIsUnlockOffsetDiff;

	//get hex-value from the file-content holder and convert it to int
	s_fairyIsUnlock = this->getHexStringFromFileContent(i_fairy_isUnlock_offset, this->fairyIsUnlockOffsetLength);
	int i_fairyIsUnlock = this->HexStringToInt(s_fairyIsUnlock);

	//return the current int-value, casted as bool
	return (bool)i_fairyIsUnlock;
}



/**
* This method set the current fairy-name
* to the file-content holder
*
*/
void HWLFairy::save_fairy_name()
{
	//declare/define needed variables
	string s_fairyName = this->s_name;
	string shex_fairyName;
	int i_fairy_name_offset = this->i_offset + this->fairyNameOffsetDiff;

	//convert current name to an HexString and add needed zeros, if we
	//don't have the complete length (calculate with offset-length multiplied by 2)
	//we have to add the zero to the end, this time, because a 00 is
	//the end of the fairy-name
	shex_fairyName = this->ByteStringToHexString(s_fairyName);
	this->addZeroToHexString(shex_fairyName, this->fairyNameOffsetLength * 2, true);

	//set converted hex-value to the file-content holder and because we
	//set directly single-characters, we need the last parameter = true
	this->setHexStringToFileContent(shex_fairyName, i_fairy_name_offset, true);
}

/**
* This method set the current fairy LVL-value
* to the file-content holder
*
*/
void HWLFairy::save_fairy_lvl()
{
	//declare/define needed variables
	int i_lvl_tmp = this->i_lvl;
	string s_fairyLVL;
	int i_fairy_lvl_offset = this->i_offset + this->fairyLVLOffsetDiff;

	//convert the current integer-value to hex and add needed zeros, if we
	//don't have the complete length (calculate with offset-length multiplied by 2)
	s_fairyLVL = this->intToHexString(i_lvl_tmp, false);
	this->addZeroToHexString(s_fairyLVL, this->fairyLVLOffsetLength * 2);

	//set converted hex-value to the file-content holder
	this->setHexStringToFileContent(s_fairyLVL, i_fairy_lvl_offset);
}

/**
* This method set the current fairy Trust-value
* to the file-content holder
*
*/
void HWLFairy::save_fairy_trust()
{
	//declare/define needed variables
	int i_trust_tmp = this->i_trust;
	string s_fairyTrust;
	int i_fairy_trust_offset = this->i_offset + this->fairyTrustOffsetDiff;

	//convert the current integer-value to hex and add needed zeros, if we
	//don't have the complete length (calculate with offset-length multiplied by 2)
	s_fairyTrust = this->intToHexString(i_trust_tmp, false);
	this->addZeroToHexString(s_fairyTrust, this->fairyTrustOffsetLength * 2);

	//set converted hex-value to the file-content holder
	this->setHexStringToFileContent(s_fairyTrust, i_fairy_trust_offset);
}

/**
* This method set the current fairy Refreshes-value
* to the file-content holder
*
*/
void HWLFairy::save_fairy_iterator()
{
	//declare/define needed variables
	int i_iterator_tmp = this->i_iterator;
	string s_fairyIterator;
	int i_fairy_iterator_offset = this->i_offset + this->fairyIteratorOffsetDiff;

	//convert the current integer-value to hex and add needed zeros, if we
	//don't have the complete length (calculate with offset-length multiplied by 2)
	s_fairyIterator = this->intToHexString(i_iterator_tmp, false);
	this->addZeroToHexString(s_fairyIterator, this->fairyIteratorOffsetLength * 2);

	//set converted hex-value to the file-content holder
	this->setHexStringToFileContent(s_fairyIterator, i_fairy_iterator_offset);
}

/**
* This method set the current fairy Unlock-Stae
* to the file-content holder
*
*/
void HWLFairy::save_fairy_isUnlockState()
{
	bool b_isUnlock_tmp = this->b_isUnlock;
	string s_fairyIsUnlock;
	int i_fairy_isUnlock_offset = this->i_offset + this->fairyIsUnlockOffsetDiff;

	//convert the current integer-value (casted from bool) to hex and add needed zeros, if we
	//don't have the complete length (calculate with offset-length multiplied by 2)
	s_fairyIsUnlock = this->intToHexString(b_isUnlock_tmp, false);
	this->addZeroToHexString(s_fairyIsUnlock, this->fairyIsUnlockOffsetLength * 2);

	//set converted hex-value to the file-content holder
	this->setHexStringToFileContent(s_fairyIsUnlock, i_fairy_isUnlock_offset);
}



/**
* Setter for the fairy-name
*
*	@var string		s_name		fairy-name to set
*
*/
void HWLFairy::set_name(string s_name)
{
	//check if the name is smaller or equal the maximal-length
	//else resize it to the maximal-lengtzh (delete the last characters)
	if (s_name.size() <= this->fairyNameLength)
	{
		this->s_name = s_name;
	}
	else
	{
		int i_size = s_name.size();
		int i_diff = i_size - this->fairyNameLength;


		for (int i = 1; i <= i_diff; i++)
		{
			s_name.erase(i_size - i);
		}

		this->s_name = s_name;
	}
}

/**
* Setter for the fairy-LVL
*
*	@var int	i_lvl		lvl-value to set
*
*/
void HWLFairy::set_lvl(int i_lvl)
{
	//check if lvl-value smaller then 1, then set it directly to 1
	//also check for the maximal-value
	if (i_lvl < 1)
		i_lvl = 1;
	else if (i_lvl > this->fairyLVLMax)
		i_lvl = fairyLVLMax;

	this->i_lvl = i_lvl;
}

/**
* Setter for the fairy-Trust
*
*	@var int	i_trust		trust-value to set
*
*/
void HWLFairy::set_trust(int i_trust)
{
	//check if trust-value smaller then 1, then set it directly to 1
	//also check for the maximal-value
	if (i_trust < 1)
		i_trust = 1;
	else if (i_trust > this->fairyTrustMax)
		i_trust = fairyTrustMax;

	this->i_trust = i_trust;

}

/**
* Setter for the fairy-Refreshes
*
*	@var int	i_iterator		refreshes-value to set
*
*/
void HWLFairy::set_iterator(int i_iterator)
{
	//check if refreshes-value smaller then 0, then set it directly to 0
	//also check for the maximal-value
	if (i_iterator < 0)
		i_iterator = 0;
	else if (i_iterator > this->fairyIteratorMax)
		i_iterator = fairyIteratorMax;

	this->i_iterator = i_iterator;

}

/**
* Setter for the fairy Unlock-State
*
*	@var bool	b_isUnlock		unlock-state to set
*
*/
void HWLFairy::set_isUnlock(bool b_isUnlock)
{
	this->b_isUnlock = b_isUnlock;
}



/**
* Getter for the fairy-name
*
*	@return string		the name of the fairy
*
*/
string HWLFairy::get_name()
{
	return this->s_name;
}

/**
* Getter for the fairy-offset
*
*	@return int		the offset of the fairy
*
*/
int HWLFairy::get_offset()
{
	return this->i_offset;
}

/**
* Getter for the fairy-LVL
*
*	@return int		the LVL of the fairy
*
*/
int HWLFairy::get_lvl()
{
	return this->i_lvl;
}

/**
* Getter for the fairy-trust
*
*	@return int		the Trust of the fairy
*
*/
int HWLFairy::get_trust()
{
	return this->i_trust;
}

/**
* Getter for the fairy-refreshes
*
*	@return int		the refreshes of the fairy
*
*/
int HWLFairy::get_iterator()
{
	return this->i_iterator;
}

/**
* Getter for the fairy Unlock-State
*
*	@return bool	the current fairy Unlock-State
*
*/
bool HWLFairy::get_isUnlock()
{
	return this->b_isUnlock;
}



/**
* This method returns an formatted string, which contain all needed stati-values
*
*	@return string		formatted output with all needed stati-values, without
*						 weapons
*
*/
string HWLFairy::get_fairyForOutput()
{
	string s_output = "Name: " + this->s_name + "\n"
		//+ "  Offset: " + this->intToHexString(this->i_offset,false)+ "\n" //show offset for testing purposes
		+ "  Unlock?: " + to_string(this->b_isUnlock) + "\n"
		+ "  Level: " + to_string(this->i_lvl) + "\n"
		+ "  Trust: " + to_string(this->i_trust) + "\n"
		+ "  Refreshes: " + to_string(this->i_iterator) + "\n";

	return s_output;
}



/**
* This method is a wrapper for all known save-methods of the class
*
*/
void HWLFairy::save_Fairy()
{
	this->save_fairy_name();
	this->save_fairy_lvl();
	this->save_fairy_trust();
	this->save_fairy_iterator();
	this->save_fairy_isUnlockState();
}
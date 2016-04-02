//needed for including in a MFC-App
#ifdef __MFC__
#include "../gui/stdafx.h" 
#endif // __MFC__

#include "HWLSaveEditorCore.h"

//use the project-namespace
using namespace HWLSaveEdit;

//initialize the static-member
unsigned char* HWLSaveEditorCore::cp_filecontent = 0;

/* @var materialOffsetLength	length for all material-offsets */
const int HWLSaveEditorCore::materialOffsetLength = 0x2;

/** 
* Only the initialization of the normal-constructor
*/
HWLSaveEditorCore::HWLSaveEditorCore()
{
}

/**
* Only the initialization of the normal-destructor
*/
HWLSaveEditorCore::~HWLSaveEditorCore()
{
}

/**
* This method convert an integer value to an string with the
*	hex-content of the orignal value. 
* Also get the Hex-representation of a specific point
*	from the file-content
*
*	@var int  i_value			the value to convert/offset from file
*	@var bool is_file_content	TRUE, if we want a file-content convert to int
*								FALSE otherwise. Default TRUE
*
*	@return string				the converted HexString
*
*/
string HWLSaveEditorCore::intToHexString(int i_value, bool is_file_content)
{
	//define a string for holding the correct string
	//and define stringstream for converting
	string s_hexString;
	stringstream sstream_hexStream;

	//check if we have an offset for the file
	//if yes, use the i_value as an offset
	if (is_file_content)
	{
		//convert the int-representation of the file-content
		//to Hex
		sstream_hexStream << std::setfill('0')
			<< std::setw(2)
			<< std::hex
			<< (int)cp_filecontent[i_value];
	}
	else{
		//convert the i_value to an Hex-Content
		sstream_hexStream << std::setfill('0')
			<< std::setw(2)
			<< std::hex
			<< i_value;
	}

	//get the new hexString from the stringstream
	s_hexString = sstream_hexStream.str();

	//clears out the stringstream and 
	//set it to an empty string
	sstream_hexStream.clear();
	sstream_hexStream.str("");

	//return the converted string
	return s_hexString;
}

/**
* This method convert an HexString to the correct 
*	integer-value
*
*	@var string  s_hexString	the string to convert
*
*	@return int					the converted integer
*
*/
int HWLSaveEditorCore::HexStringToInt(string s_hexString)
{
	//define a stringstream for converting and
	//initialize it with the current hexString
	stringstream sstream_hexStream(s_hexString);

	//define an integer and convert the string
	int i_value;
	sstream_hexStream >> std::hex >> i_value;

	//return the converted integer
	return i_value;
}

/**
* This method added zeros to an uncomplete HexString
*	@var string  s_hexString	the string (as reference)
*								which will be zero-added
*
*	@var    int	 i_max_length	the max length for the string
*
*/
void HWLSaveEditorCore::addZeroToHexString(string &s_hexString, int i_max_length)
{
	//if we current string-length as lower then the 
	//max length for it, add the zeros
	if (s_hexString.length() < i_max_length)
	{
		//calc the difference for iteration-length
		int i_diff = i_max_length - s_hexString.length();

		for (int i = 0; i < i_diff; i++)
		{
			s_hexString = "0" + s_hexString;
		}
	}
}

/**
* This method get an HexString from a specifc offset 
*	within the file-content
*
*	@var int	i_offset			the file-offset-begin
*
*	@var int	i_offset_length		length of the offset
*
*	@return string					the HexString 
*
*/
string HWLSaveEditorCore::getHexStringFromFileContent(int i_offset, int i_offset_length)
{
	//define the string for holding data later
	string s_hexString;

	//if the length for that offste is bigger then one
	//we have to iterate
	if (i_offset_length > 1)
	{
		//Iterate from the offset-end to the offset-begin and
		//convert the values in this order to the string
		//because the save-file is LITTLE-ENDIAN
		for (int i = i_offset + (i_offset_length - 1); i >= i_offset; i--)
		{
			s_hexString = s_hexString + this->intToHexString(i);
		}
	}
	else
	{
		//convert the offset-content to the hexString
		s_hexString = this->intToHexString(i_offset);
	}

	//return the Hex-representation
	return s_hexString;
}

/**
* This method set an HexString to a specifc offset
*	within the file-content
*
*	@var string	s_hexString		the HexString for setting 
*								to file-content
*
*	@var int	i_offset		the file-offset-begin
*
*/
void HWLSaveEditorCore::setHexStringToFileContent(string s_hexString, int i_offset)
{
	//calculate the length of the offset and set the 
	//current offset to the right end of it
	int i_offset_length = s_hexString.size() / 2;
	i_offset = i_offset + (i_offset_length - 1);

	//Iterate over the string
	for (int i = 0; i < s_hexString.length(); i += 2)
	{
		//we need everytime a Hexdecial Value in this 
		//Format: XX 
		//so we need to get an substring from current string
		//position
		string s_tmp = s_hexString.substr(i, 2);

		//convert the current substring to an integer
		int i_tmp = this->HexStringToInt(s_tmp);

		//set the inetger (casted as unsigned char)
		//to the current offset-part of the file.
		//Decrement the offset after that.
		cp_filecontent[i_offset] = (unsigned char)i_tmp;
		i_offset--;
	}
}

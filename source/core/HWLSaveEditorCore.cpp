//needed for including in a MFC-App
#ifdef __MFC__
#include "../gui/stdafx.h" 
#endif // __MFC__

//include the correct header-file
#include "HWLSaveEditorCore.h"

//use the project-namespace
using namespace HWLSaveEdit;

//initialize the static-member
/* @var *cp_filecontent			holding the content of the save-file */
unsigned char* HWLSaveEditorCore::cp_filecontent = 0;

/* @var playerOffsetLength		length of one player/character */
const int HWLSaveEditorCore::playerOffsetLength = 0x30;

/* @var materialOffsetLength	length for all material-offsets */
const int HWLSaveEditorCore::materialOffsetLength = 0x2;

/* @var fairyFoodOffsetLength	length for all fairyFood-offsets */
const int HWLSaveEditorCore::fairyFoodOffsetLength = 0x1;

/* @var amItemOffsetLength		length for all adventureMode-Item-offsets */
const int HWLSaveEditorCore::amItemOffsetLength = 0x1;

/* @var fairyOffsetLength		length for all myFairies Offsets */
const int HWLSaveEditorCore::fairyOffsetLength = 0x98;

/* @var weaponOffsetLength		length for all weapon offsets (weapon stats only) */
const int HWLSaveEditorCore::weaponOffsetLength = 0x1F;

/* @var weaponOffsetLengthComplete		length for all weapon Offsets (with fill-data) */
const int HWLSaveEditorCore::weaponOffsetLengthComplete = 0x28;

//public members
/* @var version  hold the current version-number as string */
const string HWLSaveEditorCore::version = "2.5.0.1a";



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
*	@var int  i_value			the value to convert/ the offset from file
*	@var bool is_file_content	TRUE, if we want a file-content convert to int
*								FALSE otherwise. Default TRUE
*
*	@return string				the converted HexString
*
*/
string HWLSaveEditorCore::intToHexString(unsigned int i_value, bool is_file_content)
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
		//convert the integer value to an Hex-Content
		sstream_hexStream << std::setfill('0')
			<< std::setw(2)
			<< std::hex
			<< i_value;
	}

	//get the new hexString from the stringstream
	s_hexString = sstream_hexStream.str();

	//delete the too much FF if we have an negative integer
	if (i_value < 0)
	{
		s_hexString.erase(s_hexString.begin(), s_hexString.end() - 2);
	}

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

	//define an unsigned-integer and convert the string
	unsigned int i_value;
	sstream_hexStream >> std::hex >> i_value;

	//return the converted integer
	return i_value;
}

/**
* This method will convert an HexString to an MultiByte-String (char)
*
*	@var string  s_hexString		the string to convert
*
*	@return string					converted Byte-String
*
*/
string HWLSaveEditorCore::HexStringToByteString(string s_hexString)
{
	//declare two strings for holding content
	string s_hex_tmp, s_byte_string;

	//find the zeros and delete the rest from that positions
	//because we don't need them (an character with XX00XX is 
	//not an character, that will be something other)
	int i_pos = s_hexString.find("00");
	if (i_pos != string::npos)
		s_hexString.erase(s_hexString.begin()+i_pos, s_hexString.end());

	//make a temporary copy of the input-hex-string
	s_hex_tmp = s_hexString;
	
	// iterate over the hex-string and make sub-strings of the form
	// XX. Convert each sub-string to its Integer-Value and used
	// it for an unsgined char. Pusch it to the new string
	for (int i = 0; i < (signed)s_hex_tmp.length(); i += 2)
	{
		string s_tmp = s_hex_tmp.substr(i, 2);
		unsigned char c_tmp = this->HexStringToInt(s_tmp);
		s_byte_string.push_back(c_tmp);
	}

	//return the new MultiByte-String
	return s_byte_string;
}

/**
* This method will convert an Byte-String to an HexString 
*
*	@var string  s_byteString		the string to convert
*
*	@return string					converted HexString
*
*/
string HWLSaveEditorCore::ByteStringToHexString(string s_byteString)
{
	//declare a needed string
	string s_hexString;

	//iterate over the byte-string and convert each unsigned-char
	//of it to its Hex-Value and add them to to the new
	//hex-string itself
	for (int i = 0; i < (signed)s_byteString.length(); i++)
	{
		unsigned char uc_byte = s_byteString[i];
		s_hexString = s_hexString + this->intToHexString(uc_byte, false);
	}

	//return the new hex-string
	return s_hexString;
}

/**
* This method will convert an Byte-String as CharPointer 
* to an WideString
*
*	@var char*  cp_multibyte_str	the string to convert as char-pointer
*
*	@return wstring					converted WideString
*
*/
wstring HWLSaveEditorCore::ByteStringAsCharToWideString(const char* cp_multibyte_str)
{

	mbstate_t multibyte_state = mbstate_t();
	int i_len = 1 + mbsrtowcs(NULL, &cp_multibyte_str, 0, &multibyte_state);
	vector<wchar_t> vw_wide_str(i_len);
	mbsrtowcs(&vw_wide_str[0], &cp_multibyte_str, vw_wide_str.size(), &multibyte_state);
	wstring ws_wide_str;

	for (int i = 0; i < (signed)vw_wide_str.size() - 1; i++)
	{
		ws_wide_str.push_back(vw_wide_str[i]);
	}

	return ws_wide_str;
}

/**
* This method will convert an WideString to an Byte-String
* as CharPointer
*
*	@var wchar_t*  wcp_wide_str		the WideString to convert as wide-char-pointer
*
*	@return string					converted Byte-String
*
*/
string HWLSaveEditorCore::WideStringAsCharToByteString(const wchar_t* wcp_wide_str)
{
	std::mbstate_t multibyte_state = std::mbstate_t();
	int i_len = 1 + std::wcsrtombs(nullptr, &wcp_wide_str, 0, &multibyte_state);
	std::vector<char> vc_multibyte_str(i_len);
	std::wcsrtombs(&vc_multibyte_str[0], &wcp_wide_str, vc_multibyte_str.size(), &multibyte_state);
	string s_byte_str;

	for (int i = 0; i < (signed)vc_multibyte_str.size() - 1; i++)
	{
		s_byte_str.push_back(vc_multibyte_str[i]);
	}

	return s_byte_str;
}


/**
* This method will add zeros to an uncomplete HexString
*	@var string  s_hexString	the string (as reference)
*								which will be zero-added
*
*	@var    int	 i_max_length	the max length for the string
*
*	@var    bool b_to_end		if TRUE, the zeros will be added
*								to the end of the string. If FALSE
*								then to the beginning. Default: FALSE
*/
void HWLSaveEditorCore::addZeroToHexString(string &s_hexString, int i_max_length, bool b_to_end)
{
	//if we current string-length as lower then the 
	//max length for it, add the zeros
	if ((signed)s_hexString.length() < i_max_length)
	{
		//calc the difference for iteration-length
		int i_diff = i_max_length - s_hexString.length();

		for (int i = 0; i < i_diff; i++)
		{
			if (!b_to_end)	{ s_hexString = "0" + s_hexString; }
			else { s_hexString = s_hexString + "0"; }
		}
	}
}

/**
* This method convert the ByteOrder of an HexString (Little-Endian
* to Big-Endian and the other way around).
*
*	@var string  s_hexString		the HexString to convert
*									 (as reference)
*
*/
void HWLSaveEditorCore::convertByteOrder(string &s_hexString)
{
	//declare the needed temp-string
	string s_hexString_convert = "";

	//iterate over the hex-string, start from end to begin
	for (int i = 0 + (s_hexString.size() - 1); i >= 0; i -= 2)
	{
		//because we don't need to reverse the string and only
		//want to switch the order, we need the i-1 position
		//first and then the i-position
		s_hexString_convert.push_back(s_hexString[i - 1]);
		s_hexString_convert.push_back(s_hexString[i]);
	}

	//set the input-hex-string to the new content of the temp-string
	s_hexString = s_hexString_convert;

}

/**
* This method get an HexString from a specifc offset 
*	within the file-content
*
*	@var int	i_offset			the file-offset-begin
*
*	@var int	i_offset_length		length of the offset
*
*	@var bool	b_is_char			if TRUE, we have directly
*									single characters and need
*									Big-Endian-Order. Default: FALSE
*
*	@return string					the HexString 
*
*/
string HWLSaveEditorCore::getHexStringFromFileContent(int i_offset, int i_offset_length, bool b_is_char)
{
	//define the string for holding data later
	string s_hexString;

	//if the length for that offset is bigger then one
	//we have to iterate
	if (i_offset_length > 1)
	{
		if (!b_is_char)
		{
			//Iterate from the offset-end to the offset-begin and
			//convert the values in this order to the string
			//because the save-file is LITTLE-ENDIAN
			for (int i = i_offset + (i_offset_length - 1); i >= i_offset; i--)
			{
				s_hexString = s_hexString + this->intToHexString(i);
			}
		}else
		{
			//Iterate from offset-begin to offset-end, because
			//we have directly single characters and they are
			//in the normal order
			for (int i = i_offset; i < i_offset + (i_offset_length); i++)
			{
				s_hexString = s_hexString + this->intToHexString(i);
			}
		}

	}else
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
*	@var bool	b_is_char		if TRUE, we have directly
*								single characters and need
*								Big-Endian-Order. Default: FALSE
*
*/
void HWLSaveEditorCore::setHexStringToFileContent(string s_hexString, int i_offset, bool b_is_char)
{
	//Check if we have only a character string, if not
	//calculate the length of the offset and set the 
	//current offset to the right end of it
	if (!b_is_char)
	{
		int i_offset_length = s_hexString.size() / 2;
		i_offset = i_offset + (i_offset_length - 1);
	}


	//Iterate over the string
	for (int i = 0; i < (signed)s_hexString.length(); i += 2)
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
		//Decrement the offset after that (or increment, if we have an char-string)
		cp_filecontent[i_offset] = (unsigned char)i_tmp;

		if(!b_is_char) i_offset--;
		else i_offset++;
	}
}


/*
//orginal function to print out a wide_string (wchar_vector) from normal MultiByte-String

void print_as_wide(const char* mbstr)
{
mbstate_t state = mbstate_t();
int len = 1 + mbsrtowcs(NULL, &mbstr, 0, &state);
vector<wchar_t> wstr(len);
mbsrtowcs(&wstr[0], &mbstr, wstr.size(), &state);
wcout << &wstr[0] << '\n';
}

*/
#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>


//add the class to the project-namespace
namespace HWLSaveEdit
{
	//use the std-namespace within the project-namespace to avoid
	//such things like std::string etc.
	using namespace std;

	class HWLSaveEditorCore
	{
		protected:
			/* @var *cp_filecontent  this static member hold the 
									content of the save-file
			*/						
			static unsigned char* cp_filecontent;

			static const int playerOffsetLength;
			static const int materialOffsetLength;
			static const int fairyFoodOffsetLength;
			static const int amItemOffsetLength;
			static const int fairyOffsetLength;

		public:
			static const string version;

			/* Constructor and pure-virtual Destructor 
				(to make the class abstract)
			*/
			HWLSaveEditorCore();
			virtual ~HWLSaveEditorCore() = 0;

			/* Convertion for int to a HexString and the other
			   way around with zero-adding 
			   */
			string intToHexString(int i_value, bool is_file_content = true);
			int HexStringToInt(string s_hexString);
			string HexStringToByteString(string s_hexString);
			string ByteStringToHexString(string s_byteString);
			wstring ByteStringAsCharToWideString(const char* cp_multibyte_str);
			string WideStringAsCharToByteString(const wchar_t* wcp_wide_str);
			void addZeroToHexString(string &s_hexString, int i_max_length, bool b_to_end=false);

			/* Methods to get and set content from/to the save-file */
			string getHexStringFromFileContent(int i_offset, int i_offset_length, bool b_is_char = false);
			void   setHexStringToFileContent(string s_hexString, int i_offset, bool b_is_char = false);
	};
}



#pragma once
#include <string>
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

		public:
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
			void addZeroToHexString(string &s_hexString, int i_max_length);

			/* Methods to get and set content from/to the save-file */
			string getHexStringFromFileContent(int i_offset, int i_offset_length);
			void   setHexStringToFileContent(string s_hexString, int i_offset);
	};
}



#pragma once
#include "HWLSaveEditorCore.h" //include the main-class, because of the namespace and using std

//add the class to the project-namespace
namespace HWLSaveEdit
{
	//extend the standard-exception
	class HWLException : public exception
	{
		private:
			/* @var	int i_error_code	the current error-code */
			int i_error_code;

			/* @var	char* c_desc		the description/message of the current error */
			const char* c_desc;

		public:
			HWLException(const char* const& c_desc, int i_code);
			~HWLException();

			//extend/overwrite the standard methods
			virtual const char* what();
			int get_code();
	};


}

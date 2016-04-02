#pragma once
#include "HWLSaveEditorCore.h"

namespace HWLSaveEdit
{
	class HWLException : public exception
	{
	private:
		int i_error_code;
		const char* c_desc;
	public:
		HWLException(const char* const& c_desc, int i_code);
		~HWLException();

		virtual const char* what();
		int get_code();

	};


}

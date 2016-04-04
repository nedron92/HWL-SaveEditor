//needed for including in a MFC-App
#ifdef __MFC__
#include "../gui/stdafx.h" 
#endif // __MFC__

#include "HWLException.h"

//use the project-namespace
using namespace HWLSaveEdit;

HWLException::HWLException(const char* const& c_desc, int i_code)
{
	this->c_desc = c_desc;
	this->i_error_code = i_code;
}


HWLException::~HWLException()
{
}

const char *HWLException::what()
{
	return this->c_desc;
}

int HWLException::get_code()
{
	return this->i_error_code;
}
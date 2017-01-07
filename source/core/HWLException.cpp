/*
 * @author: nedron92, 2016
 */
//needed for including in a MFC-App
#ifdef __MFC__
#include "../gui/stdafx.h" 
#endif // __MFC__

//include the correct header-file
#include "HWLException.h"

//use the project-namespace
using namespace HWLSaveEdit;

/**
* Only the initialization of the normal-constructor,
* set the code and message
*
*/
HWLException::HWLException(const char* const& c_desc, int i_code)
{
	this->c_desc = c_desc;
	this->i_error_code = i_code;
}

/**
* Only the initialization of the normal-destructor
*/
HWLException::~HWLException()
{
}

/**
* This method return the current error-message
*
*/
const char *HWLException::what()
{
	return this->c_desc;
}

/**
* This method return the current error-code
*
*/
int HWLException::get_code()
{
	return this->i_error_code;
}
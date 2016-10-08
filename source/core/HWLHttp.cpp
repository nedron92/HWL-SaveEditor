//include the correct header-file
#include "HWLHttp.h"

//use the project-namespace
using namespace HWLSaveEdit;

/* @var sp_http_client		pointer for the http-client lib */
HTTP_Client HWLHttp::o_http_client = HTTP_Client();

/* @var maxVersionLength		max length of a version-string (for comparison) */
const int HWLHttp::maxVersionLength = 10;


/* @var nightlyURL	url of the nightly-server, user defined */
const string HWLHttp::nightlyURL = NIGHTLY_URL;

/* @var latestURL	url of the latest stable release */
const string HWLHttp::latestURL = "https://github.com/nedron92/HWL-SaveEditor/releases/latest";


/**
* Only the initialization of the normal-constructor
*/
HWLHttp::HWLHttp()
{
}

/**
* Only the initialization of the normal-destructor
*/
HWLHttp::~HWLHttp()
{
}

/**
* This method return the current latest stable version of the editor itself
*
* @return string       the current latest stable version
*
*/
string HWLHttp::get_current_version()
{
	this->o_http_client.set_current_url(this->s_version_check_http_url);
	this->o_http_client.send_http_request();

	return this->o_http_client.get_current_output();
}

/**
* This method return the current latest nightly version of the editor itself
*
* @return string       the current latest nightly version
*
*/
string HWLHttp::get_current_nightly_version()
{
	this->o_http_client.set_current_url(this->s_version_check_nightly_http_url);
	this->o_http_client.send_http_request();

	return this->o_http_client.get_current_output();
}

/**
* This methods compare the current program-version with the newest version of the stable or nightly
* releases and return some information, if a download is needed or not.
*
* @return string       a string with information based on the compare between editor-version and latest versions
*
*/
string HWLHttp::compare_with_current_version(bool b_compare_with_nightly)
{
	string s_program_version = HWLSaveEditorCore::version;
	string s_compare_version = "";

	if (b_compare_with_nightly)
		s_compare_version = this->get_current_nightly_version();
	else
		s_compare_version = this->get_current_version();

	int i_program_version_length = this->maxVersionLength - s_program_version.length();

	char c_last_char_program_version = ' ';
	char c_last_char_compare_version = ' ';

	if (isalpha(s_program_version.back()))
	{
		c_last_char_program_version = s_program_version.back();
		s_program_version.back() = ' ';
	}

	if (isalpha(s_compare_version.back()))
	{
		c_last_char_compare_version = s_compare_version.back();
		s_compare_version.back() = ' ';
	}

	for (int i = 0; i < i_program_version_length; i++) {
		s_program_version = s_program_version + " ";
	}

	i_program_version_length = this->maxVersionLength - s_compare_version.length();
	for (int i = 0; i < i_program_version_length; i++) {
		s_compare_version = s_compare_version + " ";
	}

	//add addiotnal check
	bool b_add_check = true;

	if (s_program_version.compare(s_compare_version) == 0)
		b_add_check = false;

	if (c_last_char_program_version != ' ')
		s_program_version.back() = c_last_char_program_version;

	if (c_last_char_compare_version != ' ')
		s_compare_version.back() = c_last_char_compare_version;

	int compare = s_program_version.compare(s_compare_version);

	string s_current_output = "";

	if (compare < 0)
	{
		if (b_compare_with_nightly)
			s_current_output = "There is a new nightly Version, you can download at the above URL. \nBut always take care with those versions!";
		else
			s_current_output = "There is a new stable version. \nPlease download it at the above URL!";
	}
	else if (compare == 0)
	{
		if (b_compare_with_nightly)
			s_current_output = "You are on the newest nightly version.";
		else
			s_current_output = "You are on the newest stable version.";
	}
	else if (compare > 0)
	{
		if (b_compare_with_nightly)
			s_current_output = "You are on a dev-version which is newer and not released yet. \nNo download needed";
		else
			s_current_output = "You are on a nightly version which is newer then the stable release. \nNo download needed!";
	}

	return s_current_output;

}


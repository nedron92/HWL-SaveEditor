/*
 * @author: nedron92, 2016
 */
//include the correct header-file
#include "HWLHttp.h"

//use the project-namespace
using namespace HWLSaveEdit;

/* @var o_http_client		object for the http-client lib */
HTTP_Client HWLHttp::o_http_client = HTTP_Client();

/* @var maxVersionLength	max length of a version-string (for comparison) */
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
* This method change the current proxy-settings and set the proxy if
* using it is enabled
*
* @var bool     b_use_proxy     state, if proxy will be used or not
* @var string   s_proxyHost     the proxyHost
* @var int      i_proxyPort     the proxyPort
*
*/
void HWLHttp::change_proxy(bool b_use_proxy, string s_proxyHost, int i_proxyPort)
{
	this->o_http_client.use_proxy(b_use_proxy);

	if (b_use_proxy)
		this->o_http_client.set_current_proxy(s_proxyHost, i_proxyPort);

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
* releases and return some information + if a download is needed or not.
*
*   @var bool     b_compare_with_nightly    state, if we have compare to the nightly-version
*   @var bool     b_return_as_intString     state, if we have to return the integer-representation as string
*
* @return string       a string with information based on the compare between editor-version and latest versions
*
*/
string HWLHttp::compare_with_current_version(bool b_compare_with_nightly, bool b_return_as_intString)
{
	//get the current version and define a 'clean' compare-variable
	string s_program_version = HWLSaveEditorCore::version;
	string s_compare_version = "";

	//check if we compare the current version with the nightly or stable-latest
	if (b_compare_with_nightly)
		s_compare_version = this->get_current_nightly_version();
	else
		s_compare_version = this->get_current_version();

	//if we have a non-empty compare version: continue, else: return error-information
	if (s_compare_version != "")
	{
		//get the diff-length for string compare
		int i_program_version_length = this->maxVersionLength - s_program_version.length();

		//define variables to hold the last char (if it is really alphabetical char)
		char c_last_char_program_version = ' ';
		char c_last_char_compare_version = ' ';

		//check if the last char (of current version) is an alphabetical one
		//backup this char, and delete it from the orig string
		if (isalpha(s_program_version.back()))
		{
			c_last_char_program_version = s_program_version.back();
			s_program_version.back() = ' ';
		}

		//check if the last char (of compare version) is an alphabetical one
		//backup this char, and delete it from the orig string
		if (isalpha(s_compare_version.back()))
		{
			c_last_char_compare_version = s_compare_version.back();
			s_compare_version.back() = ' ';
		}

		//fill up the string to the max-value
		for (int i = 0; i < i_program_version_length; i++) {
			s_program_version = s_program_version + " ";
		}

		//get the diff-length for string compare
		i_program_version_length = this->maxVersionLength - s_compare_version.length();

		//fill up the string to the max-value
		for (int i = 0; i < i_program_version_length; i++) {
			s_compare_version = s_compare_version + " ";
		}

		//if we had an backuped-last-char append it to the version-string now.
		if (c_last_char_program_version != ' ')
			s_program_version.back() = c_last_char_program_version;

		//if we had an backuped-last-char append it to the version-string now.
		if (c_last_char_compare_version != ' ')
			s_compare_version.back() = c_last_char_compare_version;

		//do a string-compare
		int compare = s_program_version.compare(s_compare_version);

		//return the compare-value as string, if we have to
		if (b_return_as_intString)
			return (to_string(compare));

		//define a 'clean' output variable
		string s_current_output = "";

		//check for the compare-value:
		//compare  < 0 => There is a new nightly/stable version
		//compare == 0 => Using the newest nightly/stable version
		//compare  > 0 => Using a nightly-version(compare to stable) or using dev-version (compare to nightly)
		//                  both is a true fact. 
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
				s_current_output = "You are using the newest nightly version.";
			else
				s_current_output = "You are using the newest stable version.";
		}
		else if (compare > 0)
		{
			if (b_compare_with_nightly)
				s_current_output = "You are using a dev-version which is newer and not released yet. \nNo download needed";
			else
				s_current_output = "You are using a nightly version which is newer then the stable release. \nNo download needed!";
		}

		//return current-output
		return s_current_output;
	}
	else
	{
		//return error-information
		return "Sorry. Couldn't retrieve the newest version. \nPlease check your internet-connection or check manually. ";
	}

}


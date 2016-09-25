//include the correct header-file
#include "HWLHttp.h"

//use the project-namespace
using namespace HWLSaveEdit;

/* @var sp_http_client		pointer for the http-client lib */
HTTP_Client HWLHttp::o_http_client = HTTP_Client();

/* @var nightlyURL	url of the nightly-server, user defined */
const string HWLHttp::nightlyURL = NIGHTLY_URL;

/* @var latestURL	url of the latest stable release */
const string HWLHttp::latestURL  = "https://github.com/nedron92/HWL-SaveEditor/releases/latest";


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

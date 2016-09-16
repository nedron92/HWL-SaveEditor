
//include the correct header-file
#include "HWLHttp.h"

//offsets definitions

const string HWLHttp::nightlyURL = NIGHTLY_URL;

const string HWLHttp::latestURL  = "https://github.com/nedron92/HWL-SaveEditor/releases/latest";

/**
* Only the initialization of the normal-constructor
*/
HWLHttp::HWLHttp()
{
	memset(&this->o_request_parameters,0,sizeof(HTTPParameters));
	this->init();
}

/**
* Only the initialization of the normal-destructor
*/
HWLHttp::~HWLHttp()
{
}

void HWLHttp::init()
{
	//url, default nothing special
	strcpy(this->o_request_parameters.Uri, "");

	//proxy
	this->o_request_parameters.UseProxy = this->b_use_proxy;
	strcpy(this->o_request_parameters.ProxyHost, this->s_http_proxy_host.c_str());
	this->o_request_parameters.ProxyPort = this->i_http_proxy_port;

	//auth..not implemented yet
	strcpy(this->o_request_parameters.UserName, this->s_http_auth_name.c_str());
	strcpy(this->o_request_parameters.Password, this->s_http_auth_password.c_str());
	this->o_request_parameters.AuthType = AuthSchemaNone;

	//this->s_http_result = "";

	#ifdef _WIN32
	    // OS specific call to start Winsock
	    HTTPOSInit(1);
	#endif
}

void HWLHttp::init(string s_url)
{
	this->init();

	//url by parameter
	strcpy(this->o_request_parameters.Uri, s_url.c_str());
}

void HWLHttp::send_http_request()
{
    do
    {    
	// Open the HTTP request handle
	this->o_http_session = HTTPClientOpenRequest(0);

        // Use Proxy server
        if(this->b_use_proxy)
        {
            if((this->i_return_code = HTTPClientSetProxy(this->o_http_session,this->o_request_parameters.ProxyHost,
		this->o_request_parameters.ProxyPort,NULL,NULL)) != HTTP_CLIENT_SUCCESS)
            {

                break;
            }
        }

        // Send a request for the home page 
        if((this->i_return_code = HTTPClientSendRequest(this->o_http_session,this->o_request_parameters.Uri,NULL,0,FALSE,0,0)) != HTTP_CLIENT_SUCCESS)
        {
            break;
        }

        // Retrieve the the headers and analyze them
        if((this->i_return_code = HTTPClientRecvResponse(this->o_http_session,3)) != HTTP_CLIENT_SUCCESS)
        {
            break;
        }
    
        // Get the data until we get an error or end of stream code
        // printf("Each dot represents %d bytes:\n",HTTP_BUFFER_SIZE );
        while(this->i_return_code == HTTP_CLIENT_SUCCESS || this->i_return_code != HTTP_CLIENT_EOS)
        {
            // Set the size of our buffer
            this->i_size = HTTP_CLIENT_BUFFER_SIZE;   

            // Get the data
            this->i_return_code = HTTPClientReadData(this->o_http_session,this->c_http_buffer,this->i_size,0,&this->i_size);
            this->i_total_size += this->i_size;

        }
	HTTPClientCloseRequest(&this->o_http_session);
    } while(0); // Run only once

this->s_http_result = this->c_http_buffer;

strcpy(this->c_http_buffer, "");

}

string HWLHttp::get_current_version()
{
	this->init(this->s_version_check_http_url);
	this->send_http_request();

	return this->s_http_result;
}

string HWLHttp::get_current_nightly_version()
{
	this->init(this->s_version_check_nightly_http_url);
	this->send_http_request();

	return this->s_http_result;
}

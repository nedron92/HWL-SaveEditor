//include needed and correct header-files
#include <string>
#include "CHTTP_Client.h"

/**
* The defined constructor.
* It will initialize the needed data with the current values of the class.
* If we have an given url, it will set it instead of the hardcoded one
*
* @var string  s_url       the url as a string
*
*/
HTTP_Client::HTTP_Client(string s_url)
{
	if (s_url != "")
		this->s_current_url = s_url;

	memset(&this->o_request_parameters, 0, sizeof(HTTPParameters));
	this->init();
}

/**
* Only the initialization of the normal-destructor
*/
HTTP_Client::~HTTP_Client()
{
}



/**
* This method will initialize all needed data with the current class-values
* and also do OS-specific call (WIN32) if needed
*
*/
void HTTP_Client::init()
{
	//url, default nothing special
	strcpy(this->o_request_parameters.Uri, this->s_current_url.c_str());

	//proxy
	this->o_request_parameters.UseProxy = this->b_use_proxy;
	strcpy(this->o_request_parameters.ProxyHost, this->s_http_proxy_host.c_str());
	this->o_request_parameters.ProxyPort = this->i_http_proxy_port;

	//auth..not implemented yet
	strcpy(this->o_request_parameters.UserName, this->s_http_auth_name.c_str());
	strcpy(this->o_request_parameters.Password, this->s_http_auth_password.c_str());
	this->o_request_parameters.AuthType = AuthSchemaNone;

#ifdef _WIN32
	// OS specific call to start Winsock
	HTTPOSInit(1);
#endif
}



/**
* This method return the current url
*
* @return string       the current url to send the http-request
*
*/
string HTTP_Client::get_current_url()
{
	return this->s_current_url;
}

/**
* This method return the current output. At default the variable is empty, but after
* an successfull request it has the output of the request itself.
*
* @return string       the current output (after successfull sending)
*
*/
string HTTP_Client::get_current_output()
{
	return this->s_http_result;
}



/**
* This method set the current url for an http-request
*
* @var string  s_url       the url as a string
*
*/
void HTTP_Client::set_current_url(string s_url)
{
	this->s_current_url = s_url;
	this->init();
}



/**
* This method send a http_request (GET-Method) and the returned
* output will send to the internal result-variable.
*
* @todo add error handling
*
*/
void HTTP_Client::send_http_request()
{
	//Clean buffer first
	strcpy(this->c_http_buffer, "");

	do
	{
		// Open the HTTP request handle
		this->o_http_session = HTTPClientOpenRequest(0);

		// Use Proxy server
		if (this->b_use_proxy)
		{
			if ((this->i_return_code = HTTPClientSetProxy(this->o_http_session, this->o_request_parameters.ProxyHost,
				this->o_request_parameters.ProxyPort, NULL, NULL)) != HTTP_CLIENT_SUCCESS)
			{

				break;
			}
		}

		// Send a request for the home page 
		if ((this->i_return_code = HTTPClientSendRequest(this->o_http_session, this->o_request_parameters.Uri, NULL, 0, FALSE, 0, 0)) != HTTP_CLIENT_SUCCESS)
		{
			break;
		}

		// Retrieve the the headers and analyze them
		if ((this->i_return_code = HTTPClientRecvResponse(this->o_http_session, 3)) != HTTP_CLIENT_SUCCESS)
		{
			break;
		}

		// Get the data until we get an error or end of stream code
		// printf("Each dot represents %d bytes:\n",HTTP_BUFFER_SIZE );
		while (this->i_return_code == HTTP_CLIENT_SUCCESS || this->i_return_code != HTTP_CLIENT_EOS)
		{
			// Set the size of our buffer
			this->i_size = HTTP_CLIENT_BUFFER_SIZE;

			// Get the data
			this->i_return_code = HTTPClientReadData(this->o_http_session, this->c_http_buffer, this->i_size, 0, &this->i_size);
			this->i_total_size += this->i_size;

		}
		HTTPClientCloseRequest(&this->o_http_session);
	} while (0); // Run only once

	//copy buffer to the internal output-string and delete the last newline-character 
	if (strcmp(this->c_http_buffer, "") != 0)
	{
		this->s_http_result = this->c_http_buffer;
		this->s_http_result.erase(remove(this->s_http_result.begin(), this->s_http_result.end(), '\n'), this->s_http_result.end());
	}
	else
		this->s_http_result = "";



	//clear buffer
	strcpy(this->c_http_buffer, "");

}
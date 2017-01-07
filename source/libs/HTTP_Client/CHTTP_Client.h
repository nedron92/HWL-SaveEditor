/*
 * @author: nedron92, 2016 
 * @desc: C++ - Wrapper with code from the original example. See License.txt for more information
 */
#pragma once

/*
* You need lib ws2_32.lib to compile
* uncomment these line or link the lib in your options directly
* WIN32 only!
*
*/
//#pragma comment(lib, "ws2_32.lib")

#ifndef HTTP_CLIENT_CPP
#define HTTP_CLIENT_CPP

#include <algorithm>
#include "API/HTTPClient.h"

/*
* Typedef of needed structure (holding the data)
*
*/
typedef struct _HTTPParameters
{
	char                    Uri[1024];
	char                    ProxyHost[1024];
	unsigned int            UseProxy;
	unsigned int            ProxyPort;
	unsigned int            Verbose;
	char                    UserName[64];
	char                    Password[64];
	HTTP_AUTH_SCHEMA        AuthType;

} HTTPParameters;

#define HTTP_CLIENT_BUFFER_SIZE		8192

using namespace std;

class HTTP_Client
{
	private:

		/* @var s_current_url   the current url for an http-request */
		string s_current_url = "";


		/* @var b_use_proxy   Toogling if http-request will use an proxy or not */
		bool b_use_proxy = false;

		/* @var s_http_proxy_host   the proxy-host */
		string s_http_proxy_host = "0.0.0.0";

		/* @var i_http_proxy_port   the proxy-port */
		unsigned int i_http_proxy_port = 0;


		/* @var b_use_auth   Toogling if http-request will use authentication or not */
		bool b_use_auth = false;

		/* @var s_http_auth_name   username for authentication */
		string s_http_auth_name = "";

		/* @var s_http_auth_password   password for authentication */
		string s_http_auth_password = "";

		/* @var s_http_auth_type   type of authentication */
		string s_http_auth_type = "";


		/* @var s_http_result   hold the current output (after successfull http-request) */
		string s_http_result = "";

		//import from old example
		int i_return_code;
		long unsigned int i_size = 0;
		long unsigned int i_total_size = 0;
		char c_http_buffer[HTTP_CLIENT_BUFFER_SIZE];
		HTTPParameters o_request_parameters;
		HTTP_SESSION_HANDLE o_http_session;

		void init();

	public:
		//constructor and destructor
		HTTP_Client(string s_url = "", bool b_useProxy = false, string s_proxyHost = "127.0.0.1", int i_proxyPort = 8080);
		~HTTP_Client();

		//needed getter/setter methods
		string get_current_url();
		string get_current_proxy();
		//string get_auth_settings - not implemented yet
		string get_current_output();

		void set_current_url(string s_url);
		void set_current_proxy(string s_proxyHost, int i_proxyPort);
                void use_proxy(bool b_use_proxy);
		//void change_auth_settings - not implemented yet

		//method for sending http-requests
		void send_http_request();
};

#endif // HTTP_CLIENT_CPP

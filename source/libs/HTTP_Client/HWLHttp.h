#pragma once

/* 
* You need lib ws2_32.lib to compile
* uncomment these line or link the lib in your options directly
* WIN32 only!
*/
//#pragma comment(lib, "ws2_32.lib")

#ifndef HTTP_CLIENT_HWL
#define HTTP_CLIENT_HWL

#include <string>

#include "API/HTTPClient.h"


typedef struct _HTTPParameters
{
    char                    Uri[1024];        
    char                    ProxyHost[1024];  
    unsigned int            UseProxy ;  
    unsigned int            ProxyPort;
    unsigned int            Verbose;
    char                    UserName[64];
    char                    Password[64];
    HTTP_AUTH_SCHEMA        AuthType;

} HTTPParameters;


#ifndef VERSION_CHECK_NIGHTLY_HTTP_URL
 #define VERSION_CHECK_NIGHTLY_HTTP_URL "http://nightly.nedron92.php-friends.de/hwl_save-editor/builds/version_nightly.txt"
#endif

#ifndef NIGHTLY_URL
 #define NIGHTLY_URL "https://nightly.nedron92.php-friends.de/hwl_save-editor/"
#endif

#define HTTP_CLIENT_BUFFER_SIZE     8192

using namespace std;
//include the parent-class
//#include "HWLSaveEditorCore.h"


	//extend our Core-Class
	class HWLHttp
	{
		private:
			string s_version_check_http_url = "http://nightly.nedron92.php-friends.de/hwl_save-editor/builds/version.txt";
			string s_version_check_nightly_http_url = VERSION_CHECK_NIGHTLY_HTTP_URL;

			bool b_use_proxy = false;
			string s_http_proxy_host = "183.57.17.194";
			unsigned int i_http_proxy_port = 8081;

			bool b_use_auth = false;
			string s_http_auth_name = "";
			string s_http_auth_password = "";
			string s_http_auth_type = "";

			string s_http_result = "";
			
			//import from old example
			int i_return_code;
			long unsigned int i_size = 0;
			long unsigned int i_total_size = 0;
			char c_http_buffer[HTTP_CLIENT_BUFFER_SIZE];
			HTTPParameters o_request_parameters;
			HTTP_SESSION_HANDLE o_http_session;
			
			void init();
			void init(string s_url);
			void send_http_request();

		public:

			//needed public members/constants
			static const string nightlyURL;
			static const string latestURL;

			//constructor and destructor
			HWLHttp();
			~HWLHttp();


			//change_proxy_settings - not implemented yet
			//change_auth_settings - not implemented yet

			string get_current_version();
			string get_current_nightly_version();

	};

#endif // HTTP_CLIENT_HWL

#pragma once

//include needed standard-libraries
#include <string>
#include <memory>

//include the main-class
#include "HWLSaveEditorCore.h"

//including needed third-party library/c++ wrapper
#include "../libs/HTTP_Client/CHTTP_Client.h"

//set user-defined content or define hardcoded-standard instead
#ifndef VERSION_CHECK_NIGHTLY_HTTP_URL
#define VERSION_CHECK_NIGHTLY_HTTP_URL "http://nightly.nedron92.php-friends.de/hwl_save-editor/builds/version_nightly.txt"
#endif

#ifndef NIGHTLY_URL
#define NIGHTLY_URL "https://nightly.nedron92.php-friends.de/hwl_save-editor/"
#endif


//add the class to the project-namespace
namespace HWLSaveEdit
{
	//use the std-namespace within the project-namespace to avoid
	//such things like std::string etc.
	using namespace std;

	class HWLHttp
	{
		private:

			/* @var s_version_check_http_url		the url of the version-check-file */
			string s_version_check_http_url = "http://nightly.nedron92.php-friends.de/hwl_save-editor/builds/version.txt";

			/* @var s_version_check_nightly_http_url        the url of the nightly-version-check-file, user defined */
			string s_version_check_nightly_http_url = VERSION_CHECK_NIGHTLY_HTTP_URL;


			//needed private constants/static members
			static HTTP_Client o_http_client;
			static const int maxVersionLength;


		public:

			//needed public members/constants
			static const string nightlyURL;
			static const string latestURL;

			//constructor and destructor
			HWLHttp();
			~HWLHttp();

			//methods to get the versions and compare with current one
			string get_current_version();
			string get_current_nightly_version();
			string compare_with_current_version(bool b_compare_with_nightly = false);

	};
}
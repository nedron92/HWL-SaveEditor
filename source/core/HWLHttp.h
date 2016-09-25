#pragma once

#include <string>
#include <memory>

//including needed third-party library/c++ wrapper
#include "../libs/HTTP_Client/CHTTP_Client.h"

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
            
            /* @var s_version_check_http_url        the url of the version-check-file */
            string s_version_check_http_url = "http://nightly.nedron92.php-friends.de/hwl_save-editor/builds/version.txt";
            
            /* @var s_version_check_nightly_http_url        the url of the nightly-version-check-file, user defined */
            string s_version_check_nightly_http_url = VERSION_CHECK_NIGHTLY_HTTP_URL;
                
            
            //needed private constants
            static HTTP_Client o_http_client;


        public:

                //needed public members/constants
                static const string nightlyURL;
                static const string latestURL;

                //constructor and destructor
                HWLHttp();
                ~HWLHttp();

                //methods to get the versions
                string get_current_version();
                string get_current_nightly_version();

    };
}
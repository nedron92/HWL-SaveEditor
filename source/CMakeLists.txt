#name the project
project(HWLSaveEditor)

#set needed ENV-variables to the right DIRs
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

#compile with c++14, cause we need it 
#and include sub-dirs
ADD_DEFINITIONS(-std=c++14)
add_subdirectory(libs)
add_subdirectory(core)
add_subdirectory(console)

#check if own URL will be used, default OFF
option(USE_OWN_URLS "Use your own URLs for some HTTP-Requests" OFF)

if(USE_OWN_URLS)
#add messager.....
  MESSAGE(STATUS "Your using USE_OWN_URLS")
  SET(VERSION_CHECK_NIGHTLY_HTTP_URL '\"http://nightly.nedron92.php-friends.de/hwl_save-editor/builds/version_nightly.txt\"' CACHE STRING "Own Version-Nighly-Check-URL")
  SET(NIGHTLY_URL '\"https://nightly.nedron92.php-friends.de/hwl_save-editor/\"' CACHE STRING "Own Nightly-Server-URL")

  add_definitions( -DVERSION_CHECK_NIGHTLY_HTTP_URL=${VERSION_CHECK_NIGHTLY_HTTP_URL} )
  add_definitions( -DNIGHTLY_URL=${NIGHTLY_URL} )

endif()


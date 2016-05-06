#name the project
project(HWLSaveEditor)

#set needed ENV-variables to the right DIRs
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

#compile with c++14, cause we need it 
#and include sub-dirs
ADD_DEFINITIONS(-std=c++14)
add_subdirectory(core)
add_subdirectory(console)


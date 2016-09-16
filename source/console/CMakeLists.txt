#create an executable-file of main.cpp
add_executable(HWLSaveEditor main.cpp)

#link the created static-lib to the executable-file
target_link_libraries(HWLSaveEditor -lpthread)
target_link_libraries(HWLSaveEditor core)

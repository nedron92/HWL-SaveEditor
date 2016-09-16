#add all .cpp files of the core folder to the Variable "HWLSaveSrc"
file(GLOB_RECURSE HTTPClientSrc
    "*.c"
    "*.cpp"
)

#create a static library from core-sources
add_library(http_client STATIC ${HTTPClientSrc})

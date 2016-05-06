#add all .cpp files of the core folder to the Variable "HWLSaveSrc"
file(GLOB HWLSaveSrc
    "*.cpp"
)

#create a static library from core-sources
add_library(core STATIC ${HWLSaveSrc})


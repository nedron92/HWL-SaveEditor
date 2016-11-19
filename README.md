# HWL-SaveEditor (3DS)
This is an Save-Editor for the game Hyrule Warriors Legends (Nintendo 3DS)

It's written in C++ and with MS Visual Studio 2013. You need that compiler for compiling the gui. (MFC application).  
But there are also CMakeLists-files to compile the console-version under linux with cmake.  

The main-files are located at source/core (all main functions are located here).  

## How to Build under Linux
There are some prerequisites before you can compile it.  
Make sure, that you have `cmake`, `make`, `gcc` and `g++`.  
You need CMake >=2.8, GCC/G++ >= 5.0  

After that check compiling under linux is very easily.  
In terminal/console change to the source-directory and then run these commands:  
`mkdir output && cd output`  
`cmake ..`  
`make`  

The binary executable is within the `output`-dir under `bin`.


## Prerequisites
You should have a Version of SaveDataFiler (or able to use .cia files on your 3DS), JK's Save Manager (.cia) or able to run homebrew to get your savefile of the game.  
Possible Homebrew for exporting a savefile: svdt, 3DS Save Manager and/or JK3DSTool (as a .3dsx file), search for it with your favourite search-engine ;)  
If you not able to run homebrew yet, then visit http://smealum.github.io/3ds/ for more information.   

## How to use it? 
First, download the latest stable release!  
Once you have your savefile (normally called "zmha.bin"), copy to your PC, made a backup of that savefile before you edit   anything, run the editor, open the savefile and change what you want, save the file, copy it back to your 3DS SD-Card and   import it back with the programm, you used before to get the savefile.   

## Nightly-Builds
If you don't want to wait for a new stable-release, then you can check the nightly-build-server.  
It will build automatically windows- and linux-builds every night (about 3 o'clock CET) after there was a new commit to  
this repository.  
But use them on your own risk, the nightly-builds can be unstable and with more failures/bugs as a new release.  
You can download them on https://nightly.nedron92.php-friends.de/hwl_save-editor/


## Questions?
Ask me wherever you want, but basically at http://gbatemp.net/ (my name there is also nedron92).   
You can also ask your question within the main-thread:   
http://gbatemp.net/threads/release-hyrule-warriors-legends-save-editor-ntr-plugin.411349/

## Failures, Bugs etc.
If you find any kind of failures, bugs and other then post it in the main-thread, which I named above.   
If you are a programmer, correct the mistake and send me a request here at github.

## Credits
main-src (core/console/gui): nedron92, 2016  
lib/HTTP-Client: Eitan Michaelson, Bob Wirka, 2014 (many thanks for that lightweight C-Lib)   

Have fun^^

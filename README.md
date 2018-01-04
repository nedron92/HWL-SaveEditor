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


## How to change the configfile (settings.cfg - since Version 3.1+)
Open this file with your favourite text-editor like Wordpad or Notepad++.  
There some parameters you can change to change the behaviour of the editor itself:  
* `autoUpdateCheck` - a boolean (true/false) param. If its set to 'true', the editor check at every start if there is an new stable version and let you know if there is one.  Default: false
* `autoTrim` - a boolean (true/false) param. If its set to 'true', the editor will trim the current opened savefile if its too long (to avoid some errors). Default: true
* `DlcSafetyCheck` - a boolean (true/false) param. If its set to 'true', the editor checks all things if there are compatible with your installed DLCs that were found. It will cut things, that you can't or should'nt edit without a specific DLC.  
Default: true (and only deactivate it, if the DLC-identification don't work correctly with your savefile, be careful).
* `createBackupFileOnOpening` - a boolean (true/false) param. If its set to 'true', the editor create an automatically a backup-file of your opened savefile (if it's could successfully opened). Default: true
* `openLastSaveFileOnStart` - a boolean (true/false) param. If its set to 'true', the editor will opened your last opened saveFile on the next start (you can define it yourself, see next).
* `LastSaveFile` - a string (text) param. This parameter contain the path (normally the fullpath) to the last opened savefile. 
Something like: `C:\Users\da da\Desktop\zmha.bin`. Also relative paths will work. This parameter will be ignored if `openLastSaveFileOnStart` is deactivated (set to 'false'). Default: zmha.bin
* `useHTTPProxy` - a boolean (true/false) param. If its set to 'true', the editor will use the specified proxy-settings. BUT only real HTTP-PROXIES are supported, no Socks-proxy.  Default: false
* `ProxyHost` - a string (text) param. This parameter contain the IP adress of your used proxy-server. Default: 127.0.0.1
* `ProxyPort` - a string (text) param. This parameter contain the Port of your used proxy-server. Default: 8080  
  
If you have problems after editing your configfile, simply delete it. The editor will recognize it and will create a new default configfile on start. 

## Nightly-Builds
If you don't want to wait for a new stable-release, then you can check the nightly-build-server.  
It will build automatically windows- and linux-builds every night (about 3 o'clock CET) after there was a new commit to  
this repository.  
But use them on your own risk, the nightly-builds can be unstable and with more failures/bugs as a new release.  
You can download them on https://nightly.nedron92.de/hwl_save-editor/


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

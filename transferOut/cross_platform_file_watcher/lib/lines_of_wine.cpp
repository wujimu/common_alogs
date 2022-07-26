#include<iostream>
#include<string>
#include <stdio.h>  /* defines FILENAME_MAX */

 #include "../include/efsw/efsw.hpp"
 extern "C"{

 #include "../include/efsw/efsw.h"

 }


#ifdef WINDOWS
    #include <direct.h>
    #define GetCurrentDir _getcwd
#else
    #include <unistd.h>
    #define GetCurrentDir getcwd
 #endif
// using namespace std;
 char cCurrentPath[FILENAME_MAX];






class UpdateListener : 
public efsw::FileWatchListener
{
public:
	UpdateListener() {};

	void handleFileAction( efsw::WatchID watchid, const std::string& dir, const std::string& filename, efsw::Action action, std::string oldFilename = "" )
	{
		switch( action )
		{
		case efsw::Actions::Add:
			std::cout << "DIR (" << dir << ") FILE (" << filename << ") has event Added" << std::endl;
			break;
		case efsw::Actions::Delete:
			std::cout << "DIR (" << dir << ") FILE (" << filename << ") has event Delete" << std::endl;
			break;
		case efsw::Actions::Modified:
			std::cout << "DIR (" << dir << ") FILE (" << filename << ") has event Modified" << std::endl;
			break;
		case efsw::Actions::Moved:
				std::cout << "DIR (" << dir << ") FILE (" << filename << ") has event Moved from (" << oldFilename << ")" << std::endl;
			break;
		default:
			std::cout << "Should never happen!" << std::endl;
		}
	}
};
// Create the file system watcher instance
// efsw::FileWatcher allow a first boolean parameter that indicates if it should start with the generic file watcher instead of the platform specific backend


// Create the instance of your efsw::FileWatcherListener implementation


int main(){

 char cCurrentPath[FILENAME_MAX];

 if (!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath)))
     {
     return errno;
     }

cCurrentPath[sizeof(cCurrentPath) - 1] = '\0'; /* not really required */

 std::cout << "The current working directory is " <<  cCurrentPath << std::endl;


// Create the file system watcher instance
// efsw::FileWatcher allow a first boolean parameter that indicates if it should start with the generic file watcher instead of the platform specific backend
efsw::FileWatcher * fileWatcher = new efsw::FileWatcher();

// Create the instance of your efsw::FileWatcherListener implementation
UpdateListener * listener = new UpdateListener();

// Add a folder to watch, and get the efsw::WatchID
// It will watch the /tmp folder recursively ( the third parameter indicates that is recursive )
// Reporting the files and directories changes to the instance of the listener
efsw::WatchID watchID = fileWatcher->addWatch( "/c/Users/dickcata/Documents/algorthims/cross_platform_file_watcher/include", listener, true );

// Adds another directory to watch. This time as non-recursive.
efsw::WatchID watchID2 = fileWatcher->addWatch( "/c/Users/dickcata/Documents/algorthims/cross_platform_file_watcher/bin", listener, false );

// Start watching asynchronously the directories
fileWatcher->watch();

std::cin.get();

}
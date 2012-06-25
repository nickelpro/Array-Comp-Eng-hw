#include "cpos.hpp"

#ifdef __WIN32__
#include <windows.h>
coord_t getpos() {               //We're going to get the current position of the cursor!
const int OFFSET=1;                    //Windows command promt coordinates are 1 off regular terminals
CONSOLE_SCREEN_BUFFER_INFO csbi; //Create screen info structure
coord_t coord;                   //Create our coordinate structure

if (GetConsoleScreenBufferInfo (               //And assuming nothing breaks (thus the if statement)
    GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) { //Pass the info into the screen info structure
   coord.x = csbi.dwCursorPosition.X+OFFSET;   //Set our coordinate x equal to the screen info X
   coord.y = csbi.dwCursorPosition.Y+OFFSET;   //Set our coordinate y equal to the screen info Y
   return coord;                               //Return our structure and we're done!
   }

else {           //If it does break, just set everything 0 and return the structure
   coord.x = 0;  //This shouldn't happen...
   coord.y = 0;
   return coord; //...but if it does, this should stop a crash while failing loudly
   }
}

void setpos(int x, int y) {
const int OFFSET=1;
CONSOLE_SCREEN_BUFFER_INFO csbi;                //Create screen info structure
HANDLE hStdout=GetStdHandle(STD_OUTPUT_HANDLE); //Get the handle for Std Out
GetConsoleScreenBufferInfo(hStdout, &csbi);     //Pass the info into the screen info structure
csbi.dwCursorPosition.X=x-OFFSET;               //Set the screen info X equal to our x
csbi.dwCursorPosition.Y=y-OFFSET;               //Set the screen info Y equal to our y
SetConsoleCursorPosition(hStdout, csbi.dwCursorPosition); //And ship it out!
}

#else
#include <iostream>
#include <sstream>
#include <termios.h>

using namespace std;

coord_t getpos() {

//Create the variables and what not that we're going to use
coord_t coord;
string buffer;
stringstream ss;
int fd=0, i=0;
termios oldio, newio;

//Get the current terminal attributes, one to backup, one to alter
tcgetattr(fd, &oldio);
tcgetattr(fd, &newio);
//Turn off echo and line controls
newio.c_lflag &= ~ECHO;
newio.c_lflag &= ~ICANON;
//Flush the terminal and give it the new parameters
tcflush(fd, TCIFLUSH);
tcsetattr(fd,TCSANOW,&newio);

//Ask the terminal for the coordinates
cout << "\E[6n";
getline(cin, buffer, 'R');

//Restore the old parameters
tcflush(fd, TCIFLUSH);
tcsetattr(fd,TCSANOW,&oldio);

//Cut off the escape character
buffer.erase(0,3);
//Extract the coordinates with a couple loops
while (isdigit(buffer[i])) {
	ss << buffer[i];
	i++;
	}
ss << " ";
ss >> coord.y;
i++;
while (isdigit(buffer[i])) {
	ss << buffer[i];
	i++;
	}
ss << " ";
ss >> coord.x;
return coord;
}

void setpos(int x, int y) {
//Yep, one escape code, just pass the coordinates
cout << "\E["<<y<<";"<<x<<"H";
}
#endif
#include "cpos.hpp"
#include <iostream>
using namespace std;

//ITS A BUNCH OF HACKS
//IT ONLY DOES THIS ONE THING
//HACK HACK HACK HACK NEVER USE!!!

//This draws a nice little bar graph, it was coded in 5 minutes to do that and only that

void bar(int pay[]) {
int x,y;
setpos(30,11);
cout << "        Hundred $'s in Pay";
setpos(30,10);
cout << "2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10+";
setpos(30,9);
cout << "----------------------------------";
x=30;
for (int i=0; i<=9; i++,x+=4) {
	y=8;
	for (int cnt=0; cnt<pay[i]; cnt++, y--){
		setpos(x,y);
		cout << "#";
		}
	}
}

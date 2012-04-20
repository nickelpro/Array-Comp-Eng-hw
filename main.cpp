#include <iostream>
#include "convert.hpp"
#include "clear.hpp"
#include "draw.hpp"
using namespace std;

int main() {

//Enum just makes code convienent to read
enum {p200_299,		
	p300_399,
	p400_499,
	p500_599,
	p600_699,
	p700_799,
	p800_899,
	p900_999,
	p1000over};
//Rest of the variables we'll be using
string response;
int sales, lookup;
int pay[9];

//Quickly zero out the array
for (int i=0; i<9; i++)
pay[i]=0;

//Clear whatever crap might be on the screen and we're ready to get started
clear();		

do {
	do {
	
		//Clear the old screen
		clear();
		//Draw the new screen
		draw(pay);
		//Accept the user input
		cin >> response;
		//Make sure it's a valid input
	} while (response!="x"&&!isdigit(response[0]));
	//If they haven't chosen to quit...
	if (response!="x") {
		//Convert to an int
		sales= stoi(&response);
		//Adjust to what the actual pay is
		sales=(sales*.09)+200;
		//Quick lookup table so we can use a switch
		int lookup_table[] = {
			(sales<300),
			((sales>=300)&&(sales<400)),
			((sales>=400)&&(sales<500)),
			((sales>=500)&&(sales<600)),
			((sales>=600)&&(sales<700)),
			((sales>=700)&&(sales<800)),
			((sales>=800)&&(sales<900)),
			((sales>=900)&&(sales<1000)),
			(sales>=1000)};

		//Run through the table and find the correct range
		lookup=0;                
		while(!lookup_table[lookup])
		lookup++;                   

		//Increment the range
		switch (lookup) {
			case 0:
				//Told you enum made code more readable
				pay[p200_299]++;
				break;
			case 1:
				//Isn't this so much nicer than the subscript being random numbers?
				pay[p300_399]++;
				break;
			case 2:
				pay[p400_499]++;
				break;
			case 3:
				pay[p500_599]++;
				break;
			case 4:
				pay[p600_699]++;
				break;
			case 5:
				pay[p700_799]++;
				break;
			case 6:
				pay[p800_899]++;
				break;
			case 7:
				pay[p900_999]++;
				break;
			case 8:
				pay[p1000over]++;
				break;
			}
		}
	//Kill when the user tells us too
	} while(response!="x");
//Clear our crap
clear();
}
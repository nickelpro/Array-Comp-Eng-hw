#include <sstream>
using namespace std;
int stoi(string *str) {
//Create our int
int x;
//Create our stream containing our string
stringstream stream (*str);
//Pass the string to the int
stream >> x;
//Return the int
return x;
}
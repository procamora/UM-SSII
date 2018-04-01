#include <iostream>

using namespace std;
#include <string>
#include <sstream>


#include <sstream>
int stoiMia(const std::string& s) {
    std::istringstream str(s);
    int i;
    str >> i;
    return i;
}

int main()
{
    std::string str1 = "45";
    std::string str2 = "3.14159";
    std::string str3 = "31337 with words";


    int myint1 = stoiMia(str1);
    int myint2 = stoiMia(str2);
    int myint3 = stoiMia(str3);


    std::cout << "std::stoi(\"" << str1 << "\") is " << myint1 << '\n';
    std::cout << "std::stoi(\"" << str2 << "\") is " << myint2 << '\n';
    std::cout << "std::stoi(\"" << str3 << "\") is " << myint3 << '\n';

}
  
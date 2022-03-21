#include <string>
#include <iostream>
#include "Automata.h"

using namespace std;

int main() {
    string input, output;
    string aIsEvenConfig = "AIsEvenConfig.txt";
    string isValidEmailConfig = "IsValidEmailConfig.txt";
    try {
        // Check if the count of "a"s is even.
        Automata aIsEven(aIsEvenConfig);
        input = "ababbabbababababbababababbaaa"; // String in whcih the "a" charachter is used 14 times.
        output = aIsEven.run(input);
        cout << "Output's last charachter show if the count of 'a' charachters is even. In Input 'a' charachter is used 14 times."<<endl;
        cout << input << "  :  " << output << endl<<endl;


        // Check if string is a valid email.
        Automata isValidEmail(isValidEmailConfig);
        input = "bacbac@abc.cab"; // Valid Email
        output = isValidEmail.run(input);
        cout << "The Email is valid if it looks like [a,b,c]@[a,b,c].[a,b,c]. Where [a,b,c] includes at least one symbol." << endl;
        cout << input << "  :  " << output << endl << endl;

        cout << "Check your Email(use only [a,b,c,@,.] symbols) : ";
        cin >> input;
        cout << endl;
        output = isValidEmail.run(input);
        cout << input << "  :  " << output << endl << endl;
    }
    catch (invalid_argument & err) {
        cout << err.what();
    }

    return 0;
}
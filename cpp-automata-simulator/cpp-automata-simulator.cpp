#include <string>
#include <iostream>
#include "Automata.h"

int main() {
    string input, output;
    string aIsEvenConfig = "AIsEvenConfig.txt";
    string isValidEmailConfig = "IsValidEmailConfig.txt";
    try {
        // Check if the count of "a"s is even.
        Automata aIsEven(aIsEvenConfig);
        input = "ababbabbababababbababababbaaa"; // String in whcih the "a" charachter is used 14 times.
        std::cout << "Output's last charachter show if the count of 'a' charachters is even. In Input 'a' charachter is used 14 times."<<endl;
        output = aIsEven.run(input);
        std::cout << input << "  :  " << output << endl<<endl;

        input = "ababbabbababaababbaaa"; // String in whcih the "a" charachter is used 11 times.
        output = aIsEven.run(input);
        std::cout << "In Input 'a' charachter is used 11 times." << endl;
        std::cout << input << "  :  " << output << endl << endl;


        // Check if string is a valid email.
        Automata isValidEmail(isValidEmailConfig);
        input = "bacbac@abc.cab"; // Valid Email
        std::cout << "The Email is valid if it looks like [a,b,c]@[a,b,c].[a,b,c]. Where [a,b,c] includes at least one symbol." << endl;
        output = isValidEmail.run(input);
        std::cout << input << "  :  " << output << endl;
        input = "@acccabc.cab"; // Valid Email
        output = isValidEmail.run(input);
        std::cout << input << "  :  " << output << endl;
        input = "acc@.cab"; // Valid Email
        output = isValidEmail.run(input);
        std::cout << input << "  :  " << output << endl << endl;

        std::cout << "Check your Email(use only [a,b,c,@,.] symbols) : ";
        cin >> input;
        std::cout << endl;
        output = isValidEmail.run(input);
        std::cout << input << "  :  " << output << endl << endl;
    }
    catch (invalid_argument & err) {
        std::cerr << err.what() << endl;
    }

    return 0;
}
#include <string>
#include <iostream>
#include "Automata.h"

int main() {
    std::string input, output;
    std::string aIsEvenConfig = "AIsEvenConfig.txt";
    std::string isValidEmailConfig = "IsValidEmailConfig.txt";
    try {
        // Check if the count of "a"s is even.
        Automata aIsEven(aIsEvenConfig);
        input = "ababbabbababababbababababbaaa"; // String in whcih the "a" charachter is used 14 times.
        std::cout << "Output's last charachter show if the count of 'a' charachters is even. In Input 'a' charachter is used 14 times."<< std::endl;
        output = aIsEven.run(input);
        std::cout << input << "  :  " << output << std::endl<< std::endl;

        input = "ababbabbababaababbaaa"; // String in whcih the "a" charachter is used 11 times.
        output = aIsEven.run(input);
        std::cout << "In Input 'a' charachter is used 11 times." << std::endl;
        std::cout << input << "  :  " << output << std::endl << std::endl;


        // Check if string is a valid email.
        Automata isValidEmail(isValidEmailConfig);
        input = "bacbac@abc.cab"; // Valid Email
        std::cout << "The Email is valid if it looks like [a,b,c]@[a,b,c].[a,b,c]. Where [a,b,c] includes at least one symbol." << std::endl;
        output = isValidEmail.run(input);
        std::cout << input << "  :  " << output << std::endl;
        input = "@acccabc.cab"; // Valid Email
        output = isValidEmail.run(input);
        std::cout << input << "  :  " << output << std::endl;
        input = "acc@.cab"; // Valid Email
        output = isValidEmail.run(input);
        std::cout << input << "  :  " << output << std::endl << std::endl;

        std::cout << "Check your Email(use only [a,b,c,@,.] symbols) : ";
        std::cin >> input;
        std::cout << std::endl;
        output = isValidEmail.run(input);
        std::cout << input << "  :  " << output << std::endl << std::endl;
    }
    catch (std::invalid_argument & err) {
        std::cerr << err.what() << std::endl;
    }

    return 0;
}
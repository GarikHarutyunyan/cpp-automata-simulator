#ifndef AUTOMATA_H
#define AUTOMATA_H

#include <string>
#include <vector>
#include <map>

class Automata {
	public:
		Automata(std::string);
		std::string run(std::string input);

	private:
		std::string inputAlphabet, outputAlphabet, activeState;
		std::vector <std::string> states;
		std::map<std::string, std::string> functionResults;

};
#endif // AUTOMATA_H
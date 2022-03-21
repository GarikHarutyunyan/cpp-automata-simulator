#ifndef AUTOMATA_H
#define AUTOMATA_H

#include <string>
#include <vector>

using namespace std;

class Automata {
	public:
		Automata(string);
		string run(string input);

	private:
		string inputAlphabet, outputAlphabet, activeState;
		vector <string> states;
		vector <vector <string>> functionResults;

};
#endif // AUTOMATA_H
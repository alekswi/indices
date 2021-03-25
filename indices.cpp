#include "header.h"

int main(int argc, char** argv)
{
	string* input = new string;
	string* output = new string;
	bool flag1 = false, flag2 = false;
	if (argc != 5)
		cout << "Nieodpowiednia ilosc argumentow!" << endl;
	else {
		for (int i = 1; i < argc - 1; i++)
		{
			if (string(argv[i]) == "-i")
			{
				*input = (argv[i + 1]);
				flag1 = true;
			}
			if (string(argv[i]) == "-o")
			{
				*output = (argv[i + 1]);
				flag2 = true;
			}
		}
		if (flag1 == true && flag2 == true)
			read_file(*input, *output);
		else
			cout << "Podano nieprawidlowe argumenty" << endl;
	}
	delete input;
	delete output;
	_CrtDumpMemoryLeaks();
	return 0;
}
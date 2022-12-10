#include <iostream>
#include <exception>
#include "engine.h"

class Subject {
public:
	int f3(int a, int b, int c) {
		return a + b + c;
	}
};
int main(int argc, char** argv) {
	try
	{
		Subject subj;
		Wrapper wrapper(&subj, &Subject::f3, { {"arg1", 0}, {"arg2", 0} , {"arg3", 0} });
		Engine engine;
		engine.registerCommand(&wrapper, "command1");
		std::cout << engine.execute("command1", { {"arg2", 4}, {"arg1", 5} , {"arg3", 5} }) << std::endl;
	}
	catch (std::exception& er)
	{
		std::cout << er.what() << std::endl;
	}

	return 0;
}
// Simbiotic and it's source files are (c) 2015, Abject Entertainment

#include "test.h"
#include <iostream>

static uint t=0, s=0, f=0;
extern "C" int main(int argc, char ** argv)
{
	RunTests();
	std::cout '\n' << t << " tests, " << s << " succeded, " << f << " failed.\n";
	return 0;
}

static bool started = false;
static bool in_test = false;
static int indent = 0;

const uint WIDTH = 50;

void _incompleteTest()
{ ++t;
	if (indent >= WIDTH)
	{
		std::cout << "\n | ";
		indent = 0;
	}
	std::cout << std::string(WIDTH - indent, '.') << " INCOMPLETE\n";
	in_test = false;
}

void TestSuite(std::string name, bool stopOnFail)
{
	if (!started)
		{ std::cout << "\n"; }
	started = true;

	if (in_test)
		{ _incompleteTest(); }

	std::cout << " - " << name << "\n";
}

void Test(std::string name)
{
	if (in_test)
		{ _incompleteTest(); }

	std::cout << "    > " << name << '\n';
	indent = 0; //name.length();
	in_test = true;
}

void Succeed()
{ ++t; ++s;
	std::cout << "         ";
	indent = 0;
	std::cout << std::string(WIDTH - indent, '.') << "..  SUCCESS\n";
	in_test = false;
}

void Fail(std::string message)
{ ++t; ++f;
	std::cout << "         ";
	indent = 0;
	std::cout << std::string(WIDTH - indent, '.') << ".....  FAIL\n";
	in_test = false;

	if (message.length() > 0)
	{
		std::cout << "            " << message << "\n";
	}
}




#include <string>

void RunTests();

void TestSuite(std::string name, bool stopOnFail = true);
void Test(std::string name);
void Succeed();
void Fail(std::string message = "");

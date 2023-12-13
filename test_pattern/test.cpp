#include <iostream>
#include <string>

//fwd
void visitor_test();
void decorator_test();

int main()
{
	visitor_test();
	std::cout << std::string(40, '-') << "\n\n";

	decorator_test();
	std::cout << std::string(40, '-') << "\n\n";



}


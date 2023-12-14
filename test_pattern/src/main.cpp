#include <iostream>
#include <string>

#include <conio.h> //getch() - windos only - todo get rid

//fwd
void visitor_test();
void decorator_test();

int main()
{
	visitor_test();
	std::cout << std::string(40, '-') << "\n\n";

	decorator_test();
	std::cout << std::string(40, '-') << "\n\n";



	//------------------------
	std::cout <<"\n\nEnd - press any key\n";
	//windos only - todo get rid
	(void)getch();
}


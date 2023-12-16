#include <iostream>
#include <string>

//windos only - todo get rid
#ifdef  _WIN32
#include <conio.h> //getch()
#endif

#define DEF_FUN(fn_name) void fn_name##_test()

#define CALL_FUN(fn_name) \
do \
{ \
	std::cout << "----------------------------------------------------------\n"; \
	std::cout << "\t\t\t\t<"#fn_name">\n"; \
	std::cout << "----------------------------------------------------------\n"; \
	fn_name##_test(); \
	std::cout << "==========================================================\n\n"; \
} \
while (false)
//[END] CALL_FUN



//fwd
DEF_FUN(abstractFactory);
DEF_FUN(composit);
DEF_FUN(decorator);
DEF_FUN(factory);
DEF_FUN(iterator);
DEF_FUN(observer);
DEF_FUN(state);
DEF_FUN(stratege);
DEF_FUN(templMethod);
DEF_FUN(visitor);


int main()
{
	CALL_FUN(abstractFactory);
	CALL_FUN(composit);
	CALL_FUN(decorator);
	CALL_FUN(factory);
	CALL_FUN(iterator);
	CALL_FUN(observer);
	CALL_FUN(state);
	CALL_FUN(stratege);
	CALL_FUN(templMethod);
	CALL_FUN(visitor);

	//------------------------
    //windos only - todo get rid
#ifdef  _WIN32
    std::cout <<"\n\nEnd - press any key\n";
    (void)getch();
#endif
}

#undef DEF_FUN
#undef CALL_FUN

#include <iostream>
#include <string>


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


#define IS_TRUE(condition) \
do \
{ \
	std::cout << "The <"#condition"> is " << ((condition) ? "true (ok)" : "FALSE") << "\n"; \
} \
while (false)
//[END] IS_TRUE





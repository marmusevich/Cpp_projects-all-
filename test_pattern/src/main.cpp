#include "macros.h"



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

//------------------------
//review questions
DEF_FUN(rq1);
DEF_FUN(rq2);


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
	//review questions
	CALL_FUN(rq1);
	CALL_FUN(rq2);

	//------------------------
#ifndef _MSC_VER
	std::cout << "\n\nEnd - press 'any'Enter' key\n";
	(void)std::cin.get();
#endif // !_MSC_VER


	
}


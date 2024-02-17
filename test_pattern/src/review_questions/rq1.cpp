#include "macros.h"

#include <vector>
#include <algorithm>
#include <stack>
#include <array>


namespace
{
	struct Data
	{
		explicit Data(std::string_view data)
			: _data(data)
		{
			std::cout << " Data()   --> " << _data << "\n";
		}

		virtual ~Data()
		{
			std::cout << "~Data()   --> " << _data << "\n";
		}

		std::string _data;
	};

	struct I
	{
		I()
		{
			std::cout << "   1 I()\n";
			doV();
			std::cout << "   2 I()\n";
		}

		void doA()  const
		{
			std::cout << "  [from I] 1 doA()\n";
			doV();
			std::cout << "  [from I] 2 doA()\n";
		}

		virtual void doV() const
		{
			std::cout << "I::doV\n";
		}

		virtual ~I() = default;
	};

	struct A : public I
	{
		A()
		:_d("A")
		{
			std::cout << "   A()\n";
			doV();
			std::cout << "   A()\n";
		}

		virtual void doV() const override
		{
			std::cout << "A::doV\n";
		}

		virtual ~A()
		{
			std::cout << "    ~A          \n";
			doV();
			std::cout << "    ~A          \n";
		}

		Data _d;
	};

	struct B : public A
	{
		B()
		:A()
        //, _d("B")
		{
			std::cout << " B() \n";
			doV();
			std::cout << " B() \n";
		}

		virtual void doV() const override
		{
			std::cout << "B::doV\n";
		}

	//private :
		~B()
		{
			std::cout << " ~B()    \n";
			doV();
			std::cout << " ~B()    \n";
		}

//        Data _d;
	};



	void bin_search()
	{   //                           0  1  2  3  4  5  6  7  8  9  10
		const std::vector<int> data{ 1, 3, 4, 5, 5, 5, 5, 6, 6, 6, 10, 10 };

		std::cout << "=================\n";

		const int target = 6;

		std::size_t l{ 0u };
		std::size_t h{ data.size() - 1 };
		std::size_t m{ 0u };
		while (h > l)
		{
			m = (h + l) / 2;

std::cout << "target = " << target << "\t data[m] = " << data[m] << "\t m = " << m << "\t l = " << l << "\t h = " << h << "\n";

			if (target == data[m])
			{
				std::cout << "!!!!!!!!!\n";
				//break;
				h = std::max(m, 1ull) - 1ull;
				//l = m + 1;
				//h = l = m;
			}
			else if (target > data[m])
			{
				l =  m + 1;
			}
			else// if(target < data[m])
			{
				h = std::max(m , 1ull)  -1ull;
			}

		}
		std::cout << "=================\n";
		std::cout << "target = " << target << "\t index = " << m << "\n";
		std::cout << "=================\n";
	}

	/*
от Саши
   Балансировка строки со скобками+ '*' символ служит любой скобкой или пустой строкой
   Строка может содержать три символа '()*'. Нужно удостоверится что у каждой открывающей скобки есть закрывающая + '*' может быть любой скобкой или пустой строкой
	*/
	struct BracketValidator
	{
		static bool valid(const std::string_view in)
		{
			std::stack<char> pa;
			for (const char c : in)
			{
				const char t = pa.empty() ? '.' : pa.top();

				//std::cout << "\t\t\t c = <" << c << "> \t top = <" << t << "> ,"
				//	<< "pa.size()  = " << pa.size() << " pa.size() % 2  = " << pa.size() % 2 << "\n";

				if (c == '*')
				{
					if (t == '(')
					{
						pa.pop();
					}
					else
					{
						pa.push(c);
					}
				}
				else if (c == '(')
				{
					pa.push(c);
				}
				else //if (c == ')')
				{
					if (t == '(' || t == '*')
					{
						pa.pop();
					}
					else
					{
						return false;
					}
				}
			}
			
			//std::cout << "\t\t\t pa.size()  = " << pa.size() << " pa.size() % 2  = " << pa.size() % 2 << "\n";
			return pa.empty() || pa.size() % 2 == 0; //
		}

		static void test()
		{
			const std::array strs
			{ 
				"",
				"*",
				"**",
				"()",
				")(",
				"(*",
				"*)",
				"(*)",
				"*()*",
				"()**",
				"*)(*",
				"*(*)*",
				"*(*)",
				"***(**)*)**(*)",
				"**)***)**(**",
			};

			for (const auto s : strs)
			{
				const auto val{ valid(s) };
				std::cout << "'" << s << "'\t\t" << std::boolalpha << val << "\n";
			}
		}
	};



}

void rq1_test()
{
	//bin_search();

	BracketValidator::test();


	//I* a = new B;
	//std::cout << "---------------------------\n";
	//a->doA();
	//std::cout << "---------------------------\n";
	//delete a;

	//std::cout << "BBB  ===============================\n";
	//{
	//	B b;
	//	std::cout << "---------------------------\n";
	//	b.doA();
	//	std::cout << "---------------------------\n";
	//}
	//std::cout << "AA    ===============================\n";
	//{
	//	A b;
	//	std::cout << "---------------------------\n";
	//	b.doA();
	//	std::cout << "---------------------------\n";
	//}
	//std::cout << "===============================\n";
	//{
	//	I& r{ B() };
	//	std::cout << "---------------------------\n";
	//	r.doA();
	//	std::cout << "---------------------------\n";
	//}


	std::cout << "\n";
}

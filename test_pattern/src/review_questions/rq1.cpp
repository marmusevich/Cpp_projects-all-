#include <iostream>
#include <string>


namespace
{
	struct Data
	{
		explicit Data(std::string_view data)
			: _data(data)
		{
			std::cout << "Data::Data   --> " << _data << std::endl;
		}

		virtual ~Data()
		{
			std::cout << "   Data::~Data   --> " << _data << std::endl;
		}

		std::string _data;
	};


	struct A
	{
		A()
		:_d("A")
		{
			std::cout << "  A::A" << std::endl;
		}


		void doA()
		{
			doV();
		}

		virtual void doV()
		{
			std::cout << "A::doV" << std::endl;
		}

		virtual ~A()
		{
			std::cout << "   A::~A          ";
			doV();
		}

		Data _d;
	};

	struct B : public A
	{
		B()
		:A()
        , _d("B")

		{
			std::cout << " B::B " << std::endl;
		}

		void doV() override
		{
			std::cout << "B::doV" << std::endl;
		}

		~B()
		{
			std::cout << "   B::~B    ";
			doV();
		}

        Data _d;
	};
}


void rq1_test()
{
	A* a = new B;
	a->doA();


	delete a;
}




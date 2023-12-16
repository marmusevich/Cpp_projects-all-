#include <iostream>
#include <memory>


namespace
{
	class ADificultCalc
	{
	public:
		ADificultCalc() = default;
		virtual ~ADificultCalc() = default;

		void calc() const noexcept
		{
			p1();
			m1();
			p2();
			m2();
			p3();
			m3();
			p4();
		}

	protected:
		virtual void m1() const noexcept = 0;
        virtual void m2() const noexcept = 0;
        virtual void m3() const noexcept = 0;

	private:
		void p1() const noexcept
		{
			std::cout << "part 1\n";
		}

		void p2() const noexcept
		{
			std::cout << "part 2\n";
		}

		void p3() const noexcept
		{
			std::cout << "part 3\n";
		}

		void p4() const noexcept
		{
			std::cout << "part 4\n";
		}
	};

	class cConcreteCalc1 : public ADificultCalc
	{
	protected:
		void m1() const noexcept override
		{
			std::cout << "   m1 - variant 1\n";
		}

		void m2() const noexcept override
		{
			std::cout << "   m2 - variant 1\n";
		}

		void m3() const noexcept override
		{
			std::cout << "   m3 - variant 1\n";
		}
	};

	class cConcreteCalc2 : public ADificultCalc
	{
	protected:
		void m1() const noexcept override
		{
			std::cout << "        m1 - variant 2 !!!! \n";
		}

		void m2() const noexcept override
		{
			//do nothing
		}

		void m3() const noexcept override
		{
			//use default impl
            std::cout << "ERROR in *NIX (but not in ms visual c++): ADificultCalc::m3();\n";
		}

	private:
		void p1() const noexcept
		{
			std::cout << "ERROR MUST NOT CALL  cConcreteCalc2::p1\n";
		}
	};
}


void templMethod_test()
{
	auto c1 = std::make_shared<cConcreteCalc1>();
	auto c2 = std::make_shared<cConcreteCalc2>();

	std::cout << "*** variant   <I> \n";
	c1->calc();
	std::cout << "*** variant   <II> \n";
	c2->calc();
}


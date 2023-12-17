#include <string>
#include <iostream>

#include <vector>
#include <memory>

namespace
{
	//fwd
	struct cFirst_1;
	struct cFirst_2;

	struct iVisitor
	{
		virtual void boo(cFirst_1 const& fi1) const noexcept = 0;
		virtual void boo(cFirst_2 const& fi2) const noexcept = 0;

		virtual ~iVisitor() = default;
	};

	//----------------------------------
	struct iFirst
	{
		virtual void accept(iVisitor const& v) noexcept = 0;

		virtual ~iFirst() = default;
	};

	struct cFirst_1 : public iFirst
	{
		void accept(iVisitor const& v) noexcept override
		{
			std::cout << "cFirst_1::accept \n";
			v.boo(*this);
		}

		std::string_view doSometing() const noexcept
		{
			return " cFirst_1::doSometing ";
		}
	};

	struct cFirst_2 : public iFirst
	{
		void accept(iVisitor const& v) noexcept override
		{
			std::cout << "cFirst_2::accept \n";
			v.boo(*this);
		}

		std::string_view doAnother() const noexcept
		{
			return " cFirst_2::doAnother ";
		}
	};

	//--------------
	struct cVisitor_1 : public iVisitor
	{
		void boo(cFirst_1 const& fi1) const noexcept override
		{
			std::cout << "Visitor_1::boo with \t" << fi1.doSometing() << "\n";
		}

		void boo(cFirst_2 const& fi2) const noexcept override
		{
			std::cout << "Visitor_1::boo with \t" << fi2.doAnother() << "\n";
		}
	};

	struct cVisitor_2 : public iVisitor
	{
		void boo(cFirst_1 const& fi1) const noexcept override
		{
			std::cout << "Another Visitor_2::boo with  >>> \t" << fi1.doSometing() << "\n";
		}

		void boo(cFirst_2 const& fi2) const noexcept override
		{
			std::cout << "Another Visitor_2::boo with  >>> \t" << fi2.doAnother() << "\n";
		}
	};
}

void visitor_test()
{
	std::vector<std::shared_ptr<iFirst>> vf{
		std::make_shared<cFirst_1>(),
		std::make_shared<cFirst_2>(),
		std::make_shared<cFirst_1>(),
		std::make_shared<cFirst_2>(),
	};

	cVisitor_1 v1;
	for (auto& p : vf)
	{
		p->accept(v1);
	}

	cVisitor_2 v2;
	for (auto& p : vf)
	{
		p->accept(v2);
	}
}


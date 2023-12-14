#include <iostream>
#include <vector>
#include <functional>

namespace
{
	//fwd

	struct IServer
	{
		virtual void doTask() const noexcept = 0;

		virtual ~IServer() = default;
		IServer() = default;
	};

	struct CServer : public IServer
	{
		void doTask() const noexcept override
		{
			std::cout << "\t\t\tMake work concrete server\n";
		}
	};

	struct IExtendServer : public IServer
	{
		IExtendServer(IServer const& parent)
			: mParent(parent)
		{

		}

	protected:
		std::reference_wrapper<const IServer> mParent;
	};

	struct CLogServer : public IExtendServer
	{
		CLogServer(IServer const& parent)
			: IExtendServer(parent)
		{

		}

		void doTask() const noexcept override
		{
			std::cout << "\t\t>>> log work of server before\n";
			mParent.get().doTask();
			std::cout << "\t\t>>> log work of server after\n";
		}
	};


	struct CMeasureServer : public IExtendServer
	{
		CMeasureServer(IServer const& parent)
			: IExtendServer(parent)
		{

		}

		void doTask() const noexcept override
		{
			std::cout << "\t--- measure work of server before\n";
			mParent.get().doTask();
			std::cout << "\t--- measure work of server after\n";
		}
	};
}


void decorator_test()
{

	CServer server;

	{
		std::cout << "clear server: \n";
		server.doTask();
		std::cout << " ...\n\n";
	}

	{
		auto decarated = CLogServer{ server };
		std::cout << "logging server: \n";
		decarated.doTask();
		std::cout << " ...\n\n";
	}

	{
		auto decarated = CLogServer{ CMeasureServer{server } };
		std::cout << "logging + measure server: \n";
		decarated.doTask();
		std::cout << " ...\n\n";
	}

	{
		auto decarated = CMeasureServer{ CLogServer{server } };
		std::cout << "measure logging server: \n";
		decarated.doTask();
		std::cout << " ...\n\n";
	}
}


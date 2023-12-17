#include <iostream>
#include <memory>

namespace
{
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
		explicit IExtendServer(std::shared_ptr<IServer> parent)
			: mParent(parent)
		{

		}

	protected:
		const std::shared_ptr<IServer> mParent;
	};

	struct CLogServer : public IExtendServer
	{
		explicit CLogServer(std::shared_ptr<IServer> parent)
			: IExtendServer(parent)
		{

		}

		void doTask() const noexcept override
		{
			std::cout << "\t\t>>> log work of server before\n";
			mParent->doTask();
			std::cout << "\t\t>>> log work of server after\n";
		}
	};

	struct CMeasureServer : public IExtendServer
	{
		explicit CMeasureServer(std::shared_ptr<IServer> parent)
			: IExtendServer(parent)
		{

		}

		void doTask() const noexcept override
		{
			std::cout << "\t--- measure work of server before\n";
			mParent->doTask();
			std::cout << "\t--- measure work of server after\n";
		}
	};
}


void decorator_test()
{
	auto server = std::make_shared<CServer>();

	{
		std::cout << "clear server: \n";
		server->doTask();
		std::cout << " ...\n\n";
	}

	{
		auto decarated = std::make_shared<CLogServer>(server);
		std::cout << "logging server: \n";
		decarated->doTask();
		std::cout << " ...\n\n";
	}

	{
		auto decarated = std::make_shared<CLogServer>(std::make_shared<CMeasureServer>(server));
		std::cout << "logging + measure server: \n";
		decarated->doTask();
		std::cout << " ...\n\n";
	}

	{
		auto decarated = std::make_shared<CMeasureServer>(std::make_shared<CLogServer>(server));
		std::cout << "measure logging server: \n";
		decarated->doTask();
		std::cout << " ...\n\n";
	}
}


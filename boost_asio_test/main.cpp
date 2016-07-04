#include <iostream>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/bind.hpp>
#include <boost/array.hpp>


using namespace std;
//using namespace boost;
//using namespace boost::asio;

using boost::asio::ip::tcp;

const char *daytime = "daytime";


int client(char *srvaddr)
{
    try
    {
        boost::asio::io_service io;
        tcp::resolver resolver(io);
        tcp::resolver::query query(srvaddr, daytime);
        tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
        tcp::socket socket(io);
        boost::asio::connect(socket, endpoint_iterator);
        for(;;)
        {
            boost::array<char, 128> buf;
            boost::system::error_code error;
            size_t len = socket.read_some(boost::asio::buffer(buf), error);
            if(error == boost::asio::error::eof)
                break;
            else if(error)
                throw boost::system::system_error(error);

            cout.write(buf.data(), len);
        }
    }
    catch(exception &e)
    {
        cerr <<e.what() <<endl;
    }
    return 0;
}


int main(int argc, char *argv[])
{
    /*
        if( argc != 0 )
        {
            cerr <<"Usage: client <host>" <<endl;
            return 1;
        }
    */

    client("srvaddr");


    return 0;
}

// получить адрес
// удаленный
//From the socket object that serve given connection.
//std::cout << "Peer IP: " << socket.remote_endpoint().address().to_string() << std::endl;
// локальный
//    boost::asio::ip::address addr = socket.local_endpoint().address();
//    std::cout << "My IP according to google is: " << addr.to_string() << std::endl;

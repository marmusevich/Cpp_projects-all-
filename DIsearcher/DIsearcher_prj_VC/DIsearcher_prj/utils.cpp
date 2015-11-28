#include "utils.h"


using namespace std;


ifstream::pos_type filesize(const string &filename)
{
    ifstream in(filename.c_str(), ifstream::in | ifstream::binary);
    in.seekg(0, ifstream::end);
    return in.tellg();
}


//преобразование в строку
string Deleciya_toString(const eDeleciya &_del)
{
    switch(_del)
    {
    case eDeleciya::del_1a:
        return "del-1a";
        break;
    case eDeleciya::del_1b:
        return "del-1b";
        break;
    case eDeleciya::del_1c:
        return "del-1c";
        break;
    case eDeleciya::del_1d:
        return "del-1d";
        break;
    case eDeleciya::del_1e:
        return "del-1e";
        break;
    case eDeleciya::del_1f:
        return "del-1f";
        break;
    case eDeleciya::del_1g:
        return "del-1g";
        break;
    case eDeleciya::del_2a:
        return "del-2a";
        break;
    case eDeleciya::del_2b:
        return "del-2b";
        break;
    case eDeleciya::del_3:
        return "del-3";
        break;
    case eDeleciya::inv_1a:
        return "inv-1a";
        break;
    case eDeleciya::inv_1b:
        return "inv-1b";
        break;
    case eDeleciya::inv_1c:
        return "inv-1c";
        break;
    case eDeleciya::inv_1d:
        return "inv-1d";
        break;
    case eDeleciya::inv_1e:
        return "inv-1e";
        break;
    case eDeleciya::inv_1f:
        return "inv-1f";
        break;
    case eDeleciya::inv_1g:
        return "inv-1g";
        break;
    case eDeleciya::inv_2a:
        return "inv-2a";
        break;
    case eDeleciya::inv_2b:
        return "inv-2b";
        break;
    case eDeleciya::inv_3:
        return "inv-3";
        break;
    default:
        return "no detect";
    }
}



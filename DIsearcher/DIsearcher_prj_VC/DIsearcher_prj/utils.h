#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include <algorithm>
#include <functional>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <fstream>

#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <unordered_set>
#include <unordered_map>
#include <memory>
#include <string.h>
#include <string>


#include "my_type.h"


using namespace std;

class cOneGene;
class cRSS;
class cDI_out;
class cGloballRunable;
class cStatistic;
class cOutResult;
class cGenesParam;
class cDIindex;
class cDupl;

const size_t MaxDuplInOneGen = 7;

/// trim from start
inline string &ltrim(string &s)
{
    s.erase(s.begin(), find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace))));
    return s;
}

/// trim from end
inline string &rtrim(string &s)
{
    s.erase(find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(), s.end());
    return s;
}

/// trim from both ends
inline string &trim(string &s)
{
    return ltrim(rtrim(s));
}

/// размер файла
ifstream::pos_type filesize(const string &filename);

/// строка в целое число с проверками
template <typename T> T convertStr2Num(const string &_str, bool &flag)
{
    if(_str.empty() || !isdigit(_str.c_str()[0]))
    {
        flag = false;
        return 0;
    }
    flag = true;
    return (T)(atol(_str.c_str()));
}

/// строка в вещественное число с проверками
template <typename T> T convertStr2Real(const string &_str, bool &flag)
{
    if(_str.empty() || !isdigit(_str.c_str()[0]))
    {
        flag = false;
        return 0.0;
    }
    flag = true;
    return (T)(atof(_str.c_str()));
}


/// тип дел инв в строку для вывода
string Deleciya_toString(const eDeleciya &_del);


#endif // UTILS_H_INCLUDED

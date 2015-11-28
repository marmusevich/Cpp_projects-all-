#ifndef MY_TYPE_H_INCLUDED
#define MY_TYPE_H_INCLUDED


//HESH version
//#define _UNORDERET_MAP


using namespace std;

class sGene;

/// псевдонимы для стандартных
///тип для описания номера строки в файле
typedef unsigned int tFileLineNumer;
///тип для описания количества экзонов в генах
typedef unsigned short int tCountExon;
///тип для описания количества координаты экзонов в гене
typedef unsigned int tExonPos;
///тип для элемента таблицы RSSTableItem
typedef unsigned long int tRSSTableItem;
/// тип для длины в таблице GenTable
typedef unsigned long long int tGenTableLen;
/// тип для количества в таблице GenTable
typedef unsigned  int tGenTableCount;
/// количество дублей в генах
typedef unsigned int tDuplCount;
/// тип для длины гена
typedef unsigned int tGenLen;

/// тип для
typedef unsigned int tContigNumber;

/// тип возврат функции поиска по файлу Gene.txt
typedef pair<bool, size_t> tGenesFindResult;


/// сложные типы

/// виды Дел. Инв.
enum class eDeleciya : uint8_t
{
    none = 0,
    del_beg = 10, del_1a, del_1b, del_1c, del_1d, del_1e, del_1f, del_1g, del_2a, del_2b, del_3, del_end,
    inv_beg = 30, inv_1a, inv_1b, inv_1c, inv_1d, inv_1e, inv_1f, inv_1g, inv_2a, inv_2b, inv_3, inv_end
    ,del_or_inv, del, inv
};

///Тип генов,
enum struct eTypeGene
{
    _begin = -2,
    error = -1,
    none = 0,
    A = 'A',
    B = 'B',
    C = 'C',
    _end
};


///описание для одного гена из "Gene.txt"
class sGene
{
public:
    struct cRNA
    {
        tExonPos En;
        tExonPos Ek;
    };

    bool complement;
    tCountExon countExons;
    vector<cRNA> RNA;
    eTypeGene typeGene;

    ///поля ключа
    tContigNumber contigNumber;
    size_t geneIndex;
    size_t fileIndex;

    string line;


    bool operator==( const sGene &hs) const
    {
        return (geneIndex == hs.geneIndex)
            && (contigNumber == hs.contigNumber)
            && (fileIndex == hs.fileIndex); //реже всего сравнивать
    }
    sGene():
        complement(false),
        countExons(0),
        RNA(0),
        typeGene(eTypeGene::none),
        contigNumber(0),
        geneIndex(0),
        fileIndex(0),
        line("")
    {}
};


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
// подавить "warning: base class 'struct ' has a non-virtual destructor [-Weffc++]"
struct sGene_lees: public binary_function<sGene, sGene,  bool>
{
    bool operator() (const sGene &lhs, const sGene &rhs) const
    {

        if(lhs.geneIndex < rhs.geneIndex)
        {
            return true;
        }
        else
        {
            if(lhs.geneIndex > rhs.geneIndex)
            {
                return false;
            }
            else // =
            {
                if(lhs.contigNumber < rhs.contigNumber)
                {
                    return true;
                }
                else
                {
                    if(lhs.contigNumber > rhs.contigNumber)
                    {
                        return false;
                    }
                    else // =
                    {
                        return lhs.fileIndex < rhs.fileIndex;
                    }
                }
            }
        }
    }
};
//#pragma message "Compiling " __FILE__ "..."
#pragma GCC diagnostic pop




///элемент таблици cRSS Table Item
struct s_cRSSTableItem
{
    tRSSTableItem _12;
    tRSSTableItem _23;
    tRSSTableItem del_12;
    tRSSTableItem del_23;
    tRSSTableItem inv_12;
    tRSSTableItem inv_23;
    tRSSTableItem del_inv_12;
    tRSSTableItem del_inv_23;
    s_cRSSTableItem():_12(0), _23(0), del_12(0), del_23(0), inv_12(0), inv_23(0), del_inv_12(0), del_inv_23(0) {}
    void clear(void)
    {
    _12=0; _23=0; del_12=0; del_23=0; inv_12=0; inv_23=0; del_inv_12=0; del_inv_23=0;
    }
};


#ifndef _UNORDERET_MAP
// NOT HESH version
//шаблон для элемента таблици Gen Table
template <typename T> class tGenTable_type
{
public: //hash_eDeleciya
    map<eDeleciya, T> _m;

    void add(const eDeleciya &del, const T &znach)
    {
        pair<typename map<eDeleciya, T>::iterator, bool>
                 ret   = _m.insert( pair<eDeleciya, T>( del, znach) );
        if (!ret.second)   //значение есть
        {
            ret.first->second += znach;
        }
    }


    T findDel(const eDeleciya &del)
    {
        typename map<eDeleciya, T>::iterator p;
        p= _m.find(del);
        if(p != _m.end())
        {
            return p->second;
        }
        else
        {
            return 0;
        }
    }

    void _clear(void)
    {
        _m.clear();
    }
    tGenTable_type(): _m() {}

    tGenTable_type& operator+=(const tGenTable_type &gt_t)
    {
        for(typename map<eDeleciya, T>::const_iterator it = gt_t._m.begin(); it != gt_t._m.end(); ++it)
        {
            add((*it).first, (*it).second);
        }
        return *this;
    }
};
#endif

#ifdef _UNORDERET_MAP
//HESH version
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
// подавить "warning: base class 'struct ' has a non-virtual destructor [-Weffc++]"
//struct hash_eDeleciya : public std::unary_function<eDeleciya, size_t>
//{
//    size_t operator()(const eDeleciya &x) const
//    {
//        return hash<size_t>()(static_cast<size_t>(x));
//        //return static_cast<size_t>(x);
//    }
//};
//template<class T> class hash_eDeleciya;
//
//template<>
//class hash_eDeleciya<eDeleciya> {
//public:
//    size_t operator()(const eDeleciya &x) const
//    {
//        return hash<size_t>()(static_cast<size_t>(x));
//    }
//};

struct KeyHash {
 std::size_t operator()(const eDeleciya& x) const
 {
        return hash<uint8_t>()(static_cast<uint8_t>(x));
 }
};

struct KeyEqual {
 bool operator()(const eDeleciya& lhs, const eDeleciya& rhs) const
 {
    return (static_cast<size_t>(lhs)) == (static_cast<size_t>(rhs));
 }
};

//#pragma message "Compiling " __FILE__ "..."
#pragma GCC diagnostic pop


//шаблон для элемента таблици Gen Table
template <typename T> class tGenTable_type
{
public: //hash_eDeleciya
    unordered_map<eDeleciya, T, KeyHash, KeyEqual > _m;

    void add(const eDeleciya &del, const T &znach)
    {
        pair<typename unordered_map<eDeleciya, T>::iterator, bool>
                 ret   = _m.insert( pair<eDeleciya, T>( del, znach) );
        if (!ret.second)   //значение есть
        {
            ret.first->second += znach;
        }
    }


    T findDel(const eDeleciya &del)
    {
        typename unordered_map<eDeleciya, T>::iterator p;
        p= _m.find(del);
        if(p != _m.end())
        {
            return p->second;
        }
        else
        {
            return 0;
        }
    }

    void _clear(void)
    {
        _m.clear();
    }
    tGenTable_type(): _m() {}

    tGenTable_type& operator+=(const tGenTable_type &gt_t)
    {
        for(typename unordered_map<eDeleciya, T>::const_iterator it = gt_t._m.begin(); it != gt_t._m.end(); ++it)
        {
            add((*it).first, (*it).second);
        }
        return *this;
    }
};
#endif

///элемент таблици Gen Table
struct sGenTable
{
    /// для расчета длин

    /// для длины
    tGenTable_type <tGenTableLen> len_sum; // сумма длин
    tGenTable_type <tDuplCount> len_count; // количество

    void add(const eDeleciya &del, const tGenTableLen &_len_sum, const tDuplCount &_len_count = 1)
    {
        len_count.add(del, _len_count);
        len_sum.add(del, _len_sum);
    }

    void clear_all(void)
    {
        len_sum._clear();
        len_count._clear();
    }



    sGenTable& operator+=(const sGenTable &gt)
    {
        len_count += gt.len_count;
        len_sum += gt.len_sum;
        return *this;
    }

    sGenTable(const sGenTable &gt): //конструктор копирования
        len_sum(), len_count()
    {
        *this+=gt;
    }

    sGenTable(): // конструктор по умолчанию
        len_sum(), len_count()
    {}

};



#endif // MY_TYPE_H_INCLUDED

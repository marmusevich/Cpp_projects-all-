#ifndef CSTATISTIC_H
#define CSTATISTIC_H

#include "utils.h"

using namespace std;

class cStatistic
{
public:
    unordered_map<size_t, s_cRSSTableItem> m_cRSSTable;
    unordered_map<size_t, bool> m_genNo_DI;
    unordered_map<size_t, sGenTable> m_GenTable;

    s_cRSSTableItem cRSSTableItem_one;
    s_cRSSTableItem cRSSTableItem_count;

    size_t CountGenom_Del_Inv;
    size_t CountGenom_Del_AND_Inv;
    size_t CountGenom_Del;
    size_t CountGenom_Inv;



    tDuplCount Genom_Del_Inv;
    tDuplCount Genom_Del;
    tDuplCount Genom_Inv;
    tGenTableLen Genom_Del_InvLen;
    tGenTableLen Genom_DelLen;
    tGenTableLen Genom_InvLen;

    size_t c_genNo_DI;
    size_t c_cRSSNo_DI_12;
    size_t c_cRSSNo_DI_23;
    size_t c_cRSSNo_DI_12_23;


    /// очистить масивы
    void Clear(void);


    void update_DI(const size_t &indexGen);
    void update_No_DI(const size_t &indexGen, bool estDI = false);

    void outFile_RSS(void);

    void update_GenTable(const size_t &indexGen, const sGenTable &gt);




    cStatistic():
        m_cRSSTable(),
        m_genNo_DI(),
        m_GenTable(),
        cRSSTableItem_one(),
        cRSSTableItem_count(),
        CountGenom_Del_Inv(0),
        CountGenom_Del_AND_Inv(0),
        CountGenom_Del(0),
        CountGenom_Inv(0),
        Genom_Del_Inv(0),
        Genom_Del(0),
        Genom_Inv(0),
        Genom_Del_InvLen(0),
        Genom_DelLen(0),
        Genom_InvLen(0),
        c_genNo_DI(0),
        c_cRSSNo_DI_12(0),
        c_cRSSNo_DI_23(0),
        c_cRSSNo_DI_12_23(0)


    { }
    ~cStatistic() {}

private:


};

#endif // CSTATISTIC_H

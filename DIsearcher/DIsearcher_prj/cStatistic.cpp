#include "cStatistic.h"
#include "cGloballRunable.h"
#include "cOutResult.h"

using namespace std;


void cStatistic::Clear(void)
{
    m_cRSSTable.clear();
    m_genNo_DI.clear();
    m_GenTable.clear();
    cRSSTableItem_one.clear();
    cRSSTableItem_count.clear();
    Genom_Del_Inv =0;
    Genom_Del =0;
    Genom_Inv =0;
    Genom_Del_InvLen =0;
    Genom_DelLen =0;
    Genom_InvLen =0;
    c_genNo_DI =0;
    c_cRSSNo_DI_12 =0;
    c_cRSSNo_DI_23 =0;
    c_cRSSNo_DI_12_23 =0;
    CountGenom_Del_Inv =0;
    CountGenom_Del =0;
    CountGenom_Inv =0;


}

void cStatistic::outFile_RSS(void)
{
    cOutResult::outFile_RepGenNo_DI();
    cOutResult::outFile_RepRSSTable();
}


void cStatistic::update_DI(const size_t &indexGen)
{
    cGloballRunable *_gr = cGloballRunable::Instance();
    update_No_DI(indexGen, true);

    ///m_cRSSTable;

    s_cRSSTableItem cRSSTableItem;
    //число
    cRSSTableItem.del_12 = count_if(_gr->mGen->rss12_0.begin(), _gr->mGen->rss12_0.end(), cRSS_isDel())
    + count_if(_gr->mGen->rss12_1.begin(), _gr->mGen->rss12_1.end(), cRSS_isDel());
    cRSSTableItem.del_23 = count_if(_gr->mGen->rss23_0.begin(), _gr->mGen->rss23_0.end(), cRSS_isDel())
    + count_if(_gr->mGen->rss23_1.begin(), _gr->mGen->rss23_1.end(), cRSS_isDel());

    cRSSTableItem.inv_12 = count_if(_gr->mGen->rss12_0.begin(), _gr->mGen->rss12_0.end(), cRSS_isInv())
    + count_if(_gr->mGen->rss12_1.begin(), _gr->mGen->rss12_1.end(), cRSS_isInv());
    cRSSTableItem.inv_23 = count_if(_gr->mGen->rss23_0.begin(), _gr->mGen->rss23_0.end(), cRSS_isInv())
    + count_if(_gr->mGen->rss23_1.begin(), _gr->mGen->rss23_1.end(), cRSS_isInv());

    cRSSTableItem.del_inv_12 = count_if(_gr->mGen->rss12_0.begin(), _gr->mGen->rss12_0.end(), cRSS_isDelInv())
    + count_if(_gr->mGen->rss12_1.begin(), _gr->mGen->rss12_1.end(), cRSS_isDelInv());
    cRSSTableItem.del_inv_23 = count_if(_gr->mGen->rss23_0.begin(), _gr->mGen->rss23_0.end(), cRSS_isDelInv())
    + count_if(_gr->mGen->rss23_1.begin(), _gr->mGen->rss23_1.end(), cRSS_isDelInv());


    //для итоговой таблицы
    if((cRSSTableItem.del_inv_12+cRSSTableItem.del_inv_23) >0)
        CountGenom_Del_Inv++;
    if(((cRSSTableItem.del_12+cRSSTableItem.del_23)>0) &&
       ((cRSSTableItem.inv_12+cRSSTableItem.inv_23)>0))
        CountGenom_Del_AND_Inv++;

    if((cRSSTableItem.del_12+cRSSTableItem.del_23) >0)
        CountGenom_Del++;
    if((cRSSTableItem.inv_12+cRSSTableItem.inv_23) >0)
        CountGenom_Inv++;

    pair< unordered_map<size_t, s_cRSSTableItem>::iterator, bool> ret
    = m_cRSSTable.insert( pair<size_t, s_cRSSTableItem>(indexGen, cRSSTableItem));
    if (!ret.second)
    {
        //значение есть
        ret.first->second.del_12    += cRSSTableItem.del_12;
        ret.first->second.del_23    += cRSSTableItem.del_23;
        ret.first->second.inv_12    += cRSSTableItem.inv_12;
        ret.first->second.inv_23    += cRSSTableItem.inv_23;
        ret.first->second.del_inv_12    += cRSSTableItem.del_inv_12;
        ret.first->second.del_inv_23    += cRSSTableItem.del_inv_23;
    }
}

void cStatistic::update_No_DI(const size_t &indexGen, bool estDI)
{
    cGloballRunable *_gr = cGloballRunable::Instance();

    s_cRSSTableItem cRSSTableItem;
    //всего
    cRSSTableItem._12 = _gr->mGen->rss12_0.size() + _gr->mGen->rss12_1.size();
    cRSSTableItem._23 = _gr->mGen->rss23_0.size() + _gr->mGen->rss23_1.size();

    pair< unordered_map<size_t, s_cRSSTableItem>::iterator, bool> ret1
    = m_cRSSTable.insert( pair<size_t, s_cRSSTableItem>(indexGen, cRSSTableItem));
    if (!ret1.second)
    {
        //значение есть
        ret1.first->second._12       += cRSSTableItem._12;
        ret1.first->second._23       += cRSSTableItem._23;
    }

    pair<unordered_map<size_t, bool>::iterator, bool> ret
    = m_genNo_DI.insert( pair<size_t, bool>(indexGen, estDI));
    if (!ret.second)
    {
        //значение есть, раньше был с пометкой неопределено, а теперь определили, то помечаем как определенный
        if(!ret.first->second && estDI)
            ret.first->second = estDI;
    }
}

void cStatistic::update_GenTable(const size_t &indexGen, const sGenTable &gt)
{
    pair<unordered_map<size_t, sGenTable>::iterator, bool> ret
        = m_GenTable.insert( pair<size_t, sGenTable> (indexGen, gt));
    if (!ret.second)   //значение есть
    { ret.first->second += gt; }

}



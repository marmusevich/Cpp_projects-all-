#ifndef CDUPL_H
#define CDUPL_H

#include "utils.h"
#include "cDIindex.h"

//#define _test


class cDupl
{
public:
    tDuplCount c_duplDel;
    tDuplCount c_duplInv;
    tDuplCount c_duplDelInv;
    tDuplCount c_duplGenomeDel;
    tDuplCount c_duplGenomeInv;
    tDuplCount c_duplGenomeDelInv;

    size_t CountDuplInOneGen;

    ///поиск дублей в пределах гена
    bool calculateDublInGene_del_AND_del_inv(const eDeleciya &del, vector<cDI_out*> &index, bool isAddDelInvStat);
    bool calculateDublInGene_inv_AND_del_inv(const eDeleciya &inv, vector<cDI_out*> &index, bool isAddDelInvStat);
    bool calculateDublInGene_del_inv(vector<cDI_out*> &index_del, vector<cDI_out*> &index_inv);
    bool calculateDublInGene(vector<cDI_out*> &index_del, vector<cDI_out*> &index_inv, const eDeleciya &del, const eDeleciya &inv);
    /// пркобразовать и отфильтровать вектор делеций
    void convertVectorAndFiltered_del(const eDeleciya &del, vector<cDI_out> &vDI, vector<cDI_out*> &index);
    void convertVectorAndFiltered_inv(const eDeleciya &inv, vector<cDI_out> &vDI, vector<cDI_out*> &index);


    ///поиск дубля в пределах хромосома
    bool calculateDublInLocus(void);


    /** Default constructor */
    cDupl():
        c_duplDel(0),
        c_duplInv(0),
        c_duplDelInv(0),
        c_duplGenomeDel(0),
        c_duplGenomeInv(0),
        c_duplGenomeDelInv(0),
        CountDuplInOneGen(0)

    {}
    /** Default destructor */
    virtual ~cDupl() {}
protected:
private:

    inline void calculateDubl_cikl(vector <cDIindex> &D);


    inline bool ABS_EC_ONE(tGenLen &p1, tGenLen &p2)
    {
        //return labs(p1 - p2) == 1;
        return (p1 > p2) ? (p1 == (p2+1)) : ((p1+1) == p2);
    }



    template <typename T> inline bool ChekDubl_del_inv(T &d1, T &d2)
    {
        return  ((((d1.complement12 != d2.complement23) && (d1.Loc_pos23 == d2.Loc_pos12) && (d1.complement23 == d2.complement12) && ABS_EC_ONE(d1.Loc_pos12, d2.Loc_pos23)) ||
                  ((d2.complement12 != d1.complement23) && (d2.Loc_pos23 == d1.Loc_pos12) && (d2.complement23 == d1.complement12) && ABS_EC_ONE(d2.Loc_pos12, d1.Loc_pos23))) ? true : false)
            ||  ((((d1.complement12 != d2.complement12) && (d1.Loc_pos23 == d2.Loc_pos23) && (d1.complement23 == d2.complement23) && ABS_EC_ONE(d1.Loc_pos12, d2.Loc_pos12)) ||
                  ((d2.complement23 != d1.complement23) && (d2.Loc_pos12 == d1.Loc_pos12) && (d2.complement12 == d1.complement12) && ABS_EC_ONE(d2.Loc_pos23, d1.Loc_pos23))) ? true : false);
    }

//доп к 1 правилу
//((d1.Loc_pos12 == d2.Loc_pos23) && (d2.Loc_pos12 == d1.Loc_pos23) && (d1.complement12 == d2.complement23) && (d2.complement12 == d1.complement23)) ? true : false;


    template <typename T> inline bool ChekDubl_del(T &d1, T &d2)
    {
        if(d1.complement12 == d2.complement23)
            return ((d1.Loc_pos12 == d2.Loc_pos23) && (d2.Loc_pos12 == d1.Loc_pos23) ) ||
                   (ABS_EC_ONE(d1.Loc_pos12, d2.Loc_pos12) && ABS_EC_ONE(d1.Loc_pos23, d2.Loc_pos23));
        else
            return  ((d1.Loc_pos12 == d2.Loc_pos12) && (d1.Loc_pos23 == d2.Loc_pos23) ) ||
                    (ABS_EC_ONE(d1.Loc_pos12, d2.Loc_pos23) && ABS_EC_ONE(d1.Loc_pos23, d2.Loc_pos12));
    }

    template <typename T> inline bool ChekDubl_inv(T &d1, T &d2)
    {
        if(d1.complement12 == d2.complement23)
            return  ((d1.Loc_pos12 == d2.Loc_pos23) && (d2.Loc_pos12 == d1.Loc_pos23)) ||
                    ((d1.Loc_pos12 == d2.Loc_pos12) && (d1.Loc_pos23 == d2.Loc_pos23));
        else
            return  (ABS_EC_ONE(d1.Loc_pos12, d2.Loc_pos12) && ABS_EC_ONE(d1.Loc_pos23, d2.Loc_pos23)) ||
                    (ABS_EC_ONE(d1.Loc_pos12, d2.Loc_pos23) && ABS_EC_ONE(d1.Loc_pos23, d2.Loc_pos12));
    }

};

#endif // CDUPL_H



//    template <typename T> inline bool ChekDubl(T &d1, T &d2)
//    {
//        int usl1 = (d1.complement12 + d1.complement23);
//        int usl2 = (d2.complement12 + d2.complement23);
//
//        if(usl1 == 0) //=0/0
//        {
//            if(usl2 == 0)
//            {
//                return ChekDubl_Usl1(d1, d2);
//            }
//            else if(usl2 == 1)
//            {
//                return ChekDubl_Usl3(d1, d2);
//            }
//            else if(usl2 == 2)
//            {
//                return ChekDubl_Usl2(d1, d2);
//            }
//        }
//        else if(usl1 == 1) // =0/1 or 1/0
//        {
//            if(usl2 == 0)
//            {
//                return ChekDubl_Usl3(d1, d2);
//            }
//            else if(usl2 == 1)
//            {
//                return ChekDubl_Usl1(d1, d2) || ChekDubl_Usl2(d1, d2);
//            }
//            else if(usl2 == 2)
//            {
//                return ChekDubl_Usl3(d1, d2);
//            }
//        }
//        else if(usl1 == 2) // =1/1
//        {
//            if(usl2 == 0)
//            {
//                return ChekDubl_Usl2(d1, d2);
//            }
//            else if(usl2 == 1)
//            {
//                return ChekDubl_Usl3(d1, d2);
//            }
//            else if(usl2 == 2)
//            {
//                return ChekDubl_Usl1(d1, d2);
//            }
//        }
//        return false;
//    }
//
//
//    template <typename T> inline bool ChekDubl_Usl1(T &d1, T &d2)
//    {
//
//        return ((d1.Loc_pos12 == d2.Loc_pos23) && (d2.Loc_pos12 == d1.Loc_pos23) && (d1.complement12 == d2.complement23) && (d2.complement12 == d1.complement23)) ? true : false;
//    }
//
//    template <typename T> inline bool ChekDubl_Usl2(T &d1, T &d2)
//    {
//
//        return (((d1.complement12 != d2.complement23) && (d1.complement23 != d2.complement12) && ABS_EC_ONE(d1.Loc_pos12, d2.Loc_pos23) && ABS_EC_ONE(d2.Loc_pos12, d1.Loc_pos23)) ? true : false)
//            || (((d1.complement12 != d2.complement12) && (d1.complement23 != d2.complement23) && ABS_EC_ONE(d2.Loc_pos12, d1.Loc_pos12) && ABS_EC_ONE(d1.Loc_pos23, d2.Loc_pos23)) ? true : false);
//    }
//
//    template <typename T> inline bool ChekDubl_Usl3(T &d1, T &d2)
//    {
//        return  ((((d1.complement12 != d2.complement23) && (d1.Loc_pos23 == d2.Loc_pos12) && (d1.complement23 == d2.complement12) && ABS_EC_ONE(d1.Loc_pos12, d2.Loc_pos23)) ||
//                  ((d2.complement12 != d1.complement23) && (d2.Loc_pos23 == d1.Loc_pos12) && (d2.complement23 == d1.complement12) && ABS_EC_ONE(d2.Loc_pos12, d1.Loc_pos23))) ? true : false)
//            ||  ((((d1.complement12 != d2.complement12) && (d1.Loc_pos23 == d2.Loc_pos23) && (d1.complement23 == d2.complement23) && ABS_EC_ONE(d1.Loc_pos12, d2.Loc_pos12)) ||
//                  ((d2.complement23 != d1.complement23) && (d2.Loc_pos12 == d1.Loc_pos12) && (d2.complement12 == d1.complement12) && ABS_EC_ONE(d2.Loc_pos23, d1.Loc_pos23))) ? true : false);
//    }

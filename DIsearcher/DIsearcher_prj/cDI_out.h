#ifndef CDI_OUT_H
#define CDI_OUT_H


#include "utils.h"
#include "cRSS.h"
#include "cOneGene.h"



using namespace std;


class cDI_out
{
public:
    //eDeleciya typeDel_Inv;
    tGenLen leght;
    size_t nomerRSS12;
    size_t nomerRSS23;
    bool complement12;
    bool complement23;
    tGenLen Loc_pos12;
    tGenLen Loc_pos23;
    bool isDupl;
    tDuplCount duplDel;
    tDuplCount duplInv;
    tDuplCount duplDelInv;

    string toString(const tr1::shared_ptr<cOneGene> &gen) const;
    cDI_out():
        //typeDel_Inv(eDeleciya::none),
        leght(0),
        nomerRSS12(0),
        nomerRSS23(0),
        complement12(false),
        complement23(false),
        Loc_pos12(0), Loc_pos23(0),
        isDupl(false),
        duplDel(0),
        duplInv(0),
        duplDelInv(0)
    {}
    //virtual ~cDI_out();
protected:
private:
};


#endif // CDI_OUT_H

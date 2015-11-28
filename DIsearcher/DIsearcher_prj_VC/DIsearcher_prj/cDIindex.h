#ifndef CDIINDEX_H
#define CDIINDEX_H

#include "utils.h"
#include "cDI_out.h"

class cDIindex
{
public:
    size_t Igen;
    bool complement12;
    tGenLen Loc_pos12;
    bool complement23;
    tGenLen Loc_pos23;
    eDeleciya T;
    tGenLen leght;
    tDuplCount duplGenomeDel;
    tDuplCount duplGenomeInv;
    tDuplCount duplGenomeDelInv;






    /** Default constructor */
    cDIindex():
        Igen(0),
        complement12(false),
        Loc_pos12(0),
        complement23(false),
        Loc_pos23(0),
        T(eDeleciya::none),
       leght(0),
        duplGenomeDel(0),
        duplGenomeInv(0),
        duplGenomeDelInv(0)
    {}

    cDIindex(const tr1::shared_ptr<cOneGene>  &gen, const eDeleciya &typeDel_Inv, const cDI_out &di);

};



#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
// подавить "warning: base class 'struct ' has a non-virtual destructor [-Weffc++]"
struct cDIindex_lees: public binary_function<cDIindex, cDIindex,  bool>
{
    bool operator() (const cDIindex &lhs, const cDIindex &rhs) const
    {
        return lhs.Igen < rhs.Igen;
    }
};
//#pragma message "Compiling " __FILE__ "..."
#pragma GCC diagnostic pop



#endif // CDIINDEX_H

#include "cDIindex.h"

#include "cDI_out.h"


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
// подавить "warning: 'cDIindex::C12' should be initialized in the member initialization list [-Weffc++]"
cDIindex::cDIindex(const tr1::shared_ptr<cOneGene>  &gen, const eDeleciya &typeDel_Inv, const cDI_out &di):
    duplGenomeDel(0),
    duplGenomeInv(0),
    duplGenomeDelInv(0)
{
    Igen = gen->geneIndex; //gene
    T = typeDel_Inv;
    complement12 = di.complement12;
    complement23 = di.complement23;
    leght = di.leght;
    Loc_pos12 = di.Loc_pos12;
    Loc_pos23 = di.Loc_pos23;
}
#pragma GCC diagnostic pop

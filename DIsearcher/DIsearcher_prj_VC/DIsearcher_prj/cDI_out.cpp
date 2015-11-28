#include "cDI_out.h"


//формирование выводной строки
string cDI_out::toString(const tr1::shared_ptr<cOneGene>  &gen) const
{
    cRSS *r12;
    cRSS *r23;

    if (complement12)
        r12 = &(gen->rss12_1[nomerRSS12]);
    else
        r12 = &(gen->rss12_0[nomerRSS12]);

    if (complement23)
        r23 = &(gen->rss23_1[nomerRSS23]);
    else
        r23 = &(gen->rss23_0[nomerRSS23]);

    string h12="-", h23="-";
    if(r12->isExon)
        h12="e";
    else if(r12->isIntron)
        h12="i";
    else if(r12->isFive)
        h12="5'";
    else if(r12->isThri)
        h12="3'";

    if(r23->isExon)
        h23="e";
    else if(r23->isIntron)
        h23="i";
    else if(r23->isFive)
        h23="5'";
    else if(r23->isThri)
        h23="3'";

    ostringstream sout("");
    sout
            <<Loc_pos12 <<"_"
            <<r12->orig_matrix <<"_("
            <<complement12 <<"_"
            <<"12_"
            <<r12->orig_heptamer <<"_"
            <<r12->orig_nanomer <<"_"
            <<r12->orig_perrcent <<"_"
            <<h12 <<r12->orig_numer <<")" <<'\t'

            <<Loc_pos23 <<"_"
            <<r23->orig_matrix <<"_("
            <<complement23 <<"_"
            <<"23_"
            <<r23->orig_heptamer <<"_"
            <<r23->orig_nanomer <<"_"
            <<r23->orig_perrcent <<"_"
            <<h23 <<r23->orig_numer <<")" <<'\t'

            <<leght <<'\t'

            ;
    return sout.str();
}

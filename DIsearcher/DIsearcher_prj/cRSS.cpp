#include "cRSS.h"
#include "cGloballRunable.h"



//формирование выводной строки
string cRSS::toString()
{

    cGloballRunable *_gr = cGloballRunable::Instance();
    ostringstream sout("");
    sout    <<_gr->mGen->file <<'\t'
            <<_gr->mGen->locus <<'\t'
            <<orig_loc_pos <<'\t'
            <<orig_abs_pos <<'\t'
            <<orig_complement <<'\t'
            <<orig_spacer <<'\t'
            <<orig_matrix <<'\t'
            <<orig_par6 <<'\t'
            <<orig_par7 <<'\t'
            <<orig_spacer1 <<'\t'
            <<orig_heptamer <<'\t'
            <<orig_nanomer <<'\t'
            <<orig_perrcent <<'\t'
            <<_gr->mGen->geneName <<'\t'
            <<orig_exon <<'\t'
            <<orig_intron <<'\t'
            <<orig_five <<'\t'
            <<orig_thri <<'\t'
            <<orig_numer;

    return sout.str();
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
// подавить "warning: base class 'struct ' has a non-virtual destructor [-Weffc++]"
//расчет коэфициента А
void detectKoefA::operator() (cRSS &r)
{
    if (!r.isExon) // если не экзон, то ничего не считаем
    {
        return;
    }

    cGloballRunable *_gr = cGloballRunable::Instance();
    // если RNA нет, сообщили и вышли
    if(_gr->genesParam.mGenes[ _gr->mGen->geneIndex ].RNA.empty())
    {
        cout <<"\t\t detect 'A' - "<<r.toString() <<endl;
        cout <<"\t\t no RNA" <<endl;
        return;
    }

    // для "В"  номера обратные
    size_t numer;
    if(_gr->genesParam.mGenes[ _gr->mGen->geneIndex ].typeGene == eTypeGene::A)
        numer = r.numer-1;// тип А, номер для расчета просто -1, в С масивы начинают нумерацию с 0
    else // для Б номера обратные, т.е. отнять от конца
        numer = _gr->genesParam.mGenes[ _gr->mGen->geneIndex ].RNA.size() - r.numer;
    // если полученый номер вне пределов RNA, то ошибка
    if(numer < 0 || numer >= _gr->genesParam.mGenes[ _gr->mGen->geneIndex ].RNA.size())
    {
        cout <<"\t\t detect 'A' - "<<r.toString() <<endl;
        cout <<"\t\t Numer exon <" <<r.numer <<"> > RNA.size=(" <<_gr->genesParam.mGenes[ _gr->mGen->geneIndex ].RNA.size()<<") or < 1" <<endl;
        return;
    }
    //получить заданый RNA, по его номеру (приведеный)
    sGene::cRNA &rna = _gr->genesParam.mGenes[ _gr->mGen->geneIndex ].RNA[numer];
    // доп проверка, а действительно ли loc_pos в диапазоне указаного RNA
    if((r.loc_pos < rna.En) ||(r.loc_pos > rna.Ek))
    {
        cout <<"\t\t detect 'A' - "<<r.toString() <<endl;
        cout <<"\t\t Numer exon <" <<r.numer <<">  but loc_pos does not belong to the specified interval"
             <<" (loc_pos = " <<r.loc_pos <<", rna.En = " <<rna.En <<", rna.Ek = " <<rna.Ek <<")" <<endl;
    }
    // абсолютное значение, разница loc_pos и координата начала
    r.A = labs(r.loc_pos - rna.En);
}


//расчет коэфициента Б
void detectKoefB::operator() (cRSS &r)
{
    if (!r.isExon) // если не экзон, то ничего не считаем
    {
        return;
    }

    cGloballRunable *_gr = cGloballRunable::Instance();
    // если RNA нет, сообщили и вышли
    if(_gr->genesParam.mGenes[ _gr->mGen->geneIndex ].RNA.empty())
    {
        cout <<"\t\t detect 'B' - "<<r.toString() <<endl;
        cout <<"\t\t no RNA" <<endl;
        return;
    }

    // для "В"  номера обратные
    size_t numer;
    if(_gr->genesParam.mGenes[ _gr->mGen->geneIndex ].typeGene == eTypeGene::A)
        numer = r.numer-1; // тип А, номер для расчета просто -1, в С масивы начинают нумерацию с 0
    else  // для Б номера обратные, т.е. отнять от конца
        numer = _gr->genesParam.mGenes[ _gr->mGen->geneIndex ].RNA.size() - r.numer;
    // если полученый номер вне пределов RNA, то ошибка
    if(numer < 0 || numer >= _gr->genesParam.mGenes[ _gr->mGen->geneIndex ].RNA.size())
    {
        cout <<"\t\t detect 'B' - "<<r.toString() <<endl;
        cout <<"\t\t Numer exon " <<r.numer <<" > RNA.size=(" <<_gr->genesParam.mGenes[ _gr->mGen->geneIndex ].RNA.size() <<") or < 1" <<endl;
        return;
    }

    //получить заданый RNA, по его номеру (приведеный)
    sGene::cRNA &rna = _gr->genesParam.mGenes[ _gr->mGen->geneIndex ].RNA[numer];
    // доп проверка, а действительно ли loc_pos в диапазоне указаного RNA
    if((r.loc_pos < rna.En) ||(r.loc_pos > rna.Ek))
    {
        cout <<"\t\t detect 'B' - "<<r.toString() <<endl;
        cout <<"\t\t Numer exon <" <<r.numer <<">  but loc_pos does not belong to the specified interval"
             <<" (loc_pos = " <<r.loc_pos <<", rna.En = " <<rna.En <<", rna.Ek = " <<rna.Ek <<")" <<endl;
    }
    // абсолютное значение, разница loc_pos и координата конца
    r.B = labs(r.loc_pos - rna.Ek);
}

bool cRSS_isDel::operator() (cRSS &r)
{
    return r.isDel;
}

bool cRSS_isInv::operator() (cRSS &r)
{
    return r.isInv;
}

bool cRSS_isDelInv::operator() (cRSS &r)
{
    return r.isInv || r.isDel;
}
#pragma GCC diagnostic pop

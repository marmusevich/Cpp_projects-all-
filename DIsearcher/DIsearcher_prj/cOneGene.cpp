#include "cOneGene.h"
#include "cGloballRunable.h"
#include "cRSS.h"
#include "cOutResult.h"




//#define __test


void cOneGene::ClearGen(void)
{
    rss12_0.clear();
    rss12_1.clear();
    rss23_0.clear();
    rss23_1.clear();
    DI_out.clear();
    geneName.clear();
}

cOneGene::state cOneGene::ParseString(string _in)
{
    state state = state_ok;
    // str to vector tmp
    vector<string> tmp;

    istringstream iss(_in);
    string token;
    while(getline(iss, token, '\t'))
    {
        tmp.push_back(trim(token));
    }
    //если последний элемент не определен, поле номер = " "
    if(tmp.size()== 18)
    {
        tmp.push_back("");
    }

    //если в строке не коректное количество элементов
    //cout << endl <<tmp.size()<< endl;
    if(tmp.size()!= 19)
    {
        return state_invalidString;
    }

    //новый ген + локус
    if((geneName == "") && (file=="") && (locus==""))
    {
        ClearGen();
        file = tmp[0];
        locus = tmp[1];
        geneName = tmp[13];
    }

    //новый ген
    if((geneName == ""))
    {
        ClearGen();
        geneName = tmp[13];
    }

    //файл и локус тотже, ген новый
    if(!(geneName.compare(tmp[13])==0) &&
       ((file.compare(tmp[0])==0) &&
        (locus.compare(tmp[1])==0)) )
    {
        return state_newGene;
    }

        // все три разные
    if(!((file.compare(tmp[0])==0) &&
         (locus.compare(tmp[1])==0) &&
         (geneName.compare(tmp[13])==0)))
    {
        return state_newLokus;
    }

    cRSS r;
    r.orig_loc_pos = tmp[2];
    r.orig_abs_pos=tmp[3];
    r.orig_complement=tmp[4];
    r.orig_spacer=tmp[5];
    r.orig_matrix=tmp[6];
    r.orig_par6=tmp[7];
    r.orig_par7=tmp[8];
    r.orig_spacer1=tmp[9];
    r.orig_heptamer=tmp[10];
    r.orig_nanomer=tmp[11];
    r.orig_perrcent=tmp[12];
    r.orig_exon=tmp[14];
    r.orig_intron=tmp[15];
    r.orig_five=tmp[16];
    r.orig_thri=tmp[17];
    r.orig_numer=tmp[18];

    /// производные

    bool complement = (r.orig_complement == "1");
    bool isSpacer12 =  (r.orig_spacer == "12");
    // в конкретной строке
    convertStr2Num<unsigned long>(r.orig_exon, r.isExon);
    convertStr2Num<unsigned long>(r.orig_intron, r.isIntron);
    convertStr2Num<unsigned long>(r.orig_five, r.isFive);
    convertStr2Num<unsigned long>(r.orig_thri, r.isThri);

    bool flag=false;
    r.numer = convertStr2Num<tCountExon>(r.orig_numer, flag);
    flag = false;

    r.loc_pos = convertStr2Num<tExonPos>(r.orig_loc_pos, flag);
    if(!flag)
    {
        cout <<"Invalid convert 'loc_pos' to numeric. ='" <<r.orig_loc_pos <<"'" <<endl;
        return state_invalidString;
    }

    if(isSpacer12)
    {
        if(complement)
            {rss12_1.push_back(r);}
        else
            {rss12_0.push_back(r);}
    }
    else
    {
        if(complement)
            {rss23_1.push_back(r);}
        else
            {rss23_0.push_back(r);}
    }
    return state;
}



bool cOneGene::workOneGen(string line)
{
    size_t dlina = rss12_0.size() + rss12_1.size() + rss23_0.size() + rss23_1.size();
    ostringstream a("");

    if(dlina < 1)
    {
        return false;
    }

    cGloballRunable *_gr = cGloballRunable::Instance();
    bool flag=false;
    locusVal = convertStr2Num<tContigNumber>(locus, flag);
    if(!flag)
    {
        a <<"Do not convert 'locus' to numeric! gene = < "
          <<geneName  <<" >, file = < " <<file <<" >, locus = " <<locus
          <<" - count = " <<dlina <<" - \t" <<line;
        cout <<a.str() <<endl;
        cOutResult::outFile_ErrorGen(a.str());

        ClearGen();
        return false;
    }

    if(!(_gr->genesParam.findFileIndex(file, fileIndex) && _gr->genesParam.findGenIndex(geneName, geneNameIndex)))
    {
        a <<"NO DETECT TYPE! gene = < "  <<geneName  <<" > OR file = < " <<file <<" >, locus = " <<locus
          <<" - count = " <<dlina <<" - \t" <<line <<" - not in 'gene.txt'";
        cout <<a.str() <<endl;
        cOutResult::outFile_ErrorGen(a.str());

        ClearGen();
        return false;
    }

    tGenesFindResult rez_fin = _gr->genesParam.findGene(fileIndex, geneNameIndex, locusVal);
    if(rez_fin.first)
    {
        geneIndex = rez_fin.second;
    }
    else
    {
        a <<"NO DETECT TYPE! gene = < "  <<geneName  <<" >, file = < " <<file <<" >, locus = " <<locus
          <<" - count = " <<dlina <<" - \t" <<line;
        cout <<a.str() <<endl;
        cOutResult::outFile_ErrorGen(a.str());
        ClearGen();
        return false;
    }

    cout <<"gene = < "  <<geneName <<" >, file = < " <<file <<" >, locus = " <<locus <<endl;
    cout    <<"- cRSS(12): compl.= " <<long(rss12_1.size())
            <<", NO compl.= " <<long(rss12_0.size())
            <<"; cRSS(23): compl.= " <<long(rss23_1.size())
            <<", NO compl.= " <<long(rss23_0.size()) <<endl;

    ///определения коэф. А и В
    detectKoefAB();

    ///определения Del
    detectDel_cikl();
    ///определения Inv
    detectInv_cikl();

    ///действия после определения
    if(!DI_out.empty()) /// если в гене удалось определить Inv и Del - действия
    {
        cout <<" found < " <<DI_out.size() <<" > DEL/INV," <<endl;
        string indexFileName("");

        detectDupl();

        //обновление статистики
        _gr->mStatistic->update_DI(geneIndex);
    }
    else /// в гене нет Inv и Del - действия
    {
        cout <<"\t" <<"   NO found  DEL/INV" <<endl;
        _gr->mStatistic->update_No_DI(geneIndex);
    }

    ///сохранить те cRSS которые создают Del Inv и не создают
    cOutResult::outFile_Del_Inv_DelInv_NO();

    ClearGen();
    return true;
}


void cOneGene::detectKoefAB(void)
{
    //cout <<"        - detect Koef A0 B1" <<endl;
    for_each(rss12_0.begin(), rss12_0.end(), detectKoefA());
    for_each(rss23_0.begin(), rss23_0.end(), detectKoefA());
    for_each(rss12_1.begin(), rss12_1.end(), detectKoefB());
    for_each(rss23_1.begin(), rss23_1.end(), detectKoefB());
}


bool cOneGene::di_out_push_back(eDeleciya del_inv, const cDI_out &_di)
{
    try
    {
        unordered_map<uint8_t, vector<cDI_out> >::iterator find_it = DI_out.find (static_cast<uint8_t>(del_inv));
        if ( find_it == DI_out.end() )
        {
            vector<cDI_out> di_out;
            try
            {
                di_out.push_back(_di);
            }
            catch (bad_alloc xa)
            {
                cout <<"   !!!(VECTOR NEW) di_out.size= "<<(di_out.size()) ;// <<endl;
                cout <<"    di_out.max_size= "<<(di_out.max_size()) <<" " <<xa.what() <<endl;
                throw;
                return false;
            }

            DI_out.insert( pair<uint8_t, vector<cDI_out> >(static_cast<uint8_t>(del_inv), di_out));
        }
        else
            try
            {
                find_it->second.push_back(_di);
            }
            catch (bad_alloc xa)
            {
                cout <<"   !!!(VECTOR ADD) di_out.size= "<<(find_it->second.size()) ;// <<endl;
                cout <<"    di_out.max_size= "<<(find_it->second.max_size()) <<" " <<xa.what() <<endl;
                throw;
                return false;
            }


#ifdef __test
    cout <<endl <<"push_back "  <<endl;
#endif

//        vector<cDI_out> di_out;
//        di_out.push_back(_di);
//
//        pair<unordered_map<uint8_t, vector<cDI_out> >::iterator, bool> ret
//            = DI_out.insert( pair<uint8_t, vector<cDI_out> >(static_cast<uint8_t>(del_inv), di_out));
//        if (!ret.second)   //значение есть
//        { ret.first->second.push_back(_di); }

        return true;
    }
    catch (bad_alloc xa)
    {
        cout <<"   !!! (MAP) DI_out.size= "<<(DI_out.size());//<<endl;
        cout <<"    DI_out.max_size= "<<(DI_out.max_size()) <<" " <<xa.what() <<endl;
        return false;
    }
}



//---------------------------------------------------------------------------------------------------

bool cOneGene::detectDel_cikl(void)
{
    cGloballRunable *_gr = cGloballRunable::Instance();

    //cout <<"\t" <<"- detect DEL. number of comparisons: ";

    ///определения типа Del ->  rss12_0 сравниваем rss23_1
    //cout <<(rss12_0.size() * rss23_1.size()) <<" + ";
    size_t _size12 = rss12_0.size();
    size_t _size23 = rss23_1.size();

    for( size_t i = 0; i < _size12; i++)
    {
        for(size_t j = 0; j < _size23; j++)
        {
            bool rez_del = false;
            rez_del = detectDel(rss12_0[i], rss23_1[j]);
            if(rez_del)
            {
                tGenLen leght = labs(rss12_0[i].loc_pos - rss23_1[j].loc_pos);
                if(rss12_0[i].loc_pos > rss23_1[j].loc_pos)
                {
                    leght = leght - 1;
                }
                else
                {
                    leght = leght + 1;
                }

                //условие на длину
                if(leght < _gr->DI_min)
                {
                    continue;
                }
                if(leght > _gr->DI_max)
                {
                    continue;
                }


                rss12_0[i].isDel = true;
                rss23_1[j].isDel = true;
                //оба уловия прошли, сохраняемся
                cDI_out _di;
                _di.leght = leght;
                _di.nomerRSS12 = i;
                _di.nomerRSS23 = j;
                _di.Loc_pos12 = rss12_0[i].loc_pos;
                _di.Loc_pos23 = rss23_1[j].loc_pos;
                _di.complement12 = false;
                _di.complement23 = true;

                di_out_push_back(typeDel_Inv, _di);
            }
        }
    }

    ///определения типа Del ->  rss12_1 сравниваем rss23_0
    //cout <<(rss12_1.size() * rss23_0.size());
    _size12 = rss12_1.size();
    _size23 = rss23_0.size();

    for(size_t i = 0; i < _size12; i++)
    {
        for(size_t j = 0; j < _size23; j++)
        {
            bool rez_del = false;
            rez_del = detectDel( rss23_0[j] ,rss12_1[i]);
            if(rez_del)
            {
                tGenLen leght = labs(rss12_1[i].loc_pos - rss23_0[j].loc_pos);
                if(rss23_0[j].loc_pos > rss12_1[i].loc_pos)
                {
                    leght = leght - 1;
                }
                else
                {
                    leght = leght + 1;
                }

                //условие на длину
                if(leght < _gr->DI_min)
                {
                    continue;
                }
                if(leght > _gr->DI_max)
                {
                    continue;
                }

                rss12_1[i].isDel = true;
                rss23_0[j].isDel = true;

                //оба уловия прошли, сохраняемся
                cDI_out _di;
                _di.leght = leght;
                _di.nomerRSS12 = i;
                _di.nomerRSS23 = j;
                _di.Loc_pos12 = rss12_1[i].loc_pos;
                _di.Loc_pos23 = rss23_0[j].loc_pos;
                _di.complement12 = true;
                _di.complement23 = false;

                di_out_push_back(typeDel_Inv, _di);
            }
        }
    }
    //cout <<endl;
    return true;
}

bool cOneGene::detectDel(const cRSS &r0, const cRSS &r1)
{
    cGloballRunable *_gr = cGloballRunable::Instance();
#ifdef __test

    cout <<endl
         <<"gen.countExons = " <<_gr->genesParam.mGenes[ geneIndex ].countExons <<"\tgen.complement = " <<_gr->genesParam.mGenes[ geneIndex ].complement;
    switch(_gr->genesParam.mGenes[ geneIndex ].typeGene)
    {
    case eTypeGene::A:
        cout <<"\tgen.typeGene = A";
        break;
    case eTypeGene::B:
        cout <<"\tgen.typeGene = B";
        break;
    case eTypeGene::C:
        cout <<"\tgen.typeGene = C";
        break;
    default:
        cout <<"\tgen.typeGene = NO";
    }
    cout <<endl
         <<"r0.numer = " << r0.numer         <<"\t\t\t" <<"r1.numer = " << r1.numer <<endl
         <<"r0.isExon = " << r0.isExon       <<"\t\t\t" <<"r1.isExon = " << r1.isExon <<endl
         <<"r0.isIntron = " << r0.isIntron   <<"\t\t\t" <<"r1.isIntron = " << r1.isIntron <<endl
         <<"r0.isThri = " << r0.isThri       <<"\t\t\t" <<"r1.isThri = " << r1.isThri <<endl
         <<"r0.isFive = " << r0.isFive       <<"\t\t\t" <<"r1.isFive = " << r1.isFive <<endl
         <<"r0.A = " << r0.A                 <<"\t\t\t" <<"r1.A = " << r1.A <<endl
         <<"r0.B = " << r0.B                 <<"\t\t\t" <<"r1.B = " << r1.B <<endl

         <<endl;
#endif

    bool rez=false;
    typeDel_Inv = eDeleciya::none;
   // cGloballRunable *_gr = cGloballRunable::Instance();
    switch(_gr->genesParam.mGenes[ geneIndex ].typeGene)
    {
    case eTypeGene::A:
        rez=detectDel_TypeGene_A(r0, r1);
        break;
    case eTypeGene::B:
        rez=detectDel_TypeGene_B(r0, r1);
        break;
    case eTypeGene::C:
        rez=true;
        typeDel_Inv = eDeleciya::del_3;
//        rez=detectDel_TypeGene_C(r0, r1);
        break;
    default:
        rez=false;
    }
#ifdef __test
    cout <<endl <<"Detect as: " <<Deleciya_toString(typeDel_Inv) <<"    rez=" <<rez <<endl;
#endif
    return rez;
}

bool cOneGene::detectDel_TypeGene_A(const cRSS &r0, const cRSS &r1)
{
    cGloballRunable *_gr = cGloballRunable::Instance();
    tCountExon &countExons = _gr->genesParam.mGenes[ geneIndex ].countExons;

    bool rez=false;
    if(r0.isExon && r1.isExon && (r0.numer == r1.numer) &&(r0.A >0) && (r1.B > 0))
    {
        rez=true;
        typeDel_Inv = eDeleciya::del_1a;
    }
    else if(r0.isExon && r1.isExon && (r0.numer != r1.numer) &&(r0.A > 0) && (r1.B > 0))
    {
        rez=true;
        typeDel_Inv = eDeleciya::del_1b;
    }
    else if((r0.isExon && r1.isIntron && (r0.A > 0)) || (r0.isIntron && r1.isExon && (r1.B > 0)))
    {
        rez=true;
        typeDel_Inv = eDeleciya::del_1c;
    }
    else if(   (((r0.isFive && r1.isExon ) || (r0.isThri && r1.isExon )) && (r1.B > 0))
               || (((r1.isFive && r0.isExon ) || (r1.isThri && r0.isExon )) && (r0.A > 0))
               || (r0.isExon && r1.isExon && (r0.numer == 1) && (r0.A == 0) && (r1.B > 0))
               || (r0.isExon && r1.isExon && (r1.numer == countExons) && (r0.A > 0) && (r1.B == 0))   )
    {
        rez=true;
        typeDel_Inv = eDeleciya::del_1d;
    }
    else if(   (r0.isIntron && r1.isIntron && (r0.numer != r1.numer))
               ||(r0.isExon && r1.isExon && (r0.numer < r1.numer) && (r0.numer != 1) && (r1.numer != countExons) && (r0.A == 0) && (r1.B == 0))
               ||(r0.isExon && r1.isExon && (r0.numer == r1.numer) && (r0.numer != 1) && (r0.numer != countExons) && (r0.A == 0) && (r1.B == 0))
               ||(r0.isExon && r1.isIntron && (r0.numer != 1) && ((r0.numer - r1.numer) != 1) && (r0.A == 0))
               ||(r1.isExon && r0.isIntron && (r1.numer != countExons) && ((r1.numer - r0.numer) != 0) && (r1.B == 0))
               ||(r0.isExon && r1.isExon && (r0.numer > r1.numer)&& ((r0.numer - r1.numer) !=1) && (r0.A == 0) && (r1.B == 0))   )
    {
        rez=true;
        typeDel_Inv = eDeleciya::del_1e;
    }
    else if(   ((r0.isFive && r1.isIntron) || (r0.isThri && r1.isIntron))
               ||((r1.isFive && r0.isIntron) || (r1.isThri && r0.isIntron))
               ||(((r0.isFive && r1.isExon) || (r0.isThri && r1.isExon)) && (r1.numer != countExons) && (r1.B == 0))
               ||(((r1.isFive && r0.isExon) || (r1.isThri && r0.isExon)) && (r0.numer != 1) && (r0.A == 0))
               ||(r1.isExon && r0.isExon && (r0.numer == 1) && (r1.numer != countExons) && (r0.A == 0) && (r1.B == 0))
               ||(r1.isExon && r0.isExon && (r0.numer != 1) && (r1.numer == countExons) && (r0.A == 0) && (r1.B == 0))
               ||(r0.isExon && r1.isIntron && (r0.numer == 1) && (r0.A == 0))
               ||(r1.isExon && r0.isIntron && (r1.numer == countExons) && (r1.B == 0))    )
    {
        rez=true;
        typeDel_Inv = eDeleciya::del_1f;
    }
    else if(   ((r0.isFive && r1.isThri) || (r1.isFive && r0.isThri))
               ||(r1.isExon && r0.isExon && (r0.numer == r1.numer) && (r0.numer == 1) && (r0.numer == countExons) && (r0.A == 0) && (r1.B == 0))
               ||(r1.isExon && r0.isExon && (r0.numer != r1.numer) && (r0.numer == 1) && (r1.numer == countExons) && (r0.A == 0) && (r1.B == 0))
               ||(r0.isExon && r1.isThri && (r0.numer == 1) && (r0.A == 0))
               ||(r1.isExon && r0.isFive && (r1.numer == countExons) && (r1.B == 0))    )
    {
        rez=true;
        typeDel_Inv = eDeleciya::del_1g;
    }
    else if(   ((r0.isFive && r1.isFive) || (r1.isThri && r0.isThri))
               ||(r1.isFive && r0.isExon && (r0.numer == 1) && (r0.A == 0))
               ||(r0.isThri && r1.isExon && (r1.numer == countExons) && (r1.B == 0))    )
    {
        rez=true;
        typeDel_Inv = eDeleciya::del_2a;
    }
    else if(   (r0.isIntron && r1.isIntron && (r0.numer == r1.numer))
               ||(r1.isExon && r0.isExon && (r0.numer > r1.numer) && ((r0.numer - r1.numer) == 1) && (r0.A == 0) && (r1.B == 0))
               ||(r0.isExon && r1.isIntron && ((r0.numer - r1.numer) == 1) && (r0.A == 0))
               ||(r1.isExon && r0.isIntron && ((r1.numer - r0.numer) == 0) && (r1.B == 0))    )
    {
        rez=true;
        typeDel_Inv = eDeleciya::del_2b;
    }
    return rez;
}

bool cOneGene::detectDel_TypeGene_B(const cRSS &r0, const cRSS &r1)
{
    cGloballRunable *_gr = cGloballRunable::Instance();
    tCountExon &countExons = _gr->genesParam.mGenes[ geneIndex ].countExons;

    bool rez=false;
    if(r0.isExon && r1.isExon && (r0.numer == r1.numer) &&(r0.A >0) && (r1.B > 0))
    {
        rez=true;
        typeDel_Inv = eDeleciya::del_1a;
    }
    else if(r0.isExon && r1.isExon && (r0.numer != r1.numer) &&(r0.A > 0) && (r1.B > 0))
    {
        rez=true;
        typeDel_Inv = eDeleciya::del_1b;
    }
    else if((r0.isExon && r1.isIntron && (r0.A > 0)) || (r0.isIntron && r1.isExon && (r1.B > 0)))
    {
        rez=true;
        typeDel_Inv = eDeleciya::del_1c;
    }
    else if(   (((r0.isFive && r1.isExon ) || (r0.isThri && r1.isExon )) && (r1.B > 0))
               || (((r1.isFive && r0.isExon ) || (r1.isThri && r0.isExon )) && (r0.A > 0))
               || (r0.isExon && r1.isExon && (r0.numer == countExons) && (r0.A == 0) && (r1.B > 0))
               || (r0.isExon && r1.isExon && (r1.numer == 1) && (r0.A > 0) && (r1.B == 0))   )
    {
        rez=true;
        typeDel_Inv = eDeleciya::del_1d;
    }
    else if(   (r0.isIntron && r1.isIntron && (r0.numer != r1.numer))
               ||(r0.isExon && r1.isExon && (r0.numer > r1.numer) && (r1.numer != 1) && (r0.numer != countExons) && (r0.A == 0) && (r1.B == 0))
               ||(r0.isExon && r1.isExon && (r0.numer == r1.numer) && (r0.numer != 1) && (r0.numer != countExons) && (r0.A == 0) && (r1.B == 0))
               ||(r0.isExon && r1.isIntron && (r0.numer != countExons) && ((r0.numer - r1.numer) != 0) && (r0.A == 0))
               ||(r1.isExon && r0.isIntron && (r1.numer != 1) && ((r1.numer - r0.numer) != 1) && (r1.B == 0))
               ||(r0.isExon && r1.isExon && (r0.numer < r1.numer)&& ((r0.numer - r1.numer) != -1) && (r0.A == 0) && (r1.B == 0)))
    {
        rez=true;
        typeDel_Inv = eDeleciya::del_1e;
    }
    else if(   ((r0.isFive && r1.isIntron) || (r0.isThri && r1.isIntron))
               ||((r1.isFive && r0.isIntron) || (r1.isThri && r0.isIntron))
               ||(((r0.isFive && r1.isExon) || (r0.isThri && r1.isExon)) && (r1.numer != 1) && (r1.B == 0))
               ||(((r1.isFive && r0.isExon) || (r1.isThri && r0.isExon)) && (r0.numer != countExons) && (r0.A == 0))
               ||(r1.isExon && r0.isExon && (r0.numer == countExons) && (r1.numer != 1) && (r0.A == 0) && (r1.B == 0))
               ||(r1.isExon && r0.isExon && (r0.numer != countExons) && (r1.numer == 1) && (r0.A == 0) && (r1.B == 0))
               ||(r0.isExon && r1.isIntron && (r0.numer == countExons) && (r0.A == 0))
               ||(r1.isExon && r0.isIntron && (r1.numer == 1) && (r1.B == 0))    )
    {
        rez=true;
        typeDel_Inv = eDeleciya::del_1f;
    }
    else if(   ((r0.isFive && r1.isThri) || (r1.isFive && r0.isThri))
               ||(r1.isExon && r0.isExon && (r0.numer == r1.numer) && (r0.numer == 1) && (r0.numer == countExons) && (r0.A == 0) && (r1.B == 0))
               ||(r1.isExon && r0.isExon && (r0.numer != r1.numer) && (r0.numer == countExons) && (r1.numer == 1) && (r0.A == 0) && (r1.B == 0))
               ||(r0.isExon && r1.isFive && (r0.numer == countExons) && (r0.A == 0))
               ||(r1.isExon && r0.isThri && (r1.numer == 1) && (r1.B == 0))    )
    {
        rez=true;
        typeDel_Inv = eDeleciya::del_1g;
    }
    else if(   ((r0.isFive && r1.isFive) || (r1.isThri && r0.isThri))
               ||(r1.isThri && r0.isExon && (r0.numer == countExons) && (r0.A == 0))
               ||(r0.isFive && r1.isExon && (r1.numer == 1) && (r1.B == 0))    )
    {
        rez=true;
        typeDel_Inv = eDeleciya::del_2a;
    }
    else if(   (r0.isIntron && r1.isIntron && (r0.numer == r1.numer))
               ||(r1.isExon && r0.isExon && (r0.numer < r1.numer) && ((r0.numer - r1.numer) == -1) && (r0.A == 0) && (r1.B == 0))
               ||(r0.isExon && r1.isIntron && ((r0.numer - r1.numer) == 0) && (r0.A == 0))
               ||(r1.isExon && r0.isIntron && ((r1.numer - r0.numer) == 1) && (r1.B == 0))    )
    {
        rez=true;
        typeDel_Inv = eDeleciya::del_2b;
    }
    return rez;
}

bool cOneGene::detectDel_TypeGene_C(const cRSS &r0, const cRSS &r1)
{
    bool rez = false;
    if(r0.loc_pos < r1.loc_pos)
    {
        rez=true;
        typeDel_Inv = eDeleciya::del_3;
    }

    return rez;
}


//---------------------------------------------------------------------------------------------------

bool cOneGene::detectInv_cikl(void)
{
    cGloballRunable *_gr = cGloballRunable::Instance();

    //cout <<"\t" <<"- detect INV. number of comparisons: ";

    ///определения типа Inv ->  rss12_0 сравниваем rss23_0
    //cout <<(rss12_0.size() * rss23_0.size()) <<" + ";
    size_t _size12 = rss12_0.size();
    size_t _size23 = rss23_0.size();
    for(size_t i = 0; i < _size12; i++)
    {
        for(size_t j = 0; j < _size23; j++)
        {
            bool rez_inv = false;
            rez_inv = detectInv_0(rss12_0[i], rss23_0[j]);
            if(!rez_inv)
            {
                rez_inv = detectInv_0(rss23_0[j],rss12_0[i]);
            }
            if(rez_inv)
            {
                tGenLen leght = labs(rss12_0[i].loc_pos - rss23_0[j].loc_pos);
#ifdef __test
    cout <<endl <<"leght: " <<leght
                <<" (leght < _gr->DI_min) = " <<(leght < _gr->DI_min)
                <<" (leght > _gr->DI_max) = " <<(leght > _gr->DI_max) <<endl;
#endif
                //условие на длину
                if(leght < _gr->DI_min)
                {
                    continue;
                }
                if(leght > _gr->DI_max)
                {
                    continue;
                }

                rss12_0[i].isInv = true;
                rss23_0[j].isInv = true;

                //оба уловия прошли, сохраняемся
                cDI_out _di;
                _di.leght = leght;
                _di.nomerRSS12 = i;
                _di.nomerRSS23 = j;
                _di.Loc_pos12 = rss12_0[i].loc_pos;
                _di.Loc_pos23 = rss23_0[j].loc_pos;
                _di.complement12 = false;
                _di.complement23 = false;

                di_out_push_back(typeDel_Inv, _di);
            }
        }
    }

    ///определения типа Inv ->  rss12_1 сравниваем rss23_1
    //cout <<(rss12_1.size() * rss23_1.size());
    _size12 = rss12_1.size();
    _size23 = rss23_1.size();
    for(size_t i = 0; i < _size12; i++)
    {
        for(size_t j = 0; j < _size23; j++)
        {
            bool rez_inv = false;
            rez_inv = detectInv_1(rss12_1[i], rss23_1[j]);
            if(!rez_inv)
            {
                rez_inv = detectInv_1(rss23_1[j],rss12_1[i]);
            }
            if(rez_inv)
            {
                tGenLen leght = labs(rss12_1[i].loc_pos - rss23_1[j].loc_pos);
                //условие на длину
                if(leght < _gr->DI_min)
                {
                    continue;
                }
                if(leght > _gr->DI_max)
                {
                    continue;
                }
                rss12_1[i].isInv = true;
                rss23_1[j].isInv = true;

                //оба уловия прошли, сохраняемся
                cDI_out _di;
                _di.leght = leght;
                _di.nomerRSS12 = i;
                _di.nomerRSS23 = j;
                _di.Loc_pos12 = rss12_1[i].loc_pos;
                _di.Loc_pos23 = rss23_1[j].loc_pos;
                _di.complement12 = true;
                _di.complement23 = true;

                di_out_push_back(typeDel_Inv, _di);
            }
        }
    }
    //cout <<endl;
    return true;
}

bool cOneGene::detectInv_0(const cRSS &r1, const cRSS &r2)
{
    cGloballRunable *_gr = cGloballRunable::Instance();
#ifdef __test
    cout <<endl
         <<"gen.countExons = " <<_gr->genesParam.mGenes[ geneIndex ].countExons <<"\tgen.complement = " <<_gr->genesParam.mGenes[ geneIndex ].complement;
    switch(_gr->genesParam.mGenes[ geneIndex ].typeGene)
    {
    case eTypeGene::A:
        cout <<"\tgen.typeGene = A";
        break;
    case eTypeGene::B:
        cout <<"\tgen.typeGene = B";
        break;
    case eTypeGene::C:
        cout <<"\tgen.typeGene = C";
        break;
    default:
        cout <<"\tgen.typeGene = NO";
    }
    cout <<endl
         <<"r1.complement = 0"               <<"\t\t" <<"r2.complement = 0 " <<endl
         <<"r1.numer = " << r1.numer         <<"\t\t\t" <<"r2.numer = " << r2.numer <<endl
         <<"r1.isExon = " << r1.isExon       <<"\t\t\t" <<"r2.isExon = " << r2.isExon <<endl
         <<"r1.isIntron = " << r1.isIntron   <<"\t\t\t" <<"r2.isIntron = " << r2.isIntron <<endl
         <<"r1.isThri = " << r1.isThri       <<"\t\t\t" <<"r2.isThri = " << r2.isThri <<endl
         <<"r1.isFive = " << r1.isFive       <<"\t\t\t" <<"r2.isFive = " << r2.isFive <<endl
         <<"r1.A = " << r1.A                 <<"\t\t\t\t" <<"r2.A = " << r2.A <<endl
         <<"r1.B = " << r1.B                 <<"\t\t\t\t" <<"r2.B = " << r2.B <<endl
         <<"r1.loc_pos = " << r1.loc_pos                 <<"\t\t" <<"r2.loc_pos = " << r2.loc_pos <<endl
         <<endl;
#endif
    bool rez=false;
    typeDel_Inv = eDeleciya::none;
    //cGloballRunable *_gr = cGloballRunable::Instance();
    switch(_gr->genesParam.mGenes[ geneIndex ].typeGene)
    {
    case eTypeGene::A:
        rez=detectInv_TypeGene_A_0(r1, r2);
        break;
    case eTypeGene::B:
        rez=detectInv_TypeGene_B_0(r1, r2);
        break;
    case eTypeGene::C:
        rez=true;
        typeDel_Inv = eDeleciya::inv_3;
        //rez=detectInv_TypeGene_C_0(r1, r2);
        break;
    default:
        rez=false;
    }
#ifdef __test
    cout <<endl <<"Detect as(0): " <<Deleciya_toString(typeDel_Inv) <<"    rez=" <<rez <<endl;
#endif
    return rez;
}

bool cOneGene::detectInv_TypeGene_A_0(const cRSS &r1, const cRSS &r2)
{
//    cGloballRunable *_gr = cGloballRunable::Instance();
//    tCountExon &countExons = _gr->genesParam.mGenes[ geneIndex ].countExons;
    bool rez=false;
    if(r1.isExon && r2.isExon && (r1.numer == r2.numer) &&(r1.A >0) && (r2.A > 0))
    {
        rez=true;
        typeDel_Inv = eDeleciya::inv_1a;
    }
    else if(r1.isExon && r2.isExon && (r1.numer != r2.numer) &&(r1.A >0) && (r2.A > 0))
    {
        rez=true;
        typeDel_Inv = eDeleciya::inv_1b;
    }
    else if(r1.isExon && r2.isIntron && (r1.A > 0))
    {
        rez=true;
        typeDel_Inv = eDeleciya::inv_1c;
    }
    else if(   (((r1.isFive && r2.isExon ) || (r1.isThri && r2.isExon )) && (r2.A > 0))
               || (r1.isExon && r2.isExon && (r1.numer == 1) && (r1.A == 0) && (r2.A > 0))   )
    {
        rez=true;
        typeDel_Inv = eDeleciya::inv_1d;
    }
    else if(   (r1.isIntron && r2.isIntron && (r1.numer != r2.numer))
               ||(r1.isExon && r2.isExon && (r1.numer != r2.numer) && (r1.numer != 1)&& (r2.numer != 1) && (r1.A == 0) && (r2.A == 0))
               ||(r1.isExon && r2.isIntron && (r1.numer != 1) && ((r1.numer - r2.numer) != 1) && (r1.A == 0))   )
    {
        rez=true;
        typeDel_Inv = eDeleciya::inv_1e;
    }
    else if(   ((r1.isFive && r2.isIntron) || (r1.isThri && r2.isIntron))
               ||(((r1.isFive && r2.isExon) || (r1.isThri && r2.isExon)) && (r2.numer != 1) && (r2.A == 0))
               ||(r1.isExon && r2.isExon && ((r1.numer - r2.numer) != 0)  && (r1.numer == 1) && (r1.A == 0) && (r2.A == 0))
               ||(r1.isExon && r2.isIntron && (r1.numer == 1) && (r1.A == 0))    )
    {
        rez=true;
        typeDel_Inv = eDeleciya::inv_1f;
    }
    else if(   ((r1.isFive && r2.isThri))
               ||(r1.isExon && r2.isThri && (r1.numer == 1) && (r1.A == 0))  )
    {
        rez=true;
        typeDel_Inv = eDeleciya::inv_1g;
    }
    else if(   ((r1.isFive && r2.isFive) || (r1.isThri && r2.isThri))
               ||(r1.isFive && r2.isExon && (r2.numer == 1) && (r2.A == 0))    )
    {
        rez=true;
        typeDel_Inv = eDeleciya::inv_2a;
    }
    else if(   (r1.isIntron && r2.isIntron )
               ||(r1.isIntron && r2.isExon && ((r2.numer - r1.numer) == 1) && (r2.A == 0))    )
    {
        rez=true;
        typeDel_Inv = eDeleciya::inv_2b;
    }
    return rez;
}

bool cOneGene::detectInv_TypeGene_B_0(const cRSS &r1, const cRSS &r2)
{
    cGloballRunable *_gr = cGloballRunable::Instance();
    tCountExon &countExons = _gr->genesParam.mGenes[ geneIndex ].countExons;
    bool rez=false;
    if(r1.isExon && r2.isExon && (r1.numer == r2.numer) &&(r1.A >0) && (r2.A > 0))
    {
        rez=true;
        typeDel_Inv = eDeleciya::inv_1a;
    }
    else if(r1.isExon && r2.isExon && (r1.numer != r2.numer) &&(r1.A >0) && (r2.A > 0))
    {
        rez=true;
        typeDel_Inv = eDeleciya::inv_1b;
    }
    else if(r1.isExon && r2.isIntron && (r1.A > 0))
    {
        rez=true;
        typeDel_Inv = eDeleciya::inv_1c;
    }
    else if(   (((r1.isFive && r2.isExon ) || (r1.isThri && r2.isExon )) && (r2.A > 0))
               || (r1.isExon && r2.isExon && (r1.numer == countExons) && (r1.A > 0) && (r2.A == 0))   )
    {
        rez=true;
        typeDel_Inv = eDeleciya::inv_1d;
    }
    else if(   (r1.isIntron && r2.isIntron && (r1.numer != r2.numer))
               ||(r1.isExon && r2.isExon && (r1.numer != r2.numer) && (r1.numer != countExons)&& (r2.numer != countExons) && (r1.A == 0) && (r2.A == 0))
               ||(r1.isExon && r2.isIntron && (r1.numer != countExons) && ((r1.numer - r2.numer) != 0) && (r1.A == 0))   )
    {
        rez=true;
        typeDel_Inv = eDeleciya::inv_1e;
    }
    else if(   ((r1.isFive && r2.isIntron) || (r1.isThri && r2.isIntron))
               ||(((r1.isFive && r2.isExon) || (r1.isThri && r2.isExon)) && (r2.numer != countExons) && (r2.A == 0))
               ||(r1.isExon && r2.isExon && ((r1.numer - r2.numer) != 0)  && (r1.numer == countExons) && (r1.A == 0) && (r2.A == 0))
               ||(r1.isExon && r2.isIntron && (r1.numer == countExons) && (r1.A == 0))    )
    {
        rez=true;
        typeDel_Inv = eDeleciya::inv_1f;
    }
    else if(   ((r1.isFive && r2.isThri))
               ||(r1.isExon && r2.isFive && (r1.numer == countExons) && (r1.A == 0))  )
    {
        rez=true;
        typeDel_Inv = eDeleciya::inv_1g;
    }
    else if(   ((r1.isFive && r2.isFive) || (r1.isThri && r2.isThri))
               ||(r1.isThri && r2.isExon && (r2.numer == countExons) && (r2.A == 0))    )
    {
        rez=true;
        typeDel_Inv = eDeleciya::inv_2a;
    }
    else if(   (r1.isIntron && r2.isIntron )
               ||(r1.isIntron && r2.isExon && ((r2.numer - r1.numer) == 0) && (r2.A == 0))    )
    {
        rez=true;
        typeDel_Inv = eDeleciya::inv_2b;
    }
    return rez;
}

bool cOneGene::detectInv_TypeGene_C_0(const cRSS &r1, const cRSS &r2)
{
    bool rez = false;
    if(r1.loc_pos < r2.loc_pos)
    {
        rez=true;
        typeDel_Inv = eDeleciya::inv_3;
    }
    return rez;
}


bool cOneGene::detectInv_1(const cRSS &r1, const cRSS &r2)
{
    cGloballRunable *_gr = cGloballRunable::Instance();
#ifdef __test

    cout <<endl
         <<"gen.countExons = " <<_gr->genesParam.mGenes[ geneIndex ].countExons <<"\tgen.complement = " <<_gr->genesParam.mGenes[ geneIndex ].complement;
    switch(_gr->genesParam.mGenes[ geneIndex ].typeGene)
    {
    case eTypeGene::A:
        cout <<"\tgen.typeGene = A";
        break;
    case eTypeGene::B:
        cout <<"\tgen.typeGene = B";
        break;
    case eTypeGene::C:
        cout <<"\tgen.typeGene = C";
        break;
    default:
        cout <<"\tgen.typeGene = NO";
    }
    cout <<endl
         <<"r1.complement = 1"               <<"\t\t\t" <<"r2.complement = 1 " <<endl
         <<"r1.numer = " << r1.numer         <<"\t\t\t" <<"r2.numer = " << r2.numer <<endl
         <<"r1.isExon = " << r1.isExon       <<"\t\t\t" <<"r2.isExon = " << r2.isExon <<endl
         <<"r1.isIntron = " << r1.isIntron   <<"\t\t\t" <<"r2.isIntron = " << r2.isIntron <<endl
         <<"r1.isThri = " << r1.isThri       <<"\t\t\t" <<"r2.isThri = " << r2.isThri <<endl
         <<"r1.isFive = " << r1.isFive       <<"\t\t\t" <<"r2.isFive = " << r2.isFive <<endl
         <<"r1.A = " << r1.A                 <<"\t\t\t\t" <<"r2.A = " << r2.A <<endl
         <<"r1.B = " << r1.B                 <<"\t\t\t\t" <<"r2.B = " << r2.B <<endl
         <<endl;
#endif
    bool rez=false;
    typeDel_Inv = eDeleciya::none;
   // cGloballRunable *_gr = cGloballRunable::Instance();
    switch(_gr->genesParam.mGenes[ geneIndex ].typeGene)
    {
    case eTypeGene::A:
        rez=detectInv_TypeGene_A_1(r1, r2);
        break;
    case eTypeGene::B:
        rez=detectInv_TypeGene_B_1(r1, r2);
        break;
    case eTypeGene::C:
        rez=true;
        typeDel_Inv = eDeleciya::inv_3;
        //rez=detectInv_TypeGene_C_1(r1, r2);
        break;
    default:
        rez=false;
    }
#ifdef __test
    cout <<endl <<"Detect as(1): " <<Deleciya_toString(typeDel_Inv) <<"    rez=" <<rez <<endl;
#endif
    return rez;
}

bool cOneGene::detectInv_TypeGene_A_1(const cRSS &r1, const cRSS &r2)
{
    cGloballRunable *_gr = cGloballRunable::Instance();
    tCountExon &countExons = _gr->genesParam.mGenes[ geneIndex ].countExons;
    bool rez=false;
    if(r1.isExon && r2.isExon && (r1.numer == r2.numer) &&(r1.B >0) && (r2.B > 0))
    {
        rez=true;
        typeDel_Inv = eDeleciya::inv_1a;
    }
    else if(r1.isExon && r2.isExon && (r1.numer != r2.numer) &&(r1.B >0) && (r2.B > 0))
    {
        rez=true;
        typeDel_Inv = eDeleciya::inv_1b;
    }
    else if(r1.isExon && r2.isIntron && (r1.B > 0))
    {
        rez=true;
        typeDel_Inv = eDeleciya::inv_1c;
    }
    else if(   (((r1.isFive && r2.isExon ) || (r1.isThri && r2.isExon )) && (r2.B > 0))
               || (r1.isExon && r2.isExon && (r1.numer == countExons) && (r1.B == 0) && (r2.B > 0))   )
    {
        rez=true;
        typeDel_Inv = eDeleciya::inv_1d;
    }
    else if(   (r1.isIntron && r2.isIntron && (r1.numer != r2.numer))
               ||(r1.isExon && r2.isExon && (r1.numer != r2.numer) && (r1.numer != countExons)&& (r2.numer != countExons) && (r1.B == 0) && (r2.B == 0))
               ||(r1.isExon && r2.isIntron && (r1.numer != countExons) && ((r1.numer - r2.numer) != 0) && (r1.B == 0))   )
    {
        rez=true;
        typeDel_Inv = eDeleciya::inv_1e;
    }
    else if(   ((r1.isFive && r2.isIntron) || (r1.isThri && r2.isIntron))
               ||(((r1.isFive && r2.isExon) || (r1.isThri && r2.isExon)) && (r2.numer != countExons) && (r2.B == 0))
               ||(r1.isExon && r2.isExon && ((r1.numer - r2.numer) != 0)  && (r1.numer == countExons) && (r1.B == 0) && (r2.B == 0))
               ||(r1.isExon && r2.isIntron && (r1.numer == countExons) && (r1.B == 0))    )
    {
        rez=true;
        typeDel_Inv = eDeleciya::inv_1f;
    }
    else if(   ((r1.isFive && r2.isThri))
               ||(r1.isExon && r2.isFive && (r1.numer == countExons) && (r1.B == 0))  )
    {
        rez=true;
        typeDel_Inv = eDeleciya::inv_1g;
    }
    else if(   ((r1.isFive && r2.isFive) || (r1.isThri && r2.isThri))
               ||(r1.isThri && r2.isExon && (r2.numer == countExons) && (r2.B == 0))    )
    {
        rez=true;
        typeDel_Inv = eDeleciya::inv_2a;
    }
    else if(   (r1.isIntron && r2.isIntron )
               ||(r1.isIntron && r2.isExon && ((r2.numer - r1.numer) == 0) && (r2.B == 0))    )
    {
        rez=true;
        typeDel_Inv = eDeleciya::inv_2b;
    }
    return rez;
}

bool cOneGene::detectInv_TypeGene_B_1(const cRSS &r1, const cRSS &r2)
{
//    cGloballRunable *_gr = cGloballRunable::Instance();
//    tCountExon &countExons = _gr->mGen->gen.countExons;
    bool rez=false;
    if(r1.isExon && r2.isExon && (r1.numer == r2.numer) &&(r1.B >0) && (r2.B > 0))
    {
        rez=true;
        typeDel_Inv = eDeleciya::inv_1a;
    }
    else if(r1.isExon && r2.isExon && (r1.numer != r2.numer) &&(r1.B >0) && (r2.B > 0))
    {
        rez=true;
        typeDel_Inv = eDeleciya::inv_1b;
    }
    else if(r1.isExon && r2.isIntron && (r1.B > 0))
    {
        rez=true;
        typeDel_Inv = eDeleciya::inv_1c;
    }
    else if(   (((r1.isFive && r2.isExon ) || (r1.isThri && r2.isExon )) && (r2.B > 0))
               || (r1.isExon && r2.isExon && (r1.numer == 1) && (r1.B == 0) && (r2.B > 0))   )
    {
        rez=true;
        typeDel_Inv = eDeleciya::inv_1d;
    }
    else if(   (r1.isIntron && r2.isIntron && (r1.numer != r2.numer))
               ||(r1.isExon && r2.isExon && (r1.numer != r2.numer) && (r1.numer != 1)&& (r2.numer != 1) && (r1.B == 0) && (r2.B == 0))
               ||(r1.isExon && r2.isIntron && (r1.numer != 1) && ((r1.numer - r2.numer) != 1) && (r1.B == 0))   )
    {
        rez=true;
        typeDel_Inv = eDeleciya::inv_1e;
    }
    else if(   ((r1.isFive && r2.isIntron) || (r1.isThri && r2.isIntron))
               ||(((r1.isFive && r2.isExon) || (r1.isThri && r2.isExon)) && (r2.numer != 1) && (r2.B == 0))
               ||(r1.isExon && r2.isExon && ((r1.numer - r2.numer) != 0)  && (r1.numer == 1) && (r1.B == 0) && (r2.B == 0))
               ||(r1.isExon && r2.isIntron && (r1.numer == 1) && (r1.B == 0))    )
    {
        rez=true;
        typeDel_Inv = eDeleciya::inv_1f;
    }
    else if(   ((r1.isFive && r2.isThri))
               ||(r1.isExon && r2.isThri && (r1.numer == 1) && (r1.B == 0))  )
    {
        rez=true;
        typeDel_Inv = eDeleciya::inv_1g;
    }
    else if(   ((r1.isFive && r2.isFive) || (r1.isThri && r2.isThri))
               ||(r1.isFive && r2.isExon && (r2.numer == 1) && (r2.B == 0))    )
    {
        rez=true;
        typeDel_Inv = eDeleciya::inv_2a;
    }
    else if(   (r1.isIntron && r2.isIntron )
               ||(r1.isIntron && r2.isExon && ((r2.numer - r1.numer) == 1) && (r2.B == 0))    )
    {
        rez=true;
        typeDel_Inv = eDeleciya::inv_2b;
    }

    return rez;
}

bool cOneGene::detectInv_TypeGene_C_1(const cRSS &r1, const cRSS &r2)
{
    bool rez = false;
    if(r1.loc_pos < r2.loc_pos)
    {
        rez=true;
        typeDel_Inv = eDeleciya::inv_3;
    }
    return rez;
}



void cOneGene::detectDupl(void)
{
    cout <<"Detect dupl" <<endl;
    cGloballRunable *_gr = cGloballRunable::Instance();
    vector<cDI_out*> index_del;
    vector<cDI_out*> index_inv;
    unordered_set<uint8_t> workedINV;

    // проверить DEL
    for(uint8_t del = static_cast<uint8_t>(eDeleciya::del_1a); del < static_cast<uint8_t>(eDeleciya::del_end); del++)
    {
        eDeleciya _Del = static_cast<eDeleciya>(del);
        unordered_map<uint8_t, vector<cDI_out> >::iterator it = DI_out.find(del);
        if(it != DI_out.end())
        {
            vector<cDI_out> &vDI = it->second;
            //найти соответствующий INV
            eDeleciya _Inv = static_cast<eDeleciya>(del + 20);
            unordered_map<uint8_t, vector<cDI_out> >::iterator it1 = DI_out.find(static_cast<uint8_t>(_Inv));

            bool isDelEqvInv = (it1 != DI_out.end()); //т.у. нашли
            if(isDelEqvInv) //нашли
            {
                     // пометить как провереный
                    workedINV.insert(static_cast<uint8_t>(_Inv));
                vector<cDI_out> &vDI1 = it1->second;
                cout <<"   worked Deleciya [" <<Deleciya_toString(_Del)  <<"], count rec = " <<vDI.size();
                _gr->mDupl->convertVectorAndFiltered_del(_Del, vDI, index_del);
                cout <<"        + Deleciya [" <<Deleciya_toString(_Inv)  <<"], count rec = " <<vDI1.size();
                _gr->mDupl->convertVectorAndFiltered_inv(_Inv, vDI1, index_inv);
                if(! _gr->mDupl->calculateDublInGene(index_del, index_inv, _Del, _Inv))
                    _gr->mDupl->calculateDublInGene_inv_AND_del_inv(_Inv, index_inv, true);
            }
            else //не нашли, ищем только дел
            {
                cout <<"   worked Deleciya [" <<Deleciya_toString(_Del)  <<"], count rec = " <<vDI.size() <<endl;
                _gr->mDupl->convertVectorAndFiltered_del(_Del, vDI, index_del);
                _gr->mDupl->calculateDublInGene_del_AND_del_inv(_Del, index_del, true);

            }
        }
    }

    //обработать те INV которых еще не обрабатывали
    for(uint8_t inv = static_cast<uint8_t>(eDeleciya::inv_1a); inv < static_cast<uint8_t>(eDeleciya::inv_end); inv++)
    {
        eDeleciya _Inv = static_cast<eDeleciya>(inv);

        // проверка на выполненую проверку
        if(workedINV.find(inv) != workedINV.end())
        {
            continue;
        }

        // найти такой INV
        unordered_map<uint8_t, vector<cDI_out> >::iterator it = DI_out.find(inv);
        if(it != DI_out.end())
        {
            //выполнить поиск
            vector<cDI_out> &vDI = it->second;
            cout <<"   worked Deleciya [" <<Deleciya_toString(_Inv)  <<"], count rec = " <<vDI.size();

            _gr->mDupl->convertVectorAndFiltered_inv(_Inv, vDI, index_inv);
            _gr->mDupl->calculateDublInGene_inv_AND_del_inv(_Inv, index_inv, true);
        }
    }
    //сохранить результат
    cOutResult::outFile_tmpDI_index();
}



// обработка одного локуса
bool cOneGene::LocusDublWork()
{
    file.clear();
    locus.clear();
    cGloballRunable *_gr = cGloballRunable::Instance();
    _gr->mDupl->calculateDublInLocus();
    cOutResult::outFile_DI();
    return true;
}





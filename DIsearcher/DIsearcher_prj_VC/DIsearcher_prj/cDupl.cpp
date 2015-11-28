#include "cDupl.h"
#include "cStatistic.h"
#include "cDIindex.h"
#include "cGloballRunable.h"
#include "cOutResult.h"

//#define __test


void cDupl::convertVectorAndFiltered_del(const eDeleciya &del, vector<cDI_out> &vDI, vector<cDI_out*> &index)
{
    if (vDI.empty()) return;
    size_t _size = vDI.size();
    cDI_out *di = &vDI[0];
    sGenTable gt;
    cGloballRunable *_gr = cGloballRunable::Instance();

    //вектор для хранения проверяемых индексов
    index.clear();

    if(_size > _gr->Max_count_dupl) // применить условие
    {
        //найти исключения исключения
        cout <<". Filtered...";
        index.reserve(_size/4);

        size_t &fileIndex = _gr->mGen->fileIndex;
        tContigNumber &locusVal = _gr->mGen->locusVal;

        //выписать индексы подлежащие проверке
        for(size_t i = 0; i < _size ; i++)
        {
            cDI_out &di1 = *(di+i);
            //условие включения
            if(_gr->genesParam.chekOneDIonNeedFindDubl(fileIndex, locusVal, di1.Loc_pos12, di1.Loc_pos23))
            {
                index.push_back(di+i);
            }
            else
            {
            //ненашли, добавить в статистику, они некогда небудут проверятся
                gt.add(del, di1.leght);
                gt.add(eDeleciya::del, di1.leght);
                gt.add(eDeleciya::del_or_inv, di1.leght);
                _gr->mStatistic->Genom_Del_Inv++;
                _gr->mStatistic->Genom_Del_InvLen += di1.leght;
                _gr->mStatistic->Genom_Del++;
                _gr->mStatistic->Genom_DelLen += di1.leght;

            }
        }
        _gr->mStatistic->update_GenTable(_gr->mGen->geneIndex, gt);
        cout <<"      Remained " <<index.size() <<endl;
    }
    else
    {
        //выписать индексы подлежащие проверке
        index.reserve(_size);
        for(size_t i = 0; i < _size ; i++)
        {
            index.push_back(di+i);
        }
        cout <<endl;
    }
}

void cDupl::convertVectorAndFiltered_inv(const eDeleciya &inv, vector<cDI_out> &vDI, vector<cDI_out*> &index)
{
    if (vDI.empty()) return ;
    size_t _size = vDI.size();
    sGenTable gt;
    cDI_out *di = &vDI[0];
    cGloballRunable *_gr = cGloballRunable::Instance();

    //вектор для хранения проверяемых индексов
    index.clear();
#ifdef __test
    cout <<endl <<"_gr->Max_count_dupl " <<_gr->Max_count_dupl <<endl;
#endif
    if(_size > _gr->Max_count_dupl) // применить условие
    {
        //найти исключения исключения
        cout <<". Filtered...";
        index.reserve(_size/4);

        size_t &fileIndex = _gr->mGen->fileIndex;
        tContigNumber &locusVal = _gr->mGen->locusVal;

        //выписать индексы подлежащие проверке
        for(size_t i = 0; i < _size ; i++)
        {
            cDI_out &di1 = *(di+i);
            //условие включения
            if(_gr->genesParam.chekOneDIonNeedFindDubl(fileIndex, locusVal, di1.Loc_pos12, di1.Loc_pos23))
            {
                index.push_back(di+i);
    #ifdef __test
    cout <<endl <<"push_back " <<i <<endl;
#endif
            }
            else
            {
            //ненашли, добавить в статистику, они некогда небудут проверятся
                gt.add(inv, di1.leght);
                gt.add(eDeleciya::inv, di1.leght);
                gt.add(eDeleciya::del_or_inv, di1.leght);
                _gr->mStatistic->Genom_Del_Inv++;
                _gr->mStatistic->Genom_Del_InvLen += di1.leght;
                _gr->mStatistic->Genom_Inv++;
                _gr->mStatistic->Genom_InvLen += di1.leght;
    #ifdef __test
    cout <<endl <<"add stat " <<i <<endl;
#endif
            }
        }
        _gr->mStatistic->update_GenTable(_gr->mGen->geneIndex, gt);
        cout <<"      Remained " <<index.size() <<endl;
    }
    else
    {
        //выписать индексы подлежащие проверке
        index.reserve(_size);
        for(size_t i = 0; i < _size ; i++)
        {
            index.push_back(di+i);
        }
        cout <<endl;
    }
}




bool cDupl::calculateDublInGene_del_AND_del_inv(const eDeleciya &del, vector<cDI_out*> &index, bool isAddDelInvStat)
{
#ifdef __test
    cout <<endl <<"calculateDublInGene_del_AND_del_inv "  <<endl;
#endif
    if (index.empty()) return false;
    CountDuplInOneGen = 0;
    sGenTable gt;
    cGloballRunable *_gr = cGloballRunable::Instance();
    size_t index_size = index.size();

    cDI_out **di = &index[0];

    for(size_t i = 0; i < index_size; i++)
    {
        // *(di+i) == di[i]
        cDI_out &di1 = *(*(di+i));

        //cDI_out &di1 = *(index[i]);
        for(size_t j = i+1; j < index_size ; j++)
        {
            cDI_out &di2 = *(*(di+j));
            if(di2.isDupl)   //если есть, значит уже проверяли
            {
                continue;   // пропускаем
            }
            if(CountDuplInOneGen > MaxDuplInOneGen) //прервать если достигли максимума
            {
                CountDuplInOneGen = 0;
                break;
            }
            if(!ChekDubl_del(di1, di2))
            {
                continue;
            }
            CountDuplInOneGen++;
            di2.isDupl = true;

            if(di1.duplDel ==0)
            {
                di1.isDupl = true;
                di1.duplDel = ++c_duplDel;
                gt.add(del, di1.leght);
                gt.add(eDeleciya::del, di1.leght);
            }
            di2.duplDel = di1.duplDel;

            if(di1.duplDelInv ==0 )
            {
                di1.isDupl = true;
                di1.duplDelInv = ++c_duplDelInv;
                gt.add(eDeleciya::del_or_inv, di1.leght);
            }
            di2.duplDelInv = di1.duplDelInv;

        } //for j
        //ненашли, добавить в статистику, они некогда небудут проверятся
        if(!di1.isDupl)
        {
            gt.add(del, di1.leght);
            gt.add(eDeleciya::del, di1.leght);
            if(isAddDelInvStat) // соответствуещего INV нет, значит DelInv искаться не будет
            {                // иначе решение принимается поже
                _gr->mStatistic->Genom_Del++;
                _gr->mStatistic->Genom_DelLen += di1.leght;
                gt.add(eDeleciya::del_or_inv, di1.leght);
                _gr->mStatistic->Genom_Del_Inv++;
                _gr->mStatistic->Genom_Del_InvLen += di1.leght;

            }
        }
    }//for i

    _gr->mStatistic->update_GenTable(_gr->mGen->geneIndex, gt);

    return true;
}

bool cDupl::calculateDublInGene_inv_AND_del_inv(const eDeleciya &inv, vector<cDI_out*> &index, bool isAddDelInvStat)
{
#ifdef __test
    cout <<endl <<"calculateDublInGene_inv_AND_del_inv "  <<endl;
#endif
    if (index.empty()) return false;

    CountDuplInOneGen = 0;
    sGenTable gt;
    cGloballRunable *_gr = cGloballRunable::Instance();
    cDI_out **di = &index[0];

    size_t index_size = index.size();
    for(size_t i = 0; i < index_size; i++)
    {
        cDI_out &di1 = *(*(di+i));

        for(size_t j = i+1; j < index_size; j++)
        {
            cDI_out &di2 = *(*(di+j));

            if(di2.isDupl)   //если есть, значит уже проверяли
            {
                continue;   // пропускаем
            }
            if(CountDuplInOneGen > MaxDuplInOneGen) //прервать если достигли максимума
            {
                CountDuplInOneGen = 0;
                break;
            }
            if(!ChekDubl_inv(di1, di2))
            {
                continue;
            }

            di2.isDupl = true;
            CountDuplInOneGen++;

            if(di1.duplInv ==0)
            {
                di1.duplInv = ++c_duplInv;
                di1.isDupl = true;
                gt.add(inv, di1.leght);
                gt.add(eDeleciya::inv, di1.leght);
            }
            di2.duplInv = di1.duplInv;

            if(di1.duplDelInv == 0 )
            {
                di1.isDupl = true;
                di1.duplDelInv = ++c_duplDelInv;

                if(isAddDelInvStat) // соответствуещего INV нет, значит DelInv искаться не будет
                {               // иначе решение принимается поже
                    gt.add(eDeleciya::del_or_inv, di1.leght);
                }
            }
            di2.duplDelInv = di1.duplDelInv;

        } // for j
        //ненашли, добавить в статистику
        if(di1.duplInv ==0)
        {
            gt.add(inv, di1.leght);
            gt.add(eDeleciya::inv, di1.leght);
            if(isAddDelInvStat) // соответствуещего INV нет, значит DelInv искаться не будет
            {                // иначе решение принимается поже
                _gr->mStatistic->Genom_Inv++;
                _gr->mStatistic->Genom_InvLen += di1.leght;

                gt.add(eDeleciya::del_or_inv, di1.leght);
                _gr->mStatistic->Genom_Del_Inv++;
                _gr->mStatistic->Genom_Del_InvLen += di1.leght;

            }
        }

    } //for i
    _gr->mStatistic->update_GenTable(_gr->mGen->geneIndex, gt);
    return true;
}

bool cDupl::calculateDublInGene_del_inv(vector<cDI_out*> &index_del, vector<cDI_out*> &index_inv)
{
    #ifdef __test
    cout <<endl <<"calculateDublInGene_del_inv "  <<endl;
#endif
    if (index_del.empty()) return false;
    if (index_inv.empty()) return false;

    CountDuplInOneGen = 0;
    sGenTable gt;
    unordered_set<size_t> ind;

    cGloballRunable *_gr = cGloballRunable::Instance();
    size_t index_size_del = index_del.size();
    size_t index_size_inv = index_inv.size();
    cout <<(index_size_inv + index_size_del) <<" rec"  <<endl;

    cDI_out **di_del = &index_del[0];
    cDI_out **di_inv = &index_inv[0];

    for(size_t i = 0; i < index_size_del; i++)
    {
        //cDI_out &di1 = *(index_del[i]);
        cDI_out &di1 = *(*(di_del+i));

        for(size_t j = 0; j < index_size_inv; j++)
        {
            cDI_out &di2 = *(*(di_inv+j));

            if((di2.duplDelInv) && ( di1.duplDelInv == di2.duplDelInv))   //если есть, значит уже проверяли
            {
                continue;   // пропускаем
            }
            if(CountDuplInOneGen > MaxDuplInOneGen) //прервать если достигли максимума
            {
                CountDuplInOneGen = 0;
                break;
            }
            if(!ChekDubl_del_inv(di1, di2))
            {
                continue;
            }

            if(di1.duplDelInv == 0)
            {
                di1.duplDelInv = ++c_duplDelInv;
                di1.isDupl = true;
                //доэтого небыло, а теперь есть
                gt.add(eDeleciya::del_or_inv, di1.leght);
            }
            di2.isDupl = true;
            ind.insert(j);
            CountDuplInOneGen++;
            di2.duplDelInv = di1.duplDelInv;
        } // for j
        //ненашли, добавить в статистику
        if(di1.duplDelInv ==0)
        {
            gt.add(eDeleciya::del_or_inv, di1.leght);
            _gr->mStatistic->Genom_Del_Inv++;
            _gr->mStatistic->Genom_Del_InvLen += di1.leght;

        }

    } //for i


    //статистика по INV
    for(size_t i = 0; i < index_size_inv; i++)
    {
        cDI_out &di1 = *(*(di_inv +i));
        //которые не найдены, и проверятся не будут
        if(di1.duplDelInv == 0)
        {
            gt.add(eDeleciya::del_or_inv, di1.leght);
            _gr->mStatistic->Genom_Del_Inv++;
            _gr->mStatistic->Genom_Del_InvLen += di1.leght;
        }
        else
        {
            //значение есть, проверяем в перечне
            if (ind.insert(i).second) //такого нет
            {
                gt.add(eDeleciya::del_or_inv, di1.leght);
            }
        }
    } //for i

    _gr->mStatistic->update_GenTable(_gr->mGen->geneIndex, gt);
    return true;
}


bool cDupl::calculateDublInGene(vector<cDI_out*> &index_del, vector<cDI_out*> &index_inv, const eDeleciya &del, const eDeleciya &inv)
{
#ifdef __test
    cout <<endl <<"index_del.empty() "  <<index_del.empty() <<"  index_inv.empty() " <<index_inv.empty() <<endl;
    cout <<endl <<"calculateDublInGene "  <<endl;
#endif
    if (index_del.empty()) return false;
    if (index_inv.empty()) return false;

    CountDuplInOneGen = 0;
    sGenTable gt;
    unordered_set<size_t> ind;

    cGloballRunable *_gr = cGloballRunable::Instance();
    size_t index_size_del = index_del.size();
    size_t index_size_inv = index_inv.size();
    cout <<"all "<<(index_size_inv + index_size_del) <<" rec"  <<endl;

    cDI_out **di_del = &index_del[0];
    cDI_out **di_inv = &index_inv[0];

    for(size_t i = 0; i < index_size_del; i++)
    {
        cDI_out &di1 = *(*(di_del+i));
        for(size_t j = i+1; j < index_size_del; j++)
        {
            cDI_out &di2 = *(*(di_del+j));
            if(di2.duplDel !=0)   //если есть, значит уже проверяли
            {
                continue;   // пропускаем
            }
            if(CountDuplInOneGen > MaxDuplInOneGen) //прервать если достигли максимума
            {
                CountDuplInOneGen = 0;
                break;
            }
            if(!ChekDubl_del(di1, di2))
            {
                continue;
            }
            CountDuplInOneGen++;
            di2.isDupl = true;

            if(di1.duplDel ==0)
            {
                di1.isDupl = true;
                di1.duplDel = ++c_duplDel;
                gt.add(del, di1.leght);
                gt.add(eDeleciya::del, di1.leght);
            }
            di2.duplDel = di1.duplDel;

            if(di1.duplDelInv ==0 )
            {
                di1.isDupl = true;
                di1.duplDelInv = ++c_duplDelInv;
                gt.add(eDeleciya::del_or_inv, di1.leght);
            }
            di2.duplDelInv = di1.duplDelInv;
        }

        for(size_t j = 0; j < index_size_inv; j++)
        {
            cDI_out &di2 = *(*(di_inv+j));
            if((di2.duplDelInv !=0))   //если есть, значит уже проверяли
            {
                continue;   // пропускаем
            }
            if(CountDuplInOneGen > MaxDuplInOneGen) //прервать если достигли максимума
            {
                CountDuplInOneGen = 0;
                break;
            }
            if(!ChekDubl_del_inv(di1, di2))
            {
                continue;
            }
            if(di1.duplDelInv == 0)
            {
                di1.duplDelInv = ++c_duplDelInv;
                di1.isDupl = true;
                gt.add(eDeleciya::del_or_inv, di1.leght);
            }
            di2.isDupl = true;
            ind.insert(j);
            CountDuplInOneGen++;
            di2.duplDelInv = di1.duplDelInv;
        } // for j


        //ненашли, добавить в статистику
        if(di1.duplDelInv == 0)
        {
            gt.add(eDeleciya::del_or_inv, di1.leght);
#ifdef __test
    cout <<endl <<"1 "  <<endl;
#endif
        }

        if(di1.duplDel == 0)
        {
            gt.add(del, di1.leght);
            gt.add(eDeleciya::del, di1.leght);
 #ifdef __test
    cout <<endl <<"2 "  <<endl;
#endif
       }

        if(!di1.isDupl)
        {
 #ifdef __test
    cout <<endl <<"3 "  <<endl;
#endif
             _gr->mStatistic->Genom_Del_Inv++;
            _gr->mStatistic->Genom_Del_InvLen += di1.leght;
            _gr->mStatistic->Genom_Del++;
            _gr->mStatistic->Genom_DelLen += di1.leght;
        }


    } //for i

    CountDuplInOneGen = 0;

    for(size_t i = 0; i < index_size_inv; i++)
    {
        cDI_out &di1 = *(*(di_inv+i));
        for(size_t j = i+1; j < index_size_inv; j++)
        {
            cDI_out &di2 = *(*(di_inv+j));

            if(di2.duplInv !=0)   //если есть, значит уже проверяли
            {
                continue;   // пропускаем
            }
            if(CountDuplInOneGen > MaxDuplInOneGen) //прервать если достигли максимума
            {
                CountDuplInOneGen = 0;
                break;
            }
            if(!ChekDubl_inv(di1, di2))
            {
                continue;
            }

            di2.isDupl = true;
            CountDuplInOneGen++;
            if(di1.duplInv ==0)
            {
                di1.duplInv = ++c_duplInv;
                di1.isDupl = true;
                gt.add(inv, di1.leght);
                gt.add(eDeleciya::inv, di1.leght);
            }
            di2.duplInv = di1.duplInv;

            if(di1.duplDelInv == 0 )
            {
                di1.isDupl = true;
                di1.duplDelInv = ++c_duplDelInv;
                gt.add(eDeleciya::del_or_inv, di1.leght);
            }
            di2.duplDelInv = di1.duplDelInv;

        } // for j
        //ненашли, добавить в статистику
        if(di1.duplDelInv == 0)
        {
            gt.add(eDeleciya::del_or_inv, di1.leght);
 #ifdef __test
    cout <<endl <<"4 "  <<endl;
#endif
         }

        if(di1.duplInv == 0)
        {
            gt.add(inv, di1.leght);
            gt.add(eDeleciya::inv, di1.leght);
  #ifdef __test
    cout <<endl <<"5 "  <<endl;
#endif
        }

        if(!di1.isDupl)
        {
  #ifdef __test
    cout <<endl <<"6 "  <<endl;
#endif
            _gr->mStatistic->Genom_Del_Inv++;
            _gr->mStatistic->Genom_Del_InvLen += di1.leght;
            _gr->mStatistic->Genom_Inv++;
            _gr->mStatistic->Genom_InvLen += di1.leght;
        }
    } //for i

    _gr->mStatistic->update_GenTable(_gr->mGen->geneIndex, gt);
    return true;
}




/////////////////////////////////////////////////////////////////////////////////
//     ---  в ХРОМОСОМЕ  ----
////////////////////////////////////////////////////////////////////////////////


bool cDupl::calculateDublInLocus(void)
{
    bool fOk = false;
    vector <cDIindex> D;

    ///загрузить
    fOk = cOutResult::load_index_File(D);
    if(!fOk)
        return fOk;
    cout <<endl <<"Calculate GENOM dubl - count rec = " <<D.size() <<endl <<endl;

    /// посчитасть
    calculateDubl_cikl(D);

    ///сохранить результат
    cOutResult::save_index_File(D);

    return fOk;
}

void cDupl::calculateDubl_cikl(vector <cDIindex> &D)
{
    if(D.empty())
        return;
    cGloballRunable *_gr = cGloballRunable::Instance();
    size_t _size = D.size();
    cDIindex *di = &D[0];

    /// собственнно расчет
    for(size_t i = 0; i < _size; i++)
    {
        cDIindex &d1 = *(di+i);
        //делиция
        if( (d1.T > eDeleciya::del_beg) && (d1.T < eDeleciya::del_end))
        {
            for(size_t j = (i+1); j < _size; j++)
            {
                cDIindex &d2 = *(di+j);

                if(CountDuplInOneGen > MaxDuplInOneGen) //прервать если достигли максимума
                {
                    CountDuplInOneGen = 0;
                    break;
                }

                if( (d2.T > eDeleciya::del_beg) && (d2.T < eDeleciya::del_end)) // del
                {
                    if(!ChekDubl_del(d1, d2))
                    {
                        continue;
                    }
                    CountDuplInOneGen++;

                    if(d1.duplGenomeDel == 0 )
                    {
                        d1.duplGenomeDel = ++c_duplGenomeDel;
                        _gr->mStatistic->Genom_Del++;
                        _gr->mStatistic->Genom_DelLen += d1.leght;
                    }
                    d2.duplGenomeDel = d1.duplGenomeDel;

                    if(d1.duplGenomeDelInv == 0 )
                    {
                        d1.duplGenomeDelInv = ++c_duplGenomeDelInv;
                        _gr->mStatistic->Genom_Del_Inv++;
                        _gr->mStatistic->Genom_Del_InvLen += d1.leght;
                    }
                    d2.duplGenomeDelInv = d1.duplGenomeDelInv;
                }
                else
                {
                    if(!ChekDubl_del_inv(d1, d2))
                    {
                        continue;
                    }
                    CountDuplInOneGen++;
                    if(d1.duplGenomeDelInv == 0 )
                    {
                        d1.duplGenomeDelInv = ++c_duplGenomeDelInv;
                        _gr->mStatistic->Genom_Del_Inv++;
                        _gr->mStatistic->Genom_Del_InvLen += d1.leght;
                    }
                    d2.duplGenomeDelInv = d1.duplGenomeDelInv;                }
            }// for j
            if(d1.duplGenomeDel == 0 )
            {
                _gr->mStatistic->Genom_Del++;
                _gr->mStatistic->Genom_DelLen += d1.leght;
            }

        }
        //инверсия
        else
        {
            for(size_t j = (i+1); j < _size; j++)
            {
                cDIindex &d2 = *(di+j);
                if(CountDuplInOneGen > MaxDuplInOneGen) //прервать если достигли максимума
                {
                    CountDuplInOneGen = 0;
                    break;
                }
                if( (d2.T > eDeleciya::inv_beg) && (d2.T < eDeleciya::inv_end)) // del
                {
                    if(!ChekDubl_inv(d1, d2))
                    {
                        continue;
                    }
                    CountDuplInOneGen++;

                    if(d1.duplGenomeInv == 0 )
                    {
                        d1.duplGenomeInv = ++c_duplGenomeInv;
                        _gr->mStatistic->Genom_Inv++;
                        _gr->mStatistic->Genom_InvLen += d1.leght;
                    }
                    d2.duplGenomeInv = d1.duplGenomeInv;

                    if(d1.duplGenomeDelInv == 0 )
                    {
                        d1.duplGenomeDelInv = ++c_duplGenomeDelInv;
                        _gr->mStatistic->Genom_Del_Inv++;
                        _gr->mStatistic->Genom_Del_InvLen += d1.leght;
                    }
                    d2.duplGenomeDelInv = d1.duplGenomeDelInv;
                }
                else
                {
                    if(!ChekDubl_del_inv(d1, d2))
                    {
                        continue;
                    }
                    CountDuplInOneGen++;
                    if(d1.duplGenomeDelInv == 0 )
                    {
                        d1.duplGenomeDelInv = ++c_duplGenomeDelInv;
                        _gr->mStatistic->Genom_Del_Inv++;
                        _gr->mStatistic->Genom_Del_InvLen += d1.leght;
                    }
                    d2.duplGenomeDelInv = d1.duplGenomeDelInv;                }
            }// for j
            if(d1.duplGenomeInv == 0 )
            {
                _gr->mStatistic->Genom_Inv++;
                _gr->mStatistic->Genom_InvLen += d1.leght;
            }

        }

        if(d1.duplGenomeDelInv ==0)
        {
            _gr->mStatistic->Genom_Del_Inv++;
            _gr->mStatistic->Genom_Del_InvLen += d1.leght;
        }
    }// for i
}


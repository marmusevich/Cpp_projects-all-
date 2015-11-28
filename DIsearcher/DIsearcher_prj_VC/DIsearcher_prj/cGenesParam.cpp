#include "cGenesParam.h"




bool cGenesParam::LoadGene(const string &fileName)
{
    bool f = false;
    mGenes.clear();
    clearMemory();
    mGenes.reserve(256);
    mFile.reserve(8);

    cout <<"Load 'Gene.txt' from " <<fileName <<endl;

    string line;
    tFileLineNumer recCout = 0;
    ifstream inputFile((fileName).c_str());

    if (!inputFile.is_open())
    {
        cout << "Unable to open file <" <<fileName <<">" <<endl;
        return f;
    }

    //первая строка заголовок, пропускаем
    getline (inputFile, line);
    while ( inputFile.good() )
    {
        getline (inputFile, line);
        line = trim(line);
        //пустые строки не добавляем
        if((line.length() < 1)||(line.empty()))
        {
            recCout++;
            continue;
        }
        sGene gen;
        if(ParseOneLineGene(line, gen))
        {
            gen.line = line;
            if(gen.countExons>0)
            {
                if(gen.complement)
                    gen.typeGene = eTypeGene::B;
                else
                    gen.typeGene = eTypeGene::A;
            }
            else
            {
                gen.typeGene = eTypeGene::C;
            }

//            if(find(mGenes.begin(), mGenes.end(), gen) != mGenes.end()) // проверить а если уже
//            {
//                cout <<"Error: Line #"<<recCout
//                     <<" File name <" <<mFile[gen.fileIndex]
//                     <<" Gene name <" <<mGenNames[gen.geneIndex]
//                     <<" Contig number <" <<gen.contigNumber
//                     <<"> - is clone! " <<endl;
//            }
//            else //если нету добавить
//            {
                mGenes.push_back(gen);
                if(recCout%1000 == 0)
                    cout <<".";
//            }
            recCout++;
        }
    }
    inputFile.close();
    cout <<endl <<"Loading from Gene file "<<recCout <<" lines. Saving to prog " <<mGenes.size() <<endl <<endl;

    sort(mGenes.begin(), mGenes.end(), sGene_lees());
    vector<sGene>::iterator it = unique(mGenes.begin(), mGenes.end());
    mGenes.resize( distance(mGenes.begin(),it) );
    vector<sGene>(mGenes).swap(mGenes);
    vector<string>(mFile).swap(mFile);
    vector<string>(mGenNames).swap(mGenNames);
    return true;
}


bool cGenesParam::ParseOneLineGene(const string &line, sGene &gen)
{
    //колонки из файла
    // 0        1           2           3               4           5           6           7   8   9   10    11
    //File name	Gene name	Contig name	Contig number	Coordinates	Complement	Note	Product	5'	3'	RNA	num. exons

    bool fOk = false;

    // str to vector tmp
    vector<string> tmp;

    istringstream iss(line);
    string token;
    while(getline(iss, token, '\t'))
    {
        tmp.push_back(trim(token));
    }

    //если в строке не коректное количество элементов
    if(tmp.size()!= 12)
    {
        return fOk;
    }

    gen.complement = (tmp[5]=="1");
    gen.countExons = convertStr2Num< tCountExon >(tmp[11], fOk);
    gen.contigNumber = convertStr2Num<tCountExon>(tmp[3], fOk);

    find_addFileName(tmp[0], gen.fileIndex);
    find_addGenName(tmp[1], gen.geneIndex);


    //gen.RNA;
    if(fOk && gen.countExons > 0)
        fOk = ParseOneLineGene_RNA(tmp[10], gen);

    return fOk;
}

bool cGenesParam::ParseOneLineGene_RNA(const string &str_rna, sGene &gen)
{
    //str_rna = 'mRNA_CDS(CCDS_1/1)_2312138..2314795,2315232..2315416,2316130..2316322,2318510..2318939,2319342..2319806,2325617..2325767'

    unsigned int n = str_rna.rfind("_");
    if(string::npos == n || (n) > str_rna.size())
    {
        cout <<"Error RNA string!" <<endl;
        return false;
    }

    string str;
    str.assign(str_rna, n+1, str_rna.size());
    //str = '2312138..2314795,2315232..2315416,2316130..2316322,2318510..2318939,2319342..2319806,2325617..2325767'

    // str to vector tmp
    vector<string> tmp;
    tmp.reserve(gen.countExons);
    istringstream iss(str);
    string token;
    while(getline(iss, token, ','))
    {
        tmp.push_back(trim(token));
    }

    if(tmp.empty())
    {
        cout <<"Error RNA string!" <<endl;
        return false;
    }
    if(gen.countExons != tmp.size())
    {
        cout <<"Error: RNA string count <> count Exons!" <<endl;
        return false;
    }

    //token = '2312138..2314795'
    for(size_t i = 0; i < tmp.size(); i++)
    {
        n = tmp[i].find("..");
        if(string::npos == n || (n) > str_rna.size())
        {
            continue;
        }
        sGene::cRNA rna;
        bool f = false;
        str.assign(tmp[i], 0, n);
        rna.En = convertStr2Num< tExonPos >(str, f);
        if(!f)
        {
            cout <<"Error parse RNA: En!" <<endl;
            return false;
        }

        str.assign(tmp[i], n+2, str_rna.size());
        rna.Ek = convertStr2Num< tExonPos >(str, f);
        if(!f)
        {
            cout <<"Error parse RNA: Ek!" <<endl;
            return false;
        }
        gen.RNA.push_back(rna);
    }
    return true;
}


void cGenesParam::toString(void)
{
    cout <<"********************************************************" <<endl;
    cout <<"*           GENE.TXT in memory                         *" <<endl;
    cout <<"********************************************************" <<endl;

    cout    <<"  mFile.size = " <<mFile.size()
            <<", mGenNames.size = " <<mGenNames.size()
            <<", mGenes.size = " <<mGenes.size() <<endl;

    for(size_t i = 0; i < mGenes.size(); ++i)
    {
        sGene &gen = mGenes[i];
        cout
                <<" File name [" <<gen.fileIndex
                <<"] <" <<mFile[gen.fileIndex]
                <<">, Gene name [" <<gen.geneIndex
                <<"] <" <<mGenNames[gen.geneIndex]
                <<">, Contig number = " <<gen.contigNumber

                <<", \tis comp? ( " <<gen.complement
                <<" ), \tcount exons = " <<gen.countExons <<"" <<endl;
//        for(size_t j = 0; j < gen.RNA.size(); j++)
//        {
//            cout <<"\t\t [ " <<j <<" ] ( " <<gen.RNA[j].En <<", " <<gen.RNA[j].Ek <<" )" <<endl;
//        }
    }
    cout <<"********************************************************" <<endl;
    cout <<"*           GENE.TXT in memory                         *" <<endl;
    cout <<"********************************************************" <<endl;
}



//найти имя файла или  добавить, num - индех найденого / добавленого
bool cGenesParam::find_addFileName(const string &fileName,  size_t &num)
{
    size_t _size = mFile.size();
    for(size_t i = 0; i < _size; i++)
    {
        if(mFile[i] == fileName)
        {
            num = i;
            return true;
        }
    }


    // нету - добавим
    mFile.push_back(fileName);
    num = mFile.size()-1;
    return true;
}

//найти имя гена или  добавить, num - индех найденого / добавленого
bool cGenesParam::find_addGenName(const string &genName,  size_t &num)
{
    size_t _size = mGenNames.size();
    for(size_t i = 0; i < _size; i++)
    {
        if(mGenNames[i] == genName)
        {
            num = i;
            return true;
        }
    }

//
//    vector<string>::iterator find_it = find( mGenNames.begin(), mGenNames.end(), genName);
//    if( find_it != mGenNames.end() )
//    {
//        num = distance(mGenNames.begin(),find_it);    ;
//        return true;
//    }

    // нету добавим
    mGenNames.push_back(genName);
    num = mGenNames.size()-1;
    return true;
}


//найти имя файла index - индех найденого / добавленого
bool cGenesParam::findFileIndex(const string &fileName,  size_t &index)
{
    vector<string>::iterator find_it = find( mFile.begin(), mFile.end(), fileName);
    if( find_it != mFile.end() )
    {
        index  = distance(mFile.begin(), find_it);    ;
        return true;
    }
    return false;
}

//найти имя гена index - индех найденого / добавленого
bool cGenesParam::findGenIndex(const string &genName,  size_t &index)
{
    vector<string>::iterator find_it = find( mGenNames.begin(), mGenNames.end(), genName);
    if( find_it != mGenNames.end() )
    {
        index = distance(mGenNames.begin(), find_it);    ;
        return true;
    }
    return false;
}



tGenesFindResult cGenesParam::findGene(const size_t &fileIndex, const size_t &geneNameIndex, const tContigNumber &contigNumber)
{
    tGenesFindResult rez;

    //cout <<"file find. ";
    sGene gen; // временный объект
    gen.contigNumber = contigNumber;
    gen.geneIndex = geneNameIndex;
    gen.fileIndex = fileIndex;

    //поиск
    pair<vector<sGene>::iterator, vector<sGene>::iterator>
    range = equal_range(mGenes.begin(), mGenes.end(), gen, sGene_lees());
    if(range.first != range.second) // что то нашли
    {
        rez.first = true;
        rez.second = distance (mGenes.begin(), range.first);
        return rez;
    }

    return rez;
}



//-----------------------------------------------------------------------------------------------------------------

// загрузить файл list.txt, второй параметр номер варианта: list1 или list2
bool cGenesParam::LoadList(const string &fileName, int tipFile)
{
    bool f = false;

    if(tipFile == 1)
        list1.clear();
    else if(tipFile == 1)
        list2.clear();
    else if(tipFile == 1)
            return f;

    cout <<"Load 'List.txt' from " <<fileName <<endl;

    string line;
    tFileLineNumer recCout = 0;
    ifstream inputFile((fileName).c_str());

    if (!inputFile.is_open())
    {
        cout << "Unable to open file <" <<fileName <<">" <<endl;
        return f;
    }
    //первая строка заголовок, пропускаем
    getline (inputFile, line);
    while ( inputFile.good() )
    {
        getline (inputFile, line);
        line = trim(line);
        //пустые строки не добавляем
        if((line.length() < 1)||(line.empty()))
        {
            recCout++;
            continue;
        }
        size_t chr=0;
        tContigNumber locus=0;
        tGenLen pos=0;
        string chr_str="";
        if(ParseOneLineList(line, chr_str, chr, locus, pos))
        {
            if(tipFile == 1)
            {
                 if(insertOneListLine(list1, chr, locus, pos))
                     cout <<"Error: Line #"<<recCout
                     <<" chr <" <<chr_str
                     <<">, locus <" <<locus
                     <<">, Loc.pos <" <<pos
                     <<"> - is clone! " <<endl;
            }
            else
            {
                 if(insertOneListLine(list2, chr, locus, pos))
                     cout <<"Error: Line #"<<recCout
                     <<" chr <" <<chr_str
                     <<">, locus <" <<locus
                     <<">, Loc.pos <" <<pos
                     <<"> - is clone! " <<endl;
            }
            recCout++;
        }
    }
    inputFile.close();
    cout <<endl <<"Loading from List file "<<recCout <<" lines." <<endl;

    return true;
}

// парсить одну строку файла List.txt
bool cGenesParam::ParseOneLineList(const string &line, string &chr_line, size_t &chr, tContigNumber &locus, tGenLen &pos)
{
    //колонки из файла
    // File	Locus	Loc.pos
//
    bool fOk = false;
    //распарсить ключевые поля
    vector<string> tmp;
    istringstream iss(line);
    string token;
    int i=0;
    while(getline(iss, token, '\t') && (i < 4)) //только начало строки
    {
        tmp.push_back(trim(token));
        i++;
    }

    chr_line = tmp[0];
    fOk = findFileIndex(chr_line, chr);
    if(!fOk)
    {
        cout <<"not find file <" <<chr_line <<">" <<endl;
        return false;
    }

    locus = convertStr2Num<tContigNumber>(tmp[1], fOk);

    if(!fOk)
    {
        cout <<"locus <"  <<tmp[1] <<"> is not numeric" <<endl;
        return false;
    }

    pos = convertStr2Num<size_t>(tmp[2], fOk);
    if(!fOk)
    {
        cout <<"loc_pos <"  <<tmp[2] <<"> is not numeric" <<endl;
        return false;
    }

    return fOk;
}

// проверить одину строку DI на необходимость поиска дублей
bool cGenesParam::chekOneDIonNeedFindDubl(const size_t &chr, const tContigNumber &locus, const tGenLen &pos1, const tGenLen &pos2)
{
    //по list 1
    {
        Tmap_LIST::iterator fRezChr = list1.find(chr);
        if ( fRezChr != list1.end() ) //чтото есть
        {
            Tmap_locus_pos::iterator fRezLocus = fRezChr->second.find(locus);
            if ( fRezLocus != fRezChr->second.end() ) //чтото есть
            {
                Tset_pos::iterator fRez1 = fRezLocus->second.find(pos1);
                Tset_pos::iterator fRez2 = fRezLocus->second.find(pos2);
                if (( fRez1 != fRezLocus->second.end()) && (fRez2 != fRezLocus->second.end()) ) //координаты есть обе
                    return true;
            }
        }
    }

  //по list 2
    {
        Tmap_LIST::iterator fRezChr = list2.find(chr);
        if ( fRezChr != list1.end() ) //чтото есть
        {
            Tmap_locus_pos::iterator fRezLocus = fRezChr->second.find(locus);
            if ( fRezLocus != fRezChr->second.end() ) //чтото есть
            {
                Tset_pos::iterator fRez1 = fRezLocus->second.find(pos1);
                Tset_pos::iterator fRez2 = fRezLocus->second.find(pos2);
                if (( fRez1 != fRezLocus->second.end()) || (fRez2 != fRezLocus->second.end()) ) //координаты есть любая
                    return true;
            }
        }
    }
    return false;
}


// всавить строку in LIST
bool cGenesParam::insertOneListLine(Tmap_LIST &li, const size_t &chr, const tContigNumber &locus, const tGenLen &pos)
{
    Tmap_LIST::iterator fRezChr = li.find(chr);
    if ( fRezChr != list1.end() ) //чтото есть
    { //хромосома есть
        Tmap_locus_pos::iterator fRezLocus = fRezChr->second.find(locus);
        if ( fRezLocus != fRezChr->second.end() ) //чтото есть
        {//хромосома и локус есть, добавляем координату
            if(fRezLocus->second.insert(pos).second) // запись есть
                return false;
        }
        else // локуса нет
        {
            Tset_pos _pos;
            _pos.insert(pos);
            (*fRezChr).second.insert( pair<tContigNumber, Tset_pos >(locus, _pos));
        }
    }
    else //нет такой хромосомы, добовляем все
    {
        Tset_pos _pos;
        _pos.insert(pos);
        Tmap_locus_pos _Chr;
        _Chr.insert( pair<tContigNumber, Tset_pos >(locus, _pos));
        li.insert( pair<size_t, Tmap_locus_pos >(chr, _Chr));
    }
    return false;
}




#include "cOutResult.h"
#include "cDIindex.h"
#include "cDupl.h"


#if defined (_WIN32) || defined (WIN32)
    //код WIN
    #include <io.h>
    #include <direct.h>
    #define _LARGEFILE64_SOURCE
#else
    //код LINUX
    #include <unistd.h>
    #include <sys/stat.h>
#endif

string cOutResult::fileNamePrefix = "";
string cOutResult::tmpDir = "";
size_t cOutResult::countFiles = 1;
tFileLineNumer cOutResult::recCout = 0;

const tFileLineNumer cOutResult::MaxRecInDI = 50000;


const string cOutResult::Dir    ="DIsearcher";
const string cOutResult::RepDir ="DIsearcher/Table";


// имена файлов и каталогов
const string cOutResult::Del         ="_Del.txt";
const string cOutResult::DelUnc      ="_Del_unique.txt";
const string cOutResult::DelInv      ="_Del_Inv.txt";
const string cOutResult::DelInvUnc   ="_Del_Inv_unique.txt";
const string cOutResult::DI          ="_DI";
const string cOutResult::DI_dupl     ="_DI_dupl";
const string cOutResult::Inv         ="_Inv.txt";
const string cOutResult::InvUnc      ="_Inv_unique.txt";
const string cOutResult::NoDelInv    ="_no_Del_Inv.txt";
const string cOutResult::NoDelInvUnc ="_no_Del_Inv_unique.txt";

//reports
const string cOutResult::RepRSSTable1    ="_cRSSTable_1.txt";
const string cOutResult::RepRSSTable2    ="_cRSSTable_2.txt";
const string cOutResult::RepGenNo_DI     ="_GenNo_DI.txt";
const string cOutResult::RepGenTable1    ="_GenTable_1.txt";
const string cOutResult::RepGenTable2    ="_GenTable_2.txt";
const string cOutResult::RepGenTable3    ="_GenTable_3.txt";
const string cOutResult::RepLengthTable1 ="_LengthTable_1.txt";
const string cOutResult::RepLengthTable2 ="_LengthTable_2.txt";
const string cOutResult::RepTotalResults ="_TotalResults.txt";

// ощибочные
const string cOutResult::ErrorGen ="_ErrorGene.txt";

// временные
const string cOutResult::DI_tmp ="DI.tmp";
const string cOutResult::DI_idx ="DI.idx";



bool cOutResult::createDir(void)
{
    //создать структуру котологов
    if(_access(Dir.c_str(), 00) == -1) //если нет католога создаём
#if defined (_WIN32) || defined (WIN32)
    //код WIN
        if(_mkdir(Dir.c_str())==-1)
#else
    //код LINUX
        if(mkdir(Dir.c_str(), 0777)==-1)
#endif
        {
            cout <<"1 - Failed to create a directory for the result. \n";
            return false;
        }
    if(_access(RepDir.c_str(), 00) == -1) //если нет католога создаём
#if defined (_WIN32) || defined (WIN32)
    //код WIN
        if(_mkdir(RepDir.c_str())==-1)
#else
    //код LINUX
        if(mkdir(RepDir.c_str(), 0777)==-1)
#endif
        {
            cout <<"2 - Failed to create a directory for the result. \n";
            return false;
        }
    return true;
}

bool cOutResult::createFiles(void)
{
    //создать (если есть обнулить) файлы
    string fn;
    ofstream outFile;
    //"DIsearcher/";
    fn= Dir+"/"+ fileNamePrefix  +DI +"-1.txt";
    outFile.open(fn.c_str(), ios::out);
    outFile <<"Chr	Locus	Gene	12cRSS	23cRSS	Length	Type	Del-dupl	Inv-dupl	Del/Inv-dupl	Genome-Del-dupl	Genome-Inv-dupl	Genome-Del/Inv-dupl" <<endl;
    outFile.close();

    fn= Dir+"/"+ fileNamePrefix  +DI_dupl +"-1.txt";
    outFile.open(fn.c_str(), ios::out);
    outFile <<"Chr	Locus	Gene	12cRSS	23cRSS	Length	Type	Del-dupl	Inv-dupl	Del/Inv-dupl	Genome-Del-dupl	Genome-Inv-dupl	Genome-Del/Inv-dupl" <<endl;
    outFile.close();


    fn = Dir+"/" + fileNamePrefix + Del;
    outFile.open(fn.c_str(), ios::out);
    outFile <<"File	Locus	Loc.pos	Abs.pos	Complement	Spacer	Matrix			spacer	heptamer	nanomer	%	gene	exon	intron	5'	3'	#" <<endl;
    outFile.close();

    fn = Dir+"/" + fileNamePrefix + DelInv;
    outFile.open(fn.c_str(), ios::out);
    outFile <<"File	Locus	Loc.pos	Abs.pos	Complement	Spacer	Matrix			spacer	heptamer	nanomer	%	gene	exon	intron	5'	3'	#" <<endl;
    outFile.close();

    fn = Dir+"/" + fileNamePrefix + DelInvUnc ;
    outFile.open(fn.c_str(), ios::out);
    outFile <<"File	Locus	Loc.pos	Abs.pos	Complement	Spacer	Matrix			spacer	heptamer	nanomer	%	gene	exon	intron	5'	3'	#" <<endl;
    outFile.close();

    fn = Dir+"/" + fileNamePrefix + DelUnc;
    outFile.open(fn.c_str(), ios::out);
    outFile <<"File	Locus	Loc.pos	Abs.pos	Complement	Spacer	Matrix			spacer	heptamer	nanomer	%	gene	exon	intron	5'	3'	#" <<endl;
    outFile.close();

    fn = Dir+"/" + fileNamePrefix + Inv ;
    outFile.open(fn.c_str(), ios::out);
    outFile <<"File	Locus	Loc.pos	Abs.pos	Complement	Spacer	Matrix			spacer	heptamer	nanomer	%	gene	exon	intron	5'	3'	#" <<endl;
    outFile.close();

    fn = Dir+"/" + fileNamePrefix + InvUnc ;
    outFile.open(fn.c_str(), ios::out);
    outFile <<"File	Locus	Loc.pos	Abs.pos	Complement	Spacer	Matrix			spacer	heptamer	nanomer	%	gene	exon	intron	5'	3'	#" <<endl;
    outFile.close();

    fn = Dir+"/" + fileNamePrefix + NoDelInv;
    outFile.open(fn.c_str(), ios::out);
    outFile <<"File	Locus	Loc.pos	Abs.pos	Complement	Spacer	Matrix			spacer	heptamer	nanomer	%	gene	exon	intron	5'	3'	#" <<endl;
    outFile.close();

    fn = Dir+"/" + fileNamePrefix + NoDelInvUnc;
    outFile.open(fn.c_str(), ios::out);
    outFile <<"File	Locus	Loc.pos	Abs.pos	Complement	Spacer	Matrix			spacer	heptamer	nanomer	%	gene	exon	intron	5'	3'	#" <<endl;
    outFile.close();

    //"DIsearcher/Table/"
    fn = RepDir+"/" + fileNamePrefix + RepRSSTable1;
    outFile.open(fn.c_str(), ios::out);
    outFile <<"cRSS	obsch. kol	Del/Inv	Del	Inv" <<endl;
    outFile.close();

    fn = RepDir+"/" + fileNamePrefix + RepRSSTable2;
    outFile.open(fn.c_str(), ios::out);
    outFile <<"	obsch. kol			Del/Inv			Del			Inv	" <<endl;
    outFile <<"Gene	12/23 cRSS	12cRSS	23cRSS	12/23 cRSS	12cRSS	23cRSS	12/23 cRSS	12cRSS	23cRSS	12/23 cRSS	12cRSS	23cRSS" <<endl;
    outFile.close();

    fn = RepDir+"/" + fileNamePrefix + RepGenNo_DI;
    outFile.open(fn.c_str(), ios::out);
    outFile <<"File name	Gene name	Contig name	Contig number	Coordinates	Complement	Note	Product	5'	3'	RNA	num. exons" <<endl;
    outFile.close();

    fn = RepDir+"/" + fileNamePrefix + RepGenTable1;
    outFile.open(fn.c_str(), ios::out);
    outFile <<"kol gens	Genom-Del/Inv	Genom-Del	Genom-Inv  \tDel/Inv	Del	Inv	Del-1a	Del-1b	Del-1c	Del-1d	Del-1e	Del-1f	Del-1g	Del-2a	Del-2b	Del-3	Inv-1a	Inv-1b	Inv-1c	Inv-1d	Inv-1e	Inv-1f	Inv-1g	Inv-2a	Inv-2b	Inv-3" <<endl;
    outFile.close();

    fn = RepDir+"/" + fileNamePrefix + RepGenTable2;
    outFile.open(fn.c_str(), ios::out);
    outFile <<"File name	Gene name	Contig name	Contig number	Coordinates	Complement	Note	Product	5'	3'	RNA	num. exons";
    outFile <<"\tDel/Inv	Del	Inv	Del-1a	Del-1b	Del-1c	Del-1d	Del-1e	Del-1f	Del-1g	Del-2a	Del-2b	Del-3	Inv-1a	Inv-1b	Inv-1c	Inv-1d	Inv-1e	Inv-1f	Inv-1g	Inv-2a	Inv-2b	Inv-3" <<endl;
    outFile.close();

    fn = RepDir+"/" + fileNamePrefix + RepGenTable3;
    outFile.open(fn.c_str(), ios::out);
    outFile <<"Del/Inv	Del	Inv	Del-1a	Del-1b	Del-1c	Del-1d	Del-1e	Del-1f	Del-1g	Del-2a	Del-2b	Del-3	Inv-1a	Inv-1b	Inv-1c	Inv-1d	Inv-1e	Inv-1f	Inv-1g	Inv-2a	Inv-2b	Inv-3" <<endl;
    outFile.close();

    fn = RepDir+"/" + fileNamePrefix + RepLengthTable1;
    outFile.open(fn.c_str(), ios::out);
    outFile <<"kol gens	Del/Inv	Del	Inv	Del-1a	Del-1b	Del-1c	Del-1d	Del-1e	Del-1f	Del-1g	Del-2a	Del-2b	Del-3	Inv-1a	Inv-1b	Inv-1c	Inv-1d	Inv-1e	Inv-1f	Inv-1g	Inv-2a	Inv-2b	Inv-3" <<endl;
    outFile.close();

//    fn = RepDir+"/" + fileNamePrefix + RepLengthTable2;
//    outFile.open(fn.c_str(), ios::out);
//    outFile <<"Gene	Del/Inv	Del	Inv	Del-1a	Del-1b	Del-1c	Del-1d	Del-1e	Del-1f	Del-1g	Del-2a	Del-2b	Del-3	Inv-1a	Inv-1b	Inv-1c	Inv-1d	Inv-1e	Inv-1f	Inv-1g	Inv-2a	Inv-2b	Inv-3" <<endl;
//    outFile.close();

    fn = RepDir+"/" + fileNamePrefix + RepTotalResults;
    outFile.open(fn.c_str(), ios::out);
    outFile <<"	obsch. kol	Del/Inv	Del	Inv	No Del/Inv" <<endl;
    outFile.close();


    fn = Dir+"/" + fileNamePrefix + ErrorGen;
    outFile.open(fn.c_str(), ios::out);
    outFile.close();

    return true;
}

void cOutResult::setFileNamePrefix(string fileName)
{
    //префикс для имен файлов
    fileNamePrefix = fileName;
    unsigned int len = fileNamePrefix.length();
    if(len >= 4)
    {
        fileNamePrefix.erase(len-4, 4);
    }
    else
    {
        fileNamePrefix="";
    }
    countFiles = 1;
    recCout = 0;
    tmpDir = "";
}

//сохранить те cRSS которые создают Del Inv и не создают
bool cOutResult::outFile_Del_Inv_DelInv_NO(void)
{
    string fn_Del = Dir+"/" + fileNamePrefix + Del; // "_Del.txt"
    string fn_DelInv = Dir+"/" + fileNamePrefix + DelInv; //"_Del_Inv.txt"
    string fn_Inv = Dir+"/" + fileNamePrefix + Inv; //"_Inv.txt"
    string fn_No = Dir+"/" + fileNamePrefix + NoDelInv; //"_no_Del_Inv.txt";
    bool fOk = false;
    try
    {
        size_t c_Del = 0;
        size_t c_DelInv = 0;
        size_t c_Inv = 0;
        size_t c_No = 0;

        cGloballRunable *_gr = cGloballRunable::Instance();

        size_t &c_cRSSNo_DI_12 = _gr->mStatistic->c_cRSSNo_DI_12;
        size_t &c_cRSSNo_DI_23 = _gr->mStatistic->c_cRSSNo_DI_23;
        size_t &c_cRSSNo_DI_12_23 = _gr->mStatistic->c_cRSSNo_DI_12_23;

        ofstream outF_Del(fn_Del.c_str(), ios::out | ios::app);
        ofstream outF_DelInv(fn_DelInv.c_str(), ios::out | ios::app);
        ofstream outF_Inv(fn_Inv.c_str(), ios::out | ios::app);
        ofstream outF_No(fn_No.c_str(), ios::out | ios::app);

        for(size_t i = 0; i < _gr->mGen->rss12_0.size(); i++)
        {
            if(_gr->mGen->rss12_0[i].isDel)
            {
                if(!_gr->mGen->rss12_0[i].fSaveToDelInv)
                {
                    outF_DelInv <<_gr->mGen->rss12_0[i].toString() <<endl;
                    _gr->mGen->rss12_0[i].fSaveToDelInv = true;
                }

                outF_Del <<_gr->mGen->rss12_0[i].toString() <<endl;
                c_Del++;
                c_DelInv++;
            }
            if(_gr->mGen->rss12_0[i].isInv)
            {
                if(!_gr->mGen->rss12_0[i].fSaveToDelInv)
                {
                    outF_DelInv <<_gr->mGen->rss12_0[i].toString() <<endl;
                    _gr->mGen->rss12_0[i].fSaveToDelInv = true;
                }

                outF_Inv <<_gr->mGen->rss12_0[i].toString() <<endl;
                c_DelInv++;
                c_Inv++;
            }
            if(!(_gr->mGen->rss12_0[i].isInv) && !(_gr->mGen->rss12_0[i].isDel))
            {
                outF_No <<_gr->mGen->rss12_0[i].toString() <<endl;
                c_No++;
                c_cRSSNo_DI_12++;
                c_cRSSNo_DI_12_23++;
            }
        }

        for(size_t i = 0; i < _gr->mGen->rss12_1.size(); i++)
        {
            if(_gr->mGen->rss12_1[i].isDel)
            {
                if(!_gr->mGen->rss12_1[i].fSaveToDelInv)
                {
                    outF_DelInv <<_gr->mGen->rss12_1[i].toString() <<endl;
                    _gr->mGen->rss12_1[i].fSaveToDelInv = true;
                }

                outF_Del <<_gr->mGen->rss12_1[i].toString() <<endl;
                c_Del++;
                c_DelInv++;
            }
            if(_gr->mGen->rss12_1[i].isInv)
            {
                if(!_gr->mGen->rss12_1[i].fSaveToDelInv)
                {
                    outF_DelInv <<_gr->mGen->rss12_1[i].toString() <<endl;
                    _gr->mGen->rss12_1[i].fSaveToDelInv = true;
                }

                outF_Inv <<_gr->mGen->rss12_1[i].toString() <<endl;
                c_DelInv++;
                c_Inv++;
            }
            if(!(_gr->mGen->rss12_1[i].isInv) && !(_gr->mGen->rss12_1[i].isDel))
            {
                outF_No <<_gr->mGen->rss12_1[i].toString() <<endl;
                c_No++;
                c_cRSSNo_DI_12++;
                c_cRSSNo_DI_12_23++;
            }
        }

        for(size_t i = 0; i < _gr->mGen->rss23_0.size(); i++)
        {
            if(_gr->mGen->rss23_0[i].isDel)
            {
                if(!_gr->mGen->rss23_0[i].fSaveToDelInv)
                {
                    outF_DelInv <<_gr->mGen->rss23_0[i].toString() <<endl;
                    _gr->mGen->rss23_0[i].fSaveToDelInv = true;
                }

                outF_Del <<_gr->mGen->rss23_0[i].toString() <<endl;
                c_Del++;
                c_DelInv++;
            }
            if(_gr->mGen->rss23_0[i].isInv)
            {
                if(!_gr->mGen->rss23_0[i].fSaveToDelInv)
                {
                    outF_DelInv <<_gr->mGen->rss23_0[i].toString() <<endl;
                    _gr->mGen->rss23_0[i].fSaveToDelInv = true;
                }

                outF_Inv <<_gr->mGen->rss23_0[i].toString() <<endl;
                c_DelInv++;
                c_Inv++;
            }
            if(!(_gr->mGen->rss23_0[i].isInv) && !(_gr->mGen->rss23_0[i].isDel))
            {
                outF_No <<_gr->mGen->rss23_0[i].toString() <<endl;
                c_No++;
                c_cRSSNo_DI_23++;
                c_cRSSNo_DI_12_23++;
            }
        }

        for(size_t i = 0; i < _gr->mGen->rss23_1.size(); i++)
        {
            if(_gr->mGen->rss23_1[i].isDel)
            {
                if(!_gr->mGen->rss23_1[i].fSaveToDelInv)
                {
                    outF_DelInv <<_gr->mGen->rss23_1[i].toString() <<endl;
                    _gr->mGen->rss23_1[i].fSaveToDelInv = true;
                }

                outF_Del <<_gr->mGen->rss23_1[i].toString() <<endl;
                c_Del++;
                c_DelInv++;
            }
            if(_gr->mGen->rss23_1[i].isInv)
            {
                if(!_gr->mGen->rss23_1[i].fSaveToDelInv)
                {
                    outF_DelInv <<_gr->mGen->rss23_1[i].toString() <<endl;
                    _gr->mGen->rss23_1[i].fSaveToDelInv = true;
                }

                outF_Inv <<_gr->mGen->rss23_1[i].toString() <<endl;
                c_DelInv++;
                c_Inv++;
            }
            if(!(_gr->mGen->rss23_1[i].isInv) && !(_gr->mGen->rss23_1[i].isDel))
            {
                outF_No <<_gr->mGen->rss23_1[i].toString() <<endl;
                c_No++;
                c_cRSSNo_DI_23++;
                c_cRSSNo_DI_12_23++;
            }
        }

        outF_Del.close();
        outF_DelInv.close();
        outF_Inv.close();
        outF_No.close();
        //сообщаем только если что то записывали
//        if(c_Del)
//            cout <<"\t  to '" <<fn_Del <<"' -  add " <<c_Del <<" rec" <<endl;
//        if(c_Inv)
//            cout <<"\t  to '" <<fn_Inv <<"' -  add " <<c_Inv <<" rec" <<endl;
//        if(c_DelInv)
//            cout <<"\t  to '" <<fn_DelInv <<"' -  add " <<c_DelInv <<" rec" <<endl;
//        if(c_No)
//            cout <<"\t  to '" <<fn_No <<"' -  add " <<c_No <<" rec" <<endl;
        fOk = true;// удалось записать
    }
    catch(...)
    {
        cout <<endl <<"ERROR add to '" <<fn_Del <<"' or '" <<fn_Inv <<"' or '" <<fn_DelInv <<"'!!!" <<endl;
        fOk = false;
    }
    return fOk;
}


bool cOutResult::outFile_DelUnc(void)
{
    string fn_in = Dir+"/" + fileNamePrefix + Del;
    string fn = Dir+"/" + fileNamePrefix + DelUnc;
    bool fOk = false;
    try
    {
        ofstream outFile(fn.c_str(), ios::out | ios::app);
        ifstream inFile(fn_in.c_str(), ios::in);

        cGloballRunable *_gr = cGloballRunable::Instance();
        s_cRSSTableItem &RSSTableItem_count = _gr->mStatistic->cRSSTableItem_count;

        size_t c_ = make_Unc(inFile, outFile, RSSTableItem_count.del_12, RSSTableItem_count.del_23);

        outFile.close();
        inFile.close();
        cout <<"in '" <<fn <<"' -  save " <<c_ <<" rec" <<endl;
        fOk = true;// удалось записать
    }
    catch(...)
    {
        cout <<endl <<"ERROR add to '" <<fn <<"'!!!" <<endl;
        fOk = false;
    }
    return fOk;

}

bool cOutResult::outFile_InvUnc (void)
{
    string fn_in = Dir+"/" + fileNamePrefix + Inv ;
    string fn = Dir+"/" + fileNamePrefix + InvUnc ;
    bool fOk = false;
    try
    {
        ofstream outFile(fn.c_str(), ios::out | ios::app);
        ifstream inFile(fn_in.c_str(), ios::in);

        cGloballRunable *_gr = cGloballRunable::Instance();
        s_cRSSTableItem &RSSTableItem_count = _gr->mStatistic->cRSSTableItem_count;
        size_t c_ = make_Unc(inFile, outFile, RSSTableItem_count.inv_12, RSSTableItem_count.inv_23);

        outFile.close();
        inFile.close();
        cout <<"in '" <<fn <<"' -  save " <<c_ <<" rec" <<endl;
        fOk = true;// удалось записать
    }
    catch(...)
    {
        cout <<endl <<"ERROR add to '" <<fn <<"'!!!" <<endl;
        fOk = false;
    }
    return fOk;

}

bool cOutResult::outFile_DelInvUnc(void)
{
    string fn_in = Dir+"/" + fileNamePrefix + DelInv;
    string fn = Dir+"/" + fileNamePrefix + DelInvUnc ;
    bool fOk = false;
    try
    {
        ofstream outFile(fn.c_str(), ios::out | ios::app);
        ifstream inFile(fn_in.c_str(), ios::in);

        cGloballRunable *_gr = cGloballRunable::Instance();
        s_cRSSTableItem &RSSTableItem_count = _gr->mStatistic->cRSSTableItem_count;
        size_t c_ = make_Unc(inFile, outFile, RSSTableItem_count.del_inv_12, RSSTableItem_count.del_inv_23);

        outFile.close();
        inFile.close();
        cout <<"in '" <<fn <<"' -  save " <<c_ <<" rec" <<endl;
        fOk = true;// удалось записать
    }
    catch(...)
    {
        cout <<endl <<"ERROR add to '" <<fn <<"'!!!" <<endl;
        fOk = false;
    }
    return fOk;

}

bool cOutResult::outFile_NoDelInvUnc(void)
{
    string fn_in = Dir+"/" + fileNamePrefix + NoDelInv;
    string fn = Dir+"/" + fileNamePrefix + NoDelInvUnc;
    bool fOk = false;
    try
    {
        ofstream outFile(fn.c_str(), ios::out | ios::app);
        ifstream inFile(fn_in.c_str(), ios::in);


        cGloballRunable *_gr = cGloballRunable::Instance();
        s_cRSSTableItem &RSSTableItem_count = _gr->mStatistic->cRSSTableItem_count;

        size_t c_ = make_Unc(inFile, outFile, RSSTableItem_count._12, RSSTableItem_count._23);

        outFile.close();
        inFile.close();
        cout <<"in '" <<fn <<"' -  save " <<c_ <<" rec" <<endl;
        fOk = true;// удалось записать
    }
    catch(...)
    {
        cout <<endl <<"ERROR add to '" <<fn <<"'!!!" <<endl;
        fOk = false;
    }
    return fOk;
}


//создает файл уникальных записей, параметры - потоки входа/выхода, возвращает количество записаных строк
size_t cOutResult::make_Unc(ifstream &inFile, ofstream &outFile, tRSSTableItem &_12,tRSSTableItem &_23)
{
    unordered_set<string> mUnic;

    //проблемы с открытием
    if (!inFile.is_open() || !outFile.is_open())
        return 0;
    //пропустить строку заголовок

    string line;
    getline(inFile, line);
    while ( inFile.good() )
    {
        //читаем исходную строку
        getline (inFile, line);
        if(line.length()<1)
        {
            continue;
        }

        string str="";
        vector<string> tmp;

        { //распарсить ключевые поля
            istringstream iss(line);
            string token;
            int i=0;
            while(getline(iss, token, '\t') && (i<6)) //только начало строки
            {
                tmp.push_back(trim(token));
                i++;
            }
               //   File	       Locus	       Loc.pos	   Complement	      Spacer
            str = tmp[0] + "&" + tmp[1] + "&" + tmp[2] + "&" + tmp[4] + "&" + tmp[5] ;
        }

        if(mUnic.insert(str).second)
        {
           outFile <<line <<endl;
           if(tmp[5] == "12")
                _12++;
           else
                _23++;
        }
    }
    return mUnic.size();
}


//------------------------------------------------------------------------
//reports "DIsearcher/Table/"
//------------------------------------------------------------------------

bool cOutResult::outFile_RepRSSTable(void)
{
    //RepRSSTable2
    string fn = RepDir+"/" + fileNamePrefix + RepRSSTable2;
    cGloballRunable *_gr = cGloballRunable::Instance();

    s_cRSSTableItem &cRSSTableItem = _gr->mStatistic->cRSSTableItem_one;

    bool fOk = false;
    try
    {
        ofstream outFile(fn.c_str(), ios::out | ios::app);
        size_t c_RSSTable1 = 0;
        for (unordered_map<size_t, s_cRSSTableItem>::iterator it = _gr->mStatistic->m_cRSSTable.begin();
                it !=_gr->mStatistic->m_cRSSTable.end(); ++it)
        {
            outFile <<_gr->genesParam.mGenNames[_gr->genesParam.mGenes[it->first].geneIndex] <<"\t"
                    <<(it->second._12 + it->second._23) <<"\t"
                    <<it->second._12 <<"\t"
                    <<it->second._23 <<"\t"
                    <<(it->second.del_inv_12 + it->second.del_inv_23) <<"\t"
                    <<(it->second.del_inv_12) <<"\t"
                    <<(it->second.del_inv_23) <<"\t"

                    <<(it->second.del_12 + it->second.del_23) <<"\t"
                    <<it->second.del_12 <<"\t"
                    <<it->second.del_23 <<"\t"
                    <<(it->second.inv_12 + it->second.inv_23) <<"\t"
                    <<it->second.inv_12 <<"\t"
                    <<it->second.inv_23 <<"\t"
                    <<endl;
            c_RSSTable1++;
            //общая сумма всего
            cRSSTableItem._12 += it->second._12;
            cRSSTableItem._23 += it->second._23;
            cRSSTableItem.del_12 += it->second.del_12;
            cRSSTableItem.del_23 += it->second.del_23;
            cRSSTableItem.inv_12 += it->second.inv_12;
            cRSSTableItem.inv_23 += it->second.inv_23;
            cRSSTableItem.del_inv_12 += it->second.del_inv_12;
            cRSSTableItem.del_inv_23 += it->second.del_inv_23;
        }
        outFile <<_gr->mStatistic->m_cRSSTable.size() <<"\t"
                <<(cRSSTableItem._12 + cRSSTableItem._23) <<"\t"
                <<cRSSTableItem._12 <<"\t"
                <<cRSSTableItem._23 <<"\t"
                <<(cRSSTableItem.del_inv_12 + cRSSTableItem.del_inv_23) <<"\t"
                <<(cRSSTableItem.del_inv_12) <<"\t"
                <<(cRSSTableItem.del_inv_23) <<"\t"

                <<(cRSSTableItem.del_12 + cRSSTableItem.del_23) <<"\t"
                <<cRSSTableItem.del_12 <<"\t"
                <<cRSSTableItem.del_23 <<"\t"
                <<(cRSSTableItem.inv_12 + cRSSTableItem.inv_23) <<"\t"
                <<cRSSTableItem.inv_12 <<"\t"
                <<cRSSTableItem.inv_23 <<"\t"
                <<endl;

        outFile.close();
        cout <<"in '" <<fn <<"' -  save " <<c_RSSTable1 <<" rec" <<endl;
        fOk = true;// удалось записать
    }
    catch(...)
    {
        cout <<endl <<"ERROR add to '" <<fn <<"'!!!" <<endl;
        fOk = false;
    }

    //RepRSSTable1
    fn = RepDir+"/" + fileNamePrefix + RepRSSTable1;
    fOk = false;
    try
    {
        ofstream outFile(fn.c_str(), ios::out | ios::app);
        s_cRSSTableItem &RSSTableItem_count = _gr->mStatistic->cRSSTableItem_count;

        outFile
                <<"12/23cRSS" <<"\t"
                <<(cRSSTableItem._12 + cRSSTableItem._23) <<"\t"
                <<(RSSTableItem_count.del_inv_12 + RSSTableItem_count.del_inv_23) <<"\t"
                <<(RSSTableItem_count.del_12 + RSSTableItem_count.del_23) <<"\t"
                <<(RSSTableItem_count.inv_12 + RSSTableItem_count.inv_23) <<endl
                <<"12cRSS" <<"\t"
                <<cRSSTableItem._12 <<"\t"
                <<(RSSTableItem_count.del_inv_12) <<"\t"
                <<RSSTableItem_count.del_12 <<"\t"
                <<RSSTableItem_count.inv_12 <<endl
                <<"23cRSS" <<"\t"
                <<cRSSTableItem._23 <<"\t"
                <<(RSSTableItem_count.del_inv_23) <<"\t"
                <<RSSTableItem_count.del_23 <<"\t"
                <<RSSTableItem_count.inv_23 <<endl;
        outFile.close();
        cout <<"in '" <<fn <<"' -  save - ok" <<endl;
        fOk = true;// удалось записать
    }
    catch(...)
    {
        cout <<endl <<"ERROR add to '" <<fn <<"'!!!" <<endl;
        fOk = false;
    }
    return fOk;
}


bool cOutResult::outFile_RepGenNo_DI(void)
{
    string fn = RepDir+"/" + fileNamePrefix + RepGenNo_DI;
    bool fOk = false;
    try
    {
        cGloballRunable *_gr = cGloballRunable::Instance();
        ofstream outFile(fn.c_str(), ios::out | ios::app);
        size_t &c_genNo_DI = _gr->mStatistic->c_genNo_DI;
        c_genNo_DI =0;
        for (unordered_map<size_t, bool>::iterator it = _gr->mStatistic->m_genNo_DI.begin(); it !=_gr->mStatistic->m_genNo_DI.end(); ++it)
        {
            if(!it->second) // толко те что не определились
            {
                outFile <<_gr->genesParam.mGenes[it->first].line <<endl;
                c_genNo_DI++;
            }
        }
        outFile.close();
        cout <<"in '" <<fn <<"' -  save " <<c_genNo_DI <<" rec" <<endl;
        fOk = true;// удалось записать
    }
    catch(...)
    {
        cout <<endl <<"ERROR add to '" <<fn <<"'!!!" <<endl;
        fOk = false;
    }
    return fOk;
}

bool cOutResult::outFile_RepTable(void)
{
    bool fOk = false;

    sGenTable gt_sum;
    tGenTable_type <tDuplCount> gt_count;

    cGloballRunable *_gr = cGloballRunable::Instance();
    cGenesParam &_gp = _gr->genesParam;
    string fn_gt2 = RepDir+"/" + fileNamePrefix + RepGenTable2;
   // string fn_lt2 = RepDir+"/" + fileNamePrefix + RepLengthTable2;
    string fn_gt1 = RepDir+"/" + fileNamePrefix + RepGenTable1;
    string fn_gt3 = RepDir+"/" + fileNamePrefix + RepGenTable3;
    string fn_lt1 = RepDir+"/" + fileNamePrefix + RepLengthTable1;

    try
    {
        ofstream outFile_gt2(fn_gt2.c_str(), ios::out | ios::app);
       // ofstream outFile_lt2(fn_lt2.c_str(), ios::out | ios::app);

        //цикл Вывод, сумирование
        size_t c_gt2 = 0;//, c_lt2 = 0;

        for (unordered_map<size_t, sGenTable>::iterator it = _gr->mStatistic->m_GenTable.begin(); it !=_gr->mStatistic->m_GenTable.end(); ++it)
        {
            outFile_gt2 <<_gp.mGenes[it->first].line;
           // outFile_lt2 <<_gp.mGenNames[_gp.mGenes[it->first].geneIndex];
            string s_gt="", s_lt="";
            sGenTable &_gt = it->second;

            gt_sum += _gt;
            tDuplCount len_count = 0;

            //
            for(uint8_t di = static_cast<uint8_t>(eDeleciya::del_or_inv); di <= static_cast<uint8_t>(eDeleciya::inv); di++)
            {
                len_count = _gt.len_count.findDel(static_cast<eDeleciya>(di));
                if(len_count != 0)
                    gt_count.add(static_cast<eDeleciya>(di), 1);
                outFile_gt2 <<'\t' <<len_count;
              //  outFile_lt2 <<'\t' <<_gt.len_sum.findDel(static_cast<eDeleciya>(di));
            }

            //
            for(uint8_t del = static_cast<uint8_t>(eDeleciya::del_1a); del < static_cast<uint8_t>(eDeleciya::del_end); del++)
            {
                len_count = _gt.len_count.findDel(static_cast<eDeleciya>(del));
                if(len_count != 0)
                    gt_count.add(static_cast<eDeleciya>(del), 1);
                outFile_gt2 <<'\t' <<len_count;
              //  outFile_lt2 <<'\t' <<_gt.len_sum.findDel(static_cast<eDeleciya>(del));
            }

            //
            for(uint8_t inv = static_cast<uint8_t>(eDeleciya::inv_1a); inv < static_cast<uint8_t>(eDeleciya::inv_end); inv++)
            {
                len_count = _gt.len_count.findDel(static_cast<eDeleciya>(inv));
                if(len_count != 0)
                    gt_count.add(static_cast<eDeleciya>(inv), 1);
                outFile_gt2 <<'\t' <<len_count;
             //   outFile_lt2 <<'\t' <<_gt.len_sum.findDel(static_cast<eDeleciya>(inv));
            }
            outFile_gt2 <<'\n';
          //  outFile_lt2 <<'\n';
            c_gt2++;
        //    c_lt2++;
        }
        outFile_gt2.close();
       // outFile_lt2.close();
        cout <<"in '" <<fn_gt2 <<"' -  save " <<c_gt2 <<" rec" <<endl;
      //  cout <<"in '" <<fn_lt2 <<"' -  save " <<c_lt2 <<" rec" <<endl;

        fOk = true;// удалось записать
    }
    catch(...)
    {
        cout <<endl <<"ERROR add to '" <<fn_gt2 <<"'!!!" <<endl;
     //   cout <<endl <<"ERROR add to '" <<fn_lt2 <<"'!!!" <<endl;
        fOk = false;
    }

    try
    {
        ofstream outFile_gt1(fn_gt1.c_str(), ios::out | ios::app);
        ofstream outFile_lt1(fn_lt1.c_str(), ios::out | ios::app);

        outFile_gt1 <<_gr->mStatistic->m_GenTable.size() <<'\t'
                    <<_gr->mStatistic->Genom_Del_Inv <<'\t'
                    <<_gr->mStatistic->Genom_Del <<'\t'
                    <<_gr->mStatistic->Genom_Inv;
        outFile_lt1 <<_gr->mStatistic->m_GenTable.size();

        tDuplCount len_count = 0;
        //
        for(uint8_t di = static_cast<uint8_t>(eDeleciya::del_or_inv); di <= static_cast<uint8_t>(eDeleciya::inv); di++)
        {
            len_count = gt_sum.len_count.findDel(static_cast<eDeleciya>(di));
            outFile_gt1 <<'\t' <<len_count;
            if(len_count != 0)
                outFile_lt1 <<'\t' <<(gt_sum.len_sum.findDel(static_cast<eDeleciya>(di)) / len_count);
            else
                outFile_lt1 <<'\t' <<0;
        }

        //
        for(uint8_t del = static_cast<uint8_t>(eDeleciya::del_1a); del < static_cast<uint8_t>(eDeleciya::del_end); del++)
        {
            len_count = gt_sum.len_count.findDel(static_cast<eDeleciya>(del));
            outFile_gt1 <<'\t' <<len_count;
            if(len_count != 0)
                outFile_lt1 <<'\t' <<(gt_sum.len_sum.findDel(static_cast<eDeleciya>(del)) / len_count);
            else
                outFile_lt1 <<'\t' <<0;
        }

        //
        for(uint8_t inv = static_cast<uint8_t>(eDeleciya::inv_1a); inv < static_cast<uint8_t>(eDeleciya::inv_end); inv++)
        {
            len_count = gt_sum.len_count.findDel(static_cast<eDeleciya>(inv));
            outFile_gt1 <<'\t' <<len_count;
            if(len_count != 0)
                outFile_lt1 <<'\t' <<(gt_sum.len_sum.findDel(static_cast<eDeleciya>(inv)) / len_count);
            else
                outFile_lt1 <<'\t' <<0;
        }

        outFile_gt1 <<'\n';
        outFile_lt1 <<'\n';

        outFile_gt1.close();
        outFile_lt1.close();
        cout <<"in '" <<fn_gt1 <<"' -  save - ok " <<endl;
        cout <<"in '" <<fn_lt1 <<"' -  save - ok " <<endl;
        fOk = true;// удалось записать
    }
    catch(...)
    {
        cout <<endl <<"ERROR add to '" <<fn_gt1 <<"'!!!" <<endl;
        cout <<endl <<"ERROR add to '" <<fn_lt1 <<"'!!!" <<endl;
        fOk = false;
    }

    try
    {
        ofstream outFile_gt3(fn_gt3.c_str(), ios::out | ios::app);

        //
        outFile_gt3 <<_gr->mStatistic->CountGenom_Del_AND_Inv <<'\t';

        for(uint8_t di = static_cast<uint8_t>(eDeleciya::del); di <= static_cast<uint8_t>(eDeleciya::inv); di++)
        {
            outFile_gt3 <<gt_count.findDel(static_cast<eDeleciya>(di)) <<'\t';
        }

        //
        for(uint8_t del = static_cast<uint8_t>(eDeleciya::del_1a); del < static_cast<uint8_t>(eDeleciya::del_end); del++)
        {
            outFile_gt3 <<gt_count.findDel(static_cast<eDeleciya>(del)) <<'\t';
        }

        //
        for(uint8_t inv = static_cast<uint8_t>(eDeleciya::inv_1a); inv < static_cast<uint8_t>(eDeleciya::inv_end); inv++)
        {
            outFile_gt3 <<gt_count.findDel(static_cast<eDeleciya>(inv)) <<'\t';
        }

        outFile_gt3 <<'\n';

        outFile_gt3.close();
        cout <<"in '" <<fn_gt3 <<"' -  save - ok " <<endl;
        fOk = true;// удалось записать
    }
    catch(...)
    {
        cout <<endl <<"ERROR add to '" <<fn_gt3 <<"'!!!" <<endl;

        fOk = false;
    }
    return fOk;
}

bool cOutResult::outFile_RepTotalResults(void)
{

    string fn = RepDir+"/" + fileNamePrefix + RepTotalResults;
    cGloballRunable *_gr = cGloballRunable::Instance();

    s_cRSSTableItem &cRSSTableItem = _gr->mStatistic->cRSSTableItem_count;
    s_cRSSTableItem &cRSSTableItem_one = _gr->mStatistic->cRSSTableItem_one;


    bool fOk = false;
    try
    {
        ofstream outFile(fn.c_str(), ios::out | ios::app);
        outFile
                <<"Gene"<<"\t"
                <<(_gr->mStatistic->m_GenTable.size()+_gr->mStatistic->c_genNo_DI) <<"\t"
                <<_gr->mStatistic->CountGenom_Del_Inv <<"\t"
                <<_gr->mStatistic->CountGenom_Del <<"\t"
                <<_gr->mStatistic->CountGenom_Inv  <<"\t"
                <<_gr->mStatistic->c_genNo_DI <<endl

                <<"12/23cRSS" <<"\t"
                <<(cRSSTableItem_one._12 + cRSSTableItem_one._23) <<"\t"
                <<(cRSSTableItem.del_inv_12 + cRSSTableItem.del_inv_23) <<"\t"
                <<(cRSSTableItem.del_12 + cRSSTableItem.del_23) <<"\t"
                <<(cRSSTableItem.inv_12 + cRSSTableItem.inv_23) <<"\t"
                <<(cRSSTableItem._12 + cRSSTableItem._23) <<endl
                //<<_gr->mStatistic->c_cRSSNo_DI_12_23 <<endl

                <<"12cRSS" <<"\t"
                <<cRSSTableItem_one._12 <<"\t"
                <<(cRSSTableItem.del_inv_12) <<"\t"
                <<cRSSTableItem.del_12 <<"\t"
                <<cRSSTableItem.inv_12 <<"\t"
                <<cRSSTableItem._12  <<endl
                //<<_gr->mStatistic->c_cRSSNo_DI_12 <<endl

                <<"23cRSS" <<"\t"
                <<cRSSTableItem_one._23 <<"\t"
                <<(cRSSTableItem.del_inv_23) <<"\t"
                <<cRSSTableItem.del_23 <<"\t"
                <<cRSSTableItem.inv_23 <<"\t"
                <<cRSSTableItem._23  <<endl;
                //<<_gr->mStatistic->c_cRSSNo_DI_23 <<endl;

        outFile.close();
        cout <<"in '" <<fn <<"' -  save - ok" <<endl;
        fOk = true;// удалось записать
    }
    catch(...)
    {
        cout <<endl <<"ERROR add to '" <<fn <<"'!!!" <<endl;
        fOk = false;
    }
    return fOk;
}


//------------------------------------------------------------------------
// ощибочные
bool cOutResult::outFile_ErrorGen(string line)
{
    string fn = Dir+"/" + fileNamePrefix + ErrorGen;
    bool fOk = false;
    try
    {
        ofstream outFile(fn.c_str(), ios::out | ios::app);
        outFile <<line <<endl;
        outFile.close();
        fOk = true;// удалось записать
    }
    catch(...)
    {
        cout <<endl <<"ERROR add to '" <<fn <<"'!!!" <<endl;
        fOk = false;
    }
    return fOk;
}

//------------------------------------------------------------------------

//временные файлы
//создать котолог
bool cOutResult::createTmpDir(void)
{
    //создать структуру котологов
    tmpDir = Dir+"/" + fileNamePrefix + ".temp";

    if(_access(tmpDir.c_str(), 00) == -1) //если нет католога создаём
#if defined (_WIN32) || defined (WIN32)
    //код WIN
        if(_mkdir(tmpDir.c_str())==-1)
#else
    //код LINUX
        if(mkdir(tmpDir.c_str(), 0777)==-1)
#endif
        {
            cout <<"Failed to create a directory for the temp. \n";
            return false;
        }
    return true;
}


//сохранить в временые файлы структуры поиска
bool cOutResult::outFile_tmpDI_index(void)
{
    bool fOk = false;
    cGloballRunable *_gr = cGloballRunable::Instance();
    string fn_index = tmpDir +"/"+DI_idx;
    string fn_tmp = tmpDir +"/"+DI_tmp;

    try
    {
        ofstream outFile_index(fn_index.c_str(), ios::out | ios::app | ios::binary );
        ofstream outFile_tmp(fn_tmp.c_str(), ios::out | ios::app);

        outFile_index.seekp(0, ios::end);

        for (unordered_map<uint8_t, vector<cDI_out> >::iterator it = _gr->mGen->DI_out.begin(); it !=_gr->mGen->DI_out.end(); ++it)
        {
            vector<cDI_out> &vDI = it->second;
            for(size_t i = 0; i < vDI.size() ; i++)
            {
                cDI_out &di = vDI[i];
                if (di.isDupl)
                {
                    outFile_tmp <<outFile_index.tellp() <<'\t';
                    cDIindex dii(_gr->mGen, static_cast<eDeleciya>(it->first), di);
                    outFile_index.write(reinterpret_cast<char*>(&dii), sizeof(class cDIindex) );
                }
                else
                {
                    outFile_tmp <<"-1" <<'\t';
                }
                            //поля необходимые
                outFile_tmp <<_gr->mGen->file <<'\t'
                            <<_gr->mGen->locus <<'\t'
                            <<_gr->mGen->geneName <<'\t'
                            <<di.toString(_gr->mGen)
                            <<Deleciya_toString(static_cast<eDeleciya>(it->first)) <<'\t'
                            <<di.duplDel <<'\t'
                            <<di.duplInv <<'\t'
                            <<di.duplDelInv
                            <<endl;
            }
        }

        outFile_index.seekp(0,ios::end);
        outFile_tmp.close();
        outFile_index.close();

        fOk = true;// удалось записать
    }
    catch(...)
    {
        cout <<endl <<"ERROR add to '" <<fn_index <<"'!!!" <<endl;
        cout <<endl <<"ERROR add to '" <<fn_tmp <<"'!!!" <<endl;
        fOk = false;
    }
    return fOk;

}


//попытка удалить
bool cOutResult::remove_tmp_files(void)
{
    bool fOk = true;
    try
    {

        string fn_index = tmpDir +"/"+DI_idx;
        if(remove(fn_index.c_str()))
        {
            fOk=false;
            cout <<"Dont del: " <<fn_index <<endl;
        }

        string fn_tmp = tmpDir +"/"+DI_tmp;
        if(remove(fn_tmp.c_str()))
        {
            fOk=false;
            cout <<"Dont del: " <<fn_tmp <<endl;
        }
    }
    catch(...)
    {
        cout <<endl <<"No delete !!!" <<endl;
        fOk = false;
    }

    return fOk;
}


//попытка удалить
bool cOutResult::remove_tmp_dir(void)
{
    bool fOk = true;
    try
    {
        if(_rmdir(tmpDir.c_str())==-1)
        {
            cout <<"Dont del tmp dir: " <<tmpDir <<endl;
            fOk = false;
        }
    }
    catch(...)
    {
        cout <<endl <<"No delete !!!" <<endl;
        fOk = false;
    }
    return fOk;
}


bool cOutResult::createFiles_DI(void)
{
    bool fOk = false;
    string fn_DI;
    try
    {
        ostringstream sout("");
        sout  <<Dir <<"/" <<fileNamePrefix  <<DI <<"-" <<(countFiles) <<".txt";
        fn_DI = sout.str();
        ofstream outFile_DI(fn_DI.c_str(), ios::out);
        outFile_DI <<"Chr	Locus	Gene	12cRSS	23cRSS	Length	Type	Del-dupl	Inv-dupl	Del/Inv-dupl	Genome-Del-dupl	Genome-Inv-dupl	Genome-Del/Inv-dupl" <<endl;
        outFile_DI.close();
    }
    catch(...)
    {
        cout <<endl <<"Can't create '" <<fn_DI <<"'!!!" <<endl;
        fOk = false;
    }
    try
    {
        ostringstream sout("");
        sout  <<Dir <<"/" <<fileNamePrefix  <<DI_dupl <<"-" <<(countFiles) <<".txt";
        fn_DI = sout.str();
        ofstream outFile_DI(fn_DI.c_str(), ios::out);
        outFile_DI <<"Chr	Locus	Gene	12cRSS	23cRSS	Length	Type	Del-dupl	Inv-dupl	Del/Inv-dupl	Genome-Del-dupl	Genome-Inv-dupl	Genome-Del/Inv-dupl" <<endl;
        outFile_DI.close();
    }
    catch(...)
    {
        cout <<endl <<"Can't create '" <<fn_DI <<"'!!!" <<endl;
        fOk = false;
    }
    return fOk;

}


bool cOutResult::outFile_DI(void)
{
    bool fOk = false;
    long int pos = 0;

    string fn_index = tmpDir +"/"+DI_idx;
    string fn_tmp = tmpDir +"/"+DI_tmp;
    string fn_DI;
    string fn_DI_dupl;

    try
    {
        ifstream inFileDItmp((fn_tmp).c_str());
        ifstream inFile_index(fn_index.c_str(), ios::in | ios::binary);
        if (!inFileDItmp.is_open())
            return false;
        ofstream outFile_DI;
        ofstream outFile_DI_dupl;
        {
            //формирование имени
            ostringstream sout("");
            sout  <<Dir <<"/" <<fileNamePrefix  <<DI <<"-" <<(countFiles) <<".txt";
            fn_DI = sout.str();
            outFile_DI.open(fn_DI.c_str(), ios::out | ios::app);
        }
        {
            //формирование имени
            ostringstream sout("");
            sout  <<Dir <<"/" <<fileNamePrefix  <<DI_dupl <<"-" <<(countFiles) <<".txt";
            fn_DI_dupl = sout.str();
            outFile_DI_dupl.open(fn_DI_dupl.c_str(), ios::out | ios::app);
        }


        string line("");
        while ( inFileDItmp.good() )
        {
            inFileDItmp >>pos;
            line="";
            getline(inFileDItmp, line, '\n');
            line = ltrim(line);

            if(line.empty())
                continue; // пустая строка

            cDIindex dii;

            //найти нужный файл, позицию и прочесть
            if(pos == -1)
            {
                outFile_DI  <<line <<'\t'
                            <<0 <<'\t'
                            <<0 <<'\t'
                            <<0 <<endl;
            }
            else
            {
                inFile_index.seekg(pos, ios::beg);
                inFile_index.read(reinterpret_cast<char*>(&dii), sizeof(class cDIindex) );
                outFile_DI  <<line <<'\t'
                            <<dii.duplGenomeDel <<'\t'
                            <<dii.duplGenomeInv <<'\t'
                            <<dii.duplGenomeDelInv <<endl;
                outFile_DI_dupl <<line <<'\t'
                                <<dii.duplGenomeDel <<'\t'
                                <<dii.duplGenomeInv <<'\t'
                                <<dii.duplGenomeDelInv <<endl;

            }
            recCout++;
        }
        outFile_DI.close();
        outFile_DI_dupl.close();
        inFileDItmp.close();
        inFile_index.close();
        remove_tmp_files(); //убить временные
    }
    catch(...)
    {
        cout <<endl <<"ERROR add to '" <<fn_DI <<"'!!!" <<endl;
        fOk = false;
    }
    return fOk;

}


bool cOutResult::load_index_File(vector<cDIindex> &D)
{
    bool fOk = true;
    string fn_index = tmpDir +"/"+DI_idx;
    try
    {
            ifstream inFile_index(fn_index.c_str(), ios::in | ios::binary );
            if (!inFile_index.is_open())
            {
                //cout <<endl <<"ERROR open  '" <<fn_index <<"'!!!" <<endl;
                return false;
            }
            while ( inFile_index.good() )
            {
                cDIindex dii;
                inFile_index.read(reinterpret_cast<char*>(&dii), sizeof(class cDIindex) );
                if( inFile_index.good() )
                    D.push_back(dii);
            }
            inFile_index.close();
            fOk = true;
    }
    catch(...)
    {
        cout <<endl <<"ERROR load index  '" <<fn_index <<"'!!!" <<endl;
        fOk = false;
    }
    return fOk;
}

bool cOutResult::save_index_File(vector<cDIindex> &D)
{
    bool fOk = true;
    string fn_index = tmpDir +"/"+DI_idx;

    try
    {
        ofstream outFile_index(fn_index.c_str(), ios::out | ios::binary );
        for(size_t i = 0; i < D.size(); i++)
        {
            outFile_index.write(reinterpret_cast<char*>(&D[i]), sizeof(class cDIindex) );
        }
        outFile_index.close();
        fOk = true;
    }
    catch(...)
    {
        cout <<endl <<"ERROR save to '" <<fn_index <<"'!!!" <<endl;
        fOk = false;
    }
    return fOk;
}

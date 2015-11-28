#ifndef CGENESPARAM_H
#define CGENESPARAM_H

#include "utils.h"

using namespace std;


class cGenesParam
{
private:

typedef unordered_set<tGenLen> Tset_pos;
typedef unordered_map<tContigNumber, Tset_pos >  Tmap_locus_pos;
typedef unordered_map<size_t, Tmap_locus_pos > Tmap_LIST;

public:

    vector<string> mFile;
    vector<string> mGenNames;
    vector<sGene> mGenes;
    ///файли list - доп критерии
    Tmap_LIST list1;
    Tmap_LIST list2;



    /// загрузить файл Gene.txt
    bool LoadGene(const string &fileName);

    ///для проверки, вывод на консоль
    void toString(void);
    ///поиск нужного
    tGenesFindResult findGene(const size_t &fileIndex, const size_t &geneNameIndex, const tContigNumber &contigNumber);

    ///найти имя файла index - индех найденого / добавленого
    bool findFileIndex(const string &fileName,  size_t &index);
    ///найти имя гена index - индех найденого / добавленого
    bool findGenIndex(const string &genName,  size_t &index);


    /// загрузить файл list.txt, второй параметр номер варианта: list1 или list2
    bool LoadList(const string &fileName, int tipFile);

    /// проверить одину строку DI на необходимость поиска дублей
    bool chekOneDIonNeedFindDubl(const size_t &chr, const tContigNumber &locus, const tGenLen &pos1, const tGenLen &pos2);


    ///очистка памяти
    void clearMemory(void)
    {
        mGenes.clear();
        mFile.clear();
        mGenNames.clear();
        vector<string>(mGenNames).swap(mGenNames);
        vector<string>(mFile).swap(mFile);
        vector<sGene>(mGenes).swap(mGenes);
        list1.clear();
        list2.clear();
        reserveMemory();
    }
    ///резервирование места для векторов, степени двойки, предположительно не меньше
    void reserveMemory(void)
    {
        mGenes.reserve(36000);
        mFile.reserve(32);
        mGenNames.reserve(36000);
    }

    cGenesParam():
        mFile(),
        mGenNames(),
        mGenes(),
        list1(),
        list2()
    {
        reserveMemory();
    }

    ~cGenesParam() {}
protected:
private:

    /// парсить одну строку файла Gene.txt
    bool ParseOneLineGene(const string &line, sGene &gen);
    bool ParseOneLineGene_RNA(const string &str_rna, sGene &gen);

    ///найти имя файла или  добавить, num - индех найденого / добавленого
    bool find_addFileName(const string &fileName,  size_t &num);

    ///найти имя гена или  добавить, num - индех найденого / добавленого
    bool find_addGenName(const string &genName,  size_t &num);

    /// парсить одну строку файла List.txt
    bool ParseOneLineList(const string &line, string &chr_line, size_t &chr, tContigNumber &locus, tGenLen &pos);
    /// всавить строку in LIST
    bool insertOneListLine(Tmap_LIST &li, const size_t &chr, const tContigNumber &locus, const tGenLen &pos);

};

#endif // CGENESPARAM_H

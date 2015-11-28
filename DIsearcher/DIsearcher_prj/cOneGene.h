#ifndef CONEGENE_H
#define CONEGENE_H

#include "utils.h"
#include "cRSS.h"
#include "cDI_out.h"


using namespace std;


class cOneGene
{
public:
    enum state
    {
        state_FatalError =-2,
        state_invalidString =-1,
        state_ok=0,
        state_newGene =1,
        state_newLokus =2
    };

    /// вариант несколько масивов для каждого типа
    vector<cRSS> rss12_0;
    vector<cRSS> rss12_1;
    vector<cRSS> rss23_0;
    vector<cRSS> rss23_1;

    ///список найденых элементов
    //list<cDI_out> di_out;
    unordered_map<uint8_t, vector<cDI_out> > DI_out;


    /// параметры одного гена, для отличия одного от другого
    string geneName;
    string file;
    string locus;
    size_t fileIndex;
    size_t geneNameIndex;
    size_t geneIndex;

    tContigNumber locusVal;

    /// очистить масивы
    void ClearGen(void);

    ///очистка памяти
    void clearMemoryRSS(void)
    {
        ClearGen();
        vector<cRSS>(rss12_0).swap(rss12_0);
        vector<cRSS>(rss12_1).swap(rss12_1);
        vector<cRSS>(rss23_0).swap(rss23_0);
        vector<cRSS>(rss23_1).swap(rss23_1);
    }

    ///резервирование места для векторов, степени двойки, предположительно не меньше
    void reserveMemoryRSS(void)
    {
        rss12_0.reserve(1024);
        rss12_1.reserve(1024);
        rss23_0.reserve(1024);
        rss23_1.reserve(1024);
    }


    /// парсить строку
    state ParseString(string _in);

    /// обработка одного гена
    bool workOneGen(string line);


    /// обработка одного локуса
    bool LocusDublWork(void);


    cOneGene():
        rss12_0(),
        rss12_1(),
        rss23_0(),
        rss23_1(),
        //di_out(),
        DI_out(),
        geneName(""),
        file(""),
        locus(""),
        fileIndex(0),
        geneNameIndex(0),
        geneIndex(0),
        locusVal(0),
        typeDel_Inv()
    {
        reserveMemoryRSS();
    }
    ~cOneGene()
    {
        ClearGen();
    }

protected:
private:

    // локальная переменная для передаси через функции
    eDeleciya typeDel_Inv;

    /// определить коэфициенты A и B
    void detectKoefAB(void);


    /// вставка в список с проверкой памяти
    bool di_out_push_back(eDeleciya del_inv, const cDI_out &_di);

    /// определение делиций
    bool detectDel_cikl(void);
    bool detectDel(const cRSS &r0, const cRSS &r1);
    bool detectDel_TypeGene_A(const cRSS &r0, const cRSS &r1);
    bool detectDel_TypeGene_B(const cRSS &r0, const cRSS &r1);
    inline bool detectDel_TypeGene_C(const cRSS &r0, const cRSS &r1);

    /// определение инверсий
    bool detectInv_cikl(void);
    bool detectInv_0(const cRSS &r1, const cRSS &r2);
    bool detectInv_TypeGene_A_0(const cRSS &r1, const cRSS &r2);
    bool detectInv_TypeGene_B_0(const cRSS &r1, const cRSS &r2);
    inline bool detectInv_TypeGene_C_0(const cRSS &r1, const cRSS &r2);
    bool detectInv_1(const cRSS &r1, const cRSS &r2);
    bool detectInv_TypeGene_A_1(const cRSS &r1, const cRSS &r2);
    bool detectInv_TypeGene_B_1(const cRSS &r1, const cRSS &r2);
    inline bool detectInv_TypeGene_C_1(const cRSS &r1, const cRSS &r2);

    void detectDupl(void);

};

#endif // CONEGENE_H

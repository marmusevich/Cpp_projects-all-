#ifndef CGLOBALLRUNABLE_H
#define CGLOBALLRUNABLE_H

#include "utils.h"
#include "cOneGene.h"
#include "cStatistic.h"
#include "cGenesParam.h"
#include "cDupl.h"

using namespace std;

class cGloballRunable
{
public:

    ///
    unsigned int DI_min;
    unsigned int DI_max;


    unsigned int Max_count_dupl;
    ///
    cGenesParam genesParam;
    ///обрабатываемый ген
    tr1::shared_ptr<cOneGene> mGen;

    ///его статистика
    tr1::shared_ptr<cStatistic> mStatistic;

    ///его структура поиска дуьлей
    tr1::shared_ptr<cDupl> mDupl;


    ///загрузить и обработать cRSS
    bool LoadAndWorckRSS(string fileName);


    ///осчиста памяти
    void clearMem(void)
    {
        mGen.reset();
        mStatistic.reset();
        mDupl.reset();
    }

    /// реализация шаблона одиночька
    /// создать / получить объект
    static cGloballRunable* Instance(void)
    {
        if(!mSelf)
        {
            mSelf = new cGloballRunable();
        }
        return mSelf;
    }
    /// уничьтожить
    static bool DeleteInstance(void)
    {
        if(mSelf)
        {
            delete mSelf;
            mSelf = NULL;
            return true;
        }
        return false;
    }

protected:
private:


    // для реализации шаблона одиночка
    static cGloballRunable *mSelf;
    cGloballRunable():
        DI_min(0),
        DI_max(0),
        Max_count_dupl(0),
        genesParam(),
        mGen(),
        mStatistic(),
        mDupl()
    {}


    ~cGloballRunable()
    {

    }
    //запрет копирования и присваивания
    cGloballRunable(const cGloballRunable& root);
    const cGloballRunable& operator=(cGloballRunable&);
};

#endif // CGLOBALLRUNABLE_H

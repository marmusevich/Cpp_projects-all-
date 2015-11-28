#ifndef COUTRESULT_H
#define COUTRESULT_H

#include "utils.h"
#include "cGloballRunable.h"
#include "cDIindex.h"

using namespace std;

class cOutResult
{
public:
    ///путь к рабочим файлам
    static string Worck_path;
    static const string Dir;
    static const string Del;
    static const string DelInv;
    static const string DelInvUnc;
    static const string DelUnc;
    static const string DI;
    static const string DI_dupl;
    static const string Inv;
    static const string InvUnc;
    static const string NoDelInv;
    static const string NoDelInvUnc;
    ///reports
    static const string RepDir;
    static const string RepRSSTable1;
    static const string RepRSSTable2;
    static const string RepGenNo_DI;
    static const string RepGenTable1;
    static const string RepGenTable2;
    static const string RepGenTable3;
    static const string RepLengthTable1;
    static const string RepLengthTable2;
    static const string RepTotalResults;
    /// ощибочные
    static const string ErrorGen;
    /// временные
    static const string DI_tmp;
    static const string DI_idx;

    ///создать структуру котологов
    static bool createDir(void);
    ///создать пустые файлы с заголовками
    static bool createFiles(void);

    ///Установить префикс для имен файлов
    static void setFileNamePrefix(string fileName);

    /// функции сохранений
    static bool outFile_DI(void);
    static bool createFiles_DI(void);

    //сохранить те cRSS которые создают Del Inv и не создают
    static bool outFile_Del_Inv_DelInv_NO(void);
    static bool outFile_DelUnc(void);
    static bool outFile_InvUnc (void);
    static bool outFile_DelInvUnc(void);
    static bool outFile_NoDelInvUnc(void);
    ///reports "DIsearcher/Table/";
    static bool outFile_RepRSSTable(void);
    static bool outFile_RepGenNo_DI(void);
    static bool outFile_RepTable(void);
    static bool outFile_RepTotalResults(void);
    /// ощибочные
    static bool outFile_ErrorGen(string line);

    ///временные файлы
    ///создать котолог
    static bool createTmpDir(void);
    ///сохранить в временые файлы структуры поиска
    static bool outFile_tmpDI_index(void);
    static bool load_index_File(vector<cDIindex> &D);
    static bool save_index_File(vector<cDIindex> &D);
    ///попытка удалить
    static bool remove_tmp_files(void);
    static bool remove_tmp_dir(void);

    ///создает файл уникальных записей, параметры - потоки входа/выхода, возвращает количество записаных строк
    static size_t make_Unc(ifstream &inFile, ofstream &outFile, tRSSTableItem &_12,tRSSTableItem &_23);



    //префикс для имен файлов
    static string fileNamePrefix;
    //временный каталог
    static string tmpDir;

    static const tFileLineNumer MaxRecInDI;
    static size_t countFiles;
    static tFileLineNumer recCout;
};

#endif // COUTRESULT_H

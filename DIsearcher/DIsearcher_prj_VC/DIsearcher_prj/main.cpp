#include "utils.h"
#include "cOutResult.h"
#include "cGloballRunable.h"
#include "cStatistic.h"




///2.txt genlist_mouse_isx.txt 40 list1_.txt list2_.txt 50000
///1.txt gene.txt 40 list1.txt list2.txt 100




using namespace std;

///загрузка перечня файлов для обработки
bool LoadListRssFile(string fileName, vector<string> &fileListRss);


/// Run This
int main(int argc, char** argv)
{
    // для подсчета времени работы проги
    // начало работы
    clock_t clock_begin = clock();
    time_t seconds = time(NULL);
    tm* timeinfo = localtime(&seconds);
    cout <<"Start " <<asctime(timeinfo) <<endl;
    //*********************************************************************************************************************************
    // получение и проверка входных параметров
    if(argc != 7)
    {
        cout    <<"For run type:'DIsearcher.exe FILE_1.txt FILE_gene.txt DI_min DI_max list1.txt list2.txt', "
                <<"where: FILE_1.txt, FILE_gene.txt - file name, DI_min and DI_max  - numerik,"
                <<"list1.txt and list2.txt  - file name" <<endl;
        return 0;
    }
    bool isError=false;
    string fileNameListRSS = string(argv[1]);
    if(fileNameListRSS.empty())
    {
        cout <<"File Name 'List file RSS' is empty." <<endl;
        isError=true;
    }

    string fileNameGene = string(argv[2]);
    if(fileNameGene.empty())
    {
        cout <<"File Name 'gene' is empty." <<endl;
        isError=true;
    }

    if( ( strlen(argv[3]) < 1) ||
            ( !isdigit(argv[3][0]) ) )
    {
        cout <<"Param DI_min is empty or not numeric." <<endl;
        isError=true;
    }


    if( ( strlen(argv[4]) < 1) ||
            ( !isdigit(argv[4][0]) ) )
    {
        cout <<"Param DI_max is empty or not numeric." <<endl;
        isError=true;
    }


    string fileNameList1 = string(argv[5]);
    if(fileNameList1.empty())
    {
        cout <<"File Name 'List1' is empty." <<endl;
        isError=true;
    }

    string fileNameList2 = string(argv[6]);
    if(fileNameList2.empty())
    {
        cout <<"File Name 'List1' is empty." <<endl;
        isError=true;
    }

//    if( ( strlen(argv[7]) < 1) ||
//            ( !isdigit(argv[7][0]) ) )
//    {
//        cout <<"Param Uslovie is empty or not numeric." <<endl;
//        isError=true;
//    }


    if(isError)
    {
        cout <<"Error command line for run: '" <<argv[0] <<" " <<argv[1] <<" " <<argv[2] <<" " <<argv[3]
                <<" " <<argv[4] <<" " <<argv[5] <<" " <<argv[6] <<"'" <<endl;
        return 0;
    }

    //----------------------------------------------------------------------------------------------------------------------------------
    // подготовка
    vector<string> fileListRss;
    bool fLoadFileListRSS = LoadListRssFile(fileNameListRSS, fileListRss);
    bool fCanCreatDir = cOutResult::createDir();

    if(!(fLoadFileListRSS && fCanCreatDir )) //хотябы один плохо
    {
        cout <<"ERROR. not read / write to disk!" <<endl;
        return 0;
    }

    cGloballRunable *_gr = cGloballRunable::Instance();
    _gr->DI_min = atoi(argv[3]);
    _gr->DI_max = atoi(argv[4]);
    _gr->Max_count_dupl =0; // atoi(argv[7]);


    //загрузка Gene.txt
    //bool fLoadGene = _gr->LoadGene(fileNameGene);
    bool fLoadGene = _gr->genesParam.LoadGene(fileNameGene);

    fLoadGene = _gr->genesParam.LoadList(fileNameList1, 1) && fLoadGene;
    fLoadGene = _gr->genesParam.LoadList(fileNameList2, 2) && fLoadGene;

    if(!(fLoadGene)) //хотябы один плохо
    {
        cout <<"ERROR. not load 'Gene.txt' disk!" <<endl;
        return 0;
    }

    //----------------------------------------------------------------------------------------------------------------------------------
    // цикл по именам файлам
    for(unsigned int i = 0; i < fileListRss.size(); i++)
    {
        cOutResult::setFileNamePrefix(fileListRss[i]);
        if(!( cOutResult::createFiles() && cOutResult::createTmpDir())) //хотябы один плохо
        {
            cout <<"ERROR. not write to disk files with results for < " <<fileListRss[i] <<" >!" <<endl;
            continue;
        }

        /// создание объектов
        _gr->mGen = (tr1::shared_ptr<cOneGene> ) new cOneGene();
        _gr->mStatistic = (tr1::shared_ptr<cStatistic> ) new cStatistic();
        _gr->mDupl = (tr1::shared_ptr<cDupl> ) new cDupl();


        ///обработать RSS
        _gr->LoadAndWorckRSS(fileListRss[i]);
        _gr->mGen->clearMemoryRSS();

        /// пост обработка файлов
        cout <<"Make uniq files." <<endl;
        cOutResult::outFile_DelUnc();
        cOutResult::outFile_InvUnc();
        cOutResult::outFile_DelInvUnc();
        cOutResult::outFile_NoDelInvUnc();


        ///выод результатов
        _gr->mStatistic->outFile_RSS();
        ///выод результатов по дублям
        cOutResult::outFile_RepTable();
        ///итоговая таблица
        cOutResult::outFile_RepTotalResults();
        ///очистить статистику
        _gr->mStatistic->Clear();

        ///удалить объекты, освободить ресурсы для нового файла
        _gr->clearMem();


        ///удалить временные файлы
        cOutResult::remove_tmp_dir();
    }


    //----------------------------------------------------------------------------------------------------------------------------------
    // уничтожить глобальные объекты
    cGloballRunable::DeleteInstance();


    //*************************************************************************************************************************************
    // для подсчета времени работы проги
    // конец работы
    clock_t clock_end = clock();
    seconds = time(NULL);
    timeinfo = localtime(&seconds);
    cout <<endl <<endl <<"end " <<asctime(timeinfo) <<"Working time " << (double)(clock_end - clock_begin)/CLOCKS_PER_SEC <<" s " <<endl;


    //system("pause 0");
    return 0;
}



///загрузка перечня файлов для обработки
bool LoadListRssFile(string fileName, vector<string> &fileListRss)
{
    bool fOk = false;
    fileListRss.clear();
    string line;
    unsigned int recCout=0;
    ifstream inputFile((fileName).c_str());
    if (inputFile.is_open())
    {
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
            fileListRss.push_back(line);
            recCout++;
        }
        inputFile.close();
        cout <<"Loading from list RSS file "<<recCout <<" lines. Saving to prog " <<fileListRss.size() <<endl <<endl;
        fOk = true;
    }
    else
    {
        cout << "Unable to open file <" <<fileName <<">" <<endl;
    }
    return fOk;

}

#include "cGloballRunable.h"
#include "utils.h"
#include "cOutResult.h"

cGloballRunable* cGloballRunable::mSelf = NULL;


bool cGloballRunable::LoadAndWorckRSS(string fileName)
{
    bool f = false;
    ostringstream a("");

    string line;
    unsigned long int CharasterCout = 0;
    unsigned long int recCout = 1;
    unsigned long int fileSyze = filesize((fileName).c_str());

    ifstream inputFile((fileName).c_str());
    if (inputFile.is_open())
    {
        //пропустить первую строку - это заголовок
        getline (inputFile, line);
        while ( inputFile.good() )
        {
            //читаем исходную строку
            getline (inputFile, line);
            if(line.length()<1)
            {
                continue;
            }
            CharasterCout+=line.length();
            //парсим
            //если ген тот же, добавляем RSS
            //иначе выполняем работу для одного гена
            //обнуляем данные,
            cOneGene::state state = mGen->ParseString(line);

            switch(state)
            {
            case cOneGene::state_FatalError:
                //просто игнорируем, пока
                a <<"#" <<recCout <<" - FatalError" <<" - \t" <<line;
                cout <<a.str() <<endl <<endl;
                cOutResult::outFile_ErrorGen(a.str());
                break;
            case cOneGene::state_invalidString:
                //просто игнорируем, пока
                a <<"#" <<recCout <<" - invalidString" <<" - \t" <<line ;
                cout <<a.str() <<endl <<endl;
                cOutResult::outFile_ErrorGen(a.str());
                break;
            case cOneGene::state_newGene:

                // Работа по гену
                mGen->workOneGen(line);
                cout <<"new genes  ( " << static_cast<double>(static_cast<long long>(CharasterCout)*100/fileSyze) <<" %) CharasterCout = " <<CharasterCout <<"  fileSyze = " <<fileSyze <<endl <<endl;

                //получения параметров нового
                state = mGen->ParseString(line);
                //cout <<"New gene: " <<mGen->geneName<< endl;
                break;
            case cOneGene::state_newLokus:
                // Работа по гену
                mGen->workOneGen(line);

                // Работа по локусу
                mGen->LocusDublWork();
                cout <<"new locus/chr ( " << static_cast<double>(static_cast<long long>(CharasterCout)*100/fileSyze) <<" %) CharasterCout = " <<CharasterCout <<"  fileSyze = " <<fileSyze <<endl <<endl;

                cOutResult::countFiles++;
                cOutResult::createFiles_DI();

                //получения параметров нового
                state = mGen->ParseString(line);
                //cout <<"New locus: " <<mGen->locus<< endl;
                break;
            case cOneGene::state_ok:
                ;
                break;
            }
            recCout++;
        }
        inputFile.close();

        //обработка последнего в файле
        mGen->workOneGen(line);
        mGen->LocusDublWork();

        cout <<" ---  CharasterCout = " <<CharasterCout <<"  fileSyze = " <<fileSyze <<endl <<endl;

        cout <<endl <<"Loading from RSS file "<<(recCout-1) <<" lines" <<endl <<endl <<endl;
        f = true;
    }
    else
    {
        cout << "Unable to open file <" <<fileName <<">" <<endl;
    }
    return f;
}



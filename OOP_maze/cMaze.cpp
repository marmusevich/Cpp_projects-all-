#include "cMaze.h"


const cMaze::elements cMaze::ArrayForConvertWall[16]=
{
    cMaze::elementSpace, //0
    cMaze::elementWall_NorthSout, //1
    cMaze::elementWall_EastWest, //2
    cMaze::elementWall_NorthEast, //3
    cMaze::elementWall_NorthSout, //4
    cMaze::elementWall_NorthSout, //5
    cMaze::elementWall_SoutEast, //6
    cMaze::elementWall_NorthSoutEast, //7
    cMaze::elementWall_EastWest, //8
    cMaze::elementWall_NorthWest, //9
    cMaze::elementWall_EastWest, //10
    cMaze::elementWall_EastWestNorth, //11
    cMaze::elementWall_SoutWest, //12
    cMaze::elementWall_NorthSoutWest, //13
    cMaze::elementWall_EastWestSout, //14
    cMaze::elementWall_Kros //15
};

const wchar_t cMaze::ArrayForConvertCharToUTF[elementEnd+1]=
{0x20, 0xB2, 0xDB, 0xBA, 0xCD, 0xD0, 0xD2, 0xC6, 0xB5, 0xC8, 0xC9, 0xBC, 0xBB, 0xCC, 0xB9, 0xCA, 0xCB, 0xCE, /*0xFE*/0xB0};
//{0x20, 0x2593, 0x2588, 0x2551, 0x2550, 0x2568, 0x2565, 0x255E, 0x2561, 0x255A, 0x2554, 0x255D, 0x2557, 0x2560, 0x2563, 0x2569, 0x2566, 0x256C, 0x25A0/*0x2591*/};
const unsigned char cMaze::ArrayForConvertCharToCP866[elementEnd+1]=
{0x20, 0xB2, 0xDB, 0xBA, 0xCD, 0xD0, 0xD2, 0xC6, 0xB5, 0xC8, 0xC9, 0xBC, 0xBB, 0xCC, 0xB9, 0xCA, 0xCB, 0xCE, /*0xFE*/0xB0};



void cMaze::setSize(unsigned short int x, unsigned short int y)
{
    mArray.resize(x,y);
    mIsGenerate = genType_NONE;
    fillMaze();
}

void cMaze::setSomeSpaceNum(unsigned short int number)
{
    int count = 0;
    unsigned short int x=0;
    unsigned short int y=0;
    bool _IsConvert = mIsConvert;

    //когда хотим заполнить пустатой больще пространства чем есть стен, просто очищаем поле
    if(number >= (unsigned short int)(getCountWall()*0.9))
    {
        fillMaze(elementSpace);
        generateAroundWall();
        //если был конвертирован разконвертировать, а потом опять конвертировать
        if(_IsConvert)
        {
            convertWall(true);
        }
        return;
    }

    //если был конвертирован разконвертировать, а потом опять конвертировать
    if(_IsConvert)
    {
        deConvertWall();
    }
    //пока не заменим нужное количество стен
    while(count < number)
    {
        x = rnd(1, mArray.getSize_x()-3);
        y = rnd(1, mArray.getSize_y()-3);
        if(IsWall(x, y))
        {
            mArray(x, y)=elementSpace;
            count++;
        }

    }

    //если был конвертирован разконвертировать, а потом опять конвертировать
    if(_IsConvert)
    {
        convertWall();
    }

}

void cMaze::setSomeSpacePercent(unsigned short int percent)
{
    if(percent==0 || percent > 90)
    {
        fillMaze(elementSpace);
        generateAroundWall();
        //если был конвертирован разконвертировать, а потом опять конвертировать
        if(mIsConvert)
        {
            convertWall(true);
        }
        return;
    }

    unsigned short int number = getCountWall() * percent / 100;
    setSomeSpaceNum(number);
}


void cMaze::generate(generatorType genType, bool reGenerate)
{
    //достаточен ли размер
    if((mArray.getSize_y()<2)||(mArray.getSize_x()<2))
    {
        return;
    }
    //уже сгенерирован, регенерация не нужна
    if(!((mIsGenerate == genType_NONE) || (reGenerate)))
    {
        return;
    }
    //вызов генератора в зависемости от типа
    switch(genType)
    {
    case genType_NONE:
        break;
    case genType_1:
        generateTape1();
        break;
//    case genType_1:
//        generateTape1();
//        break;
    }
    mIsGenerate = genType;
}

void cMaze::convertWall(bool reConvert)
{
    //уже конвертирован, регенерация не нужна
    if(mIsConvert && (!reConvert))
    {
        return;
    }
    for(unsigned short int y = 0; y < mArray.getSize_y(); y++)
    {
        for(unsigned short int x = 0; x < mArray.getSize_x(); x++)
        {
            convertWallOneElement(x, y);
        }
    }
    mIsConvert=true;
}

void cMaze::convertWallOneElement(unsigned short int x, unsigned short int y)
{
    //"неразрушаемая стена"
    if(IsIndestructibleWall(x, y))
    {
        return;
    }
    unsigned short int sumAround = (  1 * (!IsSpace(x, y-1))+ //север
                                      2 * (!IsSpace(x+1, y))+ //восток
                                      4 * (!IsSpace(x, y+1))+ //юг
                                      8 * (!IsSpace(x-1, y))); //запад

    elements el = ArrayForConvertWall[sumAround*(!IsSpace(x, y))];
    //заменяем концы
    if((sumAround == 1)&&(!IsSpace(x, y)))
    {
        el = elementWall_NorthEnd; //конец стены идущей с севера
    }
    if((sumAround == 4)&&(!IsSpace(x, y)))
    {
        el = elementWall_SoutEnd; //конец стены идущей с юга
    }
    if((sumAround == 2)&&(!IsSpace(x, y)))
    {
        el = elementWall_EastEnd; //конец стены идущей с востока
    }
    if((sumAround == 8)&&(!IsSpace(x, y)))
    {
        el = elementWall_WestEnd; //конец стены идущей с запада
    }

    if((sumAround == 0)&&(!IsSpace(x, y)))
    {
        el = elementWall_Collon; //конец стены идущей с запада
    }

    mArray(x, y) = el;
}



void cMaze::deConvertWall(void)
{
    //не конвертирован
    if(!mIsConvert)
    {
        return;
    }
    for(unsigned short int y = 0; y < mArray.getSize_y(); y++)
    {
        for(unsigned short int x = 0; x < mArray.getSize_x(); x++)
        {
            //обычная стена значит стена, заменяем простой стеной
            if(IsWall(x, y))
            {
                mArray(x, y)=elementWall;
            }
        }
    }
    mIsConvert=false;
}


void cMaze::generateTape1(void)
{
    // хранит пройденый путь
    std::stack <coordinate> trail;
    fillMaze(elementWall);
    generateAroundWall();
    coordinate cell;
    cell.x = rnd(1, mArray.getSize_x()-3);
    cell.y = rnd(1, mArray.getSize_y()-3);
    trail.push(cell);
    mArray(cell.x, cell.y) = elementSpace;
    while(!trail.empty())
    {
        cell=trail.top();
        if (type1PosibNextCell(cell))
        {
            cell = type1GetNextCell(cell);
            trail.push(cell);
            mArray(cell.x, cell.y) = elementSpace;
        }
        else
        {
            trail.pop();
        }
    }
}


bool cMaze::type1IsEmpty(unsigned short int x, unsigned short int y)
{
    if (IsWall(x, y))
    {
        unsigned short int sum=  IsSpace(x+1, y)+
                                 IsSpace(x-1, y)+
                                 IsSpace(x, y+1)+
                                 IsSpace(x, y-1);
        return sum <= 1;
    }
    return false;
}

bool cMaze::type1PosibNextCell(coordinate posit)
{
    return (type1IsEmpty(posit.x+1, posit.y) ||
            type1IsEmpty(posit.x-1, posit.y) ||
            type1IsEmpty(posit.x, posit.y+1) ||
            type1IsEmpty(posit.x, posit.y-1) );
}

cMaze::coordinate cMaze::type1GetNextCell(coordinate posit)
{
    coordinate aux;
    bool ok = false;
    while ( !ok )
    {
        unsigned short int  gen =  rnd(1, 5);
        switch(gen)
        {
        case 1:
            aux=coordinate(posit.x+1, posit.y);
            break;
        case 2:
            aux=coordinate(posit.x-1, posit.y);
            break;
        case 3:
            aux=coordinate(posit.x, posit.y+1);
            break;
        case 4:
            aux=coordinate(posit.x, posit.y-1);
            break;
        }
        if ( type1IsEmpty(aux.x, aux.y) )
        {
            ok=true;
        }
    }
    return aux;
}



void cMaze::generateAroundWall(const  elements elem)
{
    // горизонтальные стены
    for(unsigned short int x = 0; x < mArray.getSize_x(); x++)
    {
        mArray(x, 0) = elem;
        mArray(x, mArray.getSize_y()-1) = elem;
    }
    // вертикальные стены
    for(unsigned short int y = 0; y < mArray.getSize_y(); y++)
    {
        mArray(0, y) = elem;
        mArray(mArray.getSize_x()-1, y) = elem;
    }
}


void cMaze::fillMaze(const  elements elem )
{
    for(unsigned short int y = 0; y < mArray.getSize_y(); y++)
    {
        for(unsigned short int x = 0; x < mArray.getSize_x(); x++)
        {
            mArray(x, y) = elem;
        }
    }
}



void cMaze::saveToTXTFile(const std::string fileName)
{
    std::wofstream outFile((fileName+".txt").c_str(),std::ios::out);
    assert(outFile);
//setlocale(LC_ALL,"");

//    setlocale (LC_ALL, "russian_russia");
    for(unsigned short int y = 0; y < mArray.getSize_y(); y++)
    {
        for(unsigned short int x = 0; x < mArray.getSize_x(); x++)
        {
            wchar_t b= ArrayForConvertCharToUTF[mArray(x, y)];
            std::wstring a(L"");
            a=a+b;
            outFile <<a;
        }
        outFile <<std::endl;
    }
    outFile.close();
}

void cMaze::printToConsole(void)
{
    for(unsigned short int y = 0; y < mArray.getSize_y(); y++)
    {
        for(unsigned short int x = 0; x < mArray.getSize_x(); x++)
        {
            std::cout <<ArrayForConvertCharToCP866[mArray(x, y)];
        }
        std::cout << std::endl;
    }
}

unsigned int cMaze::getCountIndestructibleWall(void)
{
    unsigned int  count = 0;
    for(unsigned short int y = 0; y < mArray.getSize_y(); y++)
    {
        for(unsigned short int x = 0; x < mArray.getSize_x(); x++)
        {
            if (IsIndestructibleWall(x, y))
            {
                count++;
            }
        }
    }
    return count;
}

unsigned int cMaze::getCountWall(void)
{
    unsigned int  count = 0;
    for(unsigned short int y = 0; y < mArray.getSize_y(); y++)
    {
        for(unsigned short int x = 0; x < mArray.getSize_x(); x++)
        {
            if (IsWall(x, y))
            {
                count++;
            }
        }
    }
    return count;
}

unsigned int cMaze::getCountSpace(void)
{
    unsigned int  count = 0;
    for(unsigned short int y = 0; y < mArray.getSize_y(); y++)
    {
        for(unsigned short int x = 0; x < mArray.getSize_x(); x++)
        {
            if (IsSpace(x, y))
            {
                count++;
            }
        }
    }
    return count;
}


bool cMaze::IsSpace(unsigned short int x, unsigned short int y)
{
    return (mArray(x, y) == elementSpace);
}

bool cMaze::IsIndestructibleWall(unsigned short int x, unsigned short int y)
{
    return (mArray(x, y) == elementIndestructibleWall);
}


bool cMaze::IsWall(unsigned short int x, unsigned short int y)
{
    return !(mArray(x, y)==elementSpace || mArray(x, y)==elementIndestructibleWall);
}




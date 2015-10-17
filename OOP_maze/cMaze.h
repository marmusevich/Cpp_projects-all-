#ifndef CMAZE_H
#define CMAZE_H

#include <stack>
#include <string>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <clocale>
//#include <cwctype>
#include <cwchar>
#include "c2DArray.h"



class cMaze
{
public:
    ///виды элементов
    enum elements : unsigned char
    {
        elementBegin = 0, //начало
        elementSpace = 0, //свободное пространство
        elementWall = 1, //обшее обозначение стены
        elementIndestructibleWall = 2, // неразрушаемая стена
        elementWall_NorthSout = 3, // стена с севера на юг
        elementWall_EastWest = 4, //стена с востока намзапод
        elementWall_NorthEnd = 5, //конец стены идущей с севера
        elementWall_SoutEnd = 6, //конец стены идущей с юга
        elementWall_EastEnd = 7, //конец стены идущей с востока
        elementWall_WestEnd = 8, //конец стены идущей с запада
        elementWall_NorthEast = 9, //поворот с севера на восток
        elementWall_SoutEast = 10, //поворот с юга нв восток
        elementWall_NorthWest = 11, //поворот с севера на запад
        elementWall_SoutWest = 12, //поворот с юга на запод
        elementWall_NorthSoutEast = 13, //стена с севера на юг отвод на восток
        elementWall_NorthSoutWest = 14, //стена с севера на юг отвод на запад
        elementWall_EastWestNorth = 15, //стена с востока на запод отвод на север
        elementWall_EastWestSout = 16, //стена с востока на запод отвод на юг
        elementWall_Kros = 17, // полное пересечение
        elementWall_Collon = 18, //одиноко стоящая колона

        elementEnd = 18 //конец
    };
    ///выды алгоритмов построения
    enum generatorType : unsigned char
    {
        genType_NONE = 0,
        genType_1 = 1
    };

    /// компактное хранение коордианат
    struct coordinate
    {
        unsigned short int x; // the x coordinate
        unsigned short int y; // the y coordinate
        coordinate(unsigned short int _x, unsigned short int _y):x(_x), y(_y) {}
        coordinate():x(0), y(0) {}
    };


    ///конструкторы
    cMaze() : mArray(0, 0),mIsGenerate(genType_NONE),mIsConvert(false)
    {randomize();}

    cMaze(unsigned short int x, unsigned short int y): mArray(x, y),mIsGenerate(genType_NONE),mIsConvert(false)
    {randomize();}

    // деструктор
    //virtual ~cMaze();

    /// устоновить новый размер
    void setSize(unsigned short int x, unsigned short int y);

    /// получит текущие размеры
    unsigned short int getSize_x(void)
    {
        return mArray.getSize_x();
    }
    unsigned short int getSize_y(void)
    {
        return mArray.getSize_y();
    }

    /// переопределение оператора скобки ()
    elements &operator()(unsigned short int x, unsigned short int y)
    {
        return mArray(x, y);
    }
    const elements &operator()(unsigned short int x, unsigned short int y) const
    {
        return mArray(x, y);
    }




    ///генерация лабиринта,
    void generate(generatorType genType, bool reGenerate = false);
    ///конвертировать стены в направленые стены, углы, тройники и т.д.
    void convertWall(bool reConvert = false);
    ///вернутся к простым стенам
    void deConvertWall(void);
    ///устоновить проходы (number) количеством не более 90% от количества стен
    void setSomeSpaceNum(unsigned short int number);
    ///устоновить проходы (percent) процентом от количества стен, диапозон от 0% до 90%
    void setSomeSpacePercent(unsigned short int percent);

    /// построить вокруг лабиринта стену по умолчанию неразрушимая стена
    void generateAroundWall(const  elements elem = cMaze::elementIndestructibleWall);
    /// заполнить пространство элементом
    void fillMaze(const  elements elem = cMaze::elementSpace);


    /// уже генерировали?
    bool IsGenerate(void) {return mIsGenerate!=genType_NONE;}
    ///тип генерации
    generatorType getGenerateType(void) {return mIsGenerate;}
    ///уже конвертировали?
    bool IsConvert(void) {return mIsConvert;}


    /// находится ли в указоном месте пустое постранство (не стена)
    bool IsSpace(unsigned short int x, unsigned short int y);
    bool IsSpace(coordinate cor) {return IsSpace(cor.x, cor.y);}
    /// находится ли в указоном месте обычная стена
    bool IsWall(unsigned short int x, unsigned short int y);
    bool IsWall(coordinate cor) {return IsWall(cor.x, cor.y);}
    /// находится ли в указоном месте неразрушаемая стена
    bool IsIndestructibleWall(unsigned short int x, unsigned short int y);
    bool IsIndestructibleWall(coordinate cor) {return IsIndestructibleWall(cor.x, cor.y);}

    ///количество блоков неразрушаемая стена
    unsigned int getCountIndestructibleWall(void);
    ///количество блоков обычная стена
    unsigned int getCountWall(void);
    ///количество блоков пустое постранство
    unsigned int getCountSpace(void);

    ///для случайных чисел
    /// инициировать
    static void randomize(unsigned n = 0)
    {
        if(!n)
            srand(time(NULL));
        else
            srand(n);
    }
    /// получить в диапозоне от 0 до max
    static unsigned short int rnd(unsigned short int max)
    {
        if (max>0)
        {
            return rand() % (max+1);
        }
        return 0;
    }
    /// получить в диапозоне от N до M
    static unsigned short int rnd(unsigned short int min, unsigned short int max)
    {
        if (((max-min)>0) &&(min>=0))
        {
            return rand() % (max-min+1) + min;
        }
        return 0;
    }


    /// печать в стандартный поток вывода - консоль
    void printToConsole(void);

    /// сохранить в файл
    void saveToTXTFile(const std::string fileName);
private:
    static const elements ArrayForConvertWall[16];
    static const wchar_t ArrayForConvertCharToUTF[elementEnd+1];
    static const unsigned char ArrayForConvertCharToCP866[elementEnd+1];

    // хранит масив лабиринта
    C2DArray< elements > mArray;
    // уже генерировали
    generatorType mIsGenerate;
    //уже конвертировали
    bool mIsConvert;

    // генерация тип 1
    void generateTape1(void);
    // вспомогательные для типа 1
    bool type1PosibNextCell(coordinate posit);
    coordinate type1GetNextCell(coordinate posit);
    bool type1IsEmpty(unsigned short int x, unsigned short int y);


    //конвертировать стену на одном участке
    void convertWallOneElement(unsigned short int x, unsigned short int y);

    //запрет копирования и присваивания
    cMaze(const cMaze& other);
    cMaze& operator=(const cMaze& other);
};


#endif // CMAZE_H

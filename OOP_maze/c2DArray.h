#ifndef C2DARRAY_H_INCLUDED
#define C2DARRAY_H_INCLUDED
#include <vector>
#include <assert.h>

template <class T>
class C2DArray
{
private:
    unsigned short int size_x;
    unsigned short int size_y;
    std::vector<T> data;

public:
    C2DArray() {}

    C2DArray(unsigned short int new_size_x, unsigned short int new_size_y)
    {
        resize(new_size_x, new_size_y);
    }


    unsigned short int getSize_x(void) {return size_x;}
    unsigned short int getSize_y(void) {return size_y;}

    void resize(unsigned short int new_size_x, unsigned short int new_size_y)
    {
        data.resize(new_size_x * new_size_y);
        size_x = new_size_x;
        size_y = new_size_y;
    }

    T &operator()(unsigned short int x, unsigned short int y)
    {
        assert( x<=size_x && y<size_y );
        return data[y*size_x + x];
    }

    const T &operator()(unsigned short int x, unsigned short int y) const
    {
        assert( x<=size_x && y<size_y );
        return data[y*size_x + x];
    }
};


#endif // C2DARRAY_H_INCLUDED

#include <iostream>
//#include <stdio.h>

using namespace std;

//class A
//{
//public:
//    A()
//    {
//        cout <<"ctor A " <<endl;
//    }
//    ~A()
//    {
//        cout <<"dtor A " <<endl;
//    }
//};
//
//
//class B
//{
//public:
//    B()
//    {
//        cout <<"ctor B " <<endl;
//    }
//    ~B()
//    {
//        cout <<"dtor B " <<endl;
//    }
//};
//
//class C
//{
//public:
//    A a;
//    B b;
//};
//

// forward declaration
class Square;
class Circle;
class Triangle;

class Shape
{
public:
    Shape()
    {

    }
    //
    virtual void checkIntersection_Shape(Shape* shape) = 0;

    virtual void checkIntersection_Square(Square* square) =0;

    virtual void checkIntersection_Circle(Circle* circle) =0;

    virtual void checkIntersection_Triangle(Triangle* triangle) =0;

    virtual ~Shape()
    {

    }
};

class Square :public Shape
{
public:
    virtual void checkIntersection_Shape(Shape* shape)
    {
        shape->checkIntersection_Square(this);
    }

    virtual void checkIntersection_Square(Square* square)
    {
        cout <<" square &* square " <<endl;
    }

    virtual void checkIntersection_Circle(Circle* circle)
    {
        cout <<" square &* circle" <<endl;
    }

    virtual void checkIntersection_Triangle(Triangle* triangle)
    {
        cout <<" square &* triangle" <<endl;
    }
};

class Circle :public Shape
{
public:
    virtual void checkIntersection_Shape(Shape* shape)
    {
        shape->checkIntersection_Circle(this);
    }

    virtual void checkIntersection_Square(Square* square)
    {
        cout <<" circle &* square " <<endl;
    }

    virtual void checkIntersection_Circle(Circle* circle)
    {
        cout <<" circle &* circle" <<endl;
    }

    virtual void checkIntersection_Triangle(Triangle* triangle)
    {
        cout <<" circle &* triangle" <<endl;
    }
};

class Triangle :public Shape
{
public:
    virtual void checkIntersection_Shape(Shape* shape)
    {
        shape->checkIntersection_Triangle(this);
    }

    virtual void checkIntersection_Square(Square* square)
    {
        cout <<" triangle &* square " <<endl;
    }

    virtual void checkIntersection_Circle(Circle* circle)
    {
        cout <<" triangle &* circle" <<endl;
    }

    virtual void checkIntersection_Triangle(Triangle* triangle)
    {
        cout <<" triangle &* triangle" <<endl;
    }
};




int main()
{
    Shape* square = new Square();
    Shape* circle = new Circle();
    Shape* triangle = new Triangle();

    cout <<"<< square >> " <<endl <<endl;
    square->checkIntersection_Shape(square);
    square->checkIntersection_Shape(circle);
    square->checkIntersection_Shape(triangle);

    cout <<"<< circle >> " <<endl <<endl;
    circle->checkIntersection_Shape(square);
    circle->checkIntersection_Shape(circle);
    circle->checkIntersection_Shape(triangle);

    cout <<"<< triangle >> " <<endl <<endl;
    triangle->checkIntersection_Shape(square);
    triangle->checkIntersection_Shape(circle);
    triangle->checkIntersection_Shape(triangle);


    return 0;
}


#ifndef SINGLETON_H
#define SINGLETON_H

template<typename T> class singleton
{
public:
	static T& get()
	{
		static T theSingleInstance; // у класса T есть конструктор по умолчанию
		return theSingleInstance;
	}
};

#endif

// одиночька
//class OnlyOne
//{
//public:
//        static OnlyOne& const Instance()
//        {
//                static OnlyOne theSingleInstance;
//                return theSingleInstance;
//        }
//private:
//        OnlyOne(){}
//        OnlyOne(OnlyOne& root){}
//OnlyOne& operator=(OnlyOne&){}
//};

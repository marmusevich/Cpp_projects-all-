#ifndef SINGLETON_H
#define SINGLETON_H

template<typename T> class singleton
{
public:
	static T& get()
	{
		static T theSingleInstance; // � ������ T ���� ����������� �� ���������
		return theSingleInstance;
	}
};

#endif

// ���������
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

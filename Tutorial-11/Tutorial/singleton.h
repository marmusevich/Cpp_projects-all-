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

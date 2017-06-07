#include <iostream>
#include <string>
#include <fstream>

#include "book.h"
#include "catalog.h"

using namespace std;



Catalog readCatalog(const string& fileName)
{
	Catalog c;
	ifstream in (fileName);
	in >> c;
	in.close();
	return c;
}


Catalog mergeCatalogs (const Catalog& cat1, const Catalog& cat2)
{
	Catalog result (cat1.size() + cat2.size());
	int i = 0;
	int j = 0;
	while (i < cat1.size() && j < cat2.size())
	{
		Book b1 = cat1.get(i);
		Book b2 = cat2.get(j);
		if (b1.getID() < b2.getID())
		{
			result.add(b1);
			++i;
		}
		else
		{
			result.add(b2);
			++j;
		}
	}
	while (i < cat1.size())
	{
		result.add(cat1.get(i));
		++i;
	}
	while (j < cat2.size())
	{
		result.add(cat2.get(j));
		++j;
	}
	return result;
}


void mergeCatalogFiles (const string& catalogFile1, const string& catalogFile2)
{
	Catalog c1, c2;
	c1 = readCatalog(catalogFile1);
    cout << catalogFile1 << " contained " << c1.size() << " books." << endl;
	c2 = readCatalog(catalogFile2);
    cout << catalogFile2 << " contained " << c2.size() << " books." << endl;
    Catalog c3 = mergeCatalogs (c1, c2);
    cout <<  "Their merge contains " << c3.size() << " books." << endl;
    cout << c3 << flush;
}

int main (int argc, char** argv)
{
	if (argc != 3)
	{
		cerr << "Usage: " << argv[0] <<
				"catalogFile1 catalogFile2" << endl;
		return -1;
	}
	string file1 = argv[1];
	string file2 = argv[2];
	mergeCatalogFiles (file1, file2);
	return 0;
}

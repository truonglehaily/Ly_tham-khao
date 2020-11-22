#ifndef _Categories_Data_H
#define _Categories_Data_H

#include <string>
#include <vector>
#include "../businessobjects/Categories.h"

using namespace std;

class CategoriesData{
public:
    int maxId;
private:
    vector<Categories> _data;
public:
    CategoriesData();
    CategoriesData(string s);
	int CreateCategory(Categories c);
    int UpdateCategory(int id, Categories c);
    Categories Get(int id);
    Categories* GetPointer(int id);
    int GetSize();
    int ExportToFile(string filename);
};

#endif
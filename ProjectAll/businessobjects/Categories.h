#ifndef _Categories_H
#define _Categories_H

#include <string>
#include "../libs/json.hpp"

using namespace std;
using json = nlohmann::json;

class Categories{
public:
	int CategoryID;
	string CategoryName, Description;
public:
	Categories();
	Categories(int CategoryID, string CategoryName, string Description);
	string ToString();
	json ToJson();
};

#endif

#include "Categories.h"

using namespace std;

/** @brief Function constructors an object.
 *  
 *  Function constructors an object.
 */
Categories::Categories(){
	
}

/** @brief Function constructors an object with params.
 *  
 *  Function constructors an object with params.
 */
Categories::Categories(int CategoryID, string CategoryName, string Description){
	this->CategoryID = CategoryID;
	this->CategoryName = CategoryName;
	this->Description = Description;
}

/** @brief Function converts this object to string.
 *  
 *  Function converts this object to string.
 *  @return a string;
 *  Example: Categories c(1, "Soft", "Drink") -> {1, Soft, Drink}
 */
string Categories::ToString(){
	string s;
	s += "{";
	s += to_string(CategoryID) + ", ";
	s += CategoryName + ", ";
	s += Description;
	s += "}";
	return s;
}

/** @brief Function converts this object to json object.
 *  
 *  Function converts this object to json object.
 *  @return a json object;
 *  Example: Categories c(1, "Soft", "Drink") -> {"CategoryID":1,"CategoryName":"Soft","Description":"Drink"}
 */
json Categories::ToJson(){
	json j;
	j["CategoryID"] = CategoryID;
	j["CategoryName"] = CategoryName;
	j["Description"] = Description;
	return j;
}

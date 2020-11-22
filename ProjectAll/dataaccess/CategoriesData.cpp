/** @file CategoriesData.h
 *  @brief CategoriesData stores all Categories objects
 *  
 *  @author Ly Truong (truonglehaily)
 *  @bug No known bugs.
 */

#include "CategoriesData.h"
#include <fstream>
#include "../libs/json.hpp" //https://github.com/nlohmann/json

using json = nlohmann::json;

/** @brief Function constructors an object.
 *  
 *  Function constructors an object.
 */
CategoriesData::CategoriesData(){
    maxId = 0;
    _data.resize(0);
}

/** @brief Function constructors an object.
 *  
 *  Function constructors an object, read data from file then load data to this object.
 */
CategoriesData::CategoriesData(string filename){
    maxId = 0;
    _data.resize(0);
    ifstream inFile(filename);
    const int maxSize = 255;
    char buff[maxSize];
    while (inFile.getline(buff, maxSize)){
        json j = json::parse(buff);
        Categories c(
            j["CategoryID"],
            j["CategoryName"],
            j["Description"]
        );
        _data.push_back(c);
    };
    inFile.close();
}

/** @brief Function add a Categories object to the end of the list inside CategoriesData.
 *  
 *  Function add a Categories object to the end of the list inside CategoriesData.
 *  @return maxId of Categories object inside CategoriesData;
 */
int CategoriesData::CreateCategory(Categories c){
    if(maxId < c.CategoryID) maxId = c.CategoryID;

    _data.push_back(c);
    return maxId;
}

/** @brief Function updates a Categories object at a position inside the list inside CategoriesData.
 *  
 *  Function updates a Categories object at a position inside the list inside CategoriesData.
 *  @return maxId of Categories object inside CategoriesData;
 *  if fail, return -1;
 */
int CategoriesData::UpdateCategory(int id, Categories c){
    if(id < 0) return -1;
    if(id >= _data.size()) return -1;
    _data[id] = c;
    if(maxId < c.CategoryID) maxId = c.CategoryID;
    return maxId;
}

/** @brief Function return a Categories object at a position inside the list inside CategoriesData.
 *  
 *  Function return a Categories object at a position inside the list inside CategoriesData.
 *  @return CustoCategoriesmers object;
 */
Categories CategoriesData::Get(int id){
    return _data[id];
}

/** @brief Function return a Categories object at a position inside the list inside CategoriesData.
 *  
 *  Function return a Categories object at a position inside the list inside CategoriesData.
 *  @return Categories object;
 *  if fail, return NULL;
 */
Categories* CategoriesData::GetPointer(int id){
    Categories* c = nullptr;
    if(id < 0) return c;
    if(id >= _data.size()) return c;
    c = &_data[id];
    return c;
}

/** @brief Function return size of CategoriesData.
 *  
 *  Function return size of CategoriesData. This is the quantity of Categories objects inside CategoriesData.
 *  @return number of Categories objects;
 */
int CategoriesData::GetSize(){
    return _data.size();
}

/** @brief Function write all data in CategoriesData to file.
 *  
 *  Function write all data in CategoriesData to file.
 *  @return 1 if success, 0 if fail;
 */
int CategoriesData::ExportToFile(string filename){
    ofstream outFile(filename, ios::out);
    if (!outFile) return 0;
    for(Categories c:_data){
        outFile << c.ToJson() << endl;
    }
    outFile.close();
    return 1;
}
/** @file CustomersData.h
 *  @brief CustomersData stores all Customers objects
 *  
 *  @author Ly Truong (truonglehaily)
 *  @bug No known bugs.
 */

#include "CustomersData.h"
#include <fstream>
#include "../libs/json.hpp" //https://github.com/nlohmann/json

using json = nlohmann::json;

/** @brief Function constructors an object.
 *  
 *  Function constructors an object.
 */
CustomersData::CustomersData(){
    maxId = 0;
    _data.resize(0);
}

/** @brief Function constructors an object.
 *  
 *  Function constructors an object, read data from file then load data to this object.
 */
CustomersData::CustomersData(string filename){
    maxId = 0;
    _data.resize(0);
    ifstream inFile(filename);
    const int maxSize = 255;
    char buff[maxSize];
    while (inFile.getline(buff, maxSize)){
        json j = json::parse(buff);
        Customers c(
            j["CustomerID"],
            j["CustomerName"],
            j["ContactName"],
            j["Address"],
            j["City"],
            j["PostalCode"],
            j["Country"]
        );
        _data.push_back(c);
    };
    inFile.close();
}

/** @brief Function add a Customers object to the end of the list inside CustomersData.
 *  
 *  Function add a Customers object to the end of the list inside CustomersData.
 *  @return maxId of Customers object inside CustomersData;
 */
int CustomersData::CreateCustomer(Customers c){
    if(maxId < c.CustomerID) maxId = c.CustomerID;

    _data.push_back(c);
    return maxId;
}

/** @brief Function update a Customers object at a position inside the list inside CustomersData.
 *  
 *  Function updates a Customers object at a position inside the list inside CustomersData.
 *  @return maxId of Customers object inside CustomersData;
 *  if fail, return -1;
 */
int CustomersData::UpdateCustomer(int id, Customers c){
    if(id < 0) return -1;
    if(id >= _data.size()) return -1;
    _data[id] = c;
    if(maxId < c.CustomerID) maxId = c.CustomerID;
    return maxId;
}

/** @brief Function return a Customers object at a position inside the list inside CustomersData.
 *  
 *  Function return a Customers object at a position inside the list inside CustomersData.
 *  @return Customers object;
 */
Customers CustomersData::Get(int id){
    return _data[id];
}

/** @brief Function return a Customers object at a position inside the list inside CustomersData.
 *  
 *  Function return a Customers object at a position inside the list inside CustomersData.
 *  @return Customers object;
 *  if fail, return NULL;
 */
Customers* CustomersData::GetPointer(int id){
    Customers* c = nullptr;
    if(id < 0) return c;
    if(id >= _data.size()) return c;
    c = &_data[id];
    return c;
}

/** @brief Function return size of CustomersData.
 *  
 *  Function return size of CustomersData. This is the quantity of Customers objects inside CustomersData.
 *  @return number of Customers objects;
 */
int CustomersData::GetSize(){
    return _data.size();
}

/** @brief Function write all data in CustomersData to file.
 *  
 *  Function write all data in CustomersData to file.
 *  @return 1 if success, 0 if fail;
 */
int CustomersData::ExportToFile(string filename){
    ofstream outFile(filename, ios::out);
    if (!outFile) return 0;
    for(Customers c:_data){
        outFile << c.ToJson() << endl;
    }
    outFile.close();
    return 1;
}
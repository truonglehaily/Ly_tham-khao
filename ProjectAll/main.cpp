#include <iostream>
#include <conio.h>
#include "businessobjects/Customers.h"
#include "userinterfaces/MainMenu.h"
#include "./libs/json.hpp"
using json = nlohmann::json;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
    MainMenu menu;
    int select;
	do{
        menu.UIMainMenu();
        cin >> select;
        cin.ignore();
        // system("pause");
        switch (select){
            case 1:
                menu.n.UINhapHang();
                break;
            case 2:
                break;
            case 3:
                break;
            default:
                break;
        }
    }while(select!=0);
    getch();

	return 0;
}

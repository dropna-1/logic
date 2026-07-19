#include <iostream>
#include "include/ui/MainMenu.hpp"
using namespace std;

int main(){
    MainMenu menu;
    int selected = menu.show();
    return 0;
}
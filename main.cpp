
#include <iostream>
#include "Interface.h"

using namespace std;

int main(){

    InterfaceUI ui;
    ui.ExtractBMIsFromFile();
    ui.SFMLInterface();

    return 0;
}
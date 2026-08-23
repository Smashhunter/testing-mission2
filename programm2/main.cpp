#include <string>
#include <iostream>
#include "lib.hpp"


int main(){
    std::string test = "";
    my_lib::processString(test);
    std::cout << "Project Name: " << PROJECT_NAME_STR << std::endl;
    return 0;
}

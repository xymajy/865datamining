#include <stdlib.h>
#include <iostream>
#include <cstring>

int main (){

std::string a="abc";
char* c;
c = (char*)malloc(50);
c[0]='z';
c[1]='b';
c[2]='c';
std::cout << strcmp("-p", c) <<std::endl;

return 0;
}

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "./mainMenu.h"

int main(){
    start:
    mainMenu();
    if(inGame==0) return 0;
    goto start;
    return 0;
}

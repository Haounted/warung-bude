#include "controller.h"
bool inGame = true;

void clearscreen(){
    for(int i=0;i<50;i++){
        puts("");
    }
}

void mainMenu(){
    time_t waktu;
    time(&waktu);
    while(inGame){
    clearscreen();
    printf("System : %s\n",detectOS());
    printf("%s",ctime(&waktu));
    puts("1. Add Dish");
    puts("2. Remove Dish");
    puts("3. Add Customer");
    puts("4. Search Customer");
    puts("5. View Warteg");
    puts("6. Order");
    puts("7. Payment");
    puts("8. Exit Warteg");
    int x;
    do{
        printf(">> ");
        scanf(" %d",&x);
    } while(x<1||x>8);
    clearscreen();

    if(x==1) addDish();
    else if(x==2) removeDish();
    else if(x==3) addCustomer();
    else if(x==4) searchCustomer();
    else if(x==5) viewWarteg();
    else if(x==6) inputOrder();
    else if(x==7) payment();
    else if(x==8) {
        exitWarteg();
        inGame = false;
    }
    }

}
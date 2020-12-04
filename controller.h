#include "./models.h"

/* mendektesi sistem */
const char* detectOS() {
  #ifdef _WIN32
  return "Windows 32-bit";
  #elif _WIN64
  return "Windows 64-bit";
  #elif __APPLE__ || __MACH__
  return "Mac OSX";
  #elif __linux__
  return "Linux";
  #elif __FreeBSD__
  return "FreeBSD";
  #elif __unix || __unix__
  return "Unix";
  #else
  return "Other";
  #endif
}
/* membuat node dish */
Dish *createDish(char *name,int price,int qty){
    Dish *temp = (Dish *)malloc(sizeof(Dish));
    strcpy(temp->name,name);
    temp->price = price;
    temp->qty = qty;
    temp->next = temp->prev = NULL;
    return temp;
}
/* membuat node order */
Order *createOrder(char *name,int price,int qty){
    Order *temp = (Order *)malloc(sizeof(Order));
    strcpy(temp->name,name);
    temp->price = price;
    temp->qty = qty;
    temp->next = temp->prev = NULL;
    return temp;
}
/* membuat node customer */
Customer *createCustomer(char *name){
    Customer *temp = (Customer *)malloc(sizeof(Customer));
    strcpy(temp->name,name);
    temp->next = temp->prev = NULL;
    return temp;
}

unsigned long DJB2(char *str) {
  unsigned long hash = 5381;
  int c;
  while ((c = *str++))
    hash = ((hash << 5) + hash) + c;
  return hash % max_element;
}
/* insert nama menggunakan hash table */
void insert(char *name){
    int index = DJB2(name);
    Customer *temp = createCustomer(name);
    if(!headCustomer[index]){
        headCustomer[index] = tailCustomer[index] = temp;
    } else {
        temp->prev = tailCustomer[index];
        tailCustomer[index]->next = temp;
        tailCustomer[index] = temp;
    }
}
/* mengecek bahwa nama tsb ada/tdk di hash table */
bool search(char *name){
    for(int i=0;i<max_element;i++){
        currCustomer = headCustomer[i];
        while(currCustomer){
            if(strcmp(currCustomer->name,name)==0){
                return true;
            }
            currCustomer = currCustomer->next;
        }
    }
    return false;
}
/* insert dish menggunakan linked list */
void pushTailDish(char *name,int price,int qty){
    Dish *temp = createDish(name,price,qty);
    if(!headDish){
        headDish = tailDish = temp;
    } else {
        temp->prev = tailDish;
        tailDish->next = temp;
        tailDish = temp;
    }
}
/* delete dish menggunakan linked list */
void popMidDish(char *name){
    if(!headDish){
        return;  
    } else if(headDish==tailDish && strcmp(headDish->name,name)==0){
        headDish = tailDish = NULL;
        free(headDish);
    } else if(strcmp(headDish->name,name)==0){
        Dish *newHead = headDish->next;
        headDish->next = newHead->prev = NULL;
        free(headDish);
        headDish = newHead;
    } else if(strcmp(tailDish->name,name)==0){
        Dish *newTail = tailDish->prev;
        tailDish->prev = newTail->next = NULL;
        free(tailDish);
        tailDish = newTail;
    } else {
        currDish = headDish;
        while(currDish && strcmp(currDish->name,name)!=0){
            currDish = currDish->next;
        }
        currDish->prev->next = currDish->next;
        currDish->next->prev = currDish->prev;
        currDish->prev = currDish->next = NULL;
        free(currDish);
    }
}
/* input dish */
void addDish(){
    int flag = 0;
    char name[50];
    do{
        flag = 0;
        printf("Insert the name of the dish [Lowercase letters]: ");
        scanf(" %[^\n]",name);
        for(int i=0;name[i]!='\0';i++){
            if(name[i]>='A'&&name[i]<='Z'){
                flag = 1;
                break;
            }
        }
    } while(flag==1);
    int price;
    do{
        printf("Insert the price of the dish [1000..50000]: ");
        scanf(" %d",&price);
    } while(price<1000||price>50000);
    int qty;
    do{
        printf("Insert the quantity of the dish [1..999]: ");
        scanf(" %d",&qty);
    } while(qty<1||qty>999);
    pushTailDish((char*)name,price,qty);
    puts("The dish has been added!");
    printf("Press enter to continue...");
    getchar(); getchar();
    
}
/* mengecek bahwa dish tsb ada di menu */
bool cekDish(char *name){
    currDish = headDish;
    while(currDish){
        if(strcmp(currDish->name,name)==0){
            return true;
        }
        currDish = currDish->next;
    }
    return false;
}
/* delete dish */
void removeDish(){
    puts("\t\tBude's Menu");
    puts("");
    puts("==========================================");
    puts("");
    printf("%-3s   %-10s  %-8s     %-15s\n","No.","Name","Quantity","Price");
    currDish = headDish;
    int i=1;
    while(currDish){
        printf("%-3d %-12s    %03d       Rp%-12d\n",i,currDish->name,currDish->qty,currDish->price);
        i++;
        currDish = currDish->next;
    }
    puts("");
    puts("==========================================");
    printf("Insert dish's name to be deleted: ");
    char name[50];
    scanf(" %[^\n]",name);
    if(cekDish(name)==1){
        popMidDish(name);
    }
    puts("The dish has been removed!");
    printf("Press enter to continue...");
    getchar();getchar();

}
/* menambahkan customer */
void addCustomer(){
    char name[50];
    int flag = 0;
    do {
    flag = 0;
    printf("Insert the customer's name [Without space]: ");
    scanf(" %[^\n]",name);
        for(int i=0;name[i]!='\0';i++){
            if(name[i]==' '){
                flag = 1;
                break;
            }
        }
    } while(flag==1);
    insert((char*)name);
    puts("Customer has been added!");
    printf("Press enter to continue...");
    getchar();getchar();
}
/* search customer */
void searchCustomer(){
    char name[50];
    printf("Insert the customer's name to be searched: ");
    scanf(" %[^\n]",name);
    int temp = search(name);
    temp==1? printf("%s is present.\n",name) : printf("%s is not present.\n",name);
    printf("Press enter to continue...");
    getchar();getchar();

}
/* melihat nama yg ada di warteg */
void viewWarteg(){
    puts("Customer's List");
    for(int i=0;i<max_element;i++){
        if(headCustomer[i]){
            printf("%d. ",i);
            currCustomer = headCustomer[i];
            while(currCustomer){
                if(currCustomer->next!='\0'){
                    printf("%s, ",currCustomer->name);
                } else{
                    printf("%s",currCustomer->name);
                }
                currCustomer = currCustomer->next;
            }
            puts("");
        }
    }
    printf("Press enter to continue...");
    getchar();getchar();
}
/* mencari harga untuk dimasukkan ke dalam node order */
int searchPrice(char *name){
    currDish = headDish;
    while(currDish && strcmp(currDish->name,name) !=0){
        currDish = currDish->next;
    }
    return currDish->price;
}
/* memasukkan linked list ke dalam sebuah node hash table */
void hashTableLinkedList(char *pembeli,char *name,int qty){
    int index = DJB2(pembeli);
    Customer *curr = headCustomer[index];
    while(curr && strcmp(curr->name,pembeli)!=0){
        curr = curr->next;
    }
    Order *temp = createOrder(name,searchPrice(name),qty);
    Order *now = curr->headOrder;
    if(!now){
        curr->headOrder = curr->tailOrder = temp;
    } else {
        curr->tailOrder->next = temp;
        temp->prev = curr->tailOrder;
        curr->tailOrder = temp;
    }
}
/* mengecek nama dish dan qty bahwa ada di menu dan qty yang di beli mencukupi dengan stok */
bool cek(char *name,int qty){
    currDish = headDish;
    while(currDish){
        if(strcmp(currDish->name,name)==0 && currDish->qty >= qty){
            currDish->qty = currDish->qty - qty;
            return true;
        }
        currDish = currDish->next;
    }
    return false;
}
/* input dish dan qty yang akan dibeli */
void insertTheDish(int amount,char* name){
    char temp[50],namaDish[50];
    int qty;
    for(int i=0;i<amount;i++){
        do {
            printf("[%d] Insert the dish's name and quantity: ",i+1);
            scanf(" %[^0-9]%d",temp,&qty);
            for(int j=0;j<strlen(temp)-2;j++){
            namaDish[j] = temp[j];
            }
            namaDish[strlen(temp)-2] = '\0';
        } while(cek((char*)namaDish,qty)==0);
        hashTableLinkedList((char*)name,(char*)namaDish,qty);
    }
    puts("Order succes!");
    printf("Press enter to continue...");
    getchar();getchar();
}
/* memasukkan nama dan banyak orderan */
void inputOrder(){
    char name[50];
    do{
        printf("Insert the customer's name: ");
        scanf(" %[^\n]",name);
    } while(search(name)==0);
    int amount;
    printf("Insert the amount of dish: ");
    scanf("%d",&amount);
    insertTheDish(amount,(char *)name);
    
}
/* struk pembelian dan menghapus customer yang telah membayar */
void payment(){
    start:
    int index;
    printf("Insert the customer's index: ");
    scanf("%d",&index);
    if(headCustomer[index]){
            currCustomer = headCustomer[index];
            while(currCustomer){
                puts("");
                printf("%s\n",currCustomer->name);
                currOrder = currCustomer->headOrder;
                int i = 1;
                int sum = 0;
                while(currOrder){
                    printf("[%d] %s x%d\n",i,currOrder->name,currOrder->qty);
                    i++;
                    sum+=currOrder->price;
                    currOrder = currOrder->next;
                }
                printf("Total: Rp%d\n",sum);
                if(currCustomer->next){
                        Customer *newHead = headCustomer[index]->next;
                        headCustomer[index]->next = newHead->prev = NULL;
                        free(headCustomer[index]);
                        headCustomer[index] = newHead;
                    } else {
                        headCustomer[index] = tailCustomer[index] = NULL;
                        free(headCustomer[index]);
                    }
                break;
            }
            printf("Press enter to continue...");
            getchar();getchar();
    } else {
        goto start;
    }

}
/* keluar dari warteg dan print file */
void exitWarteg(){
    puts("Please expand yout terminal to full screen!");
    printf("Press enter to continue...");
    getchar();getchar();
    FILE *fp = fopen("splash-screen.txt","r");
    char str[20][255];
    int ctr = 0;
    while(fscanf(fp,"%[^\n]\n",str[ctr])!=EOF){
        ctr++;
    }
    for(int i=0;i<ctr;i++){
        printf("%s\n",str[i]);
    }
    fclose(fp);
}
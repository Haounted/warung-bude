struct Dish {
    char name[255];
    int price, qty;
    Dish *prev, *next;
}*headDish, *tailDish, *currDish, *newDish, *delDish;

const int max_element = 26;
struct Order {
    char name[255];
    int qty, price;
    Order *prev, *next;
}*newOrder, *currOrder, *delOrder;

struct Customer {
    char name[255];
    Order *headOrder, *tailOrder;
    Customer *prev, *next;    
}*headCustomer[max_element], *tailCustomer[max_element], *currCustomer, *newCustomer, *delCustomer;


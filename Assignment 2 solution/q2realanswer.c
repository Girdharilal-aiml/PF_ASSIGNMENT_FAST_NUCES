#include <stdio.h>
#include <string.h>

#define TOTAL_PRODUCTS 4
#define MAX_CART 10

int codes[4] = {001, 002, 003, 004};
int stock[4] = {50, 10, 20, 8};
float price[4] = {100, 200, 300, 150};
int cartCode[10];
int cartQty[10];
float cartPrice[10];
int cartCount = 0;
char custName[50];
char custCNIC[20];

void inputCustomer();
void showProducts();
void buyItem();
void showBill();
void invoice();
int searchProduct(int code);

int main() {
    int choice;
    do {
        printf("\n=== Supermarket Billing System ===\n");
        printf("1. Enter Customer Info\n");
        printf("2. Show Products\n");
        printf("3. Buy Product\n");
        printf("4. View Bill\n");
        printf("5. Invoice\n");
        printf("6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1: inputCustomer();
            break;
            case 2: showProducts();
            break;
            case 3: buyItem();
            break;
            case 4: showBill();
            break;
            case 5: invoice();
            break;
            case 6: printf("Thank you for shopping.\n");
            break;
            default: printf("Invalid option! Try again.\n");
        }
    } while(choice != 6);
    return 0;
}

void inputCustomer() {
    printf("Enter name: ");
    scanf(" %[^\n]", custName);
    printf("Enter CNIC: ");
    scanf("%s", custCNIC);
    printf("Info saved!\n");
}

void showProducts() {
    printf("\n--- Available Products ---\n");
    printf("Code\tStock\tPrice\n");
    for(int i = 0; i < TOTAL_PRODUCTS; i++) {
        printf("00%d\t%d\t%.2f\n", codes[i], stock[i], price[i]);
    }
}

void buyItem() {
    int code, qty;
    showProducts();
    printf("Enter product code: ");
    scanf("%d", &code);
    
    int idx = searchProduct(code);
    if(idx == -1) {
        printf("Product not found!\n");
        return;
    }
    
    printf("Enter quantity: ");
    scanf("%d", &qty);
    if(qty > stock[idx]) {
        printf("Sorry, only %d left in stock.\n", stock[idx]);
        return;
    }
    printf("Item added to cart!\n");
    stock[idx] -= qty;
    cartCode[cartCount] = code;
    cartQty[cartCount] = qty;
    cartPrice[cartCount] = price[idx];
    cartCount++;
}

void showBill() {
    char promo[20];
    float total = 0;
    if(cartCount == 0) {
        printf("Cart is empty!\n");
        return;
    }
    printf("\n--- Cart Details ---\n");
    printf("Code\tQty\tPrice\tAmount\n");
    
    for(int i = 0; i < cartCount; i++) {
        float amount = cartQty[i] * cartPrice[i];
        total += amount;
        printf("%d\t%d\t%.2f\t%.2f\n", cartCode[i], cartQty[i], cartPrice[i], amount);
    }
    printf("Total = %.2f\n", total);
    printf("Enter promo code (if any): ");
    scanf("%s", promo);
    
    if(strcmp(promo, "eid2025") == 0) {
        float discount = total * 0.25;
        total = total - discount;
        printf("Discount applied! You saved %.2f\n", discount);
    } else {
        printf("No promo code applied.\n");
    }
    
    printf("Final Bill: %.2f\n", total);
}

void invoice() {
    float total = 0;
    if(cartCount == 0) {
        printf("No items bought yet!\n");
        return;
    }
    printf("\n===== Final Receipt =====\n");
    printf("Customer: %s\n", custName);
    printf("CNIC: %s\n", custCNIC);
    printf("-------------------------\n");
    printf("Code\tQty\tPrice\tAmount\n");
    for(int i = 0; i < cartCount; i++) {
        float amount = cartQty[i] * cartPrice[i];
        total += amount;
        printf("00%d\t%d\t%.2f\t%.2f\n", cartCode[i], cartQty[i], cartPrice[i], amount);
    }
    printf("-------------------------\n");
    printf("Total: %.2f\n", total);
    printf("With 25%% discount: %.2f\n", total * 0.75);
    printf("=========================\n");
}

int searchProduct(int code) {
    for(int i = 0; i < TOTAL_PRODUCTS; i++) {
        if(codes[i] == code)
            return i;
    }
    return -1;
}

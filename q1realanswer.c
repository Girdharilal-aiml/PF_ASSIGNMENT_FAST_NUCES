#include<stdio.h>
#include<string.h>

void AddNewBook(int isbns[100], char titles[100][50], float prices[100], int quantities[100], int *bookcount);
void ProcessSale(int isbns[100], char titles[100][50], float prices[100], int quantities[100], int bookcount);
void GenerateLowStockReport(int isbns[100], char titles[100][50], float prices[100], int quantities[100], int bookcount);

#define Maxbooks 100
int main(){
    int isbns[100] = {0};
    char titles[100][50] = {{0}};
    float prices[100] = {0};
    int quantities[100] = {0};
    int choice;
    int bookcount=0;
    
    do{
        printf("\n===== Library Books Inventory=====\n");
        printf("1. Add a New Book\n");
        printf("2. Process Sale\n");
        printf("3. Generate low stock Report\n");
        printf("4. Exit\n");
        scanf("%d", &choice);
        switch(choice){
            case 1: AddNewBook(isbns, titles, prices, quantities, &bookcount);
            break;
            case 2: ProcessSale(isbns, titles, prices, quantities, bookcount);
            break;
            case 3: GenerateLowStockReport(isbns, titles, prices, quantities, bookcount);
            break;
            case 4: printf("Exiting Program...");
            break;
            default : printf("Invalid, Try again.");
            break;
        }
        }while(choice != 4);
        return 0;
}   

void AddNewBook(int isbns[100], char titles[100][50], float prices[100], int quantities[100], int *bookcount){
    if(*bookcount >= Maxbooks){
        printf("Inventory is full!");
        return;
    }
    int newisbn;

    printf("Enter isbns: ");
    scanf("%d", &newisbn);
    for(int i=0; i < *bookcount; i++){
        if(isbns[i]==newisbn){
            printf("Book of this ISBN already exist!");
            return;
        }
    }
    printf("Enter title: ");
    scanf(" %[^\n]", titles[*bookcount]);
    printf("Enter quantity: ");
    scanf("%d", &quantities[*bookcount]);
    printf("Enter Price: ");
    scanf("%f", &prices[*bookcount]);

    isbns[*bookcount]=newisbn;
    printf("\nBook Added Successfully!\n");
    printf("ISBN=%d\nTitle=%s\nQuantity=%d\nPrice=%.2f\n", isbns[*bookcount],titles[*bookcount], quantities[*bookcount], prices[*bookcount]);
    (*bookcount)++;
    
}

void ProcessSale(int isbns[100], char titles[100][50], float prices[100], int quantities[100], int bookcount){
    int isbn, sold, found=0;
    printf("Enter ISBN number: ");
    scanf("%d", &isbn);
    for(int i = 0; i < bookcount; i++){
        if(isbns[i]==isbn){
            found=1;
            printf("Enter Number of copies: ");
            scanf("%d", &sold);
            if(quantities[i]<sold){
                printf("We don't have that much copies!\n");
            }else{
                quantities[i] -= sold;
                printf("%d books of %d isbn has sold", sold, isbn);
            }break;
        }
    }
    if(!found){
            printf("book of %d isbn not found", isbn);
        }


}

void GenerateLowStockReport(int isbns[100], char titles[100][50], float prices[100], int quantities[100], int bookcount){
    
    printf("\n=====LOW STOCK REPORT BELOW 5=====\n");
    
    int found=0;
    for(int i=0; i<bookcount;i++){
        if(quantities[i]<5){
            printf("ISBN = %d ,TITLE = %s ,QUANTITY = %d , PRICE = %.2f \n", isbns[i],titles[i], quantities[i], prices[i]);
            found=1;
        }
    }if(!found){
        printf("All books have sufficient stock!");
    }
}
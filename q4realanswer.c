#include<stdio.h>
#include<string.h>

#define MAX 100

void push(int stack[], int *top, int maxSize);
void pop(int stack[], int *top);
void peek(int stack[], int top);
void display(int stack[], int top);

int main(){
    int stack[MAX];
    int top = -1;
    int choice;
    do{
        printf("\n===== STACK MENU =====\n");
        printf("1. Push Element\n");
        printf("2. Pop Element\n");
        printf("3. Peek (View Top)\n");
        printf("4. Display All\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d",&choice);
        switch(choice){
            case 1: push(stack, &top, MAX);
            break;
            case 2: pop(stack, &top);
            break;
            case 3: peek(stack, top);
            break;
            case 4: display(stack, top);
            break;
            case 5: printf("Exiting Program...\n");
            break;
            default: printf("Invalid Option! Try again.\n");
        }
    }while(choice != 5);

    return 0;
}

void push(int stack[], int *top, int maxSize){
    int num;
    if(*top == maxSize - 1){
        printf("Stack Overflow! No more space.\n");
        return;
    }
    printf("Enter number to push: ");
    scanf("%d", &num);
    (*top)++;
    stack[*top] = num;
    printf("%d added into stack.\n", num);
}

void pop(int stack[], int *top){
    if(*top == -1){
        printf("Stack Underflow! Nothing to remove.\n");
        return;
    }
    printf("%d removed from stack.\n", stack[*top]);
    (*top)--;
}

void peek(int stack[], int top){
    if(top == -1){
        printf("Stack is empty!\n");
        return;
    }
    printf("Top element = %d\n", stack[top]);
}

void display(int stack[], int top){
    if(top == -1){
        printf("Stack is empty!\n");
        return;
    }
    printf("\n--- Stack Elements ---\n");
    for(int i = top; i >= 0; i--){
        printf("%d\n", stack[i]);
    }
}

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define rows 5
#define cols 5

int grid[rows][cols];

void InitializeGrid();
void UpdateSector();
void CheckSector();
void RunDiagnostic();
void DisplayGrid();

int main(){
    int choice;
    InitializeGrid();
    do{
        printf("\n===== IESCO Power Grid System =====\n");
        printf("1. Update Sector Status\n");
        printf("2. Check Sector Status\n");
        printf("3. Run System Diagnostic\n");
        printf("4. Display Grid\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch(choice){
            case 1: UpdateSector();
            break;
            case 2: CheckSector();
            break;
            case 3: RunDiagnostic();
            break;
            case 4: DisplayGrid();
            break;
            case 5: printf("Exiting System...\n");
            break;
            default: printf("Invalid choice, try again.\n");
            break;
        }
    }while(choice != 5);
    return 0;
}

void InitializeGrid(){
    for(int i=0; i<rows; i++){
        for(int j=0; j<cols; j++){
            grid[i][j] = 0;
        }
    }
    printf("Grid Initialized Successfully!\n");
}

void UpdateSector(){
    int row, col, flag, operation, mask = 0;
    printf("Enter Sector (row col): ");
    scanf("%d %d", &row, &col);
    if(row<0 || row>=rows || col<0 || col>=cols){
        printf("Invalid Coordinates!\n");
        return;
    }
    
    printf("Select Flag to Update:\n");
    printf("1. Power Status (Bit 0)\n");
    printf("2. Overload Warning (Bit 1)\n");
    printf("3. Maintenance Required (Bit 2)\n");
    printf("Enter choice: ");
    scanf("%d", &flag);
    printf("Select Operation (1=Set, 2=Clear): ");
    scanf("%d", &operation);
    if(flag == 1) mask = 1;
    else if(flag == 2) mask = 2;
    else if(flag == 3) mask = 4;
    else{
        printf("Invalid Flag!\n");
        return;
    }
    if(operation == 1){
        grid[row][col] = grid[row][col] | mask;
        printf("Flag Set Successfully!\n");
    }else if(operation == 2){
        grid[row][col] = grid[row][col] & ~mask;
        printf("Flag Cleared Successfully!\n");
    }else{
        printf("Invalid Operation!\n");
    }
}

void CheckSector(){
    int row, col;
    printf("Enter Sector (row col): ");
    scanf("%d %d", &row, &col);
    if(row<0 || row>=rows || col<0 || col>=cols){
        printf("Invalid Coordinates!\n");
        return;
    }
    
    int status = grid[row][col];
    printf("\n===== Sector (%d,%d) Status =====\n", row, col);
    printf("Power: %s\n", (status & 1) ? "ON" : "OFF");
    printf("Overload: %s\n", (status & 2) ? "YES" : "NO");
    printf("Maintenance: %s\n", (status & 4) ? "REQUIRED" : "NOT REQUIRED");
    
    if((status & 1) && (status & 2)){
        printf("Warning: Power is ON and Overloaded!\n");
    }
    if((status & 4) && (status & 1)){
        printf("Warning: Maintenance needed while Power is ON!\n");
    }
}

void RunDiagnostic(){
    int overload=0, maintenance=0, critical=0;
    for(int i=0; i<rows; i++){
        for(int j=0; j<cols; j++){
            int s = grid[i][j];
            if(s & 2) overload++;
            if(s & 4) maintenance++;
            if((s & 1) && (s & 2)) critical++;
        }
    }
    printf("\n===== System Diagnostic Report =====\n");
    printf("Total Sectors: %d\n", rows * cols);
    printf("Overloaded Sectors: %d\n", overload);
    printf("Maintenance Required: %d\n", maintenance);
    printf("Critical (ON + Overload): %d\n", critical);
    if(critical > 0){
        printf("Alert! Critical Sectors Found.\n");
    }else if(overload==0 && maintenance==0){
        printf("All Systems Running Fine.\n");
    }
}

void DisplayGrid(){
    printf("\n===== Grid Overview =====\n");
    printf("   ");
    for(int j=0; j<cols; j++){
        printf(" %d ", j);
    }
    printf("\n");
    for(int i=0; i<rows; i++){
        printf("%d |", i);
        for(int j=0; j<cols; j++){
            int s = grid[i][j];
            char power = (s & 1) ? '1' : '0';
            char overload = (s & 2) ? '1' : '0';
            char maint = (s & 4) ? '1' : '0';
            printf("[%c%c%c]", power, overload, maint);
        }
        printf("\n");
    }
}

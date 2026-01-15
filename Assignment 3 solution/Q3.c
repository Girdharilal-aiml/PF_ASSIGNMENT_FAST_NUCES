#include <stdio.h>
#include <string.h>

struct employee
{
    int emID;
    char name[20];
    char designation[20];
    float salary;
};

void displayem(struct employee e[], int n);
void hgsalary(struct employee e[], int n);
void updatesalary(struct employee e[], int n);
void searchem(struct employee e[], int n);
void sbyn(struct employee e[], int n);
void sbyid(struct employee e[], int n);

int main()
{
    int i;
    int n;
    printf("Enter number of emoloyees: ");
    scanf("%d", &n);
    struct employee e[n];
    for (i = 0; i < n; i++)
    {
        printf("\nEnter %d Employee data\n", i + 1);
        printf("ID: ");
        scanf("%d", &e[i].emID);
        getchar();
        if (e[i].emID < 0)
        {
            printf("Invalid ...");
            return 0;
        }
        printf("Name: ");
        fgets(e[i].name, sizeof(e[i].name), stdin);
        e[i].name[strcspn(e[i].name, "\n")] = 0;
        printf("Designation: ");
        fgets(e[i].designation, sizeof(e[i].designation), stdin);
        e[i].designation[strcspn(e[i].designation, "\n")] = 0;
        printf("Salary: ");
        scanf("%f", &e[i].salary);
        getchar();
    }
    displayem(e, n);
}

void displayem(struct employee e[], int n)
{
    printf("\n====EMPLOYEE RECORD's====\n");
    printf("| ID | NAME | DESIGNATION | SALARY |\n");
    int i;
    printf("---------------------------------------\n");
    for (i = 0; i < n; i++)
    {
        printf("| %d |  %s  |      %s     |  %.1f  |\n", e[i].emID, e[i].name, e[i].designation, e[i].salary);
        printf("---------------------------------------\n");
    }
    hgsalary(e, n);
}

void hgsalary(struct employee e[], int n)
{
    int i, max = 0;
    for (i = 0; i < n; i++)
    {
        if (e[max].salary < e[i].salary)
            max = i;
    }
    printf("====Highest Salary====\n");
    printf("| ID | NAME | DESIGNATION | SALARY |\n");
    printf("---------------------------------------\n");
    printf("| %d |  %s  |      %s     |  %.1f  |\n", e[max].emID, e[max].name, e[max].designation, e[max].salary);
    printf("---------------------------------------\n");
    searchem(e, n);
}

void searchem(struct employee e[], int n)
{
    int ch;
    do
    {
        printf("1. Search by name\n");
        printf("2. Search by ID\n");
        printf("Enter Choice: ");
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
            sbyn(e, n);
            break;
        case 2:
            sbyid(e, n);
            break;
        default:
            printf("Invalid...Try again!");
        }
    } while (ch != 1 && ch != 2);
}

void sbyn(struct employee e[], int n)
{
    char name[20];
    int i;
    printf("Enter Name: ");
    getchar();
    fgets(name, 20, stdin);
    name[strcspn(name, "\n")] = 0;
    for (i = 0; i < n; i++)
    {
        if (strcmp(name, e[i].name) == 0)
        {
            printf("Employee Found\n");
            printf("| %d |  %s  | %s |  %.1f  |\n", e[i].emID, e[i].name, e[i].designation, e[i].salary);
        }
    }
    updatesalary(e, n);
}

void sbyid(struct employee e[], int n)
{
    int id;
    int i;
    printf("Enter id: ");
    scanf("%d", &id);
    getchar();
    for (i = 0; i < n; i++)
    {
        if (id == e[i].emID)
        {
            printf("Employee Found\n");
            printf("| %d |  %s  | %s |  %.1f  |\n", e[i].emID, e[i].name, e[i].designation, e[i].salary);
        }
    }
    updatesalary(e, n);
}

void updatesalary(struct employee e[], int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        if (e[i].salary < 50000)
        {
            e[i].salary = e[i].salary + e[i].salary * (0.10);
            printf("10%% Bonus applied to %d ID : %.1f\n", e[i].emID, e[i].salary);
        }
    }
}

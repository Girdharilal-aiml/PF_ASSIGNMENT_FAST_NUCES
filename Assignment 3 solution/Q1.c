#include<stdio.h>

//IR = Interestrate
float calculateRepayment(float loan,float IR,int years, float installment){
    if(years==0){
        if(loan>0){
            printf("Loan is remaining but years have ended!\n");
        }else{
            printf("Loan Fully Paid!\n");
        }
        return loan;
    }
    loan=loan+(loan*IR/100);
    loan=loan-installment;
    printf("Year %d: Remaining loan = %.2f\n", years, loan);
    
    return calculateRepayment(loan,IR,years-1, installment);
    
}

int main(){
    float loan, IR;
    int years;
    printf("Enter Loan amount: ");
    scanf("%f", &loan);
    printf("Enter IR amount: ");
    scanf("%f", &IR);
    printf("Enter no of years: ");
    scanf("%d", &years);
    
    float installment=loan/years;
    calculateRepayment( loan, IR, years, installment);
    return 0;
}
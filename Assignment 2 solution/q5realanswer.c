#include<stdio.h>
#include<string.h>

void encode(){
    int n=1000,len;
    char msg[n],rev[n];
    printf("Enter Message: ");
    fgets(msg,n,stdin);
    len=strlen(msg);
    if(msg[len-1]=='\n'){
        msg[len-1]='\0';
        len--;
    }
    for(int i=0;i<len;i++)
        rev[i]=msg[len-1-i];
    rev[len]='\0';
    for(int i=0;i<len;i++)
        rev[i]=rev[i]^18;
    printf("\nPlain Message: %s\n",msg);
    printf("Encoded Message: %s\n",rev);
}

void decode(){
    int n=1000,len;
    char msg[n],rev[n];
    printf("Enter Encoded Message: ");
    fgets(rev,n,stdin);

    len=strlen(rev);
    if(rev[len-1]=='\n'){
        rev[len-1]='\0';
        len--;
    }
    for(int i=0;i<len;i++)
        rev[i]=rev[i]^18;

    for(int i=0;i<len;i++)
        msg[i]=rev[len-1-i];
    msg[len]='\0';
    printf("\nDecoded Message: %s\n",msg);
}

int main(){
    char ch;
    while(1){
        printf("\nEnter E to Encode, D to Decode and S to Stop:\n");
        scanf(" %c",&ch); 
        getchar();
        if(ch=='E'){
            encode();
        }
        else if(ch=='D'){
            decode();
        }
        else if(ch=='S'){
            printf("Exiting Program...\n");
            break;
        }
        else{
            printf("Invalid Option!!\n");
        }
    }
    return 0;
}

#include<stdio.h>

int calculatefuel(int fuel, int consumption, int recharge, int solarbonus, int planet, int totalplanet);

int main(){
    int fuel,consumption,recharge, solarbonus, planet, totalplanet;
    int planettype;
    printf("Enter Fuel quantity: ");
    scanf("%d", &fuel);
    printf("Enter fuel consuption: ");
    scanf("%d", &consumption);
    if(consumption>fuel){
        printf("Try again...");
        return 0;
    }
    printf("Enter Gravitional planet recharge: ");
    scanf("%d", &recharge);
    printf("Enter Solarbonus: ");
    scanf("%d", &solarbonus);
    printf("Enter Number of planets: ");
    scanf("%d", &totalplanet);
    return calculatefuel(fuel,consumption,recharge,solarbonus,1,totalplanet);
    return 0;
}

int calculatefuel(int fuel, int consumption, int recharge, int solarbonus, int planet, int totalplanet){
    if(fuel<=0){
    printf("\nMission failed!"); return -1;}
    if(planet>totalplanet) {
    printf("\nMission Successfull on %d planet with %d fuel.", totalplanet, fuel); return 0;}
    printf("\nPlanet %d : Remaining Fuel = %d", planet, fuel);
    fuel=fuel-consumption;
    if(planet==3 || planet==4) fuel=fuel+recharge;
    if(planet%4==0) fuel=fuel+solarbonus;
    calculatefuel(fuel,consumption,recharge,solarbonus,planet+1,totalplanet);
}

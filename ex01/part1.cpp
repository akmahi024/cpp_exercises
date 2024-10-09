
#include <iostream>
#include <stdbool.h>
#include <assert.h>

bool isPrime(unsigned int x){
    if(x<2){
        return false;
    }
    for(unsigned long long int i =2;i*i<=x;i++){//correction
        if(x%i==0){
            return false;
        }
    }
    return true;
}

int main()
{
    printf("%d:%s\n",60,isPrime(60) ? "true" : "false");
    printf("%d:%s\n",50,isPrime(50) ? "true" : "false");
    printf("%d:%s\n",1,isPrime(1) ? "true" : "false");
    printf("%d:%s\n",5,isPrime(5) ? "true" : "false");
    printf("%d:%s\n",500,isPrime(500) ? "true" : "false");
    printf("%d:%s\n",0,isPrime(0) ? "true" : "false");//correction


}

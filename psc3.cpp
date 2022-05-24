#include <iostream>
#include <math.h>
#include "sc3.h"
using namespace std;

int MY_I[6];
int MY_O[4];
void en_bin(int);
int de_bin();
void calculate();

int main(){
    SC_input();
    for (int i=0;i<64;i++){
        en_bin(i);
        calculate();
        SC_ans[i]=de_bin();
    }
    SC_output();
}
void en_bin(int n){
    for(int i=0;i<6;i++)MY_I[i]=0;
    for (int i=0;n>0;i++){
        MY_I[i]=n%2;
        n=int(n/2);
    }
}
void calculate(){
    for(int o=0;o<4;o++){
        int x2=0;
        for(int i=0;i<6;i++)x2+=MY_I[i]*SC_J[6*o+i];
        if(x2>0)MY_O[o]=1;
        else MY_O[o]=0;
    }
}
int de_bin(){
    int answer=0;
    for(int o=3;o>=0;o--)answer+=MY_O[o]*int(pow(2,o));
    return answer;
}
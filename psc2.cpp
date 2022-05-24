#include<iostream>
#include<math.h>
#include"sc2.h"
using namespace std;

int MY_I[6];
int MY_O[4];
int MY_H[4][7];
void en_bin(int);
int de_bin();
void H1();
void H2to4();
void output();

int main(){
    SC_input();
    for (int i=0;i<64;i++){
        en_bin(i);
        H1();
        H2to4();
        output();
        SC_ans[i]=de_bin();
    }
    SC_output();
}
void H1(){
    for(int h=0;h<7;h++){
        int x=0;
        for(int i=0;i<6;i++)x+=MY_I[i]*SC_J[h*6+i];
        if(x>0)MY_H[0][h]=1;
        else MY_H[0][h]=0;
    }
}
void H2to4(){
    for(int L=1;L<=3;L++){
        for(int h2=0;h2<7;h2++){
            int x=0;
            for(int h1=0;h1<7;h1++)x+=MY_H[L-1][h1]*SC_J[42+(L-1)*49+h2*7+h1];
            if(x>0)MY_H[L][h2]=1;
            else MY_H[L][h2]=0;
        }
    }
}
void output(){
    for(int o=0;o<4;o++){
        int x=0;
        for(int h=0;h<7;h++)x+=MY_H[3][h]*SC_J[189+(7*o)+h];
        if(x>0)MY_O[o]=1;
        else MY_O[o]=0;
    }
}
void en_bin(int n){
    for(int i=0;i<6;i++)MY_I[i]=0;
    for (int i=0;n>0;i++){
        MY_I[i]=n%2;
        n=int(n/2);
    }
}
int de_bin(){
    int answer=0;
    for(int i=3;i>=0;i--)answer+=MY_O[i]*int(pow(2,i));
    return answer;
}
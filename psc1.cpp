#include<iostream>
#include<math.h>
#include<time.h>
#include"sc1.h"
using namespace std;

int MY_I_N[6];
int MY_H_N[4][7];
int MY_O_N[4];

int MY_prob[SC_MAXPROB][SC_NDATA/2];
int MY_ans[SC_MAXPROB][SC_NDATA/2];

void init_prob();
void init_weigh(int);
int loss_bit(int);
int loss_deci(int);
bool update_weigh(int);
void change(int);
void en_bin(int,int*);
int de_bin(int*);
void calculate(int,int*);

int main(){
    SC_input();
    init_prob();
    init_genrand(0);
    for(int i=0;i<10;i++){
        int trial=1;
        do{
            init_weigh(i);
            trial++;
            if(trial>3)break;
        }while(!update_weigh(i));
        SC_output();

    }
}
bool update_weigh(int prob_num){
    int old_bit_loss,new_bit_loss;
    int old_J[SC_NJIJ];
    bool flag=true;
    int stime,ctime,ptime;
    int trial=0;
    while(new_bit_loss!=0){
        old_bit_loss=loss_bit(prob_num);
        new_bit_loss=old_bit_loss;
        trial=0;
        while(!(old_bit_loss>new_bit_loss)){
            for(int i=0;i<SC_NJIJ;i++)old_J[i]=SC_J[i];
            if(new_bit_loss>=10)change(10);
            else change(5);
            new_bit_loss=loss_bit(prob_num);
            if(new_bit_loss==0)break;
            else if(old_bit_loss<new_bit_loss)for(int i=0;i<SC_NJIJ;i++)SC_J[i]=old_J[i];
            trial++;
            if((trial>800000)&&(new_bit_loss>=3)){
                flag=false;
                break;
            }
            if((trial>1000000)&&(new_bit_loss>=2)){
                flag=false;
                break;
            }
            if((trial>2000000)&&(new_bit_loss==1)){
                flag=false;
                break;
            }
        }
        if(!flag)break;
    }
    if(!flag)return false;
    else return true;
}
void change(int rate){
    int rand=0;
    for(int i=0;i<rate;i++){
        rand=genrand_int31()%217;
        SC_J[rand]=-SC_J[rand];
    }
}
int loss_bit(int prob_num){
    int ans[10][4],out[10][4];
    int bin_out[4];
    int bin_ans[4];
    int total_error=0;
    for(int i=0;i<SC_NDATA/2;i++){
        en_bin(MY_ans[prob_num][i],bin_ans);
        calculate(MY_prob[prob_num][i],bin_out);
        for(int j=0;j<4;j++)if(bin_ans[j]!=bin_out[j])total_error++;
    }
    return total_error;
}
int loss_deci(int prob_num){
    int total_error=0;
    int bin_out[4];
    for(int i=0;i<10;i++){
        calculate(MY_prob[prob_num][i],bin_out);
        if(de_bin(bin_out)!=MY_ans[prob_num][i])total_error++;
    }
    return total_error;
}
void init_prob(){
    for(int i=0;i<SC_MAXPROB;i++){
        for(int j=0;j<SC_NDATA/2;j++){
            MY_prob[i][j]=SC_prob[i][j*2];
            MY_ans[i][j]=SC_prob[i][j*2+1];
        }
    }
}
void init_weigh(int prob_num){
    do{
        for(int i=0;i<SC_NJIJ;i++){
            if(genrand_int31()%2==0)SC_J[i]=1;
            else SC_J[i]=-1;
        }
    }while(loss_bit(prob_num)>15);
}
void en_bin(int n,int *bin){
    int digit=6;
    for(int i=digit-1;i>=0;i--){
        bin[i]=((n>>i)&1);
    }
}
int de_bin(int *out){
    int answer=0;
    for(int i=3;i>=0;i--)answer+=out[i]*int(pow(2,i));
    return answer;
}
void calculate(int n,int *bin_out){
    int bin_in[6];
    en_bin(n,bin_in);
    for(int i=0;i<6;i++)MY_I_N[i]=bin_in[i];
    for(int h=0;h<7;h++){
        int x=0;
        for(int i=0;i<6;i++)x+=MY_I_N[i]*SC_J[h*6+i];
        if(x>0)MY_H_N[0][h]=1;
        else MY_H_N[0][h]=0;
    }
    for(int l=1;l<=3;l++){
        for(int h2=0;h2<7;h2++){
            int x=0;
            for(int h1=0;h1<7;h1++)x+=MY_H_N[l-1][h1]*SC_J[42+(l-1)*49+h2*7+h1];
            if(x>0)MY_H_N[l][h2]=1;
            else MY_H_N[l][h2]=0;
        }
    }
    for(int o=0;o<4;o++){
        int x=0;
        for(int h=0;h<7;h++)x+=MY_H_N[3][h]*SC_J[189+(7*o)+h];
        if(x>0)MY_O_N[o]=1;
        else MY_O_N[o]=0;
    }
    for(int i=0;i<4;i++)bin_out[i]=MY_O_N[i];
}
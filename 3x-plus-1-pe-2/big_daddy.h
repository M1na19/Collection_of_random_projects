#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "limits.h"

#define BIG_DADDY_SIZE 1024
//in bits
#define DECIMAL_BIG_DADDY_SIZE   BIG_DADDY_SIZE*log10(2)

typedef unsigned long long ull;

//bites
typedef struct bigdaddy{
    void *num;
}Big_Daddy;

//poate fi assigned doar daca e unsigned long long
void assign_big_daddy(Big_Daddy *x, ull num){
    (*x).num=calloc(BIG_DADDY_SIZE/(8*sizeof(ull)),sizeof(ull));
    *((ull *)(*x).num)=num;
}

void free_big_daddy(Big_Daddy *x){
    free((*x).num);
}

Big_Daddy copy_big_daddy(Big_Daddy *a){
    Big_Daddy new_num;
    new_num.num=calloc(BIG_DADDY_SIZE/(8*sizeof(ull)),sizeof(ull));
    memcpy(new_num.num,(*a).num,BIG_DADDY_SIZE/8);
    return new_num;
}

//ia valoarea si dealoca spatiu ocupat de valoare curenta
void steal_value(Big_Daddy *destination, Big_Daddy source){
    free_big_daddy(destination);
    (*destination).num=source.num;
}

void increment_big_daddy(Big_Daddy* x,ull incr){
    ull* extension=(ull*)(*x).num;
    
    for(int i=0;i<BIG_DADDY_SIZE/(8*sizeof(ull)) && incr>0;i++){
        __uint128_t total=(__uint128_t)incr+(__uint128_t)extension[i];
        if(total>ULLONG_MAX){
            extension[i]=total-(ULLONG_MAX+1);
            incr=1;
        }
        else{
            extension[i]=(ull)total;
            incr=0;
        }
    }
    
}

Big_Daddy add_big_daddy(Big_Daddy *a,Big_Daddy *b){
    Big_Daddy result;
    assign_big_daddy(&result,0);

    ull *x=(ull*)(*a).num;
    ull *y=(ull*)(*b).num;

    ull *res=(ull*)result.num;

    int rest=0;
    for(int i=0;i<BIG_DADDY_SIZE/(8*sizeof(ull));i++){
        __uint128_t total=(__uint128_t)x[i]+(__uint128_t)y[i]+rest;

        if(total>ULLONG_MAX){
            res[i]=(ull)(total-(ULLONG_MAX+1));
            rest=1;
        }
        else{
            res[i]=(ull)total;
            rest=0;
        }
    }
    return result;
}

void ori3(Big_Daddy *x){
    Big_Daddy remind=copy_big_daddy(x);

    steal_value(x,add_big_daddy(x,x));
    steal_value(x,add_big_daddy(x,&remind));

    free_big_daddy(&remind);
}

void pe2_big_daddy(Big_Daddy* a){
    ull *x=(ull*)(*a).num;
    ull rest=0;
    for(int i=BIG_DADDY_SIZE/(8*sizeof(ull))-1;i>=0;i--){
        if(x[i] & 1 && i>0){
            rest=1ULL << 63;
            x[i]=x[i]>>1;
        }
        else{
            x[i]=x[i]>>1+rest;
            rest=0;
        }    
    }
}
short int is_odd(Big_Daddy *x){
    return ((ull*)((*x).num))[0] %2;
}




//returneaza 1 daca a>b, 0 daca a=b si -1 daca a<b
short int compare_big_daddy(Big_Daddy *a,Big_Daddy *b){
    ull *x=(ull*)(*a).num;
    ull *y=(ull*)(*b).num;
    for(int i=BIG_DADDY_SIZE/(8*sizeof(ull))-1;i>=0;i--){
        if(x[i]>y[i]){
            return 1;
        }
        else if(x[i]<y[i]){
            return -1;
        }
    }
    return 0;
}






//caractere
typedef struct charnum{
    char* num;
}Char_Num;

//poate fi assigned doar daca intra in unsigned long long
void assign_char_num(Char_Num *x, ull a){
    (*x).num=(char *)malloc(DECIMAL_BIG_DADDY_SIZE);
    for(int i=0;i<DECIMAL_BIG_DADDY_SIZE;i++){
        if(a>0){
            (*x).num[i]=(char)('0'+a%10);
            a/=10;
        }
        else{
            (*x).num[i]='0';
        }
    }
}

void free_char_num(Char_Num *a){
    free((*a).num);
}

void afis_char_num(Char_Num* a){
    int started=0;
    for(int i=DECIMAL_BIG_DADDY_SIZE-1;i>=0;i--){
        if(started==1){
            printf("%c",(*a).num[i]);
        }
        else if((*a).num[i]!='0'){
            started=1;
            printf("%c",(*a).num[i]);
        }
    }
    printf("\n");
}

Char_Num add_char_num(Char_Num *a,Char_Num *b){
    Char_Num result;
    assign_char_num(&result,0);
    short int rest=0;

    for(int i=0;i<DECIMAL_BIG_DADDY_SIZE;i++){
        short int x=(short)((*a).num[i]-'0');
        short int y=(short)((*b).num[i]-'0');

        if(x+y+rest<10){
            result.num[i]=(char)(x+y+rest+'0');
            rest=0;
        }
        else{
            result.num[i]=(char)(x+y+rest-10+'0');
            rest=1;
        }
    }
    return result;
}

//inmultirea intre un char num si o cifra
//devierea e o variabila ajutatoare cand inmultim doua char num
//in inmultire in baza 10 se aduna char num * cifra cu o deviere in plus la stanga pt fiecare cifra de la dreapta la stanga
Char_Num multi_char_num_and_int(Char_Num *num, int a,int deviere){
    Char_Num result;
    assign_char_num(&result,0);
    int rest=0;
    for(int i=0;i<DECIMAL_BIG_DADDY_SIZE;i++){
        if(i<deviere){
            result.num[i]='0';    
        }
        else{
            int b=(int)((*num).num[i-deviere]-'0');
            result.num[i]=(char)((a*b+rest)%10+'0');
            rest=(a*b+rest)/10;
        }
    }
    return result;
}

//inmultire intre doua char num
Char_Num multi_char_num(Char_Num *a,Char_Num *b){
    Char_Num result;
    assign_char_num(&result,0);
    for(int i=0;i<DECIMAL_BIG_DADDY_SIZE;i++){
        int x=(int)((*b).num[i]-'0');
        Char_Num coeficent=multi_char_num_and_int(a,x,i);
        result=add_char_num(&result,&coeficent);
    }
    return result;
}

//determinarea 2^p in char num pt transformarea din reprezentare bites in reprezentare char
Char_Num two_of_power(int p){
    if(p>0){
        if(p%2==0){
            Char_Num coeficient=two_of_power(p/2);
            return multi_char_num(&coeficient,&coeficient);
        }
        else{
            Char_Num coeficient=two_of_power(p-1);
            return multi_char_num_and_int(&coeficient,2,0);
        }
    }
    else{
        Char_Num result;
        assign_char_num(&result,1);
        return result;
    }
}


Char_Num big_daddy_to_char_num(Big_Daddy* a){
    ull *long_casted_num=(ull*)(*a).num;
    Char_Num number;
    assign_char_num(&number,0);

    Char_Num additional=two_of_power(sizeof(ull)*8);

    Char_Num exponent;
    assign_char_num(&exponent,1); 

    for(int i=0;i<BIG_DADDY_SIZE/(8*sizeof(ull));i++){
        

        Char_Num coeficient;
        assign_char_num(&coeficient,long_casted_num[i]);

        coeficient=multi_char_num(&coeficient,&exponent);
        number=add_char_num(&number,&coeficient);

        exponent=multi_char_num(&exponent,&additional);
        
    }
    
    return number;
}

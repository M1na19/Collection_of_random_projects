#include "big_daddy.h"
#include "timer.h"
#include <stdio.h>


void afis(Big_Daddy x){
    Char_Num show;
    show=big_daddy_to_char_num(&x);
    afis_char_num(&show);
    free_char_num(&show);
}

int main(){
    Big_Daddy startpoint,limit;
    assign_big_daddy(&startpoint,1);

    //get input power of 2
    int start_power,limit_power;
    scanf("%d",&start_power);
    scanf("%d",&limit_power);

    if(start_power>limit_power){
        printf("Wrong input");
        return 0;
    }

    //configure 2^start_power
    for(int i=0;i<start_power;i++){
        steal_value(&startpoint,add_big_daddy(&startpoint,&startpoint));
    }

    //configure 2^limit_power
    limit=copy_big_daddy(&startpoint);
    for(int i=0;i<limit_power-start_power;i++){
        steal_value(&limit,add_big_daddy(&limit,&limit));
    }

    increment_big_daddy(&startpoint,1);//uneven only

    printf("Numbers are ready\n");

    predicted_time(limit_power);
    
    start_counter();

    Big_Daddy x;
    assign_big_daddy(&x,69);//hehehe
    while(compare_big_daddy(&startpoint,&limit)==-1){

        if(check_counter()==1){
            printf("It has been 5 min since last update\nCurrent Number: ");
            afis(startpoint);
        }

        steal_value(&x,copy_big_daddy(&startpoint));
        while(compare_big_daddy(&startpoint,&x)!=1){
            if(is_odd(&x)==0){
                pe2_big_daddy(&x);
            }
            else{
                ori3(&x);
                increment_big_daddy(&x,1);
            }

            if(compare_big_daddy(&x,&startpoint)==0){
                printf("Number has been found:\n");
                afis(x);
                return 0;
            }
        }
        increment_big_daddy(&startpoint,2);
    }
    
    end_counter();

}
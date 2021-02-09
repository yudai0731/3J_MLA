#include<stdio.h>
#include<stdlib.h>
#include<sys/time.h>
#include "mulprec.h"

#define al1

struct timeval tv;
double tstart,tend;
int main(void){

    #ifdef al1
    int it =78; //何桁目まで整数に引き出すか

    int i,r;
    struct NUMBER a,n,e1,e2,temp,temp2; 

    clearByZero(&a);
    clearByZero(&e1);
    clearByZero(&e2);
    increment(&e1,&a);
    printf("init process successed\n");

    for(i=0;i<it;i++){
        mulBy10(&a,&temp);
        copyNumber(&temp,&a);
    }

    i=1;
    gettimeofday(&tv,NULL);
    tstart =(double)tv.tv_sec + (double)tv.tv_usec *1.e-6;
    while(1){
        setInt(&n,i);   
        multiple(&n,&n,&temp);
        multiple(&temp,&temp,&n);

        divide_2(&a,&n,&temp,&temp2);
        add(&e1,&temp,&temp);
        copyNumber(&temp,&e1);

        if(i%10==0){
            printf("n = %d\n e1 = ",i);
            dispNumberZeroSuppress(&e1);
            printf("\n"); 
            gettimeofday(&tv,NULL);
            tend =(double)tv.tv_sec + (double)tv.tv_usec *1.e-6;
            printf("所要時間 = %f秒\n\n",tend-tstart);
        }

        if(i%100000==0){
            setInt(&temp2,90);
            multiple(&e1,&temp2,&temp);
            printf("n = %5d sqrt process start\n",i);
            while(1){
                r = mulBy10(&temp,&temp2);
                if(r==-1){
                    break;
                }
                copyNumber(&temp2,&temp);
            }
            sqrt_newton(&temp,&temp2);
            sqrt_newton(&temp,&temp2);
            printf("e1 = ");
            dispNumberZeroSuppress(&e1);
            printf("\n");
            printf("pi = ");
            //dispNumberZeroSuppress(&e1);
            dispNumberZeroSuppress(&temp2);
            printf("\n");
            gettimeofday(&tv,NULL);
            tend =(double)tv.tv_sec + (double)tv.tv_usec *1.e-6;
            printf("所要時間 = %f秒\n\n",tend-tstart);
        }
       // if(numComp(&e1,&e2)==0){
        //    printf("結果一致\n");
          //  exit(1);
        //}
        //copyNumber(&e1,&e2);
        i++;
    }
    printf("main process successed\n");

    #endif

    #ifdef test
    struct NUMBER a,b,c,d;

    setInt(&a,7);
    setInt(&b,2);

    gettimeofday(&tv,NULL);
    tstart =(double)tv.tv_sec + (double)tv.tv_usec *1.e-6;

    divide3(&a,&b,&c,&d);

    gettimeofday(&tv,NULL);
    tend =(double)tv.tv_sec + (double)tv.tv_usec *1.e-6;
    printf("所要時間 = %f秒\n",tend-tstart);
    printf("c = ");
    dispNumber(&c);
    printf("\n");
    printf("d = ");
    dispNumber(&d);
    printf("\n");
    #endif
    return 0;
}
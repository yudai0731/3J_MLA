#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define KETA 30

/*
sign
+ 1
- -1
*/
struct NUMBER{
    int n[KETA];
    int sign;
};

void clearByZero(struct NUMBER *a){
    int i;

    for(i=0; i<KETA;i++){
        a->n[i] = 0;
    }

    a-> sign =1;
}

void dispNumber(struct NUMBER *a){
    int i;
    
    if(a->sign==1){
        printf("+ ");
    }else{
        printf("- ");
    }

    for(i=KETA-1; i>=0; i--){
        printf("%2d",a->n[i]);
    }
}
//下位k桁に乱数を生成
void setRnd(struct NUMBER *a,int k){
    int i;
    clearByZero(a);
    if(random()%2==1){
        a->sign=1;
    }else{
        a->sign=-1;
    }

    for(i=0; i<k; i++){
        a->n[i] = random()%10;
    }
}

//aをbにコピー
void copyNumber(struct NUMBER *a,struct NUMBER *b){
    int i;
    b->sign = a->sign;
    for(i=0;i<KETA;i++){
        b->n[i]=a->n[i];
    }
}

//aの絶対値をbにコピー
void getAbs(struct NUMBER *a,struct NUMBER *b){
    copyNumber(a,b);
    b->sign=1;
}

int isZero(struct NUMBER *a){
    int i;
    for(i=0; i<KETA; i++){
        if(a->n[i]!=0){
            return -1;
        }
    }
    return 0;
}

//aを10倍してbに代入
//オーバーフローしたらbをゼロクリアする.
int mulBy10(struct NUMBER *a,struct NUMBER *b){
    int i;
    b->sign = a->sign;
    if(a->n[KETA-1]!=0){
        clearByZero(b);
        return -1;
    }

    for(i=0; i<KETA-1;i++){
        b->n[i+1] = a->n[i];
    }
    b->n[0]=0;
    return 0;
}

//aを1/10倍してbに代入
//aの最下位桁を返り値とする
int divBy10(struct NUMBER *a,struct NUMBER *b){
    int i;
    int temp=a->n[0]; //返り値保存
    if(a->sign==-1){ //返り値の符号を決める
        temp=-temp;
    }
    b->sign = a->sign;
    for(i=0; i<KETA-1;i++){
        b->n[i] = a->n[i+1];
    }
    b->n[KETA-1]=0;
    return temp;
}


int main(void){
    struct NUMBER a,b,c,d,e;
    int r;
    srandom(time(NULL));

    clearByZero(&a);
    printf("a = ");
    dispNumber(&a);
    putchar('\n');

    setRnd(&b,10);
    printf("b = ");
    dispNumber(&b);
    putchar('\n');

    copyNumber(&b,&c);
    printf("c = ");
    dispNumber(&c);
    putchar('\n');

    r = mulBy10(&b,&d);
    printf("b * 10 = ");
    dispNumber(&d);
    printf(",r=%d\n",r);

    r =divBy10(&c,&e);
    printf("c / 10 = ");
    dispNumber(&e);
    printf(",r=%d\n",r);

    printf("a == 0? --> %d\n",isZero(&a));
    printf("b == 0? --> %d\n",isZero(&b));
    printf("c == 0? --> %d\n",isZero(&c));
    printf("d == 0? --> %d\n",isZero(&d));
    printf("e == 0? --> %d\n",isZero(&e));
    return 0;
}
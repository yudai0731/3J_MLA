#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<limits.h>

#define KETA 100

int sub();

struct NUMBER{
    int n[KETA];
    int sign;
};

struct BUNSU{
    struct NUMBER bunshi;
    struct NUMBER bunbo;
    int sign;
};

//aが0かをチェック
//0->return 0 else->return -1 
int isZero(struct NUMBER *a){
    int i;
    for(i=0; i<KETA; i++){
        if(a->n[i]!=0){
            return -1;
        }
    }
    return 0;
}

//aに符号をセット 
//aが0のときに-をセットしようとするとreturn -1
int setSign(struct NUMBER *a,int s){
    if(isZero(a)==0){
        if(s==-1){
            return -1;
        }
    }

    if(s==1){
        a->sign = 1;
        return 0;
    }else if(s==-1){
        a->sign = -1;
        return 0;
    }else{
        return -1;
    }
}

//aの符号を取得
//+:1 -:-1 
int getSign(struct NUMBER *a){
    if(a->sign==1){
        return 1;
    }else{
        return -1;
    }
}

//aをゼロクリア
void clearByZero(struct NUMBER *a){
    int i;

    for(i=0; i<KETA;i++){
        a->n[i] = 0;
    }

    setSign(a,1);
}

// aを全桁表示
void dispNumber(struct NUMBER *a){
    int i;

    if(getSign(a)==1){
        printf("+ ");
    }else{
        printf("- ");
    }

    for(i=KETA-1; i>=0; i--){
        printf("%2d",a->n[i]);
    }
}

// aを全桁表示
void dispNumberZeroSuppress(struct NUMBER *a){
    int i;
    int j=1;

    if(getSign(a)==1){
        printf("+ ");
    }else{
        printf("- ");
    }

    if(isZero(a)==0){
        printf("0");
    }
    for(i=KETA-1; i>=0; i--){
        if(j){
            if(a->n[i] != 0){
                printf("%2d",a->n[i]);
                j=0;
            }
        }else{
        printf("%2d",a->n[i]);
        }
    }
}

//下位k桁に乱数を生成
void setRnd(struct NUMBER *a,int k){
    int i;
    clearByZero(a);

    for(i=0; i<k; i++){
        a->n[i] = random()%10;
    }
    if(random()%2==1){
        setSign(a,1);
    }else{
        setSign(a,-1);
    }
}

//aをbにコピー
void copyNumber(struct NUMBER *a,struct NUMBER *b){
    int i;
    setSign(b,getSign(a));
    for(i=0;i<KETA;i++){
        b->n[i]=a->n[i];
    }
}

//aの絶対値をbにコピー
void getAbs(struct NUMBER *a,struct NUMBER *b){
    copyNumber(a,b);
    setSign(b,1);
}

//aを10倍してbに代入
//オーバーフローしたらbをゼロクリアする.
int mulBy10(struct NUMBER *a,struct NUMBER *b){
    int i;
    setSign(b,getSign(a));
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
    if(getSign(a)==-1){ //返り値の符号を決める
        temp=-temp;
    }
    setSign(b,getSign(a));
    for(i=0; i<KETA-1;i++){
        b->n[i] = a->n[i+1];
    }
    b->n[KETA-1]=0;
    return temp;
}

int setInt(struct NUMBER *a,int x){
    int temp,i;
    if(KETA<10){
        return -1;
    }

    clearByZero(a);

    temp=x;
    if(x<0){
        temp*=-1;
    }
    for(i=0;i<10;i++){
        a->n[i]=temp%10;
        temp-=a->n[i];
        temp/=10;
    }

    if(x<0){
        setSign(a,-1);
    }else{
        setSign(a,1);
    }
    return 0;
}

//多倍長の大小比較 a==b:0 a>b:1 a<b:-1
int numComp(struct NUMBER *a,struct NUMBER *b){
    int i,Sa,Sb;
    Sa = getSign(a);
    Sb = getSign(b);

    // a+ b-
    if((Sa==1)&&(Sb==-1)){
        return 1;
    }

    //a- b+
    if((Sa==-1)&&(Sb==1)){
        return -1;
    }
    //a+ b+
    if((Sa==1)&&(Sb==1)){
        for(i=KETA-1; i>=0; i--){
            if(a->n[i] > b->n[i]){
                return 1;
            }

            if(a->n[i] < b->n[i]){
                return -1;
            }
        }
        return 0;
    }

    if((Sa==-1)&&(Sb==-1)){
        for(i=KETA-1; i>=0; i--){
            if(a->n[i] > b->n[i]){
                return -1;
            }

            if(a->n[i] < b->n[i]){
                return 1;
            }
        }
        return 0;
    }
    return 623;
}

// c<- a+b
int add(struct NUMBER *a,struct NUMBER *b,struct NUMBER *c){
    int Sa = getSign(a);
    int Sb = getSign(b);
    struct NUMBER Nd,Ne;
    int d,i;
    int e=0;
    //a+ b+
    if((Sa==1)&&(Sb==1)){
        for(i=0;i<KETA;i++){
            d = a->n[i] + b->n[i] +e;
            c->n[i] = d%10;
            e = (d - c->n[i]) /10;
        }
        if(e==1){
            clearByZero(c);
            return -1;
        }
        setSign(c,1);
        return 0;
        }
    
    //a+ b-
    if((Sa==1)&&(Sb==-1)){
        getAbs(b,&Nd);
        sub(a,&Nd,c);
        return 0;
    }

    //a- b+
    if((Sa==-1)&&(Sb==1)){
        getAbs(a,&Nd);
        sub(b,&Nd,c);
        return 0;
    }

    //a- b-
    if((Sa==-1)&&(Sb==-1)){
        getAbs(a,&Nd);
        getAbs(b,&Ne);
        add(&Nd,&Ne,c);
        setSign(c,-1);
        return 0;
    }
    return 623; //不明なエラー検出
}

// c<- a-b 
int sub(struct NUMBER *a,struct NUMBER *b,struct NUMBER *c){
    struct NUMBER Nd,Ne;
    int Sa = getSign(a);
    int Sb = getSign(b);
    int i;
    int h=0;
    //a+ b+
    if((Sa==1)&&(Sb==1)){
    if(numComp(a,b)==1){
        setSign(c,1);
        for(i=0;i<KETA;i++){
            a->n[i]-=h;
            if(a->n[i]>=b->n[i]){
                c->n[i] = a->n[i] - b->n[i];
                h=0;
            }else{
                c->n[i] = 10 + a->n[i] - b->n[i];
                h=1;
            }
        }
        return 0;
    }

    if(numComp(a,b)==-1){
        for(i=0;i<KETA;i++){
            b->n[i]-=h;
            if(b->n[i]>=a->n[i]){
                c->n[i] = b->n[i] - a->n[i];
                h=0;
            }else{
                c->n[i] = 10 + b->n[i] - a->n[i];
                h=1;
            }
        }
        setSign(c,-1);
    }

    if(numComp(a,b)==0){
        clearByZero(c);
    }
    return 0;
    }

    //a+ b-
    if((Sa==1)&&(Sb==-1)){
        getAbs(b,&Nd);
        add(a,&Nd,c);
        return 0;
    }

    //a- b+
    if((Sa==-1)&&(Sb==1)){
        getAbs(a,&Nd);
        add(&Nd,b,c);
        setSign(c,-1);
        return 0;
    }

    //a- b-
    if((Sa==-1)&&(Sb==-1)){
        getAbs(b,&Ne);
        add(a,&Ne,c);
        return 0;
    }

    return 623;//不明なエラー検出
}

// b<- a++
int increment(struct NUMBER *a,struct NUMBER *b){
    struct NUMBER one;
    int r;
    setInt(&one,1);
    r = add(a,&one,b);
    return r;
}

// b <- a--
int decrement(struct NUMBER *a,struct NUMBER *b){
    struct NUMBER one;
    int r;

    setInt(&one,1);
    r=sub(a,&one,b);
    return r;
}

int simpleMultiple(int a,int b,int *c){
    *c=0;
    int i=0;

    if(b==0){
        return 0;
        //printf("marker\n");
    }

    while(1){
        if(INT_MAX - *c >= a){
            *c=0;
            return -1;
        }

        *c+=a;
        i++;
        if(i==abs(b)){
            if(b<0){
                *c*=-1;
            }
            return 0;
        }
    }
    return 623;
}

// c<-a*b
int multiple(struct NUMBER *a,struct NUMBER *b,struct NUMBER *c){
    int e,h,i,j;
    int Sa = getSign(a);
    int Sb = getSign(b);
    struct NUMBER d,d2,ee;
    clearByZero(c);

    if(Sa==1 && Sb==1){
        for(i=0;i<KETA;i++){
            h=0;
            clearByZero(&d);
            for(j=0;j<KETA;j++){
                e=(a->n[j]* b->n[i])+h;
                d.n[j] = e%10;
                e-=d.n[j];
                h = e/10;
            }
            if(h != 0){
                clearByZero(c);
                return -1;
            }

            for(j=0;j<i;j++){
                if(mulBy10(&d,&d2)==-1){
                    clearByZero(c);
                    return -1;
                }
                copyNumber(&d2,&d);
            }

            if(add(c,&d,c)==-1){
                clearByZero(c);
                return -1;
            }
        }
        return 0;
    }

    if(Sa==-1 && Sb==1){
        getAbs(a,&d);
        i = multiple(&d,b,c);
        if(i==-1){
            return -1;
        }
        setSign(c,-1);
        return 0;
    }

    if(Sa==1 && Sb==-1){
        getAbs(b,&d);
        i = multiple(a,&d,c);
        if(i==-1){
            return -1;
        }
        setSign(c,-1);
        return 0;
    }
    if(Sa==-1 && Sb ==-1){
        getAbs(a,&d);
        getAbs(b,&ee);
        i = multiple(&d,&ee,c);
        if(i==-1){
            return -1;
        }
        setSign(c,1);
        return 0;
    }
    return 623;
}

int Karatsuba(struct NUMBER *a,struct NUMBER *b,struct NUMBER *c,int keta){
    struct NUMBER temp,temp2,temp3,x0,x1,y0,y1,z0,z1,z2,d,ee;
    //int vv;
    //scanf("%d",&vv);
    /*printf("\na = ");
    dispNumber(a);
    printf("\n");
    printf("b = ");
    dispNumber(b);
    printf("\n");*/
    int Sa =getSign(a);
    int Sb =getSign(b);
    int i,r;
    clearByZero(c);
    clearByZero(&z1);

    if(isZero(a)==0 || isZero(b)==0){
        return 0;
    }

    clearByZero(&temp);
    increment(c,&temp);
    if(numComp(a,&temp)==0){
        copyNumber(b,c);
        return 0;
    }else if(numComp(b,&temp)==0){
        copyNumber(a,c);
        return 0;
    }

    clearByZero(&x0);
    clearByZero(&y0);
    if(Sa==1 && Sb==1){

        if(keta<=2){
            multiple(a,b,c);
        /*printf("c = ");
        dispNumber(c);
        printf("\n\n");*/
            return 0;
        }
        //x0,x1,y0,y1を作る
        copyNumber(a,&temp);
        copyNumber(b,&temp2);
        for(i=0;i<(keta/2);i++){
            r = divBy10(&temp,&x1);
            copyNumber(&x1,&temp);
            x0.n[i] = r;

            r = divBy10(&temp2,&y1);
            copyNumber(&y1,&temp2);
            y0.n[i] = r;
        }

        /*printf("x1 = ");
        dispNumber(&x1);
        printf("\n");

        printf("x0 = ");
        dispNumber(&x0);
        printf("\n");

        printf("y1 = ");
        dispNumber(&y1);
        printf("\n");

        printf("y0 = ");
        dispNumber(&y0);
        printf("\nketa/2 = %d\n",keta/2);
        printf("\n");
        */

        Karatsuba(&x0,&y0,&z0,keta/2);
        Karatsuba(&x1,&y1,&z2,keta/2);

        sub(&x1,&x0,&temp);
        sub(&y1,&y0,&temp2);
        multiple(&temp,&temp2,&temp3);
        /*printf("temp3 = ");
        dispNumber(&temp3);
        printf("\n");*/
        clearByZero(&temp);
        add(&z2,&z0,&temp);
        /*printf("z2+z0 = ");
        dispNumber(&temp);
        printf("\n");*/
        sub(&temp,&temp3,&z1);
        /*printf("z0 = ");
        dispNumber(&z0);
        printf("\n");
        printf("z1 = ");
        dispNumber(&z1);
        printf("\n");
        printf("z2 = ");
        dispNumber(&z2);
        printf("\n");
        printf("keta = %d\n",keta);
        printf("\n");
        */
        copyNumber(&z0,c);
        copyNumber(&z1,&temp);
        copyNumber(&z2,&temp2);
        for(i=0;i<(keta/2);i++){
            mulBy10(&temp,&temp3);
            copyNumber(&temp3,&temp);

            mulBy10(&temp2,&temp3);
            copyNumber(&temp3,&temp2);
        }

        for(i=0;i<(keta/2);i++){
            mulBy10(&temp2,&temp3);
            copyNumber(&temp3,&temp2);
        }

        add(c,&temp,&temp3);
        add(&temp3,&temp2,c);
        /*printf("c = ");
        dispNumber(c);
        printf("\n\n");*/
        return 0;
    }
    if(Sa==-1 && Sb==1){
        getAbs(a,&d);
        i = Karatsuba(&d,b,c,keta);
        if(i==-1){
            return -1;
        }
        setSign(c,-1);
        return 0;
    }

    if(Sa==1 && Sb==-1){
        getAbs(b,&d);
        i = Karatsuba(a,&d,c,keta);
        if(i==-1){
            return -1;
        }
        setSign(c,-1);
        return 0;
    }
    if(Sa==-1 && Sb ==-1){
        getAbs(a,&d);
        getAbs(b,&ee);
        i = Karatsuba(&d,&ee,c,keta);
        if(i==-1){
            return -1;
        }
        setSign(c,1);
        return 0;
    }

    return 623;
}

// a/b = c...d
int divide(struct NUMBER *a,struct NUMBER *b,struct NUMBER *c
,struct NUMBER *d){
    struct NUMBER m,n,p,q;
    int Sa = getSign(a);
    int Sb = getSign(b);
    clearByZero(c);
    clearByZero(d);

    if(isZero(b)==0){
        printf("div by 0\n");
        return -1;
    }

    copyNumber(a,&n);

    if(Sa==1 && Sb==1){
        while(1){
            if(numComp(&n,b)==-1){
                break;
            }
                increment(c,&m);
                copyNumber(&m,c);
                sub(&n,b,&m);
                copyNumber(&m,&n);
        }
        copyNumber(&n,d);
        return 0;
    }

    if(Sa==1 && Sb==-1){
        getAbs(b,&p);
        divide(&n,&p,c,d);
        setSign(c,-1);
        return 0;
    }

    if(Sa==-1 && Sb==1){
        getAbs(a,&p);
        divide(&p,b,c,d);
        setSign(c,-1);
        setSign(d,-1);
        return 0;
    }

    if(Sa==-1 && Sb==-1){
        getAbs(a,&p);
        getAbs(b,&q);
        divide(&p,&q,c,d);
        setSign(d,-1);
        return 0;
    }
    return 623;
}

//割り算高速化
// a/b = c...d
int divide_2(struct NUMBER *a,struct NUMBER *b,struct NUMBER *c
,struct NUMBER *d){
    struct NUMBER n,p,q,r;
    int over;
    int Sa = getSign(a);
    int Sb = getSign(b);
    clearByZero(c);
    clearByZero(d);

    if(isZero(b)==0){
        printf("div by 0\n");
        return -1;
    }

    copyNumber(a,&n);

    if(Sa==1 && Sb==1){
        while(1){
            if(numComp(&n,b)==-1){
                break;
            }
            copyNumber(b,&p);
            setInt(&q,1);
            while(1){
                over = mulBy10(&p,&r);
               if(over == -1){
                    break;
                }
                if(numComp(&n,&r)==-1){
                    break;
                }
                copyNumber(&r,&p);
                mulBy10(&q,&r);
                copyNumber(&r,&q);
            }
            sub(&n,&p,&r);
            copyNumber(&r,&n);
            add(c,&q,&r);
            copyNumber(&r,c);

        }
        copyNumber(&n,d);
        return 0;
    }
    return 623;
}


// c<- a^b !0^0=1, 1^k:高速化,0^k:高速化
int power(struct NUMBER *a,struct NUMBER *b,struct NUMBER *c){
    struct NUMBER i,j,d;
    clearByZero(c);
    if(getSign(b)==-1){
        return -1;
    }

    //a=0のとき
    if(isZero(a)==0){
        if(isZero(b)==0){
            setInt(c,1);
            return 0;
        }
        setInt(c,0);
        return 0;
    }

    //a=1のとき
    setInt(&i,1);
    if(numComp(a,&i)==0){
        setInt(c,1);
        return 0;
    }

    clearByZero(&i);
    clearByZero(&j);
    copyNumber(a,c);
    while(1){
        increment(&i,&j);
        copyNumber(&j,&i);
        if(numComp(&i,b)==0){
            return 0;
        }
        multiple(c,a,&d);
        copyNumber(&d,c);
    }
}

// c <- x^n 高速化
int p_recursive(struct NUMBER *x,struct NUMBER *n,struct NUMBER *c){

    struct NUMBER temp,temp2;

    clearByZero(&temp);
    clearByZero(&temp2);
    //n負の時終了
    if(getSign(n)==-1){
        return -1;
    }
    //n=1のときcにx入れて終わり
    setInt(c,1);   
    if(isZero(n)==0){
        return 0;
    }

    //
    if(numComp(x,c)==0){
        copyNumber(x,c);
        return 0;
    }

    increment(c,&temp);
    divide_2(n,&temp,&temp2,c);
    if(isZero(c)==0){
        multiple(x,x,&temp);
        p_recursive(&temp,&temp2,c);
        return 0;
    }
    decrement(n,&temp);
    p_recursive(x,&temp,&temp2);
    multiple(x,&temp2,c);
    return 0; 
}

// b <- a!
int factorial(struct NUMBER *a,struct NUMBER *b){
    struct NUMBER i,j;
    int over;
    clearByZero(&i);
    clearByZero(b);

    //aが負か検知
    if(numComp(a,&i)==-1){
        printf("a<0 error\n");
        return -2;
    }

    setInt(b,1);
    increment(&i,&j);
    copyNumber(&j,&i);

    //aが0か検知
    if(isZero(a)==0){
        return 0;
    }

    while(1){
        over = multiple(b,&i,&j);
        copyNumber(&j,b);
        if(over ==-1){
            printf("overflow!\n");
            return -1;
        }

        if(numComp(&i,a)==0){
            return 0;
        }
        increment(&i,&j);
        copyNumber(&j,&i);
    }
    return 623;
}

// c <- GCD(a,b) GCD:最大公約数
int gcd(struct NUMBER *a,struct NUMBER *b,struct NUMBER *c){
    struct NUMBER d,e,f,g;

    if((isZero(a)==0)||isZero(b)==0){
        clearByZero(c);
        return 0;
    }

    if(numComp(a,b)==-1){
        copyNumber(a,&d);
        copyNumber(b,&e);
        gcd(&e,&d,c);
        return 0;
    }
    copyNumber(a,&d);
    copyNumber(b,&e);

    while(1){
        divide_2(&d,&e,&f,&g);
        if(isZero(&g)==0){
            copyNumber(&e,c);
            return 0;
        }

        copyNumber(&e,&d);
        copyNumber(&g,&e);
    }
}

// c <- lcm(a,b)
int lcm(struct NUMBER *a,struct NUMBER *b,struct NUMBER *c){
    struct NUMBER n,m,temp,temp2;
    getAbs(a,&n);
    getAbs(b,&m);
    int compab = numComp(a,b);

    if((isZero(a)==0)||isZero(b)==0){
        printf("error\n");
        clearByZero(c);
        return -1;
    }

    if(compab>0){
        gcd(&n,&m,c);
        divide_2(&n,c,&temp,&temp2);
        multiple(&temp,&m,c);
        return 0;
    }
    if(compab==-1){
        gcd(&n,&m,c);
        divide_2(&m,c,&temp,&temp2);
        multiple(&temp,&n,c);
        return 0;
    }
    return 623;
}

// b<- sqrt{a} (Newton-Raphson法)
int sqrt_newton(struct NUMBER *a,struct NUMBER *b){
    struct NUMBER x,temp,temp2,c,d;
    
    setInt(&d,2);
    divide_2(a,&d,&x,&c);
    if(isZero(&x)==0){
        copyNumber(&x,b);
        return 0;
    }

    if(getSign(&x)==-1){
        return -1;
    }

    copyNumber(&x,&d);

    while(1){
        copyNumber(&d,&c);
        copyNumber(&x,&d);

        divide_2(a,&d,&temp,&temp2);
        add(&d,&temp,&temp2);
        setInt(b,2);
        divide_2(&temp2,b,&x,&temp);

        if(numComp(&x,&d)==0){
            break;
        }
        if(numComp(&x,&c)==0){
            if(numComp(&d,&x)==-1){
                copyNumber(&d,&x);
            }
        }
    }
    copyNumber(&x,b);
    return 0;
}

int isPrime(struct NUMBER *a){
    struct NUMBER temp,temp2,temp3;
    setInt(&temp,1);
    setInt(&temp2,2);


    //負の数,0,1をはじく
    if(numComp(a,&temp)<=0){
        return 0;
    }

    setInt(&temp,2);
    if(numComp(a,&temp)==0){
        return 0;
    }

    setInt(&temp,3);
    while(1){
        divide_2(a,&temp,&temp2,&temp3);
        if(isZero(&temp3)==0){
            if(numComp(a,&temp)==0){
                return 1;
            }else{
                return 0;
            }
        }
        setInt(&temp2,2);
        add(&temp,&temp2,&temp3);
        copyNumber(&temp3,&temp);
    }
    return 623;
}


int B_setSign (struct BUNSU *a,int s){
    if(s==1){
        a->sign =1;
        return 0;
    }else if(s==-1){
        a->sign=-1;
        return 0;
    }else{
        return -1;
    }
    return 623;
}

int B_getSign (struct BUNSU *a){
    if(a->sign==1){
        return 1;
    }else if(a->sign==-1){
        return -1;
    }else{
        return 623;
    }
    return 623;
}

int B_clearByZero(struct BUNSU *a){
    clearByZero(&a->bunshi);
    clearByZero(&a->bunbo);
    B_setSign(a,1);
    return 0;
}

int B_dispNumber(struct BUNSU *a){
int i;
int j=1;

    if(B_getSign(a)==1){
        printf("+ ");
    }else{
        printf("- ");
    }

    for(i=KETA-1; i>=0; i--){
        if(j){
            if(a->bunshi.n[i] != 0){
                printf("%d",a->bunshi.n[i]);
                j=0;
            }
        }else{
        printf("%d",a->bunshi.n[i]);
        }
    }
    printf(" / ");
    j=1;
    for(i=KETA-1; i>=0; i--){
        if(j){
            if(a->bunbo.n[i] != 0){
                printf("%d",a->bunbo.n[i]);
                j=0;
            }
        }else{
        printf("%d",a->bunbo.n[i]);
        }
    }
    return 0;
}

int B_copyNumber(struct BUNSU *a,struct BUNSU *b){
    copyNumber(&a->bunbo,&b->bunbo);
    copyNumber(&a->bunshi,&b->bunshi);
    B_setSign(b,B_getSign(a));
    return 0;
}

//符号の設定は分子でしてね
int B_setInt(struct BUNSU *a,int bunshi,int bunbo){
    int temp;
    if(bunbo==0){
        printf("分母が0です\n");
    }

    if(bunshi<0){
        temp=-1*bunshi;
        B_setSign(a,-1);
    }else{
        temp = bunshi;
        B_setSign(a,1);
    }

    setInt(&a->bunbo,bunbo);
    setInt(&a->bunshi,temp);
    return 0;
}

int B_getAbs(struct BUNSU *a,struct BUNSU *b){
    B_copyNumber(a,b);
    B_setSign(b,1);
    return 0;
}

//b <-約分(a)
int B_yakubun(struct BUNSU *a,struct BUNSU *b){
    struct NUMBER temp,temp2;
    gcd(&a->bunshi,&a->bunbo,&temp);
    setInt(&temp2,1);

    //gcd=0
    if(isZero(&temp)==0){
        B_clearByZero(b);
        return 0;
    }
    //gcd=1
    if(numComp(&temp,&temp2)==0){
        if(numComp(&a->bunshi,&a->bunbo)==0){
            B_setInt(b,1,1);
            B_setSign(b,B_getSign(a));
        }else{
            B_copyNumber(a,b);
        }
        return 0;
    }

    //else
    divide_2(&a->bunshi,&temp,&b->bunshi,&temp2);
    divide_2(&a->bunbo,&temp,&b->bunbo,&temp2);
    B_setSign(b,B_getSign(a));
    return 0;
}

int B_multiple(struct BUNSU *a,struct BUNSU *b,struct BUNSU *c){
    struct NUMBER A,B,E;
    struct BUNSU temp;
    int Sa = B_getSign(a);
    int Sb = B_getSign(b);
    int Sc,r;
    B_clearByZero(c);

    copyNumber(&a->bunshi,&A);
    setSign(&A,Sa);
    copyNumber(&b->bunshi,&B);
    setSign(&B,Sb);

    r = multiple(&A,&B,&E);
    if(r==-1){
        printf("overflow\n");
        return -1;
    }
    Sc=getSign(&E);

    getAbs(&E,&c->bunshi);
    B_setSign(c,Sc);
    r = multiple(&a->bunbo,&b->bunbo,&c->bunbo);
    if(r==-1){
        printf("overflow\n");
        return -1;
    }
    B_yakubun(c,&temp);
    B_copyNumber(&temp,c);
    return 0;

}

int B_add(struct BUNSU *a,struct BUNSU *b,struct BUNSU *c){
    struct NUMBER A,B,temp,temp2,temp3;
    int Sa = B_getSign(a);
    int Sb = B_getSign(b);
    int Sc,r;
    B_clearByZero(c);
    copyNumber(&a->bunshi,&A);
    setSign(&A,Sa);
    copyNumber(&b->bunshi,&B);
    setSign(&B,Sb);

    r = multiple(&a->bunbo,&b->bunbo,&c->bunbo);
    if(r==-1){
        printf("overflow\n");
        return -1;
    }
    r =multiple(&A,&b->bunbo,&temp);
    if(r==-1){
        printf("overflow\n");
        return -1;
    }
    r =multiple(&B,&a->bunbo,&temp2);
    if(r==-1){
        printf("overflow\n");
        return -1;
    }
    r =add(&temp,&temp2,&temp3);
    if(r==-1){
        printf("overflow\n");
        return -1;
    }
    Sc = getSign(&temp3);
    copyNumber(&temp3,&c->bunshi);
    B_setSign(c,Sc);
    return 0;
}


int calZeta4(struct BUNSU *a,int N){
    int n,k,r;
    struct BUNSU A,B,C,D,E,SUM;
    B_setInt(&A,4,7);
    B_copyNumber(&A,&SUM);

    for(n=1;n<N;n++){
        k=0;
        B_setInt(&B,1,2);
        B_setInt(&C,n,n-k);
        r = B_multiple(&A,&B,&D);
        if(r==-1){
            printf("overflow n= %d , k= %d\n",n,k);
            exit(1);
        }
        r = B_multiple(&C,&D,&B);
        if(r==-1){
            printf("overflow n= %d , k= %d\n",n,k);
            exit(1);
        }
        B_copyNumber(&B,&C);
        r = B_add(&SUM,&C,&B);
        if(r==-1){
            printf("overflow n= %d , k= %d\n",n,k);
            exit(1);
        }

        B_yakubun(&B,&SUM);
        B_copyNumber(&C,&A);

        /*printf("n = %d , k = 0\n",n);
        B_dispNumber(&C);
        printf("\n");*/

        for(k=1;k<=n;k++){
            B_setInt(&B,k-n-1,k);
            B_setInt(&D,k,k+1);
            //4乗計算
            r = B_multiple(&D,&D,&E);
            if(r==-1){
            printf("overflow n= %d , k= %d\n",n,k);
            exit(1);
            }
            r = B_multiple(&E,&E,&D);
            if(r==-1){
            printf("overflow n= %d , k= %d\n",n,k);
            exit(1);
            }
            
            r = B_multiple(&D,&B,&E);
            if(r==-1){
            printf("overflow n= %d , k= %d\n",n,k);
            exit(1);
            }
            r = B_multiple(&E,&C,&D);
            if(r==-1){
            printf("overflow n= %d , k= %d\n",n,k);
            exit(1);
            }

            /*printf("n = %d , k = %d\n",n,k);
            B_dispNumber(&D);
            printf("\n");*/

            r =B_add(&SUM,&D,&B);
            if(r==-1){
            printf("overflow n= %d , k= %d\n",n,k);
            exit(1);
            }
            B_yakubun(&B,&SUM);
            B_copyNumber(&D,&C);
        }
        if(n%1==0){
        printf("n = %d\nresult = ",n);
        B_dispNumber(&SUM);
        printf("\n\n");
        }
    }
    return 0;
}
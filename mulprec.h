#define KETA 100

struct NUMBER{
    int n[KETA];
    int sign;
};

struct BUNSU{
    struct NUMBER bunshi;
    struct NUMBER bunbo;
    int sign;
};

void clearByZero(struct NUMBER *a);
void dispNumber(struct NUMBER *a);
void dispNumberZeroSuppress(struct NUMBER *a);
void setRnd(struct NUMBER *a,int k);
void copyNumber(struct NUMBER *a,struct NUMBER *b);
void getAbs(struct NUMBER *a,struct NUMBER *b);
int isZero(struct NUMBER *a);
int mulBy10(struct NUMBER *a,struct NUMBER *b);
int divBy10(struct NUMBER *a,struct NUMBER *b);
int setInt(struct NUMBER *a,int x);
int getSign(struct NUMBER *a);
int setSign(struct NUMBER *a,int s);
int numComp(struct NUMBER *a,struct NUMBER *b);
int add(struct NUMBER *a,struct NUMBER *b,struct NUMBER *c);
int sub(struct NUMBER *a,struct NUMBER *b,struct NUMBER *c);
int simpleMultiple(int a,int b,int *c);
int multiple(struct NUMBER *a,struct NUMBER *b,struct NUMBER *c);
int Karatsuba(struct NUMBER *a,struct NUMBER *b,struct NUMBER *c,int keta);
int increment(struct NUMBER *a,struct NUMBER *b);
int decrement(struct NUMBER *a,struct NUMBER *b);
int divide(struct NUMBER *a,struct NUMBER *b,struct NUMBER *c,struct NUMBER *d);
int divide_2(struct NUMBER *a,struct NUMBER *b,struct NUMBER *c,struct NUMBER *d);
int power(struct NUMBER *a,struct NUMBER *b,struct NUMBER *c);
int p_recursive(struct NUMBER *x,struct NUMBER *n,struct NUMBER *c);
int factorial(struct NUMBER *a,struct NUMBER *b);
int gcd(struct NUMBER *a,struct NUMBER *b,struct NUMBER *c);
int sqrt_newton(struct NUMBER *a,struct NUMBER *b);
int lcm(struct NUMBER *a,struct NUMBER *b,struct NUMBER *c);
int isPrime(struct NUMBER *a);
int B_setSign (struct BUNSU *a,int s);
int B_getSign (struct BUNSU *a);
int B_clearByZero(struct BUNSU *a);
int B_dispNumber(struct BUNSU *a);
int B_copyNumber(struct BUNSU *a,struct BUNSU *b);
int B_setInt(struct BUNSU *a,int bunshi,int bunbo);
int B_getAbs(struct BUNSU *a,struct BUNSU *b);
int B_yakubun(struct BUNSU *a,struct BUNSU *b);
int B_multiple(struct BUNSU *a,struct BUNSU *b,struct BUNSU *c);
int B_add(struct BUNSU *a,struct BUNSU *b,struct BUNSU *c);
int calZeta4(struct BUNSU *a,int N);
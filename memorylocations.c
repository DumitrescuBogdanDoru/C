#include<stdio.h>
#include<stdlib.h>

//global variables declared and initialized here
int n1 = 0xffffffff;
unsigned int n2 = 0xffffffff; float f1 = 5.5;
double f2 = 5.5;
int *p1 = &n1;
char* s1 = "Hello world!";

//constant variable
const int i = 10;

//uninitialized variable
int un;

void encoding(int a, int b){
    int k1,k2;
    for(int c = 31; c >= 0; c--)
    {
        k1 = a >> c;

        if(k1 & 1)
            printf("1");
        else
            printf("0");
    }
    printf("\n");
    for(int c = 31; c >= 0; c--)
    {
        k2 = b >> c;

        if(k2 & 1)
            printf("1");
        else
            printf("0");
   }
   printf("\n");
}

void global(){
    //global variables
    printf("\nGlobal variables:\n");
    //address
    printf("Memory locations:\n");
    printf("address of n1 = %p\n",&n1);
    printf("address of n2 = %p\n",&n2);
    printf("address of f1 = %p\n",&f1);
    printf("address of f2 = %p\n",&f2);
    printf("address of p1 = %p\n",&p1);
    printf("address of s1 = %p\n",&s1);
    //size
    printf("Size:\n");
    printf("size of n1 = %lu\n",sizeof(n1));
    printf("size of n2 = %lu\n",sizeof(n2));
    printf("size of f1 = %lu\n",sizeof(f1));
    printf("size of f2 = %lu\n",sizeof(f2));
    printf("size of p1 = %lu\n",sizeof(p1));
    printf("size of s1 = %lu\n",sizeof(s1));
    //value
    printf("Value:\n");
    printf("n1 = %d\n",n1);
    printf("n2 = %d\n",n2); 
    printf("f1 = %f\n",f1);
    printf("f2 = %lf\n",f2);
    printf("p1 = %d\n",*p1);
    printf("s1 = %s\n",s1);
    //alignment
    printf("Alignment:\n");
    if ((int)&n1 % 4 == 0) printf("n1 is alligned\n");
    if ((int)&n2 % 4 == 0) printf("n2 is alligned\n");
    if ((int)&f1 % 4 == 0) printf("f1 is alligned\n");
    if ((int)&f2 % 8 == 0) printf("f2 is alligned\n");
    if ((int)&p1 % 8 == 0) printf("p1 is alligned\n");
    if ((int)&s1 % 8 == 0) printf("s1 is alligned\n");
    //encoding
    printf("Encoding:\n");
    encoding(n1,n2);
}

void function(int n, float f, char* c){
    printf("\nFuntion variables:\n");
    //address
    printf("Memory locations:\n");
    printf("address of int = %p\n",&n);
    printf("address of float = %p\n",&f);
    printf("address of char = %p\n",&c);
    //size
    printf("Size:\n");
    printf("size of int = %lu\n",sizeof(n));
    printf("size of float = %lu\n",sizeof(f));
    printf("size of char = %lu\n",sizeof(c));
    //value
    printf("Value:\n");
    printf("int = %d\n",n);
    printf("float = %f\n",f);
    printf("char = %s\n",c);
    //aligment
    printf("Alignment:\n");
    if ((int)&n % 4 == 0) printf("int is alligned\n");
    if ((int)&f % 4 == 0) printf("float is alligned\n");
    if ((int)&c % 8 == 0) printf("char is alligned\n");

}

void compare(int n){
    printf("\nComparing memory locations:\n");
    //.data
    //global variables
    printf(".data:\t%p\n",&n1);
    //.bss
    //uninitialized variables
    //I created an uninitialized variable named un
    printf(".bss:\t%p\n",&un);
    //.stack
    //local variables, function parameters
    printf(".stack:\t%p\n",&n);
    //.text
    //the constants are saved in the .text segment of the memory
    //I created a constant variable named i
    printf(".text:\t%p\n",&i);

}

int main(){
    //global variables declared and initialized here
    int n3 = 0xffffffff;
    unsigned int n4 = 0xffffffff;
    float f3 = 5.5;
    double f4 = 5.5;
    int *p2 = &n3;
    char* s2 = "Hello world!";

    //global
    global();

    //local
    printf("\nLocal variables:\n");
    //address
    printf("Memory locations:\n");
    printf("address of n3 = %p\n",&n3);
    printf("address of n4 = %p\n",&n4);
    printf("address of f3 = %p\n",&f3);
    printf("address of f4 = %p\n",&f4);
    printf("address of p2 = %p\n",&p2);
    printf("address of s2 = %p\n",&s2);
    //size
    printf("Size:\n");
    printf("size of n3 = %lu\n",sizeof(n3));
    printf("size of n4 = %lu\n",sizeof(n4));
    printf("size of f3 = %lu\n",sizeof(f3));
    printf("size of f4 = %lu\n",sizeof(f4));
    printf("size of p2 = %lu\n",sizeof(p2));
    printf("size of s2 = %lu\n",sizeof(s2));
    //value
    printf("Value:\n");
    printf("n3 = %d\n",n3);
    printf("n4 = %d\n",n4); 
    printf("f3 = %f\n",f3);
    printf("f4 = %lf\n",f4);
    printf("p2 = %d\n",*p2);
    printf("s2 = %s\n",s2);
    //alignment
    printf("Alignment:\n");
    if ((int)&n3 % 4 == 0) printf("n3 is alligned\n");
    if ((int)&n4 % 4 == 0) printf("n4 is alligned\n");
    if ((int)&f3 % 4 == 0) printf("f3 is alligned\n");
    if ((int)&f4 % 8 == 0) printf("f4 is alligned\n");
    if ((int)&p2 % 8 == 0) printf("p2 is alligned\n");
    if ((int)&s2 % 8 == 0) printf("s2 is alligned\n");
    //encoding
    printf("Encoding:\n");
    encoding(n3,n4);
    

    //function variables
    function(n1,f1,s1);

    //compare memory locations 
    compare(n3);
    return 0;
}
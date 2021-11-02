#include<stdio.h>

void say_hello_world(){
    printf("hello world!\n");
}

int main(void){
    say_hello_world();

    int temp=2;
    while (temp--) {
        printf("123\n");
        // break;
    }

    return 0;
}

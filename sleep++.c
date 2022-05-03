#include "stdio.h"
#include <time.h>

#include <unistd.h>

int input() {
    int number;
    //Checks to see if scanf succesfully read into number.
    if (scanf("%ia", &number) != 1) {
        printf("Please enter an integer");
    }
    return number;
}

int main() {
    int sleepTime = input();

    time_t start = time(0);
    int segments = 10;
    double interval = ((double )sleepTime / segments) * 10e5;
    double elapsed = 0;
    
    int count = 0;
    printf("\e[?25l");
    while (elapsed < sleepTime){
        printf("\r[");
        for (int i = 0; i < count; ++i){
            printf("█");
        }
        printf("%*c]", segments-count,  ' ');
        fflush(stdout);
        usleep(interval);
        count++;
    
        elapsed = difftime(time(0), start);
    }
    printf("\r[");
    for (int i = 0; i < segments; ++i){
        printf("█");
    }
    printf("]\n");
    

    printf("\e[?25l");
    return 0;


}
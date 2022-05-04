#include "stdio.h"
#include <time.h>
#include <unistd.h>

int input() {
    int time;
    char letter;
    char inp[11];
    // fgets the size of the largest integer + a trailing character for unit size
    if (fgets(inp, 11, stdin) != NULL) {
        //Reparse input into variables
        int ct = sscanf(inp, "%i %c", &time, &letter);
        //Check the number of succesful input assignments and process based on number of inputs
        if (ct == 0) {
            printf("Please enter an integer\n");
        } else if (ct == 1) {
            return time;
        }
    }

    //Scale time based on the unit ('m': minutes, 'h' hours) 
    if (letter == 'm'){
        return time * 60;
    } else if (letter == 'h') {
        return time * 3600;
    }

    //Otherwise print message and return failure
    printf("Please enter a valid unit (m or h)");
    return -1;
}

void printProgress (int length, int fill, int time) {
    printf("\r[");
    for (int i = 0; i < fill; ++i){
        printf("█");
    }
    printf("%*c %d", length - fill,  ']', time);

}

int main() {
    int sleepTime = input();
    if (sleepTime == -1)
        return -1;
        
    clock_t start = clock();
    int segments = 50;
    double interval = ((double )sleepTime / segments);
    double elapsed = 0;
    
    int count = 0;
    printf("\e[?25l");

    while (elapsed < sleepTime){
        if (interval * (double)count < elapsed) {
            printProgress(segments, count, (int) elapsed);
            fflush(stdout);
            count++;
        }
    
        elapsed = (double)(clock() - start) / CLOCKS_PER_SEC;
    }

    printProgress(segments,segments, (int)elapsed);

    printf("\e[?25h \n");
    return 0;


}
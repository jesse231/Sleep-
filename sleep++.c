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

void printProgress (int length, int fill) {
    printf("\r[");
    for (int i = 0; i < fill; ++i){
        printf("█");
    }
    printf("%*c", length - fill,  ']');

}

int main() {
    int sleepTime = input();
    if (sleepTime == -1)
        return -1;
        
    time_t start = time(0);
    int segments = 50;
    double interval = ((double )sleepTime / segments) * 10e5;
    double elapsed = 0;
    
    int count = 0;
    printf("\e[?25l");

    while (elapsed < sleepTime){
    
        printProgress(segments , count);
        fflush(stdout);
        usleep(interval);
        count++;
    
        elapsed = difftime(time(0), start);
    }

    printProgress(segments,segments);

    printf("\e[?25h \n");
    return 0;


}
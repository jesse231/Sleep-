#include "stdio.h"
#include <time.h>
#include <unistd.h>
#include <sys/ioctl.h>


int parse(char* inp) {
    int time;
    char letter;
    //parse input into variables
    int ct = sscanf(inp, "%i %c", &time, &letter);

    //Check the number of succesful input assignments and process based on number of inputs
    if (ct == 0) {
        printf("Please enter an integer\n");
        return -1;
    } else if (ct == 1) {
        return time;
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

int main(int argc, char** argv) {
    if (argc == 1){
        printf("Please enter an integer\n");
        return 1;
    }

    int sleepTime = parse(argv[1]);
    
    if (sleepTime == -1)
        return 1;
    
        
    clock_t start = clock();

    //Get terminal size
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    int segments = w.ws_col/2;

    double interval = (double) sleepTime / segments;
    double elapsed = 0;
    int count = 0;
    
    printf("\e[?25l");

    while (elapsed < sleepTime){
        if (interval * (double) count < elapsed) {
            printProgress(segments, count, elapsed);
            fflush(stdout);
            count++;
        }

        elapsed = (double) (clock() - start) / CLOCKS_PER_SEC;
    }

    printProgress(segments,segments, (int) elapsed);

    printf("\e[?25h \n");
    return 0;


}
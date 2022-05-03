#include "stdio.h"
#include <time.h>
#include <unistd.h>

struct inp {
    int number;
    char letter;
};
struct inp input() {
    struct inp length;
    char inp[11];
    int test1;
    char test2;
    // fgets the size of the largest integer + a trailing character for unit size
    if (fgets(inp,11,stdin) != NULL) {
        //Reparse input into variables
        int ct = sscanf(inp, "%i %c", &length.number, &length.letter);
        //Check the number of succesful input assignments and process based on number of inputs
        if (ct == 0) {
            printf("Please enter an integer\n");
        } else if (ct == 1) {
            length.letter = 0;
        }
    }
    return length;
}

void printProgress (int length, int fill) {
    printf("\r[");
    for (int i = 0; i < fill; ++i){
        printf("█");
    }
    printf("%*c", length - fill,  ']');

}

int main() {
    struct inp ln = input();
    int sleepTime;
    switch (ln.letter){
        case 'm':
            sleepTime = ln.number * 60;
            break;
        case 'h':
            sleepTime = ln.number * 3600;
            break;
        default:
            sleepTime = ln.number;
            break;
    }
    time_t start = time(0);
    int segments = 50;
    double interval = ((double )sleepTime / segments) * 10e5;
    double elapsed = 0;
    
    int count = 0;
    printf("\e[?25l");
    while (elapsed < sleepTime){
        // if (count != )
        // printProgress(segments , count);
        // fflush(stdout);
        printf("%c\n", ln.letter);
        usleep(interval);
        count++;
    
        elapsed = difftime(time(0), start);
    }

    printProgress(segments,segments);

    printf("\e[?25h \n");
    return 0;


}
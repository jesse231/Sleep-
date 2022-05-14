#include "stdio.h"
#include <time.h>
#include <unistd.h>
#include <sys/ioctl.h>


int parse(char* inp) {
    int time;
    char letter;
    // Parse input into variables (lets the letter be optional)
    int ct = sscanf(inp, "%i %c", &time, &letter);

    if (ct == 0) {
        printf("Please enter an integer\n");
        return -1;
    // Check if the letter was added or not
    } else if (ct == 1) {
        return time;
    }

    // Scale time based on the unit ('m': minutes, 'h' hours) 
    if (letter == 'm'){
        return time * 60;
    } else if (letter == 'h') {
        return time * 3600;
    }

    printf("Please enter a valid unit (m or h)");
    return -1;
}


void printProgress (int length, int fill, char* time) {
    printf("\r[");
    for (int i = 0; i < fill; ++i){
        printf("█");
    }
    printf("%*c %s", length - fill,  ']', time);

}

// Breaks seconds into a string with hours, minutes and seconds.
void timeDisplay (int sec, char* res, int buffSize) {
    char hours[50] = "";
    char minutes[50] = "";
    char seconds[50] = "";
    int hr, min, s;

    if ((hr = sec / (60 * 60))) {
        snprintf(hours, sizeof(hours), "%ih ", hr);
    }

    if ((min = (sec - hr * (60 * 60)) / 60)) {
        snprintf(minutes, sizeof(minutes), "%im ", min);
    }

    s = sec - hr * (60 * 60) - min * 60;
    snprintf(seconds, sizeof(seconds), "%is", sec);

    snprintf(res, buffSize, "%s%s%s", hours, minutes, seconds);



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
            char time[50];
            timeDisplay(elapsed, time, sizeof(time));
            printProgress(segments, count, time);
            fflush(stdout);
            count++;
        }

        elapsed = (double) (clock() - start) / CLOCKS_PER_SEC;
    }

    printProgress(segments ,segments ,"Done");

    printf("\e[?25h \n");
    return 0;


}
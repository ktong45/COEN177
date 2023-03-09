// Kristin Tong
// Lab 8 - paging scheduling
// test input generation

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
 
int main(int argc, char *argv[]) {
    int capNumber = atoi(argv[2]);
    int someNumber = atoi(argv[1]);
    FILE *fp;
    char buffer [someNumber];
    int i;
    fp = fopen("testInput.txt", "w");
    for (i=0; i<someNumber; i++){
        sprintf(buffer, "%d\n", rand()%capNumber);
        fputs(buffer, fp);
    }
    fclose(fp);
    return 0;
}

// takes two arguments
// (1) number of pages
// (2) maximum page number
// int main(int argc, char *argv[]) {
//     FILE *fp;
//     char buffer [sizeof(int)];
//     int i;
//     srand(time(NULL));
//     fp = fopen("testInput.txt", "w");
//     for (i=0; i< atoi(argv[1]); i++){
//         sprintf(buffer, "%d\n", rand()%500);
//         fputs(buffer, fp);
//     }
//     fclose(fp);
//     return 0;
// }
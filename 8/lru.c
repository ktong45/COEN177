// Kristin Tong
// Nov. 16, 2022
// Lab 8 - page scheduling
// LRU: least recently used

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

// page struct with number and age
typedef struct {     
        int pageno;
        int age;
} ref_page;

int main(int argc, char *argv[]) {
    int C_SIZE=atoi(argv[1]);
    ref_page cache[C_SIZE]; 
    char pageCache[100]; 
    int cacheIndex=0;
    int totalFaults=0; 
    int totalRequests=0;
    int i, j, k, page_num, oldest;
    
    //initialize array with pageno -1 and age 0
    for(i=0;i<C_SIZE;i++) {
        cache[i].pageno = -1;
        cache[i].age = 0;
    }

    while(fgets(pageCache, 100, stdin)) {
        page_num = atoi(pageCache);
        totalRequests++;
        oldest = cache[i].age;                                          // Set temporary oldest
        for(i = 0; i < C_SIZE; i++) {                                   // Loop through array
            if(cache[i].pageno == page_num) {                           // If we find in array already
                for(j = 0; j < C_SIZE; j++) {                           
                    if(cache[j].age < cache[i].age)                     // Increment ages of all younger arrays
                        cache[j].age++;
                }
                cache[i].age = 0;                                       // Reset age of array to 0 once hit
                break;
            }

            else if(i == C_SIZE-1) {                                    // If our array is full
                printf("Page %d caused a fault\n", page_num);           
                totalFaults++;  
                for(j = 0; j < C_SIZE; j++) {                           // Increment age of all indices
                    cache[j].age++;
                }
                
                for(k = 0; k < C_SIZE ; k++) {                          // Loop through array
                    if(oldest < cache[k].age){                          // If we have older index
                        oldest = cache[k].age;                          // set new oldest
                        cacheIndex = k;                                 // set index at k
                    }
                }
                cache[cacheIndex].pageno = page_num;
                cache[cacheIndex].age = 0;
            }
        }
    }

    double hitRate = (double)(totalRequests - totalFaults) / (double)totalRequests;

    printf("%d Total Page Faults\n", totalFaults);
    printf("%d Total Page Requests\n", totalRequests);
    printf("%f Total Hit Rate\n", hitRate);

    return 0;
}

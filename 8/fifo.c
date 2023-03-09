// Kristin Tong
// Nov. 16, 2022
// Lab 8 - page scheduling
// FIFO: first in first out

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

typedef struct { //to 
    int pageno;
} ref_page;


int main(int argc, char *argv[]){
	int CACHE_SIZE = atoi(argv[1]); // Size of Cache from user
    ref_page cache[CACHE_SIZE]; // Cache that stores pages
    char pageCache[100]; // Cache that holds the input from test file

    int i;
    int totalFaults = 0; // keeps track of the total page faults
    int totalRequests = 0; // keeps track of page requests
    int placeInArray = 0;
    
    for (i = 0; i < CACHE_SIZE; i++){ //initialise cache array  
         cache[i].pageno = -1;
    }

    while (fgets(pageCache, 100, stdin)){
    	int page_num = atoi(pageCache); // Stores number read from file as an int
        bool foundInCache = false;
        totalRequests++;

        // traverse cache see if pageno matches
        for (i=0; i<CACHE_SIZE; i++){
            if (cache[i].pageno == page_num){
                foundInCache = true;
                break; //break out loop because found page_num in cache  
            }
        }   
        // if pageno does not hit
        if (foundInCache == false){
            //You may print the page that caused the page fault
            cache[placeInArray].pageno = page_num;
            totalFaults++;
            placeInArray = (placeInArray + 1) % CACHE_SIZE; //Need to keep the value within the cacheSize
        }
    }

    double hitRate = (double)(totalRequests - totalFaults) / (double)totalRequests;

    printf("%d Total Page Faults\n", totalFaults);
    printf("%d Total Page Requests\n", totalRequests);
    printf("%f Total Hit Rate\n", hitRate);

    return 0;



}

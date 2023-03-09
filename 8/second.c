// Kristin Tong
// Nov. 16, 2022
// Lab 8 - page scheduling
// Second second_chance: first in first out

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

typedef struct { //to 
    int pageno;
    int second_chance;
} ref_page;


int main(int argc, char *argv[]){
	int CACHE_SIZE = atoi(argv[1]); 
    ref_page cache[CACHE_SIZE]; 
    char pageCache[100]; 

    int counter =0;
    int i, j;
    int totalFaults = 0; 
    int totalRequests = 0;
    int placeInArray = 0;
    
    for (i = 0; i < CACHE_SIZE; i++){ 
         cache[i].pageno = -1;
    }

    while (fgets(pageCache, 100, stdin)){
    	int page_num = atoi(pageCache); // Stores number read from file as an int
        bool foundInCache = false;
        totalRequests++;

    // traverse cache see if pageno matches
	for(i = 0; i < CACHE_SIZE; i++) {
		if(cache[i].pageno == page_num) // page_num already exists
		{
			if(cache[i].second_chance == 0) // set second_chance bit to 1
				cache[i].second_chance = 1;
			break;
		}
		else if(i == CACHE_SIZE-1) // page not in cache
		{
			totalFaults++; // increase number of faults
			for(j = counter; j < CACHE_SIZE; j++) //loop through array starting at counter index
			{
				// check second_chance bit
				if(cache[j].second_chance == 1) //if it is the page's second chance
				{
					cache[j].second_chance = 0; //page has had a second_chance, reset bit
					counter++;
					if(counter == CACHE_SIZE)
					{
						counter = 0;
						j = -1;
					}
				}
				else // not second_chance
				{
					cache[j].pageno = page_num; // replace pageno
					cache[j].second_chance = 0; // reset second_chance
					counter++;
					if(counter == CACHE_SIZE)
					{
						counter = 0;
					}
					break;
				}
			}
		}
	}
		
    }

    double hitRate = (double)(totalRequests - totalFaults) / (double)totalRequests;

    printf("%d Total Page Faults\n", totalFaults);
    printf("%d Total Page Requests\n", totalRequests);
    printf("%f Total Hit Rate\n", hitRate);

    return 0;



}

#include <stdio.h>
#include <stdlib.h>

#define MAX_FRAMES 3 
#define MAX_PAGES 20  

int frames[MAX_FRAMES];
int last_used[MAX_FRAMES];


void initialize()
{
    for (int i = 0; i < MAX_FRAMES; i++)
    {
        frames[i] = -1;  
        last_used[i] = -1; 
    }
}

void displayFrames()
{
    for (int i = 0; i < MAX_FRAMES; i++)
    {
        if (frames[i] != -1)
            printf("%d ", frames[i]);
        else
            printf("- ");
    }
    printf("\n");
}

int findLRU()
{
    int lru_index = 0;
    
    for (int i = 1; i < MAX_FRAMES; i++)
    {
        if (last_used[i] < last_used[lru_index]) 
            lru_index = i;
    }
    
    return lru_index;
}

void LRU(int pages[], int n)
{
    int page_faults = 0, time = 0;

    for (int i = 0; i < n; i++)
    {
        int page = pages[i];
        int found = 0;

        for (int j = 0; j < MAX_FRAMES; j++)
        {
            if (frames[j] == page)
            {
                found = 1;
                last_used[j] = time++;
                printf("Page %d is already in memory.\n", page);
                break;
            }
        }

        if (!found)
        {
            int replaceIndex = findLRU(); 
            frames[replaceIndex] = page; 
            last_used[replaceIndex] = time++; 
            page_faults++;

            printf("Page %d loaded into frame %d.\n", page, replaceIndex);
        }

        displayFrames();
    }

    printf("Total Page Faults: %d\n", page_faults);
}

int main()
{
    int pages[MAX_PAGES];
    int n;

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter the page reference sequence: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &pages[i]);
    }
    initialize();
    LRU(pages, n);

    return 0;
}

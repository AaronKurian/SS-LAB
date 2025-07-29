#include <stdio.h>
#include <stdlib.h>

#define MAX_FRAMES 3 
#define MAX_PAGES 20 

int frames[MAX_FRAMES];
int frequency[MAX_FRAMES]; 
int age[MAX_FRAMES]; 


void initialize()
{
    for (int i = 0; i < MAX_FRAMES; i++)
    {
        frames[i] = -1;  
        frequency[i] = 0; 
        age[i] = 0;      
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

int findLFU()
{
    int minFreq = frequency[0];
    int minIndex = 0;

    for (int i = 1; i < MAX_FRAMES; i++)
    {
        if (frequency[i] < minFreq)
        {
            minFreq = frequency[i];
            minIndex = i;
        }
        else if (frequency[i] == minFreq && age[i] < age[minIndex])
        {
            minIndex = i;
        }
    }
    return minIndex;
}

void LFU(int pages[], int n)
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
                frequency[j]++;
                printf("Page %d is already in memory.\n", page);
                break;
            }
        }

        if (!found)
        {
            int replaceIndex = findLFU();
            frames[replaceIndex] = page;
            frequency[replaceIndex] = 1;
            age[replaceIndex] = time++; 
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
    LFU(pages, n); 

    return 0;
}

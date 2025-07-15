#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BLOCKS 100
#define MAX_FILES 10
#define MAX_FILENAME 50

struct IndexBlock {
    int data_blocks[MAX_BLOCKS];
};

struct File {
    char filename[MAX_FILENAME];
    struct IndexBlock indexBlock;
};

void initializeIndexBlock(struct IndexBlock* indexBlock) {
    for (int i = 0; i < MAX_BLOCKS; ++i) {
        indexBlock->data_blocks[i] = -1; 
    }
}

int allocateDataBlock(struct IndexBlock* indexBlock, int blockNumber) {
    for (int i = 0; i < MAX_BLOCKS; ++i) {
        if (indexBlock->data_blocks[i] == -1) {
            indexBlock->data_blocks[i] = blockNumber;
            return 1;
        }
    }
    return 0; 
}

void displayFileBlocks(struct File* file) {
    printf("File: %s\nAllocated Blocks: ", file->filename);
    for (int i = 0; i < MAX_BLOCKS; i++) {
        if (file->indexBlock.data_blocks[i] != -1) {
            printf("%d ", file->indexBlock.data_blocks[i]);
        }
    }
    printf("\n");
}

int main() {
    struct File files[MAX_FILES];
    int num_files;

    printf("Enter number of files (max %d): ", MAX_FILES);
    scanf("%d", &num_files);
    if (num_files <= 0 || num_files > MAX_FILES) {
        printf("Invalid number of files.\n");
        return 1;
    }

    for (int i = 0; i < num_files; i++) {
        printf("\nFile %d:\n", i + 1);
        printf("Enter filename: ");
        scanf("%s", files[i].filename);

        initializeIndexBlock(&files[i].indexBlock);

        int num_blocks;
        printf("Enter number of blocks to allocate (max %d): ", MAX_BLOCKS);
        scanf("%d", &num_blocks);
        if (num_blocks <= 0 || num_blocks > MAX_BLOCKS) {
            printf("Invalid number of blocks.\n");
            i--;
            continue;
        }

        for (int j = 0; j < num_blocks; j++) {
            int block_num;
            printf("Enter block number %d: ", j + 1);
            scanf("%d", &block_num);

            if (!allocateDataBlock(&files[i].indexBlock, block_num)) {
                printf("Index block full. Cannot allocate more blocks.\n");
                break;
            }
        }
    }

    printf("\nSummary of allocated files and their blocks:\n");
    for (int i = 0; i < num_files; i++) {
        displayFileBlocks(&files[i]);
    }

    return 0;
}


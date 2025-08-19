#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void displayFile(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("Cannot open %s\n", filename);
        return;
    }
    printf("\nContents of %s:\n", filename);
    char ch;
    while ((ch = fgetc(fp)) != EOF)
        putchar(ch);
    fclose(fp);
}

void passTwo() {
    char label[10], opcode[10], operand[10], code[10], mnemonic[3];
    int loc;
    FILE *fp1, *fp2, *fp3, *fp4;

    fp1 = fopen("intermediate.txt", "r");
    fp2 = fopen("optab.txt", "r");
    fp3 = fopen("symtab.txt", "r");
    fp4 = fopen("output.txt", "w");

    if (!fp1 || !fp2 || !fp3 || !fp4) {
        printf("Error opening files\n");
        return;
    }

    char temp[50];
    fgets(temp, sizeof(temp), fp1);
    sscanf(temp, "%s %s %s", label, opcode, operand);

    if (strcmp(opcode, "START") == 0) {
        fprintf(fp4, "H^%s^%06X^\n", label, (int)strtol(operand, NULL, 16));
    }

    fscanf(fp1, "%X %s %s %s", &loc, label, opcode, operand);

    fprintf(fp4, "T^%06X^", loc);

    int first = 1;

    while (strcmp(opcode, "END") != 0) {
        int found = 0;
        rewind(fp2);
        while (fscanf(fp2, "%s %s", code, mnemonic) != EOF) {
            if (strcmp(opcode, code) == 0) {
                char symLabel[10];
                int symLoc;
                rewind(fp3);
                found = 0;
                while (fscanf(fp3, "%s %X", symLabel, &symLoc) != EOF) {
                    if (strcmp(operand, symLabel) == 0) {
                        if (first) {
                            fprintf(fp4, "%s%04X", mnemonic, symLoc);
                            first = 0;
                        } else {
                            fprintf(fp4, "^%s%04X", mnemonic, symLoc);
                        }
                        found = 1;
                        break;
                    }
                }
                if (!found) {
                    if (first) {
                        fprintf(fp4, "%s0000", mnemonic);
                        first = 0;
                    } else {
                        fprintf(fp4, "^%s0000", mnemonic);
                    }
                }
                found = 1;
                break;
            }
        }

        if (!found) {
            if (strcmp(opcode, "WORD") == 0) {
                int val = atoi(operand);
                if (first) {
                    fprintf(fp4, "%06X", val);
                    first = 0;
                } else {
                    fprintf(fp4, "^%06X", val);
                }
            }
            else if (strcmp(opcode, "BYTE") == 0) {
                if (operand[0] == 'C') {
                    for (int i = 2; operand[i] != '\''; i++) {
                        if (first) {
                            fprintf(fp4, "%02X", operand[i]);
                            first = 0;
                        } else {
                            fprintf(fp4, "^%02X", operand[i]);
                        }
                    }
                } else if (operand[0] == 'X') {
                    if (first) {
                        fprintf(fp4, "%s", operand + 2);
                        first = 0;
                    } else {
                        fprintf(fp4, "^%s", operand + 2);
                    }
                }
            }
        }

        fscanf(fp1, "%X %s %s %s", &loc, label, opcode, operand);
    }

    fprintf(fp4, "\nE^%06X\n", loc);

    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    fclose(fp4);

    printf("\nPass 2 completed. Output written to output.txt\n");
    
    displayFile("output.txt");
}

int main() {
    passTwo();
    return 0;
}


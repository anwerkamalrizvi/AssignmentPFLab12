/*Write a program which perform following operations
 Dynamically allocate memory to read the contents of a file of unknown size.
 Resize the buffer as needed while reading.
 Count the frequency of each word in the file.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define INITIAL_BUFFER_SIZE 1024
#define MAX_WORD_LENGTH 100
typedef struct {
    char* word;
    int count;
} WordFrequency;
char* readFile(const char* filename) 
{
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error: Unable to open file.\n");
        exit(1);
    }

    size_t bufferSize = INITIAL_BUFFER_SIZE;
    char* buffer = (char*)malloc(bufferSize);
    if (!buffer) 
    {
        printf("Error: Memory allocation failed.\n");
        exit(1);
    }

    size_t length = 0;
    int ch;
    while ((ch = fgetc(file)) != EOF) 
    {
        buffer[length++] = (char)ch;
        if (length >= bufferSize) 
        {
            bufferSize *= 2;
            buffer = (char*)realloc(buffer, bufferSize);
            if (!buffer) 
            {
        
                printf("Error: Memory reallocation failed.\n");
                exit(1);
            }
        
        
        }
    }
    buffer[length] = '\0';
    fclose(file);
    return buffer;
}
WordFrequency* countWordFrequency(const char* text, int* wordCount) 
{
    WordFrequency* frequencies = NULL;
    int capacity = 0;
    *wordCount = 0;

    char word[MAX_WORD_LENGTH];
    int index = 0;

    for (int i = 0; text[i] != '\0'; i++) 
    {
        if (isalnum(text[i])) 
        {
            word[index++] = tolower(text[i]);
        } else if (index > 0) {

                word[index] = '\0';
            index = 0;
            int found = 0;
            for (int j = 0; j < *wordCount; j++) 
            {
              
                if (strcmp(frequencies[j].word, word) == 0) 
                {
                    frequencies[j].count++;
                    found = 1;
                    break;
                }
            }
                if (!found) 
                {
                if (*wordCount >= capacity) {
                    capacity = capacity == 0 ? 10 : capacity * 2;
                    frequencies = (WordFrequency*)realloc(frequencies, capacity * sizeof(WordFrequency));
                    if (!frequencies) {
                        printf("Error: Memory reallocation failed.\n");
                        exit(1);
                    }
                }
                frequencies[*wordCount].word = strdup(word);
                frequencies[*wordCount].count = 1;
                (*wordCount)++;
            }
        }
    }

    return frequencies;
}//
void freeFrequencies(WordFrequency* frequencies, int wordCount) 
{
    for (int i = 0; i < wordCount; i++) {
        free(frequencies[i].word);
    }
    free(frequencies);
}
int main() {
    char filename[256];
    printf("Enter the filename: ");
    scanf("%s", filename);
    char* content = readFile(filename);

    int wordCount;
    WordFrequency* frequencies = countWordFrequency(content, &wordCount);
   printf("\nWord Frequencies:\n");
    for (int i = 0; i < wordCount; i++) 
    {
        printf("%s: %d\n", frequencies[i].word, frequencies[i].count);
    }
   free(content);
    freeFrequencies(frequencies, wordCount);
    return 0;
}//end main 

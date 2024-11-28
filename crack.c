#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "md5.h"

#if __has_include("fileutil.h")
#include "fileutil.h"
#endif

#define PASS_LEN 50     // Maximum length any password will be.
#define HASH_LEN 33     // Length of hash plus one for null.

int main(int argc, char *argv[])
{
    // Ensuring that there are an appropriate amount of arguments
    if (argc < 3) 
    {
        printf("Usage: %s hash_file dictionary_file\n", argv[0]);
        exit(1);
    }

    
    int size;
    // char (*hashes)[HASH_LEN] = loadFile(argv[1], &size);
    char **hashes = loadFileAA(argv[1], &size); // reads hash file into an array
    
    // CHALLENGE1: Sort the hashes using qsort.
    
    // TODO
    // Open the password file for reading.
    FILE *in = fopen(argv[2], "r"); // loading in the file of passwords
    if (!in) // if the file doesn't open then exit the program
    {
        printf("Couldn't open file: %s", argv[2]);
        exit(1);
    }

    // TODO
    // For each password, hash it, then use the array search
    // function from fileutil.h to find the hash.
    // If you find it, display the password and the hash.
    // Keep track of how many hashes were found.
    int count = 0; // keep track of the matched hashes
    char str[1000]; // maybe make shorter to save memory later
    while(fgets(str, PASS_LEN, in)) // gets the plaintext passwords from the file
    {
        // trim off the newline
        for(int i = 0; i < strlen(str) ; i++)
        {
            if(str[i] == '\n')
            {
                str[i] = '\0';
                break;
            }
        }
        
        // hash the current string
        char * targetHash = md5(str, strlen(str));

        // if match display pass and hash and add to count
        if (linearSearch(targetHash, hashes, size))
        {
            printf("MATCH - %35s - %-35s\n", str, targetHash);
            count++;
        }
    }
    
    // CHALLENGE1: Use binary search instead of linear search.

    fclose(in); // closing the file

    printf("Hashes found: %d/%d\n", count, size); // printing the hashes

    freeAA(hashes, size); // freeing memory (only malloc calls were in loadFile)
}
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int my_strcmp(const char *s1, const char *s2);

int main(void)
{   
    size_t BUFFER = 256;
    char *s1 = malloc(BUFFER);
    char *s2 = malloc(BUFFER);

    // check memory allocation
    if(!s1 || !s2){                 
        fprintf(stderr, "Memory allocation failed.\n");
        return 1;
    }

    printf("Enter s1: ");
    fgets(s1, BUFFER, stdin);

    printf("Enter s2: ");
    fgets(s2, BUFFER, stdin);

    // remove '\n' from fgets
    s1[strcspn(s1, "\n")] = '\0';  
    s2[strcspn(s2, "\n")] = '\0';  

    if(my_strcmp(s1, s2) == 0){
        printf("Same.\n");
    }
    else{
        printf("Different.\n");
    }

    // free allocated memory
    free(s1);                      
    free(s2);                     

    printf("Done.\n");
    return 0;
}

/*
    my_strcmp - Compare two strings lexicographically
    *s1: pointer to first string
    *s2: pointer to second string

    return:
        r = 0 if strings are equal
        r = < 0 if s1 < s2
        r = > 0 if s1 > s2
*/


int my_strcmp(const char *s1, const char *s2){
    while(*s1 && *s2 && *s1 == *s2){
        s1++;   
        s2++;   
    }

    return *s1 - *s2; 
}
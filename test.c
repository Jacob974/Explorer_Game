#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char* string1 = malloc(6);
    string1 = strcpy(string1, "jacob");
    printf("%s\n", string1);

    string1 = realloc(string1, 10);

    return 0;
}
#include <string.h>
#include <ctype.h> // for uppercase/lowercase functions



#ifdef TESTING_FUNCTIONS
#include <stdio.h>
#endif

// switches character at position x with position x+1, if they are both lower case letters
char * switchChars(char *input, int x) {
    char a, b;
    if(x > strlen(input)-2) {
        return input;
    }
    a = input[x];
    b = input[x+1];
    if(islower(a) > 0 || islower(b) > 0) {
        input[x] = b;
        input[x+1] = a;
    }

    return input;
}

// sticky caps the area at position x and x+1
char * stickyCaps(char *input, int x) {
    if(x > strlen(input)-2) {
        return input;
    }
    if(isupper(input[x])>0) {
        input[x+1] = toupper(input[x+1]);
    }
    return input;
}

// miss the capital at position x, but only if surrounding letters are not caps
char * missCap(char *input, int x) {
    int len = strlen(input);
    if(x < len) {
        if(x == 0 || (x > 0 && isupper(input[x-1]) == 0)) {
            if(x == len-1 || (x < len-1 && isupper(input[x+1]) == 0)) {
                input[x] = tolower(input[x]);
            }
        }

    }
    return input;
}

#ifdef TESTING_FUNCTIONS
int main() {
    char input[256];
    printf("Enter test string: \n");
    fgets(input, 256, stdin);
    missCap(input, 3);
    printf("%s\n", input);
    return 0;
}
#endif

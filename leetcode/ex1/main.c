#include <stdio.h>
#include <string.h>
#define MAX_BUFFER_SIZE 32

char buffer[MAX_BUFFER_SIZE];

int RomanToInt( char *s ) {
    const char *twoLettersChars[] = { "IV", "IX", "XL", "XC", "CD", "CM" };
    const char *oneLetterChars = "IVXLCDM";
    const int twoLettersValues[] = { 4, 9, 40, 90, 400, 900 };
    const int oneLetterValues[] = { 1, 5, 10, 50, 100, 500, 1000 };
    size_t length = strlen( s );
    int count = 0;

    for ( size_t i = 0; i < length; i++ ) {
        if ( length - i >= 2 ) {
            char flag = 0;

            for ( size_t j = 0; j < 6; j++ ) {
                if ( twoLettersChars[j][0] == s[i] && twoLettersChars[j][1] == s[i + 1] ) {
                    count += twoLettersValues[j];
                    flag = 1;
                    break;
                }
            }

            if ( flag == 1 ) {
                i++;
                continue;
            }
        }

        for ( size_t j = 0; j < 7; j++ ) {
            if ( oneLetterChars[j] == s[i] ) {
                count += oneLetterValues[j];
                break;
            }
        }
    }

    return count;
}

int main( void ) {
    scanf( "%s", buffer );
    printf( "%d\n", RomanToInt( buffer ) );

    return 0;
}

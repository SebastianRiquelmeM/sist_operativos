#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main( int argc, char **argv )
{
    srand(time(NULL));
    for(int i=0;i<100;i++){

        int randomnumber;
        randomnumber = rand() % 3;
        randomnumber++;
        printf("%d\n", randomnumber);
    }

    return 0;
}
/// Student's Name : Student A
/// Student's ID : STUDENT_A
/// Instroctur's Name : Dr. Abdel Salam Sayyad
/// Section : 1
/// Year of Birth : 2004
#include <sys/time.h>
#include <stdio.h>
#include <time.h> // I used this to count the time for each expirment :)

int matrixI[100][100];
int matrixII[100][100];
int matrixIII[100][100];
struct timeval start, end;

//----->>> T H I S  C O D E  I S  T H E  N O R M A L  W A Y <<<-----
int main()
{
    gettimeofday(&start, NULL);


    printf("Welcome to THE MATRIX MULTIPLIER!! \n");

    // fill the first array with a sequence
    int sequence[] = {1, 2, 1, 2, 3, 5, 9};

    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 100; j++)
        {
            matrixI[i][j] = sequence[(j + i * 2) % 7];
        }
    }
    printf("THIS IS matrixI\n");
    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 100; j++)
        {
            printf("%d ", matrixI[i][j]);
        }
        printf("\n");
    }


//------>> FILL THE SECOND ARRAY WITH ID * BIRTHDATE
    long long SecMatInt = 1234567890; //The idea of making the sample digit sequenceNT_A) and MY YBIRTH(2004), is to print it inside the matrix easier :)
    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 100; j++)
        {
            if(j%10==0)
                SecMatInt = 1234567890;
            matrixII[i][j] =SecMatInt %10; //1234567890 ---> 6
            SecMatInt/=10;//------->> 634765924
        }
    }
    printf("\nTHIS IS matrixII\n");
    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 100; j++)
        {
            printf("%d ", matrixII[i][j]);
        }
        printf("\n");
    }
    /// HERE IS THE MULTIPLICATION USING THE NORMAL METHOD
    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 100; j++)
        {
            matrixIII[i][j] = 0;

            for (int k = 0; k < 100; k++)
            {
                matrixIII[i][j] =matrixIII[i][j] +(matrixI[i][k] * matrixII[k][j]) ;
            }
        }
    }

    printf("THIS IS matrixIII which is the solution \n");
    for (int h = 0; h < 100; h++)
    {
        for (int o = 0; o < 100; o++)
        {
            printf("%d ", matrixIII[h][o]);
        }
        printf("\n");
    }
gettimeofday(&end, NULL);
    long long elapsed_time = (end.tv_sec - start.tv_sec) * 1000000LL +
                             (end.tv_usec - start.tv_usec);
    printf("The timer is %lld microseconds\n", elapsed_time);

    return 0;
}

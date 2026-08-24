/// Student's Name : Student A
/// Student's ID : STUDENT_A
/// Instroctur's Name : Dr. Abdel Salam Sayyad
/// Section : 1
/// Year of Birth : 2004
#include<unistd.h>
#include<stdio.h>
#include<sys/stat.h>
#include <sys/wait.h>
#include <time.h> // I used this to count the time for each expirment :)
#include <sys/time.h>
struct timeval start, end;
/// 50 CHILD
int mat1[100][100];
int mat2[100][100];

int main()
{
     gettimeofday(&start, NULL);// i started the timer from here so i will get the real time for all the prgoram till the end
    int pid; // this to give the ID for the process
    int p1[2],p2[2]; // this is given to use the pipes to communicate between the procsses
    pipe(p1); // array is set up as a unidirectional pipe and later will be used to read and write the data
    pipe(p2);
     // here i created the first matrix, while will be filled with the sample digit sequenceNT_A -
                int sequence[] = {1, 2, 1, 2, 3, 5, 9};
                for (int i = 0; i < 100; i++)
                {
                    for (int j = 0; j < 100; j++)
                    {
                        mat1[i][j] = sequence[(j + i * 2) % 7];
                    }
                }
                printf("THIS IS matrixI\n");
                for (int i = 0; i < 100; i++)
                {
                    for (int j = 0; j < 100; j++)
                    {
                        printf("%d ", mat1[i][j]);
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
                        mat2[i][j] =SecMatInt %10; //1234567890 ---> 6
                        SecMatInt/=10;//------->> 634765924
                    }
                }
                printf("\nTHIS IS matrixII\n");
                for (int i = 0; i < 100; i++)
                {
                    for (int j = 0; j < 100; j++)
                    {
                        printf("%d ", mat2[i][j]);
                    }
                    printf("\n");
                }


                int ans[100][100];
    for (int child = 0; child < 50; child++) // note here that this cotrols the number of childs will be created
    {
    if (pid == -1) {
            printf("There is s.th went wrong while creating new child"); // as we learned if its -1 then it's failed
            perror("Fork failed"); // this solves the problem in case it happened which will clean up the child if it doesn't work
        }

        if ((pid = fork()) == 0)
        {
            // Child process
            if((pid=fork())==0)
            {

// --->> here note that i used the write and read
/* for the write line,the parent process writes the data of the matrix mat1 to the write end (p1[1]) of the first pipe (p1).
 this data will be read by the corresponding child process. */
                write(p1[1],mat1,100*100*sizeof(int));
                write(p2[1],mat2,100*100*sizeof(int));
// --->> for the read,after writing the matrices to the pipes, the child process reads the result matrix from the read end (p1[0]) of the first pipe (p1).
//this result matrix is then used or processed further in the child process.
                read(p1[0],ans,100*100*sizeof(int));
            }
// --->> to release the unused space, which improve my program speed is to close the pipes
            close(p1[0]);
            close(p1[1]);
            close(p2[0]);
            close(p2[1]);
        wait(NULL);//wait for the child process to finish
            return 0;  //wxit the child process
        }

        else
        {
            // parent process
            int mul[100][100]= {0},m1[100][100],m2[100][100],i,j,k;
            // read matrices from the pipes i created before
            read(p1[0],m1,100*100*sizeof(int));
            read(p2[0],m2,100*100*sizeof(int));
            // the multiplication operation for the matreices
            for(i=0; i<100; i++)
                for(j=0; j<100; j++)
                    for(k=0; k<100; k++)
                        mul[i][j]+=m1[i][k]*m2[k][j];
            printf("THIS IS matrixIII which is the solution \n");
            for (int h=0; h<100; h++)
            {
                for (int o=0; o<100; o++)
                {
                    printf("%d ",mul[h][o]);
                }
                printf("\n");
            }
            //close the pipes i created
            close(p1[0]);
            close(p1[1]);
            close(p2[0]);
            close(p2[1]);
            write(p1[1],mul,100*100*sizeof(int));  //wite the result matrix to the pipe
        }
     gettimeofday(&end, NULL);
    long long elapsed_time = (end.tv_sec - start.tv_sec) * 1000000LL +
                             (end.tv_usec - start.tv_usec);
    printf("The timer is %lld microseconds\n", elapsed_time);
    return 0;
    }

}

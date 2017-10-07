#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<sys/wait.h>
#include<vector>
 
int main()
{
    int fd1[2];
    int fd2[2];

    int fd3[2];
    int fd4[2];

    int n;
    pid_t p; int b, c;
 
    if (pipe(fd1)==-1)
    {
        fprintf(stderr, "Pipe Failed" );
        return 1;
    }
    if (pipe(fd2)==-1)
    {
        fprintf(stderr, "Pipe Failed" );
        return 1;
    }
    if (pipe(fd3)==-1)
    {
        fprintf(stderr, "Pipe Failed" );
        return 1;
    }
    if (pipe(fd4)==-1)
    {
        fprintf(stderr, "Pipe Failed" );
        return 1;
    }
 
    scanf("%d", &n);

    p = fork();
    b = (int) p;

    if(b >0){
        p = fork();
        c = (int) p;
    }

    if (b > 0 && c>0)
    {
        //parent
        if(c>0){

            close(fd1[0]);
            close(fd3[0]);

            int t=0;
            for(int i=2; i<n; i++){

                if(i%2!=0 && i%3!=0 && i%5!=0 && i%7!=0 && i%11!=0){
                    if(t==0){
                        write(fd1[1], &i, sizeof(i));
                        t=1;
                    }
                    else{
                        write(fd3[1], &i, sizeof(i));
                        t=0;
                    }
                }

            }

            close(fd1[1]);
            close(fd3[1]);

            wait(NULL);

            int initial_primes[5]={2,3,5,7,11};
            int index=0;
            while(initial_primes[index]<=n && index<=4){
                printf("%d\n", initial_primes[index]);
                index++;
            }
     
            close(fd2[1]);
            close(fd4[1]);

            int temp1, temp2;
            std::vector<int> vec1, vec2;

            while(read(fd2[0], &temp1,sizeof(temp1))>0){
                vec1.push_back(temp1);
            }
            while(read(fd4[0], &temp2,sizeof(temp2))>0){
                vec2.push_back(temp2);
            }

            //merge

            int i = 0, j=0, k=0;
            int n1 =vec1.size();
            int n2 =vec2.size();

            while (i < n1 && j < n2)
            {
                if (vec1[i] < vec2[j])
                {
                    printf("%d\n", vec1[i] );
                    i++;
                }
                else
                {
                    printf("%d\n", vec2[j] );
                    j++;
                }
            }

            while (i < n1)
            {
                printf("%d\n", vec1[i] );
                i++;
            }

            while (j < n2)
            {
                printf("%d\n", vec2[j] );
                j++;
            }


            close(fd2[0]);
            close(fd4[0]);

            return 0; 
        }
        
    }
    
    // child process
    else if( b == 0 )
    {
        int temp1;


        close(fd3[0]);        
        close(fd3[1]);
        close(fd4[0]);        
        close(fd4[1]);

        close(fd1[1]);
        close(fd2[0]);

        while(read(fd1[0], &temp1,sizeof(temp1))>0){
            int flag = 0;
            for(int i=13; i<(temp1/2); i++){
                if(temp1%i==0){
                    flag =1;
                    break;
                }
            }
            if (!flag)
            {
                write(fd2[1], &temp1, sizeof(temp1));
            }
        }
        close(fd1[0]);
        close(fd2[1]);
        exit(0);
    }
    //second child
    else if(b>0 && c==0){
        int temp2;

        close(fd1[0]);        
        close(fd1[1]);
        close(fd2[0]);        
        close(fd2[1]);

        close(fd3[1]);
        close(fd4[0]);

        while(read(fd3[0], &temp2,sizeof(temp2))>0){
            int flag = 0;
            for(int i=13; i<(temp2/2); i++){
                if(temp2%i==0){
                    flag =1;
                    break;
                }
            }
            if (!flag)
            {
                write(fd4[1], &temp2, sizeof(temp2));
            }
        }
        close(fd3[0]);
        close(fd4[1]);
        exit(0);
    }

}

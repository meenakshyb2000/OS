#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/mman.h>
#include<fcntl.h>
#include<stddef.h>
#include<unistd.h>
#include<pthread.h>

int Buf[100];
int X=-1;
int Y=-1;
int E;
int F=0;
int N;
int fd;

pthread_cond_t Buffer_Not_Full=PTHREAD_COND_INITIALIZER;;
pthread_cond_t Buffer_Not_Empty=PTHREAD_COND_INITIALIZER;
pthread_mutex_t mVar=PTHREAD_MUTEX_INITIALIZER;
void *Producer()
{
    int ch;
    int* data=mmap(NULL,N*sizeof(int),PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    while(1)
    {
        pthread_mutex_lock(&mVar);
        printf("\nPRODUCE(1)orExit(0)? :");
        scanf("%d",&ch);
        if(ch==0)
        exit(0);
        if(F>=N)
        {
            printf("\nBuffer IS FULL, Need to consume!!");
            pthread_cond_wait(&Buffer_Not_Full,&mVar);
            pthread_mutex_unlock(&mVar);
        }
        else
        {
            F++;
            E--;
            X=(X+1)%N;
            data[X]=1;
            printf("\nCurrent Status: ");
            for(int i=0;i<N;i++)
            printf("%d  ",data[i]);
            pthread_mutex_unlock(&mVar);
            pthread_cond_signal(&Buffer_Not_Empty);
        }
    }
}

void *Consumer()
{
    int ch;
    int* data=mmap(NULL,N*sizeof(int),PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    while(1)
    {
        pthread_mutex_lock(&mVar);
        printf("\nCONSUME(1)orExit(0)? :");
        scanf("%d",&ch);
        if(ch==0)
        exit(0);
        if(E>=N)
        {
            printf("\nEmpty Buffer, Need to produce!!");
            pthread_cond_wait(&Buffer_Not_Empty,&mVar);
            pthread_mutex_unlock(&mVar);
        }
        else
        {
            E++;
            F--;
            Y=(Y+1)%N;
            data[Y]=0;
            printf("\nCurrent Status: ");
            for(int i=0;i<N;i++)
            printf("%d  ",data[i]);
            pthread_mutex_unlock(&mVar);
            pthread_cond_signal(&Buffer_Not_Full);
        }
    }
}
void main()
{
    printf("\nEnter the size of Buffer: ");
    scanf("%d",&N);
    E=N;
    fd=shm_open("\buffer",O_CREAT|O_RDWR,0666);
    ftruncate(fd,N*sizeof(int));
    int* data=mmap(NULL,N*sizeof(int),PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    for(int i=0;i<N;i++)
      data[i]=0;
    pthread_t ptid,ctid;
    pthread_create(&ptid,NULL,Producer,NULL);
    pthread_create(&ctid,NULL,Consumer,NULL);
    pthread_join(ptid,NULL);
    pthread_join(ctid,NULL);
    munmap(data,N*sizeof(int));
     shm_unlink("/buffer");
    close(fd);
}

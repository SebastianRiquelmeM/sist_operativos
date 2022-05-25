#include<semaphore.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
sem_t mutex,escritor;
pthread_t tid;
pthread_t writerthreads[100],readerthreads[100];
int readercount = 0;

void *reader(void* param)
{
    do{
        //sleep(1);
        sem_wait(&mutex); 
        readercount++;
        if(readercount==1)
            sem_wait(&escritor);
        sem_post(&mutex);
        printf("El lector %d esta dentro\n",readercount);
        //usleep(3);
        sleep(5);
        sem_wait(&mutex);
        readercount--;
        if(readercount==0)
        {
            sem_post(&escritor);
        }
        sem_post(&mutex);
        printf("EL lector %d se ha ido\n",readercount+1);
        sleep(5);
    }while(true);

}

void *writer(void* param)
{
    do{
        //sleep(1);
        printf("El escritor esta intentando entrar\n");
        sem_wait(&escritor);
        printf("El escritor ha entrado\n");
        sleep(5);
        sem_post(&escritor);
        printf("El escritor se ha ido\n");
        sleep(2);
    }while(true);
}

int main()
{
    int i;
    sem_init(&mutex,0,1);
    sem_init(&escritor,0,1);
    for(i=0;i<2;i++)
    {
        pthread_create(&writerthreads[i],NULL,reader,NULL);
        pthread_create(&readerthreads[i],NULL,writer,NULL);
    }
    for(i=0;i<2;i++)
    {
        pthread_join(writerthreads[i],NULL);
        pthread_join(readerthreads[i],NULL);
    }

}
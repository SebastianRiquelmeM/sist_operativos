#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <cstring>
#include <signal.h>
#include <stdlib.h>
#include <time.h>

int main( int argc, char **argv )
{
    int salir=0, existe1=0, existe2=0;
    srand(time(NULL));
    int fd1[2],fd2[2]; //Array en que la función pipe nos devolverá los file descriptors fd[0]: lectura ; fd[1]: escritura 
    pid_t pid1, pid2;
    int buffer1,buffer2;
    int num1, num2; //Para cuando read devuelva el numero de caracteres que se han leído

    pipe(fd1); //Devuelve 0 si no hay error
    pipe(fd2);
    pid1 = fork(); //Crea un hijo, devuelve valor de tipo pid_t que es como un int
    
    if(pid1 > 0) pid2 = fork(); //Crea fork si es el padre

    int i=0;
    while(salir == 0){
        if(pid1 == 0){
          printf("Soy el proceso hijo 1\n");
          //1 piedra
          //2 papel
          //3 tijera
          
          int opc1 =  rand() % 3;
          opc1 ++;
          write(fd1[1], &opc1, sizeof(opc1));
          
          sleep(3);
        }
        else if(pid2 == 0){
          printf("Soy el proceso hijo 2\n");
          int opc2 =  rand() % 3;
          opc2 ++;

          write(fd2[1], &opc2, sizeof(opc2));
          sleep(3);
        }
        else{
          printf("Soy el proceso padre\n");/*
          printf("Pid1: [%d]\n",pid1);
          printf("Pid2: [%d]\n",pid2);*/
          
          num1 = read(fd1[0], &buffer1, sizeof(buffer1));
        
          printf("Mensaje recibido desde hijo1: %d\n", buffer1);

          num2 = read(fd2[0], &buffer2, sizeof(buffer2));

          printf("Mensaje recibido desde hijo2: %d\n", buffer2);

          sleep(3);
          //kill(pid1, SIGKILL);
          //pid1 = fork();
        }
    }

    return 0;
}
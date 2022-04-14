#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <cstring>

int main( int argc, char **argv )
{
    int fd1[2],fd2[2]; //Array en que la función pipe nos devolverá los file descriptors fd[0]: lectura ; fd[1]: escritura 
    pid_t pid1, pid2;
    char buffer1[50], buffer2[50];
    char jugador1[50],jugador2[50];
    int num1, num2; //Para cuando read devuelva el numero de caracteres que se han leído

    pipe(fd1); //Devuelve 0 si no hay error
    pipe(fd2);
    pid1 = fork(); //Crea un hijo, devuelve valor de tipo pid_t que es como un int
    
    if(pid1 == -1)
    {
        printf("\nError\n");
    }
    if(pid1 == 0)
    {
      //printf("\nHijo 1\n");
      close(fd1[0]); //Se cierra descriptor de lectura (Hijo va a escribir)
      write(fd1[1], "tijera", 13);
      close(fd1[1]);
      //_exit(0);
    }
    else
    {
        //printf("\nPadre\n");
        close(fd1[1]); //Se cierra descriptor de escritura (Padre va a leer)
        num1 = read(fd1[0], buffer1, sizeof(buffer1)); //No es necesario un wait porque read esperará a que hayan datos en la pipe (esperará al hijo)
        //printf("\nPadre espera read...\n");

        //printf("Padre lee %d bytes: %s \n", num1, buffer1);
        close(fd1[0]);
    //--------------------------Compienza proceso 2-----------------------------------------
        pid2 = fork(); 
        if(pid2 == -1){
          printf("\nError\n");
        }
        if(pid2 == 0){
          //printf("\nHijo 2\n");
          close(fd2[0]); //Se cierra descriptor de lectura (Hijo va a escribir)
          write(fd2[1], "piedra", 15);
          close(fd2[1]);
          //_exit(0);
        }
        else{
          //printf("\nPadre\n");
          close(fd2[1]); //Se cierra descriptor de escritura (Padre va a leer)
          num1 = read(fd2[0], buffer2, sizeof(buffer2)); //No es necesario un wait porque read esperará a que hayan datos en la pipe (esperará al hijo)
          //printf("\nPadre espera read...\n");
          //printf("Padre lee %d bytes: %s \n", num1, buffer2);
          close(fd2[0]);
          printf("Padre recibe jugador1: %s \n\n", buffer1);
          printf("Padre recibe jugador2: %s \n\n", buffer2);
           //sleep(9999999999999999999999999999); 
          int eleccion=0 ;
          printf("¿Desea agregar un nuevo jugador?\n");
          printf("1- Si\n");
          printf("2- No\n\n");
          printf("Opcion: ");
          scanf("%d", &eleccion);
          //printf("Usted ha elejido: %d \n\n",eleccion);
          
        }

    }

  return 0;
}
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <cstring>

int main( int argc, char **argv )
{
  int fd[2]; //Array en que la función pipe nos devolverá los file descriptors fd[0]: lectura ; fd[1]: escritura 
  pid_t pidC;
  char buffer[10];
  int num; //Para cuando read devuelva el numero de caracteres que se han leído

  pipe(fd); //Devuelve 0 si no hay error
  pidC = fork(); //Crea un hijo, devuelve valor de tipo pid_t que es como un int

  if(pidC == -1){
     printf("\nError\n");
  }
  if(pidC == 0){
     printf("\nHijo\n");
     close(fd[0]); //Se cierra descriptor de lectura (Hijo va a escribir)
     write(fd[1], "abcde", 5);
     close(fd[1]);
     _exit(0);
  }
  else{
    printf("\nPadre\n");
    close(fd[1]); //Se cierra descriptor de escritura (Padre va a leer)
    num = read(fd[0], buffer, sizeof(buffer)); //No es necesario un wait porque read esperará a que hayan datos en la pipe (esperará al hijo)
    printf("\nPadre espera read...\n");
   
    printf("Padre lee %d bytes: %s \n", num, buffer);
    close(fd[0]);
  }


  return 0;
}